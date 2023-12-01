#include <iostream>
#include <vector>
#include <string>

class NotaFiscalEntrada;  // Adiciona protótipo
class NotaFiscalSaida;  // Adiciona protótipo

class Produto {
public:
    int id;
    std::string nome;
    std::string linha;
    int quantidade;

    Produto(int _id, const std::string& _nome, const std::string& _linha, int _quantidade)
        : id(_id), nome(_nome), linha(_linha), quantidade(_quantidade) {}
};

class Almoxarifado {
public:
    int id;
    std::string nome;
    std::vector<Produto> produtos;

    Almoxarifado(int _id, const std::string& _nome) : id(_id), nome(_nome) {}

    void adicionarProduto(const NotaFiscalEntrada& notaFiscalEntrada);  // Adiciona protótipo
    void removerProduto(const NotaFiscalSaida& notaFiscalSaida);  // Adiciona protótipo
};

class NotaFiscalEntrada {
public:
    int id;
    std::string numero;
    int idProduto;
    std::string fornecedor;

    NotaFiscalEntrada(int _id, const std::string& _numero, int _idProduto, const std::string& _fornecedor)
        : id(_id), numero(_numero), idProduto(_idProduto), fornecedor(_fornecedor) {}
};

class NotaFiscalSaida {
public:
    int id;
    std::string numero;
    int idProduto;
    int idCliente;

    NotaFiscalSaida(int _id, const std::string& _numero, int _idProduto, int _idCliente)
        : id(_id), numero(_numero), idProduto(_idProduto), idCliente(_idCliente) {}
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
    produtos.push_back(Produto(notaFiscalEntrada.idProduto, "", "", 0));
    std::cout << "Produto adicionado ao almoxarifado." << std::endl;
}

void Almoxarifado::removerProduto(const NotaFiscalSaida& notaFiscalSaida) {
    for (auto it = produtos.begin(); it != produtos.end(); ++it) {
        if (it->id == notaFiscalSaida.idProduto) {
            std::cout << "Produto removido do almoxarifado." << std::endl;
            produtos.erase(it);
            return;
        }
    }
    std::cout << "Produto não encontrado no almoxarifado." << std::endl;
}

int main() {
    Almoxarifado almoxarifado1(1, "Almoxarifado 1");

    Produto produto1(1, "Produto A", "Linha 1", 100);
    Produto produto2(2, "Produto B", "Linha 2", 50);

    Fornecedor fornecedorXYZ(1, "Fornecedor XYZ");
    NotaFiscalEntrada notaFiscalEntrada(1, "12345", produto1.id, fornecedorXYZ.nome);
    fornecedorXYZ.adicionarNotaFiscalEntrada(notaFiscalEntrada);

    Cliente clienteA(1, "Cliente A");
    NotaFiscalSaida notaFiscalSaida(2, "67890", produto2.id, clienteA.id);
    clienteA.adicionarNotaFiscalSaida(notaFiscalSaida);

    almoxarifado1.adicionarProduto(notaFiscalEntrada);
    almoxarifado1.removerProduto(notaFiscalSaida);

    return 0;
}
