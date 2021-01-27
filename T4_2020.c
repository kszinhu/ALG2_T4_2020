/*
TRABALHO DE ALGORITMO - AGENDA DO THIERRY [\] AlgII
> Cassiano Rodrigues
> 26/01/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

typedef struct dataNode
{
    int day, month, year, hours, minutes;
    char description[81];
} DataNode;

typedef struct node
{
    DataNode data;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
    // NOSSO DESCRITOR
    int size;
} List;

//---- HEADER

List *createList();

void push_front(List *list, DataNode data); // Copia informações para o Topo da lista

void push_back(List *list, DataNode data);

bool isEmpty(List *list); // Verifica se a lista esta vazia

void pop_front(List *list); // Remove Primeira posição da lista

void pop_back(List *list); // Remove Última posição da lista

Node *atPos(List *list, int index); // Vai até a posição do Index

int indexOf(List *list, Node *node); // Returna o Index, em determinado Node

void erase(List *list, int index); // Apaga em determinado Index

void insert(List *list, DataNode data, int index); // Inserir entre a lista

bool search(int info, List *list);

int count(List *list, int search_for); // Conta quantidade de ocorrencias de um elemento na lista

bool popElement(List *list, int search_for); // Retira todas as ocorrencias de um elemento na lista

//---- FUCTIONS

List *createList()
{
    List *list = (List *)malloc(sizeof(List));

    list->size = 0;
    list->head = NULL;

    return list;
}

void push_front(List *list, DataNode data)
{
    // Inserindo no Inicio
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

void push_back(List *list, DataNode data)
{
    // Inserindo no final da lista
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->data = data;
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
    list->size++;
}

void printList(List *list)
{
    if (isEmpty(list))
    {
        printf("SEM COMPROMISSO :)\n");
        return;
    }

    Node *pointer = list->head;

    while (pointer != NULL)
    {
        printf("[COMPROMISSO]: %s\n", pointer->data.description);
        printf("[DATA]: %2d/%2d/%4d\n", pointer->data.day, pointer->data.month, pointer->data.year);
        printf("[HOR%cRIO]: %d:%d\n", 181, pointer->data.hours, pointer->data.minutes);
        printf("\n");
        pointer = pointer->next;
    }
}

void pop_front(List *list)
{
    if (!isEmpty(list))
    {
        Node *pointer = list->head;
        list->head = pointer->next;
        free(pointer);
        list->size--;
    }
}

void pop_back(List *list)
{
    if (!isEmpty(list))
    {
        if (list->size == 1)
        {
            list->head = NULL;
        }
        else
        {
            Node *current = list->head;
            while (current->next->next != NULL) // "current->next = penultimo /  current->next->next = último elemento"
            {
                current = current->next; // vai ser atribuido no "current" o valor do "penultimo", quando achar o fim da lista
            }
            current->next = NULL; // (current = penultimo) entao next de current é o último elemento.
        }
        list->size--;
    }
}

bool isEmpty(List *list)
{
    return (list->size == 0); /* Sai o resultado da comparação */
}

Node *atPos(List *list, int index)
{
    if (index >= 0 && index < list->size)
    {
        Node *node = list->head;
        int i;
        for (i = 0; i < index; i++)
        {
            node = node->next; /* para andar para o prox. */
        }
        return node;
    }
    printf("Indice invalido\n");
    return NULL; /* Caso indíce inválido */
}

int indexOf(List *list, Node *node)
{
    if (node != NULL)
    {
        Node *pointer = list->head;
        int index = 0;
        while (pointer != node && pointer != NULL)
        {
            pointer = pointer->next;
            index++;
        }
        if (pointer != NULL)
        {
            return index;
        }
    }
    printf("No nao pertecente a lista\n");
    return -1;
}

void erase(List *list, int index)
{
    if (!isEmpty(list))
    {
        if (index == 0)
        {
            pop_front(list);
        }
        else
        {
            Node *current = atPos(list, index);

            if (current != NULL)
            {
                Node *previous = atPos(list, index - 1);
                previous->next = current->next;

                free(current);
                list->size--;
            }
        }
    }
}

void insert(List *list, DataNode data, int index)
{
    if (index == 0)
    {
        push_front(list, data);
    }
    else
    {
        Node *current = atPos(list, index);
        if (current != NULL)
        {
            Node *previous = atPos(list, index - 1);

            Node *newnode = (Node *)malloc(sizeof(Node));
            newnode->data = data;

            previous->next = newnode;
            newnode->next = current;
            list->size++;
        }
    }
}

bool search(int info, List *list)
{
    Node *pointer = atPos(list, 0);
    /* Forma interativa:
     for (; pointer != NULL; pointer = pointer->next)
    {
        if (pointer->data.id == num)
        {
            return true;
        }
    }
    return false;
    */
    if (pointer == NULL)
    {
        return false;
    }
    if (pointer->data.day == info)
    {
        return true;
    }
    list->head = pointer->next;
    return search(info, list);
}

void insertionSort(List *list)
{
    Node *pointer = list->head;
    Node *i;
    Node *j;
    for (i = list->head; i->next != NULL; i = i->next)
    {
        Node *menor = i;
        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->data.day < menor->data.day)
            {
                menor = j;
            }
        }
        DataNode aux = i->data;
        i->data = menor->data;
        menor->data = aux;
    }
}

int count(List *list, int search_for)
{
    if (!isEmpty(list))
    {
        Node *current = list->head;
        int count = 0;
        while (current != NULL)
        {
            if (current->data.day == search_for)
                count++;
            current = current->next;
        }
        return count;
    }
    return 0;
}

//--- SCREEN

