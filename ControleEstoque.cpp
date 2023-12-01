#include <iostream>
#include <vector>
#include <string>

class NotaFiscalEntrada;
class NotaFiscalSaida;

class Produto {
public:
    int id;
    std::string nome;

    Produto(int _id, const std::string& _nome)
        : id(_id), nome(_nome) {}
};

class Almoxarifado {
public:
    int id;
    std::string nome;
    std::vector<Produto> produtos;
    std::vector<int> quantidades; 

    Almoxarifado(int _id, const std::string& _nome) : id(_id), nome(_nome) {}

    void adicionarProduto(const NotaFiscalEntrada& notaFiscalEntrada);
    void removerProduto(const NotaFiscalSaida& notaFiscalSaida);
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

void Almoxarifado::adicionarProduto(const NotaFiscalEntrada& notaFiscalEntrada) {
    produtos.push_back(notaFiscalEntrada.produto);
    quantidades.push_back(notaFiscalEntrada.quantidade);  
    std::cout << "Produto adicionado ao almoxarifado. Quantidade final: " << notaFiscalEntrada.quantidade << std::endl;
}

void Almoxarifado::removerProduto(const NotaFiscalSaida& notaFiscalSaida) {
    for (size_t i = 0; i < produtos.size(); ++i) {
        if (produtos[i].id == notaFiscalSaida.produto.id) {
            if (quantidades[i] >= notaFiscalSaida.quantidade) {
                quantidades[i] -= notaFiscalSaida.quantidade;
                std::cout << "Produto removido do almoxarifado. Quantidade final: " << quantidades[i] << std::endl;
            } else {
                std::cout << "Quantidade insuficiente do produto no almoxarifado." << std::endl;
            }
            return;
        }
    }
    std::cout << "Produto não encontrado no almoxarifado." << std::endl;
}

void exibirProdutos(const Almoxarifado& almoxarifado) {
    std::cout << "\nProdutos Cadastrados (" << almoxarifado.produtos.size() << "): \n";
    for (size_t i = 0; i < almoxarifado.produtos.size(); ++i) {
        std::cout << "ID: " << almoxarifado.produtos[i].id << ", Nome: " << almoxarifado.produtos[i].nome
                  << ", Quantidade: " << almoxarifado.quantidades[i] << "\n";
    }
}



void exibirEstadoAlmoxarifado(const Almoxarifado& almoxarifado) {
    std::cout << "\n--- Estado Atual do Almoxarifado ---\n";
    exibirProdutos(almoxarifado);
}

int main() {
    
    std::cout << "\nCriando Almoxarifado..\n";
    Almoxarifado almoxarifado1(1, "Almoxarifado 1");
    std::vector<Fornecedor> fornecedores;
    std::vector<Cliente> clientes;

    std::cout << "\Criando Produto..\n";
    Produto produto(1, "Produto A");

    std::cout << "\Criando Fornecedor..\n";
    Fornecedor fornecedorXYZ(1, "Fornecedor XYZ");
    
    std::cout << "\Gerando NF Entrada..\n";
    NotaFiscalEntrada notaFiscalEntrada(1, "12345", produto, 100, fornecedorXYZ.nome);
    fornecedorXYZ.adicionarNotaFiscalEntrada(notaFiscalEntrada);
    
    std::cout << "\Criando Cliente..\n";
    Cliente clienteA(1, "Cliente A");
    
    std::cout << "\Gerando NF Saida..\n";
    NotaFiscalSaida notaFiscalSaida(2, "67890", produto, 20, clienteA.id);
    clienteA.adicionarNotaFiscalSaida(notaFiscalSaida);

    fornecedores.push_back(fornecedorXYZ);
    clientes.push_back(clienteA);

    // Menu principal
    int opcao;

    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Exibir Estado Atual do Almoxarifado\n";
        std::cout << "2. Adicionar Produto\n";
        std::cout << "3. Remover Produto\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                exibirEstadoAlmoxarifado(almoxarifado1);
                break;
        
            case 2:
                almoxarifado1.adicionarProduto(notaFiscalEntrada);
                break;

            case 3:
                almoxarifado1.removerProduto(notaFiscalSaida);
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
