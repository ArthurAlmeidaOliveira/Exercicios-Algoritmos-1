#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

const int TOTAL_PRODUTOS = 5;
const int MAX_EXTRATO = 20;   // quantidade de operações guardadas no extrato

// Guarda os dados de uma operação realizada
struct Operacao {
    string dataHora;
    string tipo;         // "Entrada" ou "Venda"
    int codigo;
    int quantidade;
    int estoqueFinal;    // estoque do produto depois da operação
    string situacao;     // "OK" ou "Recusada"
};

// Histórico circular: guarda só as últimas 20 operações
Operacao extrato[MAX_EXTRATO];
int totalOperacoes = 0;   // quantas operações já foram feitas desde o início

// Devolve a data e hora atuais no formato dd/mm/aaaa hh:mm:ss
string dataHoraAtual() {
    time_t agora = time(0);
    char texto[20];
    strftime(texto, sizeof(texto), "%d/%m/%Y %H:%M:%S", localtime(&agora));
    return texto;
}

// Grava uma operação no extrato; quando passa de 20, sobrescreve a mais antiga
void registrarOperacao(string tipo, int codigo, int quantidade, int estoqueFinal, string situacao) {
    int posicao = totalOperacoes % MAX_EXTRATO;
    extrato[posicao].dataHora = dataHoraAtual();
    extrato[posicao].tipo = tipo;
    extrato[posicao].codigo = codigo;
    extrato[posicao].quantidade = quantidade;
    extrato[posicao].estoqueFinal = estoqueFinal;
    extrato[posicao].situacao = situacao;
    totalOperacoes++;
}

// Lê um número inteiro; se o usuário digitar letras, limpa a entrada e devolve -1
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

// Pede a quantidade até o usuário digitar um valor maior que zero
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

// Exibe o menu de opções
void exibirMenu() {
    cout << "\n========= MENU =========" << endl;
    cout << "1 - Adicionar produtos" << endl;
    cout << "2 - Vender produtos" << endl;
    cout << "3 - Últimas operações" << endl;
    cout << "0 - Encerrar programa" << endl;
    cout << "========================" << endl;
    cout << "Escolha uma opção: ";
}

// Opção 1: soma uma quantidade ao estoque de um produto
void adicionarProdutos(int estoque[]) {
    cout << "\n--- Adicionar produtos ---" << endl;
    int codigo = lerCodigo();
    int quantidade = lerQuantidade();

    estoque[codigo - 1] += quantidade;
    registrarOperacao("Entrada", codigo, quantidade, estoque[codigo - 1], "OK");
    cout << "Estoque atualizado! Produto " << codigo << " agora tem "
         << estoque[codigo - 1] << " itens." << endl;
}

// Opção 2: valida e realiza a venda de um produto
void venderProdutos(int estoque[]) {
    cout << "\n--- Vender produtos ---\n" << endl;
    int codigo = lerCodigo();
    int i = codigo - 1;  // converte código (1-5) para índice (0-4)
    cout << "Unidades do produto " << codigo << ": " << estoque[i] << "\n";
    int quantidade = lerQuantidade();

    if (quantidade <= estoque[i]) {
        estoque[i] -= quantidade;
        registrarOperacao("Venda", codigo, quantidade, estoque[i], "OK");
        cout << "Venda realizada com sucesso! Foram vendidas "<< quantidade << " unidades o produto " << codigo << endl;
    } else {
        registrarOperacao("Venda", codigo, quantidade, estoque[i], "Recusada");
        cout << "Erro: Estoque insuficiente! Estoque atual do produto " << codigo <<": " << estoque[i] << " itens." << endl;
    }
}

// Mostra uma mensagem e espera o usuário apertar Enter para voltar ao menu
void pausarParaMenu() {
    cout << "\nPressione ENTER para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // descarta o Enter que sobrou da opção digitada
    cin.get();                                             // espera o novo Enter
    system("cls");
}

// Opção 3: mostra as últimas 20 operações, da mais antiga para a mais recente
void exibirExtrato() {
    system("cls");
    cout << "\n================== EXTRATO - ÚLTIMAS " << MAX_EXTRATO << " OPERAÇÕES ==================" << endl;

    if (totalOperacoes == 0) {
        cout << setw(14) << "" << "Nenhuma operação realizada até o momento.\n";
        cout << "====================================================================\n";
        pausarParaMenu();
        return;
    }

    // se já houve mais de 20 operações, mostra só as 20 últimas
    int quantidadeExibir = (totalOperacoes < MAX_EXTRATO) ? totalOperacoes : MAX_EXTRATO;
    int primeira = totalOperacoes - quantidadeExibir;   // número da operação mais antiga a mostrar

    cout << left
         << setw(5)  << "Nº"
         << setw(21) << "Data/Hora"
         << setw(9)  << "Tipo"
         << setw(9)  << "Produto"
         << setw(7)  << "Qtd"
         << setw(9)  << "Estoque"
         << "Situação" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    for (int n = primeira; n < totalOperacoes; n++) {
        Operacao op = extrato[n % MAX_EXTRATO];
        cout << left
             << setw(5)  << (n + 1)
             << setw(21) << op.dataHora
             << setw(9)  << op.tipo
             << setw(9)  << op.codigo
             << setw(7)  << op.quantidade
             << setw(9)  << op.estoqueFinal
             << op.situacao << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << right;   // volta o alinhamento padrão para a tabela de estoque

    pausarParaMenu();
}

// Opção 0: pergunta se o usuário realmente quer sair (s/n)
bool confirmarSaida() {
	system("cls");
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
            case 3:
                exibirExtrato();
                break;
            case 0:
                if (confirmarSaida()) {
                    executando = false;
                    cout << "Programa encerrado." << endl;
                }
                break;
            default:
            	system("cls");
                cout << "Erro: Opcao invalida! Digite um opção de 1 a 3, ou 0 para encerrar." << endl;
        }
    }

    return 0;
}
