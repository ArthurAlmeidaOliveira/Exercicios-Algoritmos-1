#include <iostream>
#include <vector>
#include <limits>
#include <locale.h>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <sstream>
using namespace std;

double mediaAprovacao = 6.0; // média mínima para ser aprovado (pode ser alterada no menu)

// Lê um nome: aceita letras, acentos e nomes compostos; recusa números e vazio
string lerNome(string mensagem) {
    string nome;
    while (true) { //loop infinito
        cout << mensagem;
        getline(cin, nome);

        // remove espaÃ§os do começo e do final
        size_t inicio = nome.find_first_not_of(' ');
        size_t fim = nome.find_last_not_of(' ');

        if (inicio == string::npos) {
            nome.clear();                                 // sÃ³ tinha espaÃ§os
        } else {
            nome = nome.substr(inicio, fim - inicio + 1); // pega sÃ³ a parte Ãºtil
        }

        // troca espaços repetidos no meio por um só
        string limpo;
        for (int i = 0; i < nome.length(); i++) {
            if (nome[i] == ' ' && i > 0 && nome[i - 1] == ' ') {
                continue;                                 // pula o espaÃ§o repetido
            }
            limpo += nome[i];
        }
        nome = limpo;

        if (nome.empty()) {
            system("cls");
            cout << "Nome inválido! NÃ£o pode ser vazio.\n";
            continue;
        }

        // verifica se existe algum número no nome
        bool temNumero = false;
        for (int i = 0; i < nome.length(); i++) {
            if (nome[i] >= '0' && nome[i] <= '9') {
                temNumero = true;
                break;
            }
        }

        if (temNumero) {
            system("cls");
            cout << "Nome inválido! Não digite números.\n";
            continue;
        }

        system("cls");
        return nome;
    }
}

// Lê uma nota, impedindo letras
double lerNota(string mensagem) {
    double nota;
    while (true) { //loop infinito
        cout << mensagem;
        cin >> nota;

        if (cin.fail() || nota < 0 || nota > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Entrada inválida! Digite uma nota entre 0 e 10.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            return nota;
        }
    }
}

// LÃª a opção do menu valida o intervalo
int lerOpcao(string mensagem, int min, int max) {
    string entrada;
    while (true) {
        cout << mensagem;
        getline(cin, entrada);

        //Retira os espacos no final da string
        size_t pos = entrada.find_last_not_of(' ');
        if (pos != string::npos) {
            entrada.erase(pos + 1);
        } else {
            entrada.clear();
        }

        //Verifica se for vazio
        if (entrada.empty()) {
            cout << "Opção inválida! Não pode ser vazio.\n\n";
            continue;
        }

        // Verifica se tem exatamente 1 caractere
        if (entrada.length() != 1) {
            cout << "Opção inválida! Digite apenas um número entre " << min << " e " << max << ".\n\n";
            continue;
        }

        int opcao = entrada[0] - '0'; // converte o caractere para o nÃºmero inteiro correspondente

        //verifica se está¡ dentro do intervalo
        if (opcao < min || opcao > max) {
            cout << "Opção inválida! Escolha um número entre " << min << " e " << max << ".\n\n";
            continue;
        }

        return opcao;
    }
}

// Pergunta se o usuário realmente quer sair
bool confirmarSaida() {
    system("cls");
    string letra;
    while (true) {
        cout << "\nTem certeza que deseja sair? S para sim / N para não (S/N): ";
        getline(cin, letra);

        if (letra.length() != 1) {
            system("cls");
            cout << "Resposta inválida! Digite apenas uma letra: 's' ou 'n'.\n";
            continue;
        }

        if (letra == "s" || letra == "S") {
            system("cls");
            return true;
        } else if (letra == "n" || letra == "N") {
            system("cls");
            return false;
        } else {
            system("cls");
            cout << "Resposta inválida! Digite 's' para sim ou 'n' para não.\n";
        }
    }
}

void pausarParaMenu() {
    cout << "\nPressione ENTER para voltar ao menu...";
    string lixo;
    getline(cin, lixo);   // espera um único Enter
    system("cls");
}

