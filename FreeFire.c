#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define NOME_MAX 30
#define TIPO_MAX 20

typedef struct {
    char nome[NOME_MAX];
    char tipo[TIPO_MAX];
    int quantidade;
} Item;

int contador_itens = 0; 
Item mochila[MAX_ITENS];

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    printf("\n--- Inventário (Mochila) ---\n");
    printf("1. Cadastrar Novo Item\n");
    printf("2. Remover Item pelo Nome\n");
    printf("3. Listar Todos os Itens\n");
    printf("4. Buscar Item pelo Nome\n");
    printf("0. Sair do Sistema\n");
    printf("----------------------------\n");
    printf("Escolha uma opção: ");
}

void listarItens() {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", contador_itens, MAX_ITENS);
    if (contador_itens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    for (int i = 0; i < contador_itens; i++) {
        printf("ID [%d] | Nome: %-20s | Tipo: %-10s | Qtd: %d\n", 
               i, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------\n");
}

void inserirItem() {
    if (contador_itens >= MAX_ITENS) {
        printf("\nERRO: A mochila está cheia! Não é possível cadastrar mais itens.\n");
        return;
    }
    
    printf("\n--- Cadastro de Novo Item ---\n");
    
    printf("Digite o NOME do item (max %d): ", NOME_MAX - 1);
    scanf("%29s", mochila[contador_itens].nome);
    limpar_buffer();
    
    printf("Digite o TIPO do item (max %d - ex: arma, munição, cura): ", TIPO_MAX - 1);
    scanf("%19s", mochila[contador_itens].tipo);
    limpar_buffer();

    printf("Digite a QUANTIDADE: ");
    if (scanf("%d", &mochila[contador_itens].quantidade) != 1 || mochila[contador_itens].quantidade <= 0) {
        printf("ERRO: Quantidade inválida. Item não cadastrado.\n");
        limpar_buffer(); 
        return;
    }
    limpar_buffer();
    
    contador_itens++;
    printf("\nSUCESSO: Item cadastrado. Capacidade atual: %d/%d\n", contador_itens, MAX_ITENS);

    // CHAMA A FUNÇÃO DE LISTAGEM APÓS A INSERÇÃO
    listarItens();
}

int buscarItem(const char *nome_busca) {
    for (int i = 0; i < contador_itens; i++) {
        if (strcasecmp(mochila[i].nome, nome_busca) == 0) {
            return i;
        }
    }
    return -1;
}

void removerItem() {
    char nome_busca[NOME_MAX];
    int indice;
    
    printf("\n--- Remoção de Item ---\n");
    if (contador_itens == 0) {
        printf("A mochila está vazia. Nada para remover.\n");
        return;
    }
    
    printf("Digite o NOME do item a ser removido: ");
    scanf("%29s", nome_busca);
    limpar_buffer();
    
    indice = buscarItem(nome_busca);
    
    if (indice == -1) {
        printf("\nERRO: Item '%s' não encontrado na mochila.\n", nome_busca);
        return;
    }
    
    for (int i = indice; i < contador_itens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    contador_itens--;
    printf("\nSUCESSO: Item '%s' removido da mochila.\n", nome_busca);
    
    // CHAMA A FUNÇÃO DE LISTAGEM APÓS A REMOÇÃO
    listarItens();
}

void buscarItem_interativo() {
    char nome_busca[NOME_MAX];
    int indice;
    
    printf("\n--- Busca de Item ---\n");
    if (contador_itens == 0) {
        printf("A mochila está vazia. Nada para buscar.\n");
        return;
    }
    
    printf("Digite o NOME do item para buscar: ");
    scanf("%29s", nome_busca);
    limpar_buffer();
    
    indice = buscarItem(nome_busca);
    
    if (indice != -1) {
        printf("\nItem ENCONTRADO:\n");
        printf("  Nome: %s\n", mochila[indice].nome);
        printf("  Tipo: %s\n", mochila[indice].tipo);
        printf("  Quantidade: %d\n", mochila[indice].quantidade);
    } else {
        printf("\nItem '%s' não encontrado na mochila.\n", nome_busca);
    }
}

int main() {
    int opcao;
    
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite um número de 0 a 4.\n");
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem_interativo();
                break;
            case 0:
                printf("\nSaindo do sistema de inventário. Adeus!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
        
    } while (opcao != 0);

    return 0;
}