#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100
#define MAX_PAGADORES 100

typedef struct {
    int idConta;         // Identificador único da conta
    float valor;         // Valor associado à conta
    char status[20];     // Status (ex.: "Pago", "Pendente")
    char vencimento[10]; // Data de vencimento (ex.: "YYYY-MM-DD")
    int idpagador;       // ID do pagador associado
} Conta;

typedef struct {
    int id;             // Identificador único do pagador
    char nome[50];      // Nome do pagador
    char cpfCnpj[20];   // CPF ou CNPJ do pagador
    char telefone[15];  // Telefone de contato
} Pagador;

// Função para exibir o menu principal
void menu() {
    printf("\nGerenciamento de Contas e Pagadores\n");
    printf("1. Cadastrar Pagador\n");
    printf("2. Cadastrar Conta\n");
    printf("3. Listar Pagadores\n");
    printf("4. Listar Contas\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}

// Função para verificar se um ID de pagador já existe
int verificar_pagador_existente(Pagador *pagadores, int num_pagadores, int id) {
    for (int i = 0; i < num_pagadores; i++) {
        if (pagadores[i].id == id) {
            return 1; // Pagador encontrado
        }
    }
    return 0; // Pagador não encontrado
}

// Função para verificar se um ID de conta já existe
int verificar_conta_existente(Conta *contas, int num_contas, int idConta) {
    for (int i = 0; i < num_contas; i++) {
        if (contas[i].idConta == idConta) {
            return 1; // Conta encontrada
        }
    }
    return 0; // Conta não encontrada
}

// Função para cadastrar um novo pagador
void cadastrar_pagador(Pagador *pagadores, int *num_pagadores) {
    if (*num_pagadores >= MAX_PAGADORES) {
        printf("Limite máximo de pagadores atingido!\n");
        return;
    }

    Pagador novoPagador;
    printf("Digite o ID do pagador: ");
    scanf("%d", &novoPagador.id);

    if (verificar_pagador_existente(pagadores, *num_pagadores, novoPagador.id)) {
        printf("Erro: Já existe um pagador com esse ID.\n");
        return;
    }

    printf("Digite o nome do pagador: ");
    scanf(" %[^\n]", novoPagador.nome);
    printf("Digite o CPF/CNPJ do pagador: ");
    scanf("%s", novoPagador.cpfCnpj);
    printf("Digite o telefone do pagador: ");
    scanf("%s", novoPagador.telefone);

    pagadores[*num_pagadores] = novoPagador;
    (*num_pagadores)++;
    printf("Pagador cadastrado com sucesso!\n");
}

// Função para cadastrar uma nova conta
void cadastrar_conta(Conta *contas, int *num_contas, Pagador *pagadores, int num_pagadores) {
    if (*num_contas >= MAX_CONTAS) {
        printf("Limite máximo de contas atingido!\n");
        return;
    }

    Conta novaConta;
    printf("Digite o ID da conta: ");
    scanf("%d", &novaConta.idConta);

    if (verificar_conta_existente(contas, *num_contas, novaConta.idConta)) {
        printf("Erro: Já existe uma conta com esse ID.\n");
        return;
    }

    printf("Digite o valor da conta: ");
    scanf("%f", &novaConta.valor);
    printf("Digite o status da conta (Pago/Pendente): ");
    scanf("%s", novaConta.status);
    printf("Digite a data de vencimento (YYYY-MM-DD): ");
    scanf("%s", novaConta.vencimento);
    printf("Digite o ID do pagador associado: ");
    scanf("%d", &novaConta.idpagador);

    if (!verificar_pagador_existente(pagadores, num_pagadores, novaConta.idpagador)) {
        printf("Erro: Pagador com ID %d não encontrado.\n", novaConta.idpagador);
        return;
    }

    contas[*num_contas] = novaConta;
    (*num_contas)++;
    printf("Conta cadastrada com sucesso!\n");
}

// Função para listar todos os pagadores
void listar_pagadores(Pagador *pagadores, int num_pagadores) {
    printf("\nPagadores cadastrados:\n");
    for (int i = 0; i < num_pagadores; i++) {
        printf("ID: %d | Nome: %s | CPF/CNPJ: %s | Telefone: %s\n",
               pagadores[i].id, pagadores[i].nome, pagadores[i].cpfCnpj, pagadores[i].telefone);
    }
}

// Função para listar todas as contas
void listar_contas(Conta *contas, int num_contas, Pagador *pagadores, int num_pagadores) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < num_contas; i++) {
        // Encontra o nome do pagador associado
        char nomePagador[50] = "Desconhecido";
        for (int j = 0; j < num_pagadores; j++) {
            if (pagadores[j].id == contas[i].idpagador) {
                strcpy(nomePagador, pagadores[j].nome);
                break;
            }
        }

        printf("ID Conta: %d | Valor: %.2f | Status: %s | Vencimento: %s | Pagador: %s (ID: %d)\n",
               contas[i].idConta, contas[i].valor, contas[i].status, contas[i].vencimento,
               nomePagador, contas[i].idpagador);
    }
}

int main() {
    Conta contas[MAX_CONTAS];
    Pagador pagadores[MAX_PAGADORES];
    int num_contas = 0;
    int num_pagadores = 0;

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_pagador(pagadores, &num_pagadores);
                break;

            case 2:
                cadastrar_conta(contas, &num_contas, pagadores, num_pagadores);
                break;

            case 3:
                listar_pagadores(pagadores, num_pagadores);
                break;

            case 4:
                listar_contas(contas, num_contas, pagadores, num_pagadores);
                break;

            case 5:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}