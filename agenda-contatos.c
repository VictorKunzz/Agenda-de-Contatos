#include <stdio.h>  
#include <stdlib.h> 

typedef struct {
	char nome [30];
	char telefone [15];
} Contato;

Contato agenda[100];
int numContatos = 0; 

// Protótipo das funções.
void adicionarContato(void);
void pesquisarContato(void);
void excluirContato(void);
void salvarAgenda(void);
void carregarAgenda(void);

int main(void) {
    char menu; 

    carregarAgenda();

    do {
    	printf("\n--------MENU--------\n");
    	printf("--------------------\n");
        printf("1. Adicionar Contato\n"); 
        printf("2. Consultar Contato\n"); 
        printf("3. Excluir Contato\n");  
        printf("4. Sair\n");
		printf("--------------------\n"); 
        printf("Escolha uma opcao: ");
        scanf("%c", &menu);
        fflush (stdin);
        printf("\n--------------------\n");
        

        switch (menu) {
            case '1':
                adicionarContato();
                printf("Numero atual de contatos: %d\n", numContatos);
                break;
            case '2':
                pesquisarContato(); 
                break;
            case '3':
                excluirContato(); 
                break;
            case '4':
                salvarAgenda();
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida\n"); 
        }
    } while (menu != '4');

    return 0;
}

void adicionarContato(void) {
	if (numContatos == 100) { 
        printf("Agenda cheia!\n");
        return;
    }
    printf("Digite o nome: ");
    scanf("%s", agenda[numContatos].nome);
	fflush (stdin);  
    printf("Digite o telefone: ");
    scanf("%s", agenda[numContatos].telefone);
	fflush (stdin); 
    numContatos++;
    printf("Contato adicionado.\n\n");
}

void pesquisarContato(void) {
    char nome[30];
    printf("\nDigite o nome para procurar: ");
    scanf("%s", nome);
    fflush (stdin);
    for (int i = 0; i < numContatos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            printf("\nNome: %s, Telefone: %s\n", agenda[i].nome, agenda[i].telefone);
            return;
        }
    }
    printf("\nContato nao encontrado.\n\n");
}

void excluirContato(void) {
    char nome[30];
    printf("\nDigite o nome para excluir: ");
    scanf("%s", nome);
    fflush (stdin);
    for (int i = 0; i < numContatos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            for (int j = i; j < numContatos - 1; j++) {
                agenda[j] = agenda[j + 1];
            }
            numContatos--;  
            printf("\nContato excluido!\n");
            return;
        }
    }
    printf("\nContato nao encontrado.\n");
}

void salvarAgenda(void) {
    FILE *arquivo = fopen("ListaDeContatos.bin", "wb");
    if (arquivo == NULL) {
        printf("\nErro.\n");
        return;
    }
    fwrite(agenda, sizeof(Contato), numContatos, arquivo); 
    fclose(arquivo);  
}

void carregarAgenda(void) {
    FILE *arquivo = fopen("ListaDeContatos.bin", "rb");
    if (arquivo == NULL) {
        printf("\nErro.\n");
        numContatos = 0;
        return;
    }
    numContatos = fread(agenda, sizeof(Contato), 100, arquivo);  
    fclose(arquivo); 
}