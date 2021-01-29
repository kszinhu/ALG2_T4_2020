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
    int day, month, year, hours, minutes, id;
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
        printf("[DATA]: %d/%d/%d\n", pointer->data.day, pointer->data.month, pointer->data.year);
        printf("[HOR%cRIO]: %d:%d\n", 181, pointer->data.hours, pointer->data.minutes);
        printf("\n");
        pointer = pointer->next;
    }
}

void pListDate(List *list, DataNode data)
{
    int count = 0;
    if (isEmpty(list))
    {
        printf("\n[SEM COMPROMISSOS]\n");
        return;
    }

    Node *pointer = atPos(list, 0);
    while (pointer != NULL)
    {
        if (pointer->data.day == data.day && pointer->data.month == data.month && pointer->data.year == data.year)
        {
            printf(" %c [ID]: %d\n", 254, pointer->data.id);
            printf("[COMPROMISSO]: %s\n", pointer->data.description);
            printf("[DATA]: %d/%d/%d\n", pointer->data.day, pointer->data.month, pointer->data.year);
            printf("[HOR%cRIO]: %d:%d\n", 181, pointer->data.hours, pointer->data.minutes);
            printf("\n");
        }
        pointer = pointer->next;
        count++;
    }

    if (count == 0)
    {
        printf("\n[SEM COMPROMISSOS NA DATA]\n");
    }
}