int lerNumero(string mensagem, int min, int max) {
    string entrada;
    while (true) {
        cout << mensagem;
        getline(cin, entrada);

        // remove espaços do começo e do final
        size_t inicio = entrada.find_first_not_of(' ');
        size_t fim = entrada.find_last_not_of(' ');
        if (inicio == string::npos) {
            cout << "Entrada inválida! Não pode ser vazio.\n\n";
            continue;
        }
        entrada = entrada.substr(inicio, fim - inicio + 1);

        // verifica se só tem dígitos
        bool soDigitos = true;
        for (int i = 0; i < entrada.length(); i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                soDigitos = false;
                break;
            }
        }
        if (!soDigitos || entrada.length() > 5) {
            cout << "Entrada inválida! Digite um número entre " << min << " e " << max << ".\n\n";
            continue;
        }

        // converte o texto em número (ex: "12" -> 1*10 + 2)
        int numero = 0;
        for (int i = 0; i < entrada.length(); i++) {
            numero = numero * 10 + (entrada[i] - '0');
        }

        if (numero < min || numero > max) {
            cout << "Número inválido! Escolha entre " << min << " e " << max << ".\n\n";
            continue;
        }

        return numero;
    }
}

// Transforma uma nota em texto com 1 casa decimal (ex: 7.5 -> "7.5")
string formatarNota(double nota) {
    ostringstream texto;
    texto << fixed << setprecision(1) << nota;
    return texto.str();
}

// Mostra a tabela de alunos com um número na frente de cada um
void mostrarTabelaAlunos(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias) {
    cout << fixed << setprecision(1);

    cout << "\nALUNOS CADASTRADOS\n";
    cout << left << setw(5) << "Nº" << setw(25) << "Nome"
         << setw(8) << "AV 01" << setw(8) << "AV 02" << "Média\n";
    cout << setfill('-') << setw(52) << "" << setfill(' ') << '\n';

    for (int i = 0; i < nomes.size(); i++) {
        cout << left << setw(5) << (i + 1)
             << setw(25) << nomes[i]
             << setw(8) << notas1[i]
             << setw(8) << notas2[i]
             << medias[i] << '\n';
    }

    cout.unsetf(ios::fixed);
}

// Exibe o menu de edição
void menuEditar() {
    cout << "\n---------------------\n";
    cout << "MENU EDITAR\n";
    cout << "# Digite um número de 0-2 #\n";
    cout << "1. Editar nome\n";
    cout << "2. Editar notas\n";
    cout << "0. Voltar\n";
    cout << "---------------------\n";
    cout << '\n';
}

// Escolhe um aluno pelo número e permite editar nome ou notas
void editarAluno(vector<string>& nomes, vector<double>& notas1, vector<double>& notas2, vector<double>& medias) {
    system("cls");
    if (nomes.empty()) {
        cout << "Nenhum aluno cadastrado ainda.\n";
        pausarParaMenu();
        return;
    }

    mostrarTabelaAlunos(nomes, notas1, notas2, medias);
    int numero = lerNumero("\nDigite o número do aluno (0 para voltar): ", 0, nomes.size());

    if (numero == 0) {
        system("cls");
        return;
    }

    int i = numero - 1; // o vetor começa em 0, a tabela começa em 1
    int opcao;
    system("cls");

    do {
        // mostra os dados atuais do aluno escolhido
        cout << "\nEDITANDO ALUNO Nº " << numero << '\n';
        cout << "Nome: " << nomes[i]
             << " | AV 01: " << formatarNota(notas1[i])
             << " | AV 02: " << formatarNota(notas2[i])
             << " | Média: " << formatarNota(medias[i]) << '\n';

        menuEditar();
        opcao = lerOpcao("Escolha uma opção: ", 0, 2);

        switch (opcao) {
            case 1:
                system("cls");
                nomes[i] = lerNome("Nome atual: " + nomes[i] + "\nDigite o novo nome: ");
                cout << "Nome alterado com sucesso!\n";
                break;
            case 2:
                system("cls");
                notas1[i] = lerNota("Nota atual da 1ª prova: " + formatarNota(notas1[i]) + "\nDigite a nova nota: ");
                notas2[i] = lerNota("Nota atual da 2ª prova: " + formatarNota(notas2[i]) + "\nDigite a nova nota: ");
                medias[i] = (notas1[i] + notas2[i]) / 2; // recalcula a média
                cout << "Notas alteradas com sucesso!\n";
                break;
            case 0:
                system("cls");
                break;
        }
    } while (opcao != 0);
}

