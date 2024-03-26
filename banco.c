#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

// Define o número máximo de clientes no sistema
#define MAX_CLIENTS 100

// Define o comprimento máximo para o nome do cliente
#define MAX_NAME_LENGTH 50

// Define o comprimento máximo para o CPF do cliente
#define MAX_CPF_LENGTH 15

// Define o comprimento máximo para a senha do cliente
#define MAX_PASSWORD_LENGTH 20

// Define o limite de empréstimo como percentual do total dos saldos
#define MAX_LOANS 0.2

// Estrutura que representa um cliente no sistema
struct Cliente {
    char nome[MAX_NAME_LENGTH];  // Nome do cliente
    int idade;                   // Idade do cliente
    char cpf[MAX_CPF_LENGTH];    // CPF do cliente
    char senha[MAX_PASSWORD_LENGTH];  // Senha do cliente
    double saldo;                // Saldo na conta do cliente
    int numeroConta;             // Número da conta do cliente
    int tipoConta[15];           // Tipo de conta do cliente (array de inteiros)
    int status;                  // Status da conta do cliente (aberta ou fechada)
};

// Declaração do array de clientes e variáveis globais
struct Cliente clientes[MAX_CLIENTS];
int clientCount = 0;
int usuarioLogado = -1;         // Índice do cliente que está logado
double totalSaldos = 0;         // Total dos saldos de todos os clientes
double totalEmprestimos = 0;    // Total dos empréstimos concedidos

// Protótipos de funções
void listarClientes();          // Função para listar todos os clientes cadastrados
void realizarLogin();           // Função para realizar o login de um cliente
void deslogar();                // Função para deslogar a conta
void fazerDeposito();           // Função para realizar um depósito na conta de um cliente
void fazerSaque();              // Função para realizar um saque na conta de um cliente
void salvarDados();             // Função para salvar os dados dos clientes em um arquivo
void carregarDados();           // Função para carregar os dados dos clientes de um arquivo
void abrirConta();              // Função para abrir uma nova conta para um cliente
void fecharConta();             // Função para fechar a conta de um cliente
void fazerEmprestimo();         // Função para conceder um empréstimo a um cliente