void pListDesc(List *list, DataNode data)
{
    int count = 0;
    if (isEmpty(list))
    {
        printf("\n[SEM COMPROMISSOS]\n");
        return;
    }

    Node *pointer = atPos(list, 0);
    while (pointer != NULL)
    {
        if (strstr(pointer->data.description, data.description) != NULL)
        {
            printf(" %c [ID]: %d\n", 254, pointer->data.id);
            printf("[COMPROMISSO]: %s\n", pointer->data.description);
            printf("[DATA]: %d/%d/%d\n", pointer->data.day, pointer->data.month, pointer->data.year);
            printf("[HOR%cRIO]: %d:%d\n", 181, pointer->data.hours, pointer->data.minutes);
            printf("\n");
            count++;
        }
        pointer = pointer->next;
    }
    if (count == 0)
    {
        printf("\n[NENHUM COMPROMISSO FOI ENCONTRADO COM \"%s\"]\n", data.description);
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

Node *searchID(DataNode data, List *list)
{
    Node *pointer = atPos(list, 0);
    /* Forma interativa:
     for (; pointer != NULL; pointer = pointer->next)
    {
        if (pointer->data.id == data.id)
        {
            return pointer;
        }
    }
    return pointer;
    */
    if (pointer == NULL)
    {
        // RETORNA PONTEIRO NULO, NECESSÁRIO VERIFICAÇÃO
        return pointer;
    }
    if (pointer->data.id == data.id)
    {
        return pointer;
    }

    list->head = pointer->next;
    return searchID(data, list);
}

void insertionSort(DataNode data, List *list)
{
    Node *pointer = list->head;
    Node *i;
    Node *j;
    for (i = list->head; i->next != NULL; i = i->next)
    {
        Node *menor = i;
        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->data.year < menor->data.year)
            {
                menor = j;
            }

            else if (j->data.year == menor->data.year)
            {

                if (j->data.month < menor->data.month)
                {
                    menor = j;
                }

                else if (j->data.month == menor->data.month)
                {

                    if (j->data.day < menor->data.day)
                    {
                        menor = j;
                    }

                    else if (j->data.day == menor->data.day)
                    {

                        if (j->data.hours < menor->data.hours)
                        {
                            menor = j;
                        }

                        else if (j->data.hours == menor->data.hours)
                        {
                            if (j->data.minutes <= menor->data.minutes)
                            {
                                menor = j;
                            }
                        }
                    }
                }
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

List *fileList(char *fileName)
{
    FILE *arquivo;
    DataNode tempdata;
    List *list = createList();
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
        id: 3
    */

    for (i = 0; i < 4; i++) // PULAR AS 4 LINHAS DE HEADER
    {
        while (fgetc(arquivo) != '\n')
            ;
    }

    while (!feof(arquivo))
    {
        // LEITURA DE LINHA
        fscanf(arquivo, "description: %[^\n]s", tempdata.description);
        while (fgetc(arquivo) != '\n')
            ;
        printf("description: %s\n", tempdata.description);
        fscanf(arquivo, "date: %d/%d/%d", &tempdata.day, &tempdata.month, &tempdata.year);
        while (fgetc(arquivo) != '\n')
            ;
        printf("date: %d/%d/%d\n", tempdata.day, tempdata.month, tempdata.year);
        fscanf(arquivo, "schedule: %d:%d", &tempdata.hours, &tempdata.minutes);
        while (fgetc(arquivo) != '\n')
            ;
        printf("schedule: %d:%d\n", tempdata.hours, tempdata.minutes);
        fscanf(arquivo, "id: %d\n", &tempdata.id);
        printf("id: %d\n", tempdata.id);

        // CONVERTENDO EM LISTA
        // OBRIGADO XILSU, DAVIZERA E MODSCLEO3+1
        push_front(list, tempdata);
    }
    // COMO JÁ ESTÁ EM SORT A LISTA NÃO NECESSITA SER ORDENADA NOVAMENTE
    // ACABAMOS DE LER O ARQUIVO, PORTANTO FECHAMOS O ARQUIVO
    fclose(arquivo);

    return list;
}

bool checkDate(DataNode data)
{
    //DATA DE HOJE
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    // VERIFICAÇÃO SE O FORMATO É CORRETO
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

    // VERIFICAR SE A DATA NÃO EXCEDE A DE HOJE
    if ((data.year < tm.tm_year + 1900) || ((data.year == tm.tm_year + 1900) && (data.month < tm.tm_mon + 1)) || ((data.year == tm.tm_year + 1900) && (data.month == tm.tm_mon + 1) && (data.day < tm.tm_mday)))
    {
        printf("a");
        return false;
    }
    return true;
}

//--- SCREEN

int menu()
{
    //DATA DE HOJE
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

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
    printf("\t     .----------------------------.\n");
    printf("\t     |     -- DATA DE HOJE --     |\n");
    printf("\t     |        %2d/%2d/%4d          |\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("\t     |                            |\n");
    printf("\t     '----------------------------'\n");

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
    int dia, mes, ano;

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
            printf("\n + [COMPROMISSO]: ");
            gets(data.description);

            printf("\n[DATA DE REALIZA%c%cO DE: \"%s\"]", 128, 199, data.description);
            printf("\n + [DIA]: ");
            scanf("%d", &data.day);
            setbuf(stdin, NULL);
            printf("\n + [M%cS]: ", 210);
            scanf("%d", &data.month);
            setbuf(stdin, NULL);
            printf("\n + [ANO]: ");
            scanf("%d", &data.year);
            setbuf(stdin, NULL);

            if (!checkDate(data))
            {
                printf("\n[VOC%c ALOCOU UMA DATA ERRADA]", 210);
                printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                getch();
                break;
            }

            printf("\n[HOR%cRIO DO COMPROMISSO NO DIA %d/%d/%d]", 181, data.day, data.month, data.year);
            printf("\n + [HORA]> ");
            scanf("%d", &data.hours);
            setbuf(stdin, NULL);
            printf("\n + [MINUTOS]> ");
            scanf("%d", &data.minutes);
            setbuf(stdin, NULL);

            /* 
                CONFIRMAÇÃO SE A DATA FOR VÁLIDA:
                - VERIFICA SE NÃO É PASSADO; (ANTERIOR A DATA ATUAL)
                - VERIFICA SE NÃO EXISTE DATA EXISTENTE. (30/02/X)
                >> "checkDate();" retorna "bool" - TRUE or FALSE 
            */

            data.id = lista->size + 1;
            // ID SERÁ DISTINTO PARA CADA COMPROMISSO, NÃO SERÁ UM ITEM A SER ORDENADO

            push_front(lista, data);
            insertionSort(data, lista);

            printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
            getch();
            break;

        case '2':
            setbuf(stdin, NULL);
            system("cls");
            // REMOVER COMPROMISSO
            switch (menuRemove())
            {
                system("cls");
            case '1':
                system("cls");
                // REMOÇÃO POR DATA

                /* 
                    Usuário passa a data do compromisso na qual deseja remover, 
                    aparecerá uma lista de compromissos que acontecerá na data e após selecionar
                    irá ser acionado a função de remover determinado index.
                    >> Erase();

                */
                printf("[REMOVER COMPROMISSO PELA DATA]\n");
                printf("\n[EM QUAL DATA %c O COMPROMISSO QUE DESEJA REMOVER ?]", 144);
                printf("\n - [DIA]: ");
                scanf("%d", &data.day);
                setbuf(stdin, NULL);
                printf("\n - [M%cS]: ", 210);
                scanf("%d", &data.month);
                setbuf(stdin, NULL);
                printf("\n - [ANO]: ");
                scanf("%d", &data.year);
                setbuf(stdin, NULL);

                pListDate(lista, data);
                printf("\n[QUAL ID DESEJA REMOVER ?]\n");
                printf("\n[CASO N%cO DESEJA REMOVER, DIGITE \"999\"]\n", 199);
                printf("\n - [ID]: ");
                scanf("%d", &data.id);
                if (data.id != 999)
                {
                    /* 
                        "searchID" RETORNA O "NODE" PARA O "indexOf" CAPTURANDO 
                        O ÍNDICE E ENVIAR PARA REMOÇÃO  
                    */
                    erase(lista, indexOf(lista, searchID(data, lista)));
                }

                printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
                getch();
                break;

            case '2':
                // REMOÇÃO POR PALAVRA

                /* 
                    USUÁRIO INFORMA PALAVRA QUE DESEJA PROCURAR, 
                    CASO ACHE A PALAVRA, PRINTA A LISTA COM O ID
                    >> pListDesc(lista,data);
                    E O USUÁRIO INFORMA O ID DO COMPROMISSO QUE DE-
                    SEJA EXCLUIR, CHAMANDO A FUNÇÃO "seachID()" QUE
                    RETORNA O "NODE" (PONTEIRO)
                    CASO CONTRÁRIO RETORNA NULL (NECESSITA VERIFICAÇÃO)
                */

                printf("[REMOVER COMPROMISSO POR PALAVRA]\n");
                printf("\n[QUAL PALAVRA DESEJA PROCURAR ?]\n");
                printf("\n - [PALAVRA]: ");
                scanf("%s", &data.description);
                setbuf(stdin, NULL);

                pListDesc(lista, data);
                printf("\n[QUAL ID DESEJA REMOVER ?]\n");
                printf("\n[CASO NAO DESEJA REMOVER, DIGITE \"999\"]\n");
                printf("\n - [ID]: ");
                scanf("%d", &data.id);
                setbuf(stdin, NULL);
                if (data.id != 999)
                {
                    /* 
                        "searchID" RETORNA O "NODE" PARA O "indexOf" PEGAR 
                        O ÍNDICE E ENVIAR PARA REMOÇÃO  
                    */
                    erase(lista, indexOf(lista, searchID(data, lista)));
                }

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
            printf("\n %c [DIA]: ", 254);
            scanf("%d", &data.day);
            setbuf(stdin, NULL);
            printf("\n %c [M%cS]: ", 254, 210);
            scanf("%d", &data.month);
            setbuf(stdin, NULL);
            printf("\n %c [ANO]: ", 254);
            scanf("%d", &data.year);
            setbuf(stdin, NULL);

            pListDate(lista, data);
            /* printList(lista); */

            printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
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
            printf("\n * [DIA]: ");
            scanf("%d", &data.day);
            setbuf(stdin, NULL); // LIMPA BUFFER DE ENTRADA
            printf("\n * [M%cS]: ", 210);
            scanf("%d", &data.month);
            setbuf(stdin, NULL);
            printf("\n * [ANO]: ");
            scanf("%d", &data.year);
            setbuf(stdin, NULL);

            // >> "ChangeDate();"

            printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
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
            printf("\n = [NOME DO ARQUIVO]: ");
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
            printf("\n = [NOME DO ARQUIVO]: ");
            scanf("%s", &fileName);
            setbuf(stdin, NULL);
            strcat(fileName, ".txt");

            lista = fileList(fileName);
            printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
            getch();
            break;

        case '0':
            setbuf(stdin, NULL);
            system("cls");
            // SAIR DO PROGRAMA
            printf("\n :( VOCE FINALIZOU O PROGRAMA.\n");

            // CRÉDITOS
            printf("\n[REALIZADOS PELOS ALUNOS]:\n\n");
            printf("\tCASSIANO HENRIQUE APARECIDO RODRIGUES\n");
            printf("\tJO%cO PEDRO VIEIRA RODRIGUES\n", 199);

            printf("\n[PRESSIONE QUALQUER TECLA PARA SAIR]\n");
            getch();
            control = false;
            break;

        default:
            break;
        }
    } while (control);

    system("pause");
}