// Cadastra um único aluno (nome + duas notas + média) nos vetores
void cadastrarAluno(vector<string>& nomes, vector<double>& notas1, vector<double>& notas2, vector<double>& medias) {
    system("cls");
    string nome = lerNome("Digite o nome do aluno: ");
    double nota1 = lerNota("Digite a primeira nota do aluno: ");
    double nota2 = lerNota("Digite a segunda nota do aluno: ");
    double media = (nota1 + nota2) / 2;

    nomes.push_back(nome);
    notas1.push_back(nota1);
    notas2.push_back(nota2);
    medias.push_back(media);

    system("cls");
    cout << "Aluno cadastrado com sucesso!\n";
}

// Exibe o relatório com todos os alunos cadastrados
void exibirRelatorio(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias) {
    system("cls");
    if (nomes.empty()) {
        cout << "Nenhum aluno cadastrado ainda.\n";
        return;
    }

    cout << "\nRELATÓRIO DE ALUNOS\n";
    for (int i = 0; i < nomes.size(); i++) {
        cout << "Nome:" << nomes[i] << " AV 01:" << notas1[i] << " AV 02:" << notas2[i] << " Média:" << medias[i] << '\n';
    }
}

// ---------------------- PESQUISA ----------------------

// Opção 1: mostra quem foi aprovado e quem foi reprovado
// ---------------------- PESQUISA ----------------------

// Se não houver alunos, avisa, pausa e retorna true
bool semAlunos(const vector<string>& nomes) {
    if (nomes.empty()) {
        cout << "Nenhum aluno cadastrado ainda.\n";
        pausarParaMenu();
        return true;
    }
    return false;
}

// Retorna o maior valor de um vetor
double maiorValor(const vector<double>& valores) {
    double maior = valores[0];
    for (int i = 1; i < valores.size(); i++) {
        if (valores[i] > maior) {
            maior = valores[i];
        }
    }
    return maior;
}

// Retorna o menor valor de um vetor
double menorValor(const vector<double>& valores) {
    double menor = valores[0];
    for (int i = 1; i < valores.size(); i++) {
        if (valores[i] < menor) {
            menor = valores[i];
        }
    }
    return menor;
}

// Imprime o nome de todos os alunos que têm esse valor (em caso de empate aparecem todos)
void imprimirNomesComValor(const vector<string>& nomes, const vector<double>& valores, double valor) {
    for (int i = 0; i < nomes.size(); i++) {
        if (valores[i] == valor) {
            cout << "      - " << nomes[i] << '\n';
        }
    }
}

// Opção 1: ranking pela média (decrescente)
void mostrarRanking(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias) {
    system("cls");
    if (semAlunos(nomes)) return;

    // vetor com as posições dos alunos; ordenamos as posições sem mexer nos vetores originais
    vector<int> ordem;
    for (int i = 0; i < nomes.size(); i++) {
        ordem.push_back(i);
    }

    // ordenação por seleção: coloca a maior média primeiro
    for (int i = 0; i < ordem.size() - 1; i++) {
        int posMaior = i;
        for (int j = i + 1; j < ordem.size(); j++) {
            if (medias[ordem[j]] > medias[ordem[posMaior]]) {
                posMaior = j;
            }
        }
        int temp = ordem[i];
        ordem[i] = ordem[posMaior];
        ordem[posMaior] = temp;
    }

    cout << fixed << setprecision(1);

    cout << "\nRANKING DE NOTAS (pela média)\n";
    cout << left << setw(5) << "Pos" << setw(25) << "Nome"
         << setw(8) << "AV 01" << setw(8) << "AV 02" << "Média\n";
    cout << setfill('-') << setw(52) << "" << setfill(' ') << '\n';

    for (int i = 0; i < ordem.size(); i++) {
        int a = ordem[i];
        cout << left << setw(5) << (to_string(i + 1) + "º")
             << setw(25) << nomes[a]
             << setw(8) << notas1[a]
             << setw(8) << notas2[a]
             << medias[a] << '\n';
    }

    cout.unsetf(ios::fixed);
    pausarParaMenu();
}

