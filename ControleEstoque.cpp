#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Produto {
public:
    int id;
    std::string nome;

    Produto(int _id, const std::string& _nome)
        : id(_id), nome(_nome) {}

    bool operator==(const Produto& other) const {
        return id == other.id;
    }
};

class NotaFiscalEntrada {
public:
    int id;
    std::string numero;
    Produto produto;
    int quantidade;
    std::string fornecedor;

    NotaFiscalEntrada(int _id, const std::string& _numero, const Produto& _produto, int _quantidade, const std::string& _fornecedor)
        : id(_id), numero(_numero), produto(_produto), quantidade(_quantidade), fornecedor(_fornecedor) {}

    bool operator==(const NotaFiscalEntrada& other) const {
        return id == other.id;
    }
};

class NotaFiscalSaida {
public:
    int id;
    std::string numero;
    Produto produto;
    int quantidade;
    int idCliente;

    NotaFiscalSaida(int _id, const std::string& _numero, const Produto& _produto, int _quantidade, int _idCliente)
        : id(_id), numero(_numero), produto(_produto), quantidade(_quantidade), idCliente(_idCliente) {}

    bool operator==(const NotaFiscalSaida& other) const {
        return id == other.id;
    }
};

class Cliente {
public:
    int id;
    std::string nome;
    std::vector<NotaFiscalSaida> notasFiscaisSaida;

    Cliente(int _id, const std::string& _nome) : id(_id), nome(_nome) {}

    void adicionarNotaFiscalSaida(const NotaFiscalSaida& notaFiscalSaida) {
        notasFiscaisSaida.push_back(notaFiscalSaida);
    }
};

class Fornecedor {
public:
    int id;
    std::string nome;
    std::vector<NotaFiscalEntrada> notasFiscaisEntrada;

    Fornecedor(int _id, const std::string& _nome) : id(_id), nome(_nome) {}

    void adicionarNotaFiscalEntrada(const NotaFiscalEntrada& notaFiscalEntrada) {
        notasFiscaisEntrada.push_back(notaFiscalEntrada);
    }
};

class Almoxarifado {
public:
    int id;
    std::string nome;
    std::vector<Produto> produtos;
    std::vector<int> quantidades;
    std::vector<NotaFiscalEntrada> notasFiscaisEntrada;
    std::vector<NotaFiscalSaida> notasFiscaisSaida;

    Almoxarifado(int _id, const std::string& _nome) : id(_id), nome(_nome) {}

    Produto encontrarProdutoPorId(int id);

    void adicionarProduto(const Produto& produto, int quantidade);
    void removerProduto(const NotaFiscalSaida& notaFiscalSaida, int quantidade);
    void exibirEstadoAtual();
    void cadastrarNotaFiscalEntrada();
    void cadastrarNotaFiscalSaida();
    void cadastrarProduto();
    void cadastrarCliente();
    void cadastrarFornecedor();
};

Produto Almoxarifado::encontrarProdutoPorId(int id) {
    auto it = std::find_if(produtos.begin(), produtos.end(), [id](const Produto& p) {
        return p.id == id;
    });

    if (it != produtos.end()) {
        return *it;
    }

    // Retornar um produto inválido se não for encontrado (pode ser tratado de forma diferente se necessário)
    return Produto(-1, "Produto Não Encontrado");
}

void Almoxarifado::adicionarProduto(const Produto& produto, int quantidade) {
    // Verifica se o produto está associado ao almoxarifado
    auto it = std::find(produtos.begin(), produtos.end(), produto);
    if (it != produtos.end()) {
        // Encontra a posição do produto no vetor
        size_t index = std::distance(produtos.begin(), it);

        // Atualiza a quantidade corretamente
        quantidades[index] += quantidade;

        std::cout << "Produto adicionado ao almoxarifado. Quantidade final: " << quantidades[index] << std::endl;
    } else {
        std::cout << "Produto não encontrado no almoxarifado." << std::endl;
    }
}


