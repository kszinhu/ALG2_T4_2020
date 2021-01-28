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
    int id, day, month, year, hours, minutes;
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

Node *search(DataNode info, List *list);

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

void pListDate(List *list, DataNode data)
{
}

void pListDesc(List *list, DataNode data)
{

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

Node *search(DataNode info, List *list)
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
        // RETORNA PONTEIRO NULO, NECESSÁRIO VERIFICAÇÃO
        return pointer;
    }
    if ((pointer->data.day == info.day) && (pointer->data.month == info.month) && (pointer->data.year == info.year))
    {
        return pointer;
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

void filePrint(List *list, char *fileName)
{
    FILE *arquivo;
    DataNode tempdata;

    arquivo = fopen(fileName, "w");
    // ABRE O ARQUIVO PARA ESCRITA

    /*  COMO DEVERÁ SER O ARQUIVO
        -------------------------
	        AGENDA DO THIERRY    
        -------------------------
           COMPROMISSOS SALVOS   
        description: Médico
        date: 14/3/2002
        schedule: 00:00
    */

    // IMPRESSÃO DO HEADER

    fprintf(arquivo, "-------------------------\n");
    fprintf(arquivo, "    AGENDA DO THIERRY    \n");
    fprintf(arquivo, "-------------------------\n");
    fprintf(arquivo, "   COMPROMISSOS SALVOS   \n");

    // IMPRESSÃO DA LISTA
    if (isEmpty(list))
    {
        printf("SEM COMPROMISSO :)\n");
        return;
    }

    Node *pointer = atPos(list, 0);
    while (pointer != NULL)
    {
        fprintf(arquivo, "description: %s\n", pointer->data.description);
        fprintf(arquivo, "date: %d/%d/%d\n", pointer->data.day, pointer->data.month, pointer->data.year);
        fprintf(arquivo, "schedule: %d:%d\n", pointer->data.hours, pointer->data.minutes);
        fprintf(arquivo, "id: %d\n", pointer->data.id);
        fprintf(arquivo, "\n"); // PULAR LINHA A CADA COMPROMISSO
        pointer = pointer->next;
    }
}

List fileList(char *fileName)
{
    FILE *arquivo;
    DataNode tempdata;
    List *list;
    int i;

    arquivo = fopen(fileName, "r");
    // ABRE O ARQUIVO PARA LEITURA

    /*  COMO ESTARÁ NO ARQUIVO
        -------------------------
	        AGENDA DO THIERRY    
        -------------------------
           COMPROMISSOS SALVOS   
        description: Médico
        date: 14/3/2002
        schedule: 00:00
    */

    for (i = 0; i < 4; i++) // PULAR AS 4 LINHAS DE HEADER
    {
        while (fgetc(arquivo) != '\n')
            ;
    }

    while (!feof(arquivo))
    {
        // LEITURA DE LINHA
        fscanf(arquivo, "description: %s", tempdata.description);
        while (fgetc(arquivo) != '\n')
            ;
        fscanf(arquivo, "date: %d/%d/%d", &tempdata.day, &tempdata.month, &tempdata.year);
        while (fgetc(arquivo) != '\n')
            ;
        fscanf(arquivo, "schedule: %d:%d", &tempdata.hours, &tempdata.minutes);
        while (fgetc(arquivo) != '\n')
            ;
        // CONVERTENDO EM LISTA
        push_front(list, tempdata);
    }
    // COMO JÁ ESTÁ EM SORT A LISTA NÃO NECESSITA SER ORDENADA NOVAMENTE
    // ACABAMOS DE LER O ARQUIVO, PORTANTO FECHAMOS O ARQUIVO
    fclose(arquivo);

    return *list;
}

bool checkDate(DataNode data)
{
    //DATA DE HOJE
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    // VERIFICAR SE A DATA NÃO EXCEDE A DE HOJE
    if ((data.year < tm.tm_year + 1900) || (data.year >= tm.tm_year + 1900 && data.month < tm.tm_mon + 1) || (data.year >= tm.tm_year + 1900 && data.month >= tm.tm_mon + 1 && data.day < tm.tm_mday))
    {
        return false;
    }

    if (data.month > 12)
    {
        return false;
    }
    else if (data.month == 2)
    {
        /* 
            CASO O MÊS SEJA FEVEREIRO, VERIFICAMOS SE É ANO BISSEXTO
            SE FOR ADMITIRÁ QUE O MÊS VAI ATÉ 29 DIAS, CASO CONTRÁRIO, APENAS 28 DIAS 
        */
        if (data.year % 4 == 0)
        {
            // SE FOR ANO BISSEXTO
            if (data.day > 29)
            {
                return false;
            }
        }
        else if (data.day > 28)
        {
            return false;
        }
    }

    else if (data.month < 7)
    /* 
        CASO O MÊS VÁ DE 1 A 6, 
        TODOS OS MESES PARES VÃO ATÉ 30 DIAS 
        E ÍMPARES A 31 DIAS.
    */
    {
        if (data.month % 2 == 0)
        {
            // CASO MÊS FOR PAR
            if (data.day > 30)
            {
                return false;
            }
        }
        else if (data.day > 31)
        {
            // CASO MÊS FOR ÍMPAR
            return false;
        }
    }
    else if (data.month > 6)
    {
        /* 
            CASO O MÊS SEJA MAIOR QUE 6, TODOS OS
            ÍMPARES VÃO ATÉ DIA 30, E OS MESES PARES A DIA 31
        */
        if (data.month % 2 == 0)
        {
            // CASO MÊS FOR PAR
            if (data.day > 31)
            {
                return false;
            }
        }
        else if (data.day > 30)
        {
            // CASO MÊS FOR ÍMPAR
            return false;
        }
    }
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

    bool control = true;

    system("cls");

    do
    {
        setbuf(stdin, NULL);
        system("cls");
        // ESTRUTURA DE REPETIÇÃO
        switch (menu())
        {
        case '1':
            setbuf(stdin, NULL);
            system("cls");
            // INSERIR COMPROMISSO
            // A CADA INSERÇÃO VAMOS DAR "SORT" ORDENADO PELA DATA
            printf("[ADI%c%cO DE COMPROMISSOS]\n", 128, 199);
            printf("\n[COMPROMISSO]: ");
            gets(data.description);

            printf("\n[DATA DO COMPROMISSO: \"%s\"]\n", data.description);
            printf("\n + [DIA]: ");
            scanf("%d", &data.day);
            printf("\n + [M%cS]: ", 210);
            scanf("%d", &data.month);
            printf("\n + [ANO]: ");
            scanf("%d", &data.year);
            printf("\n[HOR%cRIO DO COMPROMISSO NO DIA %d/%d/%d]\n", 181, data.day, data.month, data.year);
            printf("\n + [HORA]: ");
            scanf("%d", &data.hours);
            printf("\n + [MINUTOS]: ");
            scanf("%d", &data.minutes);

            /* 
                CONFIRMAÇÃO SE A DATA FOR VÁLIDA:
                - VERIFICA SE NÃO É PASSADO; (ANTERIOR A DATA ATUAL)
                - VERIFICA SE NÃO EXISTE DATA EXISTENTE. (30/02/X)
                >> "checkDate();" retorna "bool" - TRUE or FALSE 
            */

            if (!checkDate(data))
            {
                printf("\n[VOC%c ALOCOU UMA DATA INV%cLIDA]\n", 210, 181);
                printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                getch();
                break;
            }

            data.id = lista->size + 1;
            // ID SERÁ DISTINTO PARA CADA COMPROMISSO, NÃO SERÁ UM ITEM A SER ORDENADO

            push_front(lista, data);
            // AQUI VAI O SORT()

            printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
            getch();
            break;

        case '2':
            setbuf(stdin, NULL);
            // REMOVER COMPROMISSO
            switch (menuRemove())
            {
                system("cls");
            case '1':
                // REMOÇÃO POR DATA
                int index;

                /* 
                    Usuário passa a data do compromisso na qual deseja remover, 
                    aparecerá uma lista de compromissos que acontecerá na data e após selecionar
                    irá ser acionado a função de remover determinado index.
                    >> Erase();
                */

                printf("[REMOVER COMPROMISSO PELA DATA]\n");
                printf("\n[EM QUAL DATA %c O COMPROMISSO QUE DESEJA REMOVER ?]\n", 144);
                printf("\n[DIA]: ", 210);
                scanf("%d", &data.day);
                setbuf(stdin, NULL);
                printf("\n[M%cS]: ");
                scanf("%d", &data.month);
                setbuf(stdin, NULL);
                printf("\n[ANO]: ");
                scanf("%d", &data.year);
                setbuf(stdin, NULL);

                // >>printListDate(lista, data);
                // FUNÇÃO RETORNA O PONTEIRO QUE APONTA PARA A INFORMAÇÃO

                /* 
                printListDate(lista, data);

                if (pointer == NULL)
                {
                    printf("\n[N%cO ENCONTRADO]\n");
                    printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                    getch();
                    break;
                }
                index = indexOf(lista, pointer);

                */
                printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                getch();
                break;

            case '2':
                // REMOÇÃO POR PALAVRA

                int index;

                /* 
                    USUÁRIO INFORMA PALAVRA QUE DESEJA PROCURAR, 
                    CASO ACHE A PALAVRA, RETORNA O PONTEIRO
                    CASO CONTRÁRIO RETORNA NULL (NECESSITA VERIFICAÇÃO)
                    >> pListDesc(lista,data);
                    PRINTAMOS OS ELEMENTOS DA LISTA QUE CONTÉM A PALA-
                    VRA E O USUÁRIO INFORMA O ID DO COMPROMISSO QUE DE-
                    SEJA EXCLUIR
                */

                printf("[REMOVER COMPROMISSO POR PALAVRA]\n");
                printf("\n[QUAL PALAVRA DESEJA PROCURAR ?]\n");
                printf("\n[PALAVRA]: ");
                scanf("%s", &data.description);
                setbuf(stdin, NULL);

                // >>pListDesc(lista, data);
                // FUNÇÃO RETORNA O PONTEIRO QUE APONTA PARA A INFORMAÇÃO

                /*
                if (pointer == NULL)
                {
                    printf("\n[N%cO ENCONTRADO]\n");
                    printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                    getch();
                    break;
                }
                index = indexOf(lista, pointer);
                */
                printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                getch();

                break;

            case '0':
                // SAIR DO "menuRemove()"
                break;
            }

        case '3':
            setbuf(stdin, NULL);
            system("cls");
            // MOSTRAR COMPROMISSOS PELA DATA

            /* 
                A função verifica a data informada pelo usuário é a presente nos itens da lista
                e printa caso verdadeiro.
                >> "searchDate();" << Função "void"
            */
            printf("[MOSTRAR COMPROMISSOS]\n");
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
            setbuf(stdin, NULL);
            system("cls");
            // ALTERAR COMPROMISSO

            /* 
                Usuário informa a data do compromisso e seleciona um ID correspondente. 
                >> "ChangeDate();" << Função "void"
            */
            printf("[ALTERAR COMPROMISSO]\n");
            printf("\n[DE QUAL DATA É O COMPORMISSO QUE DESEJA ALTERAR ?]");
            printf("\n[DIA]: ");
            scanf("%d", &data.day);
            setbuf(stdin, NULL); // LIMPA BUFFER DE ENTRADA
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
            setbuf(stdin, NULL);
            system("cls");
            // GRAVAR ARQUIVO

            /* 
                Percorre toda a lista e insere em um arquivo; 
                >> "filePrint();" << Função "void"
            */
            char fileName[20];

            printf("[GRAVAR ARQUIVO BACKUP]\n");
            printf("\n[QUAL NOME DO ARQUIVO QUE DESEJA CRIAR ?]");
            printf("\n[NOME DO ARQUIVO]: ");
            scanf("%s", &fileName);
            strcat(fileName, ".txt");

            filePrint(lista, fileName);
            break;

        case '6':
            setbuf(stdin, NULL);
            system("cls");
            // LER ARQUIVO

            /* 
                Percorre todo o arquivo, capturando as informações
                e insere em uma Lista; 
                >> "fileList();" << Função retorna uma "List"
                Após returna uma "List" será atribuída a Lista vigente no código
            */

            printf("[LER ARQUIVO BACKUP]\n");
            printf("\n[QUAL ARQUIVO DESEJA LER ?]");
            printf("\n[NOME DO ARQUIVO]: ");
            scanf("%s", &fileName);
            strcat(fileName, ".txt");

            *lista = fileList(fileName);
            break;

        case '0':
            setbuf(stdin, NULL);
            system("cls");
            // SAIR DO PROGRAMA
            printf("\nVOCE FINALIZOU O PROGRAMA.\n");

            // CRÉDITOS
            printf("[REALIZADOS PELOS ALUNOS]:\n\n");
            printf("\tCASSIANO HENRIQUE APARECIDO RODRIGUES\n");
            printf("\tJO%cO PEDRO VIEIRA RODRIGUES\n", 199);

            printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
            getch();
            control = false;
            break;

        default:
            break;
        }
    } while (control);

    system("pause");
}