// Opções 2 e 3: mostra as maiores (maior = true) ou as menores (maior = false) notas
void mostrarNotasExtremas(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias, bool maior) {
    system("cls");
    if (semAlunos(nomes)) return;

    string texto = maior ? "Maior" : "Menor";

    double nota1 = maior ? maiorValor(notas1) : menorValor(notas1);
    double nota2 = maior ? maiorValor(notas2) : menorValor(notas2);
    double media = maior ? maiorValor(medias) : menorValor(medias);

    // nota geral = a maior (ou menor) entre as duas provas
    double geral;
    if (maior) {
        geral = (nota1 > nota2) ? nota1 : nota2;
    } else {
        geral = (nota1 < nota2) ? nota1 : nota2;
    }

    cout << fixed << setprecision(1);

    cout << '\n' << setfill('=') << setw(52) << "" << setfill(' ') << '\n';
    cout << (maior ? "MAIORES NOTAS\n" : "MENORES NOTAS\n");
    cout << setfill('=') << setw(52) << "" << setfill(' ') << '\n';

    cout << "\n  " << texto << " nota na 1ª prova: " << nota1 << '\n';
    imprimirNomesComValor(nomes, notas1, nota1);

    cout << "\n  " << texto << " nota na 2ª prova: " << nota2 << '\n';
    imprimirNomesComValor(nomes, notas2, nota2);

    cout << "\n  " << texto << " nota geral (entre as duas provas): " << geral << '\n';
    for (int i = 0; i < nomes.size(); i++) {
        if (notas1[i] == geral && notas2[i] == geral) {
            cout << "      - " << nomes[i] << " (nas duas provas)\n";
        } else if (notas1[i] == geral) {
            cout << "      - " << nomes[i] << " (1ª prova)\n";
        } else if (notas2[i] == geral) {
            cout << "      - " << nomes[i] << " (2ª prova)\n";
        }
    }

    cout << "\n  " << texto << " média: " << media << '\n';
    imprimirNomesComValor(nomes, medias, media);

    cout.unsetf(ios::fixed);
    pausarParaMenu();
}

// Opções 4 e 5: mostra só os aprovados (aprovados = true) ou só os reprovados (aprovados = false)
void mostrarSituacao(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias, bool aprovados) {
    system("cls");
    if (semAlunos(nomes)) return;

    cout << fixed << setprecision(1);

    cout << (aprovados ? "\nALUNOS APROVADOS" : "\nALUNOS REPROVADOS")
         << " (média mínima: " << mediaAprovacao << ")\n";
    cout << left << setw(25) << "Nome" << setw(8) << "AV 01"
         << setw(8) << "AV 02" << "Média\n";
    cout << setfill('-') << setw(47) << "" << setfill(' ') << '\n';

    int quantidade = 0;
    for (int i = 0; i < nomes.size(); i++) {
        bool passou = medias[i] >= mediaAprovacao;

        if (passou == aprovados) {   // mostra só os da situação escolhida
            cout << left << setw(25) << nomes[i]
                 << setw(8) << notas1[i]
                 << setw(8) << notas2[i]
                 << medias[i] << '\n';
            quantidade++;
        }
    }

    if (quantidade == 0) {
        cout << (aprovados ? "Nenhum aluno aprovado.\n" : "Nenhum aluno reprovado.\n");
    }

    cout << setfill('-') << setw(47) << "" << setfill(' ') << '\n';
    cout << "Total: " << quantidade << " aluno(s)\n";

    cout.unsetf(ios::fixed);
    pausarParaMenu();
}