void Almoxarifado::removerProduto(const NotaFiscalSaida& notaFiscalSaida, int quantidade) {
    // Verifica se a nota fiscal de saída está associada ao almoxarifado
    auto it = std::find(notasFiscaisSaida.begin(), notasFiscaisSaida.end(), notaFiscalSaida);
    if (it != notasFiscaisSaida.end()) {
        for (size_t i = 0; i < produtos.size(); ++i) {
            if (produtos[i].id == notaFiscalSaida.produto.id) {
                if (quantidades[i] >= quantidade) {
                    quantidades[i] -= quantidade;
                    std::cout << "Produto removido do almoxarifado. Quantidade final: " << quantidades[i] << std::endl;
                } else {
                    std::cout << "Quantidade insuficiente do produto no almoxarifado." << std::endl;
                }
                return;
            }
        }
        std::cout << "Produto não encontrado no almoxarifado." << std::endl;
    } else {
        std::cout << "Nota fiscal de saída não encontrada no almoxarifado." << std::endl;
    }
}


void Almoxarifado::exibirEstadoAtual() {
    std::cout << "\n--- Estado Atual do Almoxarifado ---\n";
    for (size_t i = 0; i < produtos.size(); ++i) {
        std::cout << "ID: " << produtos[i].id << ", Nome: " << produtos[i].nome
                  << ", Quantidade: " << quantidades[i] << "\n";
    }
}


void Almoxarifado::cadastrarNotaFiscalEntrada() {
    std::cout << "Cadastrando Nota Fiscal de Entrada:\n";
    int idProduto;
    std::string numero;
    std::string fornecedor;
    int quantidade;

    std::cout << "ID do Produto (já cadastrado): ";
    std::cin >> idProduto;

    // Encontrar o produto pelo ID
    Produto produto = encontrarProdutoPorId(idProduto);

    if (produto.id == -1) {
        std::cout << "Produto não encontrado. Cadastre o produto antes de associá-lo a uma nota fiscal de entrada.\n";
        return;
    }

    std::cout << "Número da Nota Fiscal: ";
    std::cin >> numero;
    std::cout << "Nome do Fornecedor: ";
    std::cin >> fornecedor;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    NotaFiscalEntrada nfEntrada(notasFiscaisEntrada.size() + 1, numero, produto, quantidade, fornecedor);
    notasFiscaisEntrada.push_back(nfEntrada);

    //adicionarProduto(produto, quantidade);
}

void Almoxarifado::cadastrarNotaFiscalSaida() {
    std::cout << "Cadastrando Nota Fiscal de Saída:\n";
    int idProduto;
    std::string numero;
    int idCliente;
    int quantidade;

    std::cout << "ID do Produto (já cadastrado): ";
    std::cin >> idProduto;

    // Encontrar o produto pelo ID
    Produto produto = encontrarProdutoPorId(idProduto);

    if (produto.id == -1) {
        std::cout << "Produto não encontrado. Cadastre o produto antes de associá-lo a uma nota fiscal de saída.\n";
        return;
    }

    std::cout << "Número da Nota Fiscal: ";
    std::cin >> numero;
    std::cout << "ID do Cliente: ";
    std::cin >> idCliente;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    NotaFiscalSaida nfSaida(notasFiscaisSaida.size() + 1, numero, produto, quantidade, idCliente);
    notasFiscaisSaida.push_back(nfSaida);

    // Atualiza o estoque no almoxarifado
    //removerProduto(nfSaida, quantidade);
}

void Almoxarifado::cadastrarProduto() {
    std::cout << "Cadastrando Produto:\n";
    int idProduto;
    std::string nomeProduto;

    std::cout << "ID do Produto: ";
    std::cin >> idProduto;
    std::cout << "Nome do Produto: ";
    std::cin >> nomeProduto;

    Produto produto(idProduto, nomeProduto);
    produtos.push_back(produto);
    quantidades.push_back(0);  // Inicializa a quantidade como zero
    std::cout << "Produto cadastrado com sucesso." << std::endl;
}

void Almoxarifado::cadastrarCliente() {
    std::cout << "Cadastrando Cliente:\n";
    int idCliente;
    std::string nomeCliente;

    std::cout << "ID do Cliente: ";
    std::cin >> idCliente;
    std::cout << "Nome do Cliente: ";
    std::cin >> nomeCliente;

    Cliente cliente(idCliente, nomeCliente);

    std::cout << "Cliente cadastrado com sucesso." << std::endl;
}

void Almoxarifado::cadastrarFornecedor() {
    std::cout << "Cadastrando Fornecedor:\n";
    int idFornecedor;
    std::string nomeFornecedor;

    std::cout << "ID do Fornecedor: ";
    std::cin >> idFornecedor;
    std::cout << "Nome do Fornecedor: ";
    std::cin >> nomeFornecedor;

    Fornecedor fornecedor(idFornecedor, nomeFornecedor);

    std::cout << "Fornecedor cadastrado com sucesso." << std::endl;
}