int menu()
{
    printf("\t.--------------------------------------.\n");
    printf("\t|                                      |\n");
    printf("\t|           AGENDA DO THIERRY          |\n");
    printf("\t|                                      |\n");
    printf("\t'--------------------------------------'\n");
    printf("\n"); // ESPAÇO
    printf("\t.--------------------------------------.\n");
    printf("\t| 1. INSERIR COMPROMISSO               |\n");
    printf("\t| 2. REMOVER COMPROMISSO               |\n");
    printf("\t| 3. MOSTRAR ELEMENTOS COMPROMISSOS    |\n");
    printf("\t| 4. ALTERAR COMPROMISSO               |\n");
    printf("\t|                                      |\n");
    printf("\t| 5. GERAR ARQUIVO BACKUP NO DISCO     |\n");
    printf("\t| 6. LER ARQUIVO BACKUP EM DISCO       |\n");
    printf("\t|                                      |\n");
    printf("\t| 0. SAIR DO PROGAMA                   |\n");
    printf("\t'--------------------------------------'\n");
    printf("\n"); // ESPAÇO

    int tecla = getch();
    return tecla;
}

int menuRemove()
{
    printf("\t.--------------------------------------.\n");
    printf("\t|                                      |\n");
    printf("\t|           AGENDA DO THIERRY          |\n");
    printf("\t|                                      |\n");
    printf("\t'--------------------------------------'\n");
    printf("\n"); // ESPAÇO
    printf("\t.--------------------------------------.\n");
    printf("\t|                                      |\n");
    printf("\t| 1. REMOVER COMPROMISSO PELA DATA     |\n");
    printf("\t| 2. REMOVER COMPROMISSO POR PALAVRA   |\n");
    printf("\t|                                      |\n");
    printf("\t| 0. SAIR DO PROGAMA                   |\n");
    printf("\t'--------------------------------------'\n");
    printf("\n"); // ESPAÇO

    int tecla = getch();
    return tecla;
}

main()
{
    List *lista = createList();
    DataNode data;

    //DATA DE HOJE
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    bool control = true;

    system("cls");

    do
    {
        system("cls");
        // ESTRUTURA DE REPETIÇÃO
        switch (menu())
        {
        case '1':
            system("cls");
            // INSERIR COMPROMISSO
            // A CADA INSERÇÃO VAMOS DAR "SORT" ORDENADO PELA DATA

            printf("\n[COMPROMISSO]: ");
            scanf("%s", &data.description);

            printf("\n[DATA DE REALIZAÇÃO DE:] \"%s\"", data.description);
            printf("\n[DIA]: ");
            scanf("%d", &data.day);
            printf("\n[M%cS]: ", 210);
            scanf("%d", &data.month);
            printf("\n[ANO]: ");
            scanf("%d", &data.year);
            printf("\n[HOR%cRIO DO COMPROMISSO NO DIA %2d/%2d/%4d]", 181, data.day, data.month, data.year);
            printf("\n[HORA]> ");
            scanf("%d", &data.hours);
            printf("\n[´MINUTOS]> ");
            scanf("%d", &data.minutes);

            push_front(lista, data);
            // AQUI VAI O SORT()

            printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
            getch();
            break;

        case '2':
            // REMOVER COMPROMISSO
            switch (menuRemove())
            {
                system("cls");
            case '1':
                // REMOÇÃO POR DATA
                break;

            case '2':
                // REMOÇÃO POR PALAVRA
                break;

            case '0':
                // SAIR DO "menuRemove()"
                break;
            }

        case '3':
            system("cls");
            // MOSTRAR COMPROMISSOS PELA DATA
            
            /* 
                A função verifica a data informada pelo usuário é a presente nos itens da lista
                e printa caso verdadeiro.
                >> "searchDate();" << Função "void"
            */

            printf("\n[QUAL DATA DESEJA CONFERIR ?]");
            printf("\n[DIA]: ");
            scanf("%d", &data.day);
            setbuf(stdin, NULL);
            printf("\n[M%cS]: ", 210);
            scanf("%d", &data.month);
            setbuf(stdin, NULL);
            printf("\n[ANO]: ");
            scanf("%d", &data.year);
            setbuf(stdin, NULL);

            printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
            getch();
            break;

        case '4':
            system("cls");
            // ALTERAR COMPROMISSO

            /* 
                Usuário informa a data do compromisso e seleciona um ID correspondente. 
                >> "ChangeDate();" << Função "void"
            */

            printf("\n[DE QUAL DATA É O COMPORMISSO QUE DESEJA ALTERAR ?]");
            printf("\n[DIA]: ");
            scanf("%d", &data.day);
            setbuf(stdin, NULL);
            printf("\n[M%cS]: ", 210);
            scanf("%d", &data.month);
            setbuf(stdin, NULL);
            printf("\n[ANO]: ");
            scanf("%d", &data.year);
            setbuf(stdin, NULL);

            // >> "ChangeDate();"

            printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
            getch();
            break;

        case '5':
            system("cls");
            // GRAVAR ARQUIVO

            /* 
                Percorre toda a lista e insere em um arquivo; 
                >> "filePrint();" << Função "void"
            */

            break;

        case '6':
            system("cls");
            // LER ARQUIVO

            /* 
                Percorre todo o arquivo e insere em uma lista; 
                >> "fileList();" << Função retorna uma "List"
            */

            break;

        case '0':
            // SAIR DO PROGRAMA
            printf("\nVOCE FINALIZOU O PROGRAMA.\n");

            // CRÉDITOS
            printf("[REALIZADOS PELOS ALUNOS]:\n\n");
            printf("\tCASSIANO HENRIQUE APARECIDO RODRIGUES\n");
            printf("\tJO%cO PEDRO VIEIRA RODRIGUES\n", 199);
            control = false;
            break;

        default:
            break;
        }
    } while (control);

    system("pause");
}