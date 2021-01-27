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
    int id;
} DataNode;

typedef struct node
{
    DataNode data;
    struct node *next;
} Node;

typedef struct list
{
    Node *head;
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

void xchgNodes(List *list, Node *nodeA, Node *nodeB); // Trocar dois nós

Node *min(List *list, int index); // Acha nó mínimo

Node *max(List *list, int index); // Acha o nó máximo

void incSort(List *list);

void decSort(List *list);

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
        printf("Lista Vazia\n");
        return;
    }

    Node *pointer = list->head;

    while (pointer != NULL)
    {
        printf("%d", pointer->data.id);
        pointer = pointer->next;
        printf(" ");
    }
    printf("\n");
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

void xchgNodes(List *list, Node *nodeA, Node *nodeB)
{
    if (nodeA == nodeB)
    {
        return;
    }

    int indexA = indexOf(list, nodeA);
    int indexB = indexOf(list, nodeB);

    if (indexA == -1 || indexB == -1)
    {
        return;
    }

    if (indexA > indexB)
    {
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }
    Node *pb = atPos(list, indexB - 1);

    if (nodeA == list->head)
    {
        list->head = nodeB;
    }
    else
    {
        Node *pa = atPos(list, indexA - 1);
        pa->next = nodeB;
    }

    pb->next = nodeA;

    Node *pointer = nodeA->next;

    nodeA->next = nodeB->next;
    nodeB->next = pointer;
}

Node *min(List *list, int index)
{
    Node *pointer = atPos(list, index);

    if (pointer != NULL)
    {
        Node *minNode = pointer;

        while (pointer != NULL)
        {
            if (pointer->data.id < minNode->data.id)
            {
                minNode = pointer;
            }
            pointer = pointer->next;
        }
        return minNode;
    }
}

Node *max(List *list, int index)
{
    Node *pointer = atPos(list, index);

    if (pointer != NULL)
    {
        Node *maxNode = pointer;

        while (pointer != NULL)
        {
            if (pointer->data.id > maxNode->data.id)
            {
                maxNode = pointer;
            }
            pointer = pointer->next;
        }
        return maxNode;
    }
}

void incSort(List *list)
{
    int i;

    for (i = 0; i < list->size - 1; i++)
    {
        xchgNodes(list, atPos(list, i), min(list, i));
    }
}

void decSort(List *list)
{
    int i;

    for (i = 0; i < list->size - 1; i++)
    {
        xchgNodes(list, atPos(list, i), max(list, i));
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
    if (pointer->data.id == info)
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
            if (j->data.id < menor->data.id)
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
            if (current->data.id == search_for)
                count++;
            current = current->next;
        }
        return count;
    }
    return 0;
}

main()
{
    List *lista = createList();
    DataNode data;

    //DATA DE HOJE
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    int aux, a=1;

    system("cls");
    printf("  -------------------------------\n");
    printf(" | 1. Inserir elmento            |\n");
    printf(" | 2. Remover elemento           |\n");
    printf(" | 3. Mostrar produtos vencidos  |\n");
    printf(" | 4. Gerar arquino binario      |\n");
    printf(" | 5. Sair do programa           |\n");
    printf("  -------------------------------\n");

    printf("\n");
    
    while(a!=0){
    
    scanf("%d",&aux);
    switch (aux){
    case 1:
        //inserir compromisso
        break;
    
    case 2:
        //remover compromisso usando data
        break;
    
    case 3:
        //remover compromisso especifico
        break;
    
    case 4:
        //consulta de compromissos
        break;

    case 5:
        //procurar compromissos com a palavra
        break;
    
    case 6:
        //alterar compromisso com uma palavra especifica
        break;
    
    case 7:
        //altera compromisso de uma data especifica
        break;

    case 8:
        //salva no disco os compromissos
        break;

    case 9:
        //le compromissos no disco
        break;

    case 10:
        
        printf("\nVoce finalizou o programa.\n");
        a=0;
        
        break;
    }
}

    system("pause");
}