int main() {
    Almoxarifado almoxarifado(1, "Almoxarifado XYZ");

    // Menu principal
    int opcao;

    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Cadastrar Produto\n";
        std::cout << "2. Cadastrar Cliente\n";
        std::cout << "3. Cadastrar Fornecedor\n";
        std::cout << "4. Cadastrar Nota Fiscal de Entrada\n";
        std::cout << "5. Cadastrar Nota Fiscal de Saída\n";
        std::cout << "6. Entrada de Produto\n";
        std::cout << "7. Saída de Produto\n";
        std::cout << "8. Exibir Status Atual do Almoxarifado\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                almoxarifado.cadastrarProduto();
                break;

            case 2:
                almoxarifado.cadastrarCliente();
                break;

            case 3:
                almoxarifado.cadastrarFornecedor();
                break;

            case 4:
                almoxarifado.cadastrarNotaFiscalEntrada();
                break;

            case 5:
                almoxarifado.cadastrarNotaFiscalSaida();
                break;

            case 6:
                // Entrada de Produto
                {
                    // Listar as Notas Fiscais de Entrada cadastradas
                    std::cout << "\nNotas Fiscais de Entrada Cadastradas:\n";
                    for (const auto &nfEntrada : almoxarifado.notasFiscaisEntrada) {
                        std::cout << "ID: " << nfEntrada.id << ", Número: " << nfEntrada.numero << "\n";
                    }
            
                    // Solicitar ao usuário escolher uma Nota Fiscal de Entrada
                    int escolhaNotaEntrada;
                    std::cout << "Escolha o ID da Nota Fiscal de Entrada: ";
                    std::cin >> escolhaNotaEntrada;
            
                    // Encontrar a Nota Fiscal de Entrada escolhida
                    auto notaEntradaEscolhida = std::find_if(
                        almoxarifado.notasFiscaisEntrada.begin(),
                        almoxarifado.notasFiscaisEntrada.end(),
                        [escolhaNotaEntrada](const NotaFiscalEntrada &nfEntrada) {
                            return nfEntrada.id == escolhaNotaEntrada;
                        });
            
                    if (notaEntradaEscolhida != almoxarifado.notasFiscaisEntrada.end()) {
                        // Adicionar o produto ao almoxarifado usando a quantidade da nota fiscal
                        almoxarifado.adicionarProduto(notaEntradaEscolhida->produto, notaEntradaEscolhida->quantidade);
                    } else {
                        std::cout << "Nota Fiscal de Entrada não encontrada.\n";
                    }
                    break;
                }



            case 7:
                // Saída de Produto
                {
                    // Listar as Notas Fiscais de Saída cadastradas
                    std::cout << "\nNotas Fiscais de Saída Cadastradas:\n";
                    for (const auto &nfSaida : almoxarifado.notasFiscaisSaida) {
                        std::cout << "ID: " << nfSaida.id << ", Número: " << nfSaida.numero << "\n";
                    }
            
                    // Solicitar ao usuário escolher uma Nota Fiscal de Saída
                    int escolhaNotaSaida;
                    std::cout << "Escolha o ID da Nota Fiscal de Saída: ";
                    std::cin >> escolhaNotaSaida;
            
                    // Encontrar a Nota Fiscal de Saída escolhida
                    auto notaSaidaEscolhida = std::find_if(
                        almoxarifado.notasFiscaisSaida.begin(),
                        almoxarifado.notasFiscaisSaida.end(),
                        [escolhaNotaSaida](const NotaFiscalSaida &nfSaida) {
                            return nfSaida.id == escolhaNotaSaida;
                        });
            
                    if (notaSaidaEscolhida != almoxarifado.notasFiscaisSaida.end()) {
                        // Remover o produto associado à Nota Fiscal de Saída do almoxarifado usando a quantidade da nota fiscal
                        almoxarifado.removerProduto(*notaSaidaEscolhida, notaSaidaEscolhida->quantidade);
                    } else {
                        std::cout << "Nota Fiscal de Saída não encontrada.\n";
                    }
                    break;
                }


            case 8:
                almoxarifado.exibirEstadoAtual();
                break;

            case 0:
                std::cout << "Saindo do programa.\n";
                break;

            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}