void alterarMedia() {
    system("cls");
    cout << fixed << setprecision(1);
    cout.unsetf(ios::fixed);

    // reaproveita o lerNota, que já valida número entre 0 e 10
    mediaAprovacao = lerNota("Média atual: " + formatarNota(mediaAprovacao) + "\nDigite a nova média mínima (0 a 10): ");

    cout << "Média mínima alterada para " << formatarNota(mediaAprovacao) << " com sucesso!\n";
}

// Exibe o menu principal
void menu() {
    cout << "\n---------------------------------\n";
    cout << "FERRAMENTA DE NOTAS\n";
    cout << "# Digite um número de 0-5 #\n";
    cout << "---------------------------------\n";
    cout << "1. Cadastrar aluno\n";
    cout << "2. Relatório\n";
    cout << "3. Pesquisar\n";
    cout << "4. Editar aluno\n";
    cout << "5. Alterar média (atual: " << formatarNota(mediaAprovacao) << ")\n";
    cout << "0. Encerrar programa\n";
    cout << "---------------------------------\n";
    cout << '\n';
}

// Exibe o menu de pesquisa
void menuPesquisa() {
    cout << "\n---------------------------------\n";
    cout << "MENU PESQUISA\n";
    cout << "# Digite um número de 0-5 #\n";
    cout << "---------------------------------\n";
    cout << "1. Ranking\n";
    cout << "2. Maior Nota\n";
    cout << "3. Menor Nota\n";
    cout << "4. Aprovados\n";
    cout << "5. Reprovados\n";
    cout << "0. Voltar\n";
    cout << "---------------------------------\n";
    cout << '\n';
}

// Loop do menu de pesquisa (fica aqui atÃ© o usuÃ¡rio escolher 0 - Voltar)
void pesquisar(const vector<string>& nomes, const vector<double>& notas1, const vector<double>& notas2, const vector<double>& medias) {
    system("cls");
    int opcao;
    do {
        menuPesquisa();
        opcao = lerOpcao("Escolha uma opção: ", 0, 5);

        switch (opcao) {
            case 1:
                mostrarRanking(nomes, notas1, notas2, medias);
                break;
            case 2:
                mostrarNotasExtremas(nomes, notas1, notas2, medias, true);   // maiores
                break;
            case 3:
                mostrarNotasExtremas(nomes, notas1, notas2, medias, false);  // menores
                break;
            case 4:
                mostrarSituacao(nomes, notas1, notas2, medias, true);        // aprovados
                break;
            case 5:
                mostrarSituacao(nomes, notas1, notas2, medias, false);       // reprovados
                break;
            case 0:
                system("cls");
                break;
        }
    } while (opcao != 0);
}

int main() {
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    setlocale(LC_ALL, "Portuguese");

    vector<string> nomes;
    vector<double> notas1;
    vector<double> notas2;
    vector<double> medias;

    int opcao;
    bool sair = false;

    //loop enquanto o usuÃ¡rio nÃ£o confirmar a saÃ­da
    do {
        menu();
        opcao = lerOpcao("Escolha uma opção: ", 0, 5); //chama a funcao ler opcao

        switch (opcao) {
            case 1:
                cadastrarAluno(nomes, notas1, notas2, medias); //chama funcao cadastrarAluno
                break;
            case 2:
                exibirRelatorio(nomes, notas1, notas2, medias); //chama funcao exibirRelatorio
                break;
            case 3:
                pesquisar(nomes, notas1, notas2, medias);       //abre o menu de pesquisa
                break;
            case 4:
    			editarAluno(nomes, notas1, notas2, medias);
    			break;
    		case 5:
    			alterarMedia();
    		break;
            case 0:
                sair = confirmarSaida(); //chama funcao confirmarSaida
                if (sair) { //condicao baseada no retorno da funcao confirmarSaida
                    cout << "\nEncerrando o programa\n";
                } else {
                    system("cls");
                }
                break;
        }

    } while (!sair);

    return 0;
}
