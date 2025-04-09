#include <stdio.h>
#include <string.h>
#define TAM 50

// Struct
typedef struct
{
    char nome[128];
    char telefone[15];
} Contato;

// Função para cadastrar um novo contato
void cadastrar(Contato *agenda, int *numContato, int *modificado)
{
    printf("_____ Cadastro _____\n");

    if (*numContato < TAM)
    {
        printf("Nome do contato: ");
        scanf(" %127[^\n]", agenda[*numContato].nome);

        printf("Telefone do contato: ");
        scanf(" %14[^\n]", agenda[*numContato].telefone);

        (*numContato)++;
        *modificado = 1;
        printf("Contato cadastrado!\n");
    }
    else
    {
        printf("Agenda cheia! Nao e possivel adicionar mais contatos.\n");
    }
}

// Função para imprimir a agenda
void imprimir(Contato *agenda, int numContato)
{
    printf("_____ Imprimir _____\n");

    if (numContato > 0)
    {
        for (int i = 0; i < numContato; i++)
        {
            printf("Contato %d:\n", i + 1);
            printf("Nome: %s\n", agenda[i].nome);
            printf("Telefone: %s\n", agenda[i].telefone);
        }
    }
    else
    {
        printf("Agenda vazia! Nao ha contatos para exibir.\n");
    }
}

// Função para deletar um contato
void deletar(Contato *agenda, int *numContato, int *modificado)
{
    printf("_____ Deletar _____\n");

    if (*numContato > 0)
    {
        char nomeDeletar[128];
        printf("Informe o nome do contato a ser deletado: ");
        scanf(" %127[^\n]", nomeDeletar);

        int encontrado = 0;

        for (int i = 0; i < *numContato; i++)
        {
            if (strcmp(agenda[i].nome, nomeDeletar) == 0)
            {
                for (int j = i; j < *numContato - 1; j++)
                {
                    agenda[j] = agenda[j + 1];
                }

                (*numContato)--;
                *modificado = 1;
                printf("Contato %s deletado com sucesso.\n", nomeDeletar);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Contato %s nao encontrado.\n", nomeDeletar);
        }
    }
    else
    {
        printf("Agenda vazia! Nao ha contatos para deletar.\n");
    }
}

// Função para salvar a agenda em arquivo
void salvarContatos(Contato *agenda, int numContato)
{
    FILE *arquivo = fopen("agenda.csv", "w");  // Sobrescreve o arquivo ao salvar
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < numContato; i++)
    {
        fprintf(arquivo, "%s,%s\n", agenda[i].nome, agenda[i].telefone);
    }

    fclose(arquivo);
    printf("Contatos salvos no arquivo agenda.csv\n");
}

// Função para ler os contatos do arquivo
void lerContatos(Contato *agenda, int *numContato)
{
    FILE *arquivo = fopen("agenda.csv", "r");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo encontrado. Criando um novo...\n");
        return;
    }

    *numContato = 0;
    while (fscanf(arquivo, " %127[^,],%14[^\n]\n", agenda[*numContato].nome, agenda[*numContato].telefone) == 2)
    {
        (*numContato)++;
        if (*numContato >= TAM) break;  // Evita ultrapassar o tamanho do array
    }

    fclose(arquivo);
}

int main()
{
    Contato agenda[TAM];
    int opcao = 0, modificado = 0;
    int numContato = 0;

    // Carrega os contatos do arquivo ao iniciar
    lerContatos(agenda, &numContato);

    // Menu de opções
    while (opcao != 5)
    {
        printf("_____ Agenda _____\n");
        printf("1 - Cadastro de novo contato\n");
        printf("2 - Imprimir agenda\n");
        printf("3 - Deletar um contato\n");
        printf("4 - Salvar\n");
        printf("5 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar(agenda, &numContato, &modificado);
            break;
        case 2:
            imprimir(agenda, numContato);
            break;
        case 3:
            deletar(agenda, &numContato, &modificado);
            break;
        case 4:
            salvarContatos(agenda, numContato);
            break;
        case 5:
            if (modificado == 1)
            {
                salvarContatos(agenda, numContato);
            }
            printf("Saindo... Ate logo!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    }

    return 0;
}