// Função principal
int main() {
    carregarDados(); // Carrega os dados dos clientes do arquivo

    int escolha;

    do {
        
        UINT CPAGE_UTF8 = 65001;
        UINT CPAGE_DEFAULT = GetConsoleOutputCP(); 
        SetConsoleOutputCP(CPAGE_UTF8); // Comando para ler acentuação

        // Apresentação do Menu Principal
        printf("\n                                        Menu Principal:\n");
        printf("  \n");
        printf("[1]. Listar clientes\n");
        printf("[2]. Abrir conta\n");
        printf("[3]. Fazer Login\n");
        printf("[4]. Fazer depósito\n");
        printf("[5]. Fazer Saque\n");
        printf("[6]. Fechar conta\n");
        printf("[7]. Fazer empréstimo\n");
       	printf("[8]. Deslogar\n"); 
        printf("[9]. Sair\n");
        printf("  \n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        // Switch para escolher a ação com base na escolha do usuário
        switch (escolha) {
            case 1:
                listarClientes();
                break;
            case 2:
                abrirConta();
                break;
            case 3:
                realizarLogin();
                break;
            case 4:
                fazerDeposito();
                break;
            case 5:
                fazerSaque();
                break;
            case 6:
                fecharConta();
                break;
            case 7:
                fazerEmprestimo();
                break;
            case 8:
                deslogar();
                break;
            case 9:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (escolha != 9);

    salvarDados();

    return 0;
}

// Função para listar os clientes
void listarClientes() {
    printf("\nClientes Cadastrados:\n");
    for (int i = 0; i < clientCount; i++) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Tipo de Conta: %s\n", clientes[i].tipoConta == 0 ? "Conta Corrente" : "Conta Poupança");
        printf("Numero da Conta: %d\n", clientes[i].numeroConta);
        printf("Status: %s\n", clientes[i].saldo > 0 ? "Ativa" : "Inativa");
        printf("Saldo: R$%.2f\n", clientes[i].saldo);
        printf("\n");
    }
}

// Função para abrir uma nova conta
// Função para cadastrar um novo cliente
void abrirConta() {
    if (clientCount < MAX_CLIENTS) {
        struct Cliente novoCliente;

        printf("Digite o nome do cliente: ");
        scanf("%s", novoCliente.nome);

        printf("Digite a idade do cliente: ");
        scanf("%d", &novoCliente.idade);

        printf("Digite o CPF do cliente: ");
        scanf("%s", novoCliente.cpf);

        // Verificando se o CPF já está cadastrado
        for (int i = 0; i < clientCount; i++) {
            if (strcmp(novoCliente.cpf, clientes[i].cpf) == 0) {
                printf("Cliente já cadastrado com este CPF. Retornando ao menu principal.\n");
                return;
            }
        }

        // Verificando se o cliente é menor de idade
        if (novoCliente.idade < 18) {
            printf("Cliente precisa ser maior de idade. Retornando ao menu principal.\n");
            return;
        }

        printf("Escolha o tipo de conta:\n");
        printf("1. Conta Corrente\n");
        printf("2. Conta Poupança\n");
        int tipoConta;
        scanf("%d", &tipoConta);

        // Atribuindo valores ao novo cliente
        novoCliente.saldo = 0.0;
        novoCliente.numeroConta = MAX_CLIENTS + clientCount + 1;  // Número automático
        novoCliente.tipoConta[tipoConta - 1] = 1;  // Ativando o tipo de conta escolhido
        novoCliente.status = 1;  // Conta é ativada automaticamente

        printf("Digite a senha da conta: ");
        scanf("%s", novoCliente.senha);

        clientes[clientCount++] = novoCliente;

        printf("Cliente cadastrado com sucesso! Numero da conta: %d\n", novoCliente.numeroConta);
    } else {
        printf("Limite de clientes atingido. Impossível cadastrar mais clientes.\n");
    }
}


// Função para realizar o login
void realizarLogin() {
    system("cls");
    int i = 0;
    char cpf[MAX_CPF_LENGTH];
    char senha[MAX_PASSWORD_LENGTH];

    printf("Digite o CPF: ");
    scanf("%s", cpf);

    printf("Digite a senha: ");
    scanf("%s", senha);

    for (i = 0; i < clientCount; i++) {
        if (strcmp(cpf, clientes[i].cpf) == 0 && strcmp(senha, clientes[i].senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s!\n", clientes[i].nome);
            usuarioLogado = i;
            return;
        }
    }

    printf("CPF ou senha incorretos. Tente novamente.\n");
}

// Função para realizar um depósito
void fazerDeposito() {
    system("cls");
    if (usuarioLogado != -1) {
        double valorDeposito;
        printf("Digite o valor do depósito: R$");
        scanf("%lf", &valorDeposito);
        totalSaldos += valorDeposito;
        clientes[usuarioLogado].saldo += valorDeposito;
        printf("Depósito de R$%.2f realizado. Saldo atual: R$%.2f\n", valorDeposito, clientes[usuarioLogado].saldo);
    } else {
        printf("Nenhum cliente logado. Realize o login antes de fazer um depósito.\n");
    }
}

// Função para realizar um saque
void fazerSaque() {
    system("cls");
    if (usuarioLogado != -1) {
        double valorSaque;
        printf("Digite o valor do saque: R$");
        scanf("%lf", &valorSaque);

        if (valorSaque <= clientes[usuarioLogado].saldo) {
            clientes[usuarioLogado].saldo -= valorSaque;
            printf("Saque de R$%.2f realizado. Saldo atual: R$%.2f\n", valorSaque, clientes[usuarioLogado].saldo);
        } else {
            printf("Saldo insuficiente. Saque não realizado.\n");
        }
    } else {
        printf("Nenhum cliente logado. Realize o login antes de fazer um saque.\n");
    }
}

// Função para salvar os dados dos clientes em um arquivo
void salvarDados() {
    system("cls");
    int i = 0;
    FILE *arquivo;
    arquivo = fopen("dados_clientes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (i = 0; i < clientCount; i++) {
        fprintf(arquivo, "%s %d %s %s %.2f %i\n",
                clientes[i].nome, clientes[i].idade, clientes[i].cpf, clientes[i].senha, clientes[i].saldo, clientes[clientCount].numeroConta);
    }

    fclose(arquivo);
}

// Função para carregar os dados dos clientes de um arquivo
void carregarDados() {
    system("cls");
    FILE *arquivo;
    arquivo = fopen("dados_clientes.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    while (fscanf(arquivo, "%s %d %s %s %lf %i\n",
                  clientes[clientCount].nome, &clientes[clientCount].idade,
                  clientes[clientCount].cpf, clientes[clientCount].senha, &clientes[clientCount].saldo, &clientes[clientCount].numeroConta) == 6) {
        clientCount++;
    }

    fclose(arquivo);
}

// Função para fechar a conta de um cliente
void fecharConta() {
    system("cls");
    if (usuarioLogado != -1) {
        printf("Você está logado. Saia da conta atual para fechar uma conta.\n");
        return;
    }

    int numeroConta;
    printf("Digite o número da conta a ser fechada: ");
    scanf("%d", &numeroConta);

    int i;
    for (i = 0; i < clientCount; i++) {
        if (clientes[i].numeroConta == numeroConta) {
            if (clientes[i].saldo == 0) {
                clientes[i].status = 0;
                printf("Conta fechada com sucesso.\n");
            } else {
                printf("É necessário esvaziar a conta antes de fechá-la.\n");
            }
            return;
        }
    }

    printf("Conta não encontrada.\n");
}

// Função para conceder um empréstimo a um cliente
void fazerEmprestimo() {
    if (usuarioLogado != -1) {
        printf("Você está logado. Saia da conta atual para fazer um empréstimo.\n");
        return;
    }

    int numeroConta;
    printf("Digite o número da conta para o empréstimo: ");
    scanf("%d", &numeroConta);

    int i;
    for (i = 0; i < clientCount; i++) {
        if (clientes[i].numeroConta == numeroConta) {
            double valorEmprestimo;
            printf("Digite o valor desejado para o empréstimo: ");
            scanf("%lf", &valorEmprestimo);

            if (valorEmprestimo <= 2 * clientes[i].saldo &&
                totalEmprestimos + valorEmprestimo <= MAX_LOANS * totalSaldos) {
                clientes[i].saldo += valorEmprestimo;
                totalEmprestimos += valorEmprestimo;
                printf("Empréstimo de R$%.2f efetuado. Saldo atual: R$%.2f\n", valorEmprestimo, clientes[i].saldo);
            } else {
                printf("Valor maior que o limite disponível ou ultrapassaria o crédito disponível nesta agência.\n");
            }
            return;
        }
    }

    printf("Conta não encontrada.\n");
}

//Função para deslogar a conta de Usuário
void deslogar() {
    if (usuarioLogado != -1) {
        printf("Deslogado com sucesso. Obrigado, %s!\n", clientes[usuarioLogado].nome);
        usuarioLogado = -1;
    } else {
        printf("Nenhum cliente logado.\n");
    }
}
void liberarMemoria() {
    // Adicione aqui a lógica para liberar a memória, se necessário
    // Por exemplo, se você estiver usando alocação dinâmica de memória,
    // você pode usar a função free para liberar essa memória.
}
