#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contato {
    char nome[128];
    char telefone[15];
};

int menu(int *PointOpcao) {
    printf("1- Cadastro de novo contato;\n");
    printf("2- Imprimir agenda em tela;\n");
    printf("3- Deletar um contato;\n");
    printf("4- Salvar em arquivo (formato CSV);\n");
    printf("5- Sair (ao sair, se houver alterações não salvas, deve salvar os contatos no arquivo);\n");
    scanf("%d", PointOpcao);
    return 0;
}

int main() {
    int opcao;
    int *PointOpcao = &opcao;
    int numContato = 0;
    struct Contato c[50];
    
    printf("_____ Agenda _____\n");
    
    while(numContato < 50 && opcao != 5){
        menu(PointOpcao);
        switch (opcao){
            case 1:
                if (numContato < 50) {
                    printf("_____ Cadastro _____\n");
                    printf("Nome do contato: ");
                    scanf("%s", c[numContato].nome);
                    printf("Telefone do contato: ");
                    scanf("%s", c[numContato].telefone);
                    printf("Nome cadastrado: %s\n", c[numContato].nome);
                    printf("Telefone cadastrado: %s\n", c[numContato].telefone);
                    numContato++;
                } else {
                    printf("Agenda cheia!\n");
                }
                break;
            case 2:
                printf("_____ Imprimir _____\n");
                for (int i = 0; i < numContato; i++) {
                    printf("Contato %d:\n", i + 1);
                    printf("Nome: %s\n", c[i].nome);
                    printf("Telefone: %s\n", c[i].telefone);
                }
                break;
            case 3:
                printf("_____ Deletar _____\n");
                if (numContato == 0) {
                    printf("Agenda vazia! Não há contatos para deletar.\n");
                    break;
                }
                char nomeDeletar[128];
                printf("Informe o nome do contato a ser deletado: ");
                scanf("%s", nomeDeletar);
                
                int encontrado = 0;
                for (int i = 0; i < numContato; i++) {
                    if (strcmp(c[i].nome, nomeDeletar) == 0) {
                        // Desloca os contatos para "remover" o contato
                        for (int j = i; j < numContato - 1; j++) {
                            c[j] = c[j + 1];
                        }
                        numContato--;
                        printf("Contato %s deletado com sucesso.\n", nomeDeletar);
                        encontrado = 1;
                        break;
                    }
                }
                
                if (!encontrado) {
                    printf("Contato %s não encontrado.\n", nomeDeletar);
                }
                break;
            case 4:
                printf("_____ Salvar _____\n");
                FILE *file = fopen("agenda.csv", "w");
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo para salvar.\n");
                    break;
                }
                for (int i = 0; i < numContato; i++) {
                    fprintf(file, "%s,%s\n", c[i].nome, c[i].telefone);
                }
                fclose(file);
                printf("Contatos salvos no arquivo agenda.csv\n");
                break;
            case 5:
                printf("SAINDO . . .\n");
                // Salvar automaticamente ao sair
                FILE *fileExit = fopen("agenda.csv", "w");
                if (fileExit == NULL) {
                    printf("Erro ao abrir o arquivo para salvar.\n");
                    break;
                }
                for (int i = 0; i < numContato; i++) {
                    fprintf(fileExit, "%s,%s\n", c[i].nome, c[i].telefone);
                }
                fclose(fileExit);
                printf("Contatos salvos antes de sair.\n");
                break;
        }
    }
    
    return 0;
}
