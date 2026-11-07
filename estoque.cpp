#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <windows.h>
using namespace std;

const int TOTAL_PRODUTOS = 5;

// Le um número inteiro; se o usuário digitar letras, limpa a entrada e devolve -1
int lerInteiro() {
    int valor;
    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return valor;
}

// Pede o código do produto ao usuário (digitar um valor de 1 a 5)
int lerCodigo() {
	system("cls");
    int codigo;
    do {
        cout << "Digite o código do produto (1 a " << TOTAL_PRODUTOS << "): ";
        codigo = lerInteiro();
        if (codigo < 1 || codigo > TOTAL_PRODUTOS) {
        	system("cls");
            cout << "Erro: Código de produto invalido!" << endl;
        }
    } while (codigo < 1 || codigo > TOTAL_PRODUTOS);
    return codigo;
}

// Pede a quantidade ao usuário, digitar um valor maior que zero
int lerQuantidade() {
    int quantidade;
    do {
        cout << "Digite a quantidade: ";
        quantidade = lerInteiro();
        if (quantidade <= 0) {
        	system("cls");
            cout << "Erro: Quantidade invalida!" << endl;
        }
    } while (quantidade <= 0);
    system("cls");
    return quantidade;
}

// Exibe a tabela de produtos e quantidades em estoque
void exibirTabela(const int estoque[]) {
    cout << "\n+---------+------------+" << endl;
    cout << "| Produto | Quantidade |" << endl;
    cout << "+---------+------------+" << endl;
    for (int i = 0; i < TOTAL_PRODUTOS; i++) {
        cout << "| " << setw(7) << (i + 1)
             << " | " << setw(10) << estoque[i] << " |" << endl;
    }
    cout << "+---------+------------+" << endl;
}

// Exibe o menu de opÃ§Ãµes
void exibirMenu() {
    cout << "\n========= MENU =========" << endl;
    cout << "1 - Adicionar produtos" << endl;
    cout << "2 - Vender produtos" << endl;
    cout << "0 - Encerrar programa" << endl;
    cout << "========================" << endl;
    cout << "Escolha uma opcção: ";
}

// Opção 1: soma uma quantidade ao estoque de um produto
void adicionarProdutos(int estoque[]) {
    cout << "\n--- Adicionar produtos ---" << endl;
    int codigo = lerCodigo();
    int quantidade = lerQuantidade();

    estoque[codigo - 1] += quantidade;
    cout << "Estoque atualizado! Produto " << codigo << " agora tem "
         << estoque[codigo - 1] << " itens." << endl;
}

// Opção 2: valida e realiza a venda de um produto
void venderProdutos(int estoque[]) {
    cout << "\n--- Vender produtos ---" << endl;
    int codigo = lerCodigo();
    int quantidade = lerQuantidade();
    int i = codigo - 1;  // converte código (1-5) para índice (0-4)

    if (quantidade <= estoque[i]) {
        estoque[i] -= quantidade;
        cout << "Venda realizada com sucesso! Foram vendidas "<< quantidade << " unidades o produto " << codigo << endl;
    } else {
        cout << "Erro: Estoque insuficiente! Estoque atual: " << estoque[i] << " itens." << endl;
    }
}

// Opção 0: pergunta se o usuário realmente quer sair (s/n)
bool confirmarSaida() {
    char resposta;
    do {
        cout << "Deseja realmente sair? (s/n): ";
        cin >> resposta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        resposta = tolower(resposta);
        if (resposta != 's' && resposta != 'n') {
            cout << "Erro: Digite apenas s ou n." << endl;
        }
    } while (resposta != 's' && resposta != 'n');
    return resposta == 's';
}

int main() {
	SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    
    // Inicialização: estoque dos 5 produtos
    int estoque[TOTAL_PRODUTOS] = {10, 5, 25, 0, 12};
    bool executando = true;

    while (executando) {
    	exibirTabela(estoque);
        exibirMenu();
        int opcao = lerInteiro();

        switch (opcao) {
            case 1:
                adicionarProdutos(estoque);
                break;
            case 2:
                venderProdutos(estoque);
                break;
            case 0:
                if (confirmarSaida()) {
                    executando = false;
                    cout << "Programa encerrado." << endl;
                }
                break;
            default:
            	system("cls");
                cout << "Erro: Opção inválida! Digite um opção de 1 a 2, ou 0 para encerrar." << endl;
        }
    }

    return 0;
}
