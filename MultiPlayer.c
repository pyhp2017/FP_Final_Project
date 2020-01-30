#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HeaderFiles\\Menu.h"
#include "HeaderFiles\\RandString.h"
#define ADDRESS "MAPS\\map6.bin"
//Global Variables and Arrays
char grid[100][100];
char cellsA[100][100];
char cellsB[100][100];
int EnergyBlocks[100][100];
int CellID_A = 1;
int CellID_B = 1;
int n;

enum blocks //Enum For Blocks
{
    ENERGY = 1,
    MITOSIS,
    FORBIDDEN,
    NORMAL
};

struct cell_A //Struct For cells
{
    int id;
    int x, y;
    char Name[32];
    int EnergyCell;
    struct cell_A *next;
};
struct cell_A *startA = NULL, *tmpA = NULL; //  start is header of linked list

struct cell_B //Struct For cells
{
    int id;
    int x, y;
    char Name[32];
    int EnergyCell;
    struct cell_B *next;
};
struct cell_B *startB = NULL, *tmpB = NULL; //  start is header of linked list

void insert_end_A(int n)
{
    char *Name;
    int x, y, xrand, yrand;
    struct cell_A *new_node, *ptr;
    new_node = (struct cell_A *)malloc(sizeof(struct cell_A));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    while (1)
    {
        xrand = rand() % n;
        yrand = rand() % n;
        if (grid[xrand][yrand] != 'F' && cellsA[xrand][yrand] != 'A' && cellsB[xrand][yrand] != 'B')
        {
            // Put single cell in grid
            x = xrand;
            y = yrand;
            cellsA[x][y] = 'A';
            break;
        }
    }
    new_node->id = CellID_A;
    CellID_A++;
    strcpy(new_node->Name, Name);
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 0;
    new_node->next = NULL;
    if (startA == NULL) // FIrst time
    {
        startA = new_node;
    }
    else
    {
        ptr = startA;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

void insert_end_B(int n)
{
    char *Name;
    int x, y, xrand, yrand;
    struct cell_B *new_node, *ptr;
    new_node = (struct cell_B *)malloc(sizeof(struct cell_B));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    while (1)
    {
        xrand = rand() % n;
        yrand = rand() % n;
        if (grid[xrand][yrand] != 'F' && cellsA[xrand][yrand] != 'A' && cellsB[xrand][yrand] != 'B')
        {
            // Put single cell in grid
            x = xrand;
            y = yrand;
            cellsB[x][y] = 'B';
            break;
        }
    }
    new_node->id = CellID_B;
    CellID_B++;
    strcpy(new_node->Name, Name);
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 0;
    new_node->next = NULL;
    if (startB == NULL) // FIrst time
    {
        startB = new_node;
    }
    else
    {
        ptr = startB;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// Insert to the end of linked list when you want split (for one of the cells that dosen't change location)
void insert_split_witoutrand_A(int x, int y)
{
    char *Name;
    struct cell_A *new_node, *ptr;
    new_node = (struct cell_A *)malloc(sizeof(struct cell_A));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    new_node->id = CellID_A;
    CellID_A++;
    strcpy(new_node->Name, Name);
    cellsA[x][y] = 'A';
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (startA == NULL) // FIrst time
    {
        startA = new_node;
    }
    else
    {
        ptr = startA;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}
void insert_split_witoutrand_B(int x, int y)
{
    char *Name;
    struct cell_B *new_node, *ptr;
    new_node = (struct cell_B *)malloc(sizeof(struct cell_B));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    new_node->id = CellID_B;
    CellID_B++;
    strcpy(new_node->Name, Name);
    cellsB[x][y] = 'B';
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (startB == NULL) // FIrst time
    {
        startB = new_node;
    }
    else
    {
        ptr = startB;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// Insert to the end of the linked list when you want to split with random location around that cell
void insert_Split_RandAtraf_A(int n, int x, int y)
{
    char *Name;
    int xfinal, yfinal, xrand, yrand;
    struct cell_A *new_node, *ptr;
    new_node = (struct cell_A *)malloc(sizeof(struct cell_A));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    while (1)
    {
        xrand = (rand() % 3) - 1;
        yrand = (rand() % 3) - 1;
        if (xrand == 0 || yrand == 0)
        {
            continue;
        }
        int X1 = x + xrand;
        int Y1 = y + yrand;
        if (X1 >= 0 && X1 < n && Y1 >= 0 && Y1 < n && grid[X1][Y1] != 'F' && cellsA[X1][Y1] != 'A' && cellsB[X1][Y1] != 'B')
        {
            xfinal = X1;
            yfinal = Y1;
            cellsA[X1][Y1] = 'A';
            break;
        }
        else
        {
            continue;
        }
    }
    new_node->id = CellID_A;
    CellID_A++;
    strcpy(new_node->Name, Name);
    new_node->x = xfinal;
    new_node->y = yfinal;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (startA == NULL) // FIrst time
    {
        startA = new_node;
    }
    else
    {
        ptr = startA;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}
void insert_Split_RandAtraf_B(int n, int x, int y)
{
    char *Name;
    int xfinal, yfinal, xrand, yrand;
    struct cell_B *new_node, *ptr;
    new_node = (struct cell_B *)malloc(sizeof(struct cell_B));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    while (1)
    {
        xrand = (rand() % 3) - 1;
        yrand = (rand() % 3) - 1;
        if (xrand == 0 || yrand == 0)
        {
            continue;
        }
        int X1 = x + xrand;
        int Y1 = y + yrand;
        if (X1 >= 0 && X1 < n && Y1 >= 0 && Y1 < n && grid[X1][Y1] != 'F' && cellsA[X1][Y1] != 'A' && cellsB[X1][Y1] != 'B')
        {
            xfinal = X1;
            yfinal = Y1;
            cellsB[X1][Y1] = 'B';
            break;
        }
        else
        {
            continue;
        }
    }
    new_node->id = CellID_B;
    CellID_B++;
    strcpy(new_node->Name, Name);
    new_node->x = xfinal;
    new_node->y = yfinal;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (startB == NULL) // FIrst time
    {
        startB = new_node;
    }
    else
    {
        ptr = startB;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// Put N , F , E , M in grid and read Binary File
void PutINGride()
{
    FILE *fpin = fopen(ADDRESS, "rb");
    fread(&n, sizeof(int), 1, fpin);
    int pos;
    char map[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fread(&map[i][j], sizeof(unsigned char), 1, fpin);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pos = map[i][j] - '0';
            if (pos == ENERGY)
            {
                grid[i][j] = 'E';
                EnergyBlocks[i][j] = 100;
                // break;
            }
            else if (pos == MITOSIS)
            {
                grid[i][j] = 'M';
                // break;
            }
            else if (pos == FORBIDDEN)
            {
                grid[i][j] = 'F';
                // break;
            }
            else if (pos == NORMAL)
            {
                grid[i][j] = 'N';
                // break;
            }
        }
    }
    fclose(fpin);
}

// Count Linked list Nodes
int countA(struct cell_A *start)
{
    int count;
    struct cell_A *trace = start;
    while (trace != NULL)
    {
        count++;
        trace = trace->next;
    }
    return count;
}
int countB(struct cell_B *start)
{
    int count;
    struct cell_B *trace = start;
    while (trace != NULL)
    {
        count++;
        trace = trace->next;
    }
    return count;
}

//Score
void ScoreA(struct cell_A *start)
{
    int Scoretotal;
    struct cell_A *trace = start;
    while (trace != NULL)
    {
        Scoretotal += trace->EnergyCell;
        trace = trace->next;
    }
    printf("\n\n\t\t\t Total Score for PLAYER A: %d", Scoretotal);
}
void ScoreB(struct cell_B *start)
{
    int Scoretotal;
    struct cell_B *trace = start;
    while (trace != NULL)
    {
        Scoretotal += trace->EnergyCell;
        trace = trace->next;
    }
    printf("\n\t\t\t Total Score for PLAYER B: %d", Scoretotal);
}

// Swap Elements
void swap(int *X, int *Y)
{
    int temp;
    temp = *X;
    *X = *Y;
    *Y = temp;
}

// Display Linked list Nodes
void displayA(struct cell_A *start)
{
    struct cell_A *trace = start;
    while (trace != NULL)
    {
        printf("\n[%d] %s (%d,%d) - Energy = %d -- BLOCK ENERGY = %d", trace->id, trace->Name, trace->x, trace->y, trace->EnergyCell, EnergyBlocks[trace->x][trace->y]);
        trace = trace->next;
    }
    printf("\n");
}
void displayB(struct cell_B *start)
{
    struct cell_B *trace = start;
    while (trace != NULL)
    {
        printf("\n[%d] %s (%d,%d) - Energy = %d -- BLOCK ENERGY = %d", trace->id, trace->Name, trace->x, trace->y, trace->EnergyCell, EnergyBlocks[trace->x][trace->y]);
        trace = trace->next;
    }
    printf("\n");
}

// Find and Return a Node in Linked List
struct cell_A *searchA(struct cell_A *begin, int id)
{
    struct cell_A *move = begin;
    while (move != NULL)
    {
        if (move->id == id)
        {
            return move;
        }

        move = move->next;
    }
    return NULL;
}
struct cell_B *searchB(struct cell_B *begin, int id)
{
    struct cell_B *move = begin;
    while (move != NULL)
    {
        if (move->id == id)
        {
            return move;
        }

        move = move->next;
    }
    return NULL;
}

// Draw Grid and Change Background Colors :)
void drawgrid(int n)
{
    printf("*");
    for (int z = 0; z < n; z++)
    {
        printf("    %d", z);
    }
    printf("\n");

    for (int j = n - 1; j >= 0; j--)
    {
        printf("   ");
        for (int z = 0; z < n; z++)
        {
            printf("_____");
        }
        printf("\n");
        printf("%d  ", j);
        for (int i = 0; i < n; i++)
        {
            if (grid[i][j] == 'E')
            {
                printf("\x1b[42m");
            }
            else if (grid[i][j] == 'N')
            {
                printf("\x1b[30;47m");
            }
            else if (grid[i][j] == 'F')
            {
                printf("\x1b[41m");
            }
            else if (grid[i][j] == 'M')
            {
                printf("\x1b[44m");
            }
            else
            {
                printf("\x1b[0m");
            }
            if (cellsA[i][j] == 'A')
            {
                /* code */
                printf("| %c |", cellsA[i][j]);
            }
            else if (cellsB[i][j] == 'B')
            {
                printf("| %c |", cellsB[i][j]);
            }
            else
            {
                printf("|   |");
            }
        }
        printf("\x1b[0m");
        printf("\n");
    }

    printf("   ");
    for (int w = 0; w < n; w++)
    {
        printf("-----");
    }
}

// Functions to Remove a Node
// Remove Front is for remove first node
struct cell_A *removeFrontA(struct cell_A *A)
{
    if (A == NULL)
    {
        return NULL;
    }
    struct cell_A *front = A;
    A = A->next;
    front->next = NULL;
    if (A == front)
    {
        A = NULL;
    }
    free(front);
    return A;
}
struct cell_B *removeFrontB(struct cell_B *A)
{
    if (A == NULL)
    {
        return NULL;
    }
    struct cell_B *front = A;
    A = A->next;
    front->next = NULL;
    if (A == front)
    {
        A = NULL;
    }
    free(front);
    return A;
}
struct cell_A *RemoveAnyA(struct cell_A *head, struct cell_A *temp)
{
    if (temp == NULL)
    {
        return NULL;
    }
    if (temp == head)
    {
        return removeFrontA(head);
    }

    struct cell_A *move = head;
    while (move != NULL)
    {
        if (move->next == temp)
        {
            break;
        }
        move = move->next;
    }
    if (move != NULL)
    {
        struct cell_A *Movagat = move->next;
        move->next = Movagat->next;
        Movagat->next = NULL;
        free(Movagat);
    }

    return head;
}
struct cell_B *RemoveAnyB(struct cell_B *head, struct cell_B *temp)
{
    if (temp == NULL)
    {
        return NULL;
    }
    if (temp == head)
    {
        return removeFrontB(head);
    }

    struct cell_B *move = head;
    while (move != NULL)
    {
        if (move->next == temp)
        {
            break;
        }
        move = move->next;
    }
    if (move != NULL)
    {
        struct cell_B *Movagat = move->next;
        move->next = Movagat->next;
        Movagat->next = NULL;
        free(Movagat);
    }

    return head;
}
//Functions to Read Linked List from binaryFile
struct cell_A *ReadNextFromFileA(struct cell_A *start, FILE *pFile)
{
    size_t returnValue;
    if (start == NULL)
    {
        start = malloc(sizeof(struct cell_A));
        returnValue = fread(start, sizeof(struct cell_A), 1, pFile);
        start->next = NULL;
    }
    else
    {
        struct cell_A *indexCar = start;
        struct cell_A *newCar = malloc(sizeof(struct cell_A));
        while (indexCar->next != NULL)
        {
            indexCar = indexCar->next;
        }
        returnValue = fread(newCar, sizeof(struct cell_A), 1, pFile);
        indexCar->next = newCar;
        newCar->next = NULL;
    }
    return start;
}
struct cell_A *ReadListInA(struct cell_A *start)
{
    FILE *pFile;
    pFile = fopen("SAVE_MULTI\\SavedLinkA.data", "rb");
    if (pFile != NULL)
    {

        start = NULL;
        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct cell_A)));
        // printf("numEntries:%d\n",numEntries);

        int loop = 0;
        for (loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(struct cell_A) * loop), SEEK_SET);
            start = ReadNextFromFileA(start, pFile);
        }
    }

    return start;
}
struct cell_B *ReadNextFromFileB(struct cell_B *start, FILE *pFile)
{
    size_t returnValue;
    if (start == NULL)
    {
        start = malloc(sizeof(struct cell_B));
        returnValue = fread(start, sizeof(struct cell_B), 1, pFile);
        start->next = NULL;
    }
    else
    {
        struct cell_B *indexCar = start;
        struct cell_B *newCar = malloc(sizeof(struct cell_B));
        while (indexCar->next != NULL)
        {
            indexCar = indexCar->next;
        }
        returnValue = fread(newCar, sizeof(struct cell_B), 1, pFile);
        indexCar->next = newCar;
        newCar->next = NULL;
    }
    return start;
}
struct cell_B *ReadListInB(struct cell_B *start)
{

    FILE *pFile;
    pFile = fopen("SAVE_MULTI\\SavedLinkB.data", "rb");
    if (pFile != NULL)
    {
        start = NULL;
        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct cell_B)));
        // printf("numEntries:%d\n",numEntries);

        int loop = 0;
        for (loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(struct cell_B) * loop), SEEK_SET);
            start = ReadNextFromFileB(start, pFile);
        }
    }

    return start;
}
// Function to Write Linked list on binaryFile
void WriteListToFileA(struct cell_A *start)
{
    FILE *pFile;
    pFile = fopen("SAVE_MULTI\\SavedLinkA.data", "wb+");
    if (pFile != NULL)
    {
        struct cell_A *currentCar = start;
        struct cell_A *holdNext = NULL;
        while (currentCar != NULL)
        {
            holdNext = currentCar->next;
            currentCar->next = NULL;
            fseek(pFile, 0, SEEK_END);
            fwrite(currentCar, sizeof(struct cell_A), 1, pFile);
            currentCar->next = holdNext;
            holdNext = NULL;
            currentCar = currentCar->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
}
void WriteListToFileB(struct cell_B *start)
{
    FILE *pFile;
    pFile = fopen("SAVE_MULTI\\SavedLinkB.data", "wb+");
    if (pFile != NULL)
    {
        struct cell_B *currentCar = start;
        struct cell_B *holdNext = NULL;
        while (currentCar != NULL)
        {
            holdNext = currentCar->next;
            currentCar->next = NULL;
            fseek(pFile, 0, SEEK_END);
            fwrite(currentCar, sizeof(struct cell_B), 1, pFile);
            currentCar->next = holdNext;
            holdNext = NULL;
            currentCar = currentCar->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
}

// Functions To move cell
void MoveUPA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup][Ybackup + 1] != 'F' && cellsA[Xbackup][Ybackup + 1] != 'A' && cellsB[Xbackup][Ybackup + 1] != 'B' && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpA->y = Ybackup + 1;
            cellsA[Xbackup][Ybackup + 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
    }
}
void MoveUPB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup][Ybackup + 1] != 'F' && cellsA[Xbackup][Ybackup + 1] != 'A' && cellsB[Xbackup][Ybackup + 1] != 'B' && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpB->y = Ybackup + 1;
            cellsB[Xbackup][Ybackup + 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
    }
}
void MovdeDownA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup][Ybackup - 1] != 'F' && cellsA[Xbackup][Ybackup - 1] != 'A' && cellsB[Xbackup][Ybackup - 1] != 'B' && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpA->y = Ybackup - 1;
            cellsA[Xbackup][Ybackup - 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MovdeDownB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup][Ybackup - 1] != 'F' && cellsA[Xbackup][Ybackup - 1] != 'A' && cellsB[Xbackup][Ybackup - 1] != 'B' && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpB->y = Ybackup - 1;
            cellsB[Xbackup][Ybackup - 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}

void MoveNortheastA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup + 1][Ybackup + 1] != 'F' && cellsA[Xbackup + 1][Ybackup + 1] != 'A' && cellsB[Xbackup + 1][Ybackup + 1] != 'B' && Xbackup + 1 >= 0 && Xbackup + 1 < n && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpA->x = Xbackup + 1;
            tmpA->y = Ybackup + 1;
            cellsA[Xbackup + 1][Ybackup + 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveNorthwestA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup - 1][Ybackup + 1] != 'F' && cellsA[Xbackup - 1][Ybackup + 1] != 'A' && cellsB[Xbackup - 1][Ybackup + 1] != 'B' && Xbackup - 1 >= 0 && Xbackup - 1 < n && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpA->x = Xbackup - 1;
            tmpA->y = Ybackup + 1;
            cellsA[Xbackup - 1][Ybackup + 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveSoutheastA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup + 1][Ybackup - 1] != 'F' && cellsA[Xbackup + 1][Ybackup - 1] != 'A' && cellsB[Xbackup + 1][Ybackup - 1] != 'B' && Xbackup + 1 >= 0 && Xbackup + 1 < n && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpA->x = Xbackup + 1;
            tmpA->y = Ybackup - 1;
            cellsA[Xbackup + 1][Ybackup - 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveSouthwestA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup - 1][Ybackup - 1] != 'F' && cellsA[Xbackup - 1][Ybackup - 1] != 'A' && cellsB[Xbackup - 1][Ybackup - 1] != 'B' && Xbackup - 1 >= 0 && Xbackup - 1 < n && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpA->x = Xbackup - 1;
            tmpA->y = Ybackup - 1;
            cellsA[Xbackup - 1][Ybackup - 1] = 'A';
            cellsA[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveNortheastB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup + 1][Ybackup + 1] != 'F' && cellsA[Xbackup + 1][Ybackup + 1] != 'A' && cellsB[Xbackup + 1][Ybackup + 1] != 'B' && Xbackup + 1 >= 0 && Xbackup + 1 < n && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpB->x = Xbackup + 1;
            tmpB->y = Ybackup + 1;
            cellsB[Xbackup + 1][Ybackup + 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveNorthwestB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup - 1][Ybackup + 1] != 'F' && cellsA[Xbackup - 1][Ybackup + 1] != 'A' && cellsB[Xbackup - 1][Ybackup + 1] != 'B' && Xbackup - 1 >= 0 && Xbackup - 1 < n && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmpB->x = Xbackup - 1;
            tmpB->y = Ybackup + 1;
            cellsB[Xbackup - 1][Ybackup + 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveSoutheastB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup + 1][Ybackup - 1] != 'F' && cellsA[Xbackup + 1][Ybackup - 1] != 'A' && cellsB[Xbackup + 1][Ybackup - 1] != 'B' && Xbackup + 1 >= 0 && Xbackup + 1 < n && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpB->x = Xbackup + 1;
            tmpB->y = Ybackup - 1;
            cellsB[Xbackup + 1][Ybackup - 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveSouthwestB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup - 1][Ybackup - 1] != 'F' && cellsA[Xbackup - 1][Ybackup - 1] != 'A' && cellsB[Xbackup - 1][Ybackup - 1] != 'B' && Xbackup - 1 >= 0 && Xbackup - 1 < n && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmpB->x = Xbackup - 1;
            tmpB->y = Ybackup - 1;
            cellsB[Xbackup - 1][Ybackup - 1] = 'B';
            cellsB[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}

// Boost Energy in Energy Blocks
void BoostEnergyA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        if (grid[Xbackup][Ybackup] == 'E')
        {
            if (tmpA->EnergyCell == 100)
            {
                printf("\nYou Can Not Reach More Energy !\n");
                // sleep(2);
                return;
            }
            if (EnergyBlocks[Xbackup][Ybackup] > 15)
            {
                tmpA->EnergyCell += 15;
                EnergyBlocks[Xbackup][Ybackup] -= 15;
            }
            else if (EnergyBlocks[Xbackup][Ybackup] < 15 && EnergyBlocks[Xbackup][Ybackup] >= 0)
            {
                int Tahmonda = EnergyBlocks[Xbackup][Ybackup];
                tmpA->EnergyCell += Tahmonda;
                EnergyBlocks[Xbackup][Ybackup] = 0;
                grid[Xbackup][Ybackup] = 'N';
            }
            else
            {
                printf("\nNo More Energy in Here - Empty Storage or Tank\n\n");
                // sleep(2);
            }
        }
        else
        {
            printf("\nYou Can Not Boost Energy ON %c \n\n", grid[Xbackup][Ybackup]);
            // sleep(2);
        }
    }
}
void BoostEnergyB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        if (grid[Xbackup][Ybackup] == 'E')
        {
            if (tmpB->EnergyCell == 100)
            {
                printf("\nYou Can Not Reach More Energy !\n");
                // sleep(2);
                return;
            }
            if (EnergyBlocks[Xbackup][Ybackup] > 15)
            {
                tmpB->EnergyCell += 15;
                EnergyBlocks[Xbackup][Ybackup] -= 15;
            }
            else if (EnergyBlocks[Xbackup][Ybackup] < 15 && EnergyBlocks[Xbackup][Ybackup] >= 0)
            {
                int Tahmonda = EnergyBlocks[Xbackup][Ybackup];
                tmpB->EnergyCell += Tahmonda;
                EnergyBlocks[Xbackup][Ybackup] = 0;
                grid[Xbackup][Ybackup] = 'N';
            }
            else
            {
                printf("\nNo More Energy in Here - Empty Storage or Tank\n\n");
                // sleep(2);
            }
        }
        else
        {
            printf("\nYou Can Not Boost Energy ON %c \n\n", grid[Xbackup][Ybackup]);
            sleep(2);
        }
    }
}

// Split Cell in MITOSIS Blocks
void SplitCellA(int ChosenCell)
{
    tmpA = searchA(startA, ChosenCell);
    if (tmpA != NULL)
    {
        int Xbackup = tmpA->x;
        int Ybackup = tmpA->y;
        //Check if Split is possible
        if (grid[Xbackup][Ybackup] == 'M')
        {
            //Split Code
            //check if it's possible to split
            if (tmpA->EnergyCell >= 80)
            {
                startA = RemoveAnyA(startA, tmpA);
                cellsA[Xbackup][Ybackup] = '\0';
                insert_split_witoutrand_A(Xbackup, Ybackup);
                insert_Split_RandAtraf_A(n, Xbackup, Ybackup);
            }
            else
            {
                printf("\nYour Fucking Cell Energy is too low !\n\n");
                // sleep(2);
            }
        }
        else
        {
            printf("\nYou Can Not Split ON %c\n\n", grid[Xbackup][Ybackup]);
            // sleep(2);
        }
    }
}
void SplitCellB(int ChosenCell)
{
    tmpB = searchB(startB, ChosenCell);
    if (tmpB != NULL)
    {
        int Xbackup = tmpB->x;
        int Ybackup = tmpB->y;
        //Check if Split is possible
        if (grid[Xbackup][Ybackup] == 'M')
        {
            //Split Code
            //check if it's possible to split
            if (tmpB->EnergyCell >= 80)
            {
                startB = RemoveAnyB(startB, tmpB);
                cellsB[Xbackup][Ybackup] = '\0';
                insert_split_witoutrand_B(Xbackup, Ybackup);
                insert_Split_RandAtraf_B(n, Xbackup, Ybackup);
            }
            else
            {
                printf("\nYour Fucking Cell Energy is too low !\n\n");
                // sleep(2);
            }
        }
        else
        {
            printf("\nYou Can Not Split ON %c\n\n", grid[Xbackup][Ybackup]);
            // sleep(2);
        }
    }
}

void RoundA(int flag)
{
    int NumberOfCells;
    int ChosenCell;
    int OptionList2;
    int movechosen;
    if (flag == 1)
    {
        printf("Please Enter Number of Cells For PLAYER <A>: ");
        scanf("%d", &NumberOfCells);
        for (int i = 0; i < NumberOfCells; i++)
        {
            insert_end_A(n);
        }
        return;
    }
    else
    {
        system("cls");
        drawgrid(n);
        printf("\n\t PLAYER <A> \n");
        displayA(startA);
        printf("Please choose one of your cells: ");
        scanf("%d", &ChosenCell);
        Menu1();
        printf("Please choose your option: ");
        scanf("%d", &OptionList2);
        switch (OptionList2)
        {
        case 1:
            // MOVE
            MenuMove();
            printf("Please choose your option: ");
            scanf("%d", &movechosen);

            switch (movechosen)
            {
            case 1:
                // UP Move
                MoveUPA(ChosenCell);
                break;

            case 2:
                // Down Move
                MovdeDownA(ChosenCell);
                break;

            case 3:
                // North East
                MoveNortheastA(ChosenCell);
                break;

            case 4:
                // North West
                MoveNorthwestA(ChosenCell);
                break;

            case 5:
                // South East
                MoveSoutheastA(ChosenCell);
                break;

            case 6:
                // South West
                MoveSouthwestA(ChosenCell);
                break;
            }
            break;

        case 2:
            // Split a Cell
            SplitCellA(ChosenCell);
            break;

        case 3:
            //Boost energy
            BoostEnergyA(ChosenCell);
            break;

        case 4:
            Save();
            // SaveA();
            break;

        case 5:
            ScoreA(startA);
            ScoreB(startB);
            exit(0);
            break;
        }
    }
}

void RoundB(int flag)
{
    int NumberOfCells;
    int ChosenCell;
    int OptionList2;
    int movechosen;
    if (flag == 1)
    {
        printf("Please Enter Number of Cells For PLAYER <B>: ");
        scanf("%d", &NumberOfCells);
        for (int i = 0; i < NumberOfCells; i++)
        {
            insert_end_B(n);
        }
        return;
    }
    else
    {
        system("cls");
        drawgrid(n);
        printf("\n\t PLAYER <B> \n");
        displayB(startB);
        printf("Please choose one of your cells: ");
        scanf("%d", &ChosenCell);
        Menu1();
        printf("Please choose your option: ");
        scanf("%d", &OptionList2);
        switch (OptionList2)
        {
        case 1:
            // MOVE
            MenuMove();
            printf("Please choose your option: ");
            scanf("%d", &movechosen);

            switch (movechosen)
            {
            case 1:
                // UP Move
                MoveUPB(ChosenCell);
                break;

            case 2:
                // Down Move
                MovdeDownB(ChosenCell);
                break;

            case 3:
                // North East
                MoveNortheastB(ChosenCell);
                break;

            case 4:
                // North West
                MoveNorthwestB(ChosenCell);
                break;

            case 5:
                // South East
                MoveSoutheastB(ChosenCell);
                break;

            case 6:
                // South West
                MoveSouthwestB(ChosenCell);
                break;
            }
            break;

        case 2:
            // Split a Cell
            SplitCellB(ChosenCell);
            break;

        case 3:
            //Boost energy
            BoostEnergyB(ChosenCell);
            break;

        case 4:
            //Save
            Save();
            break;

        case 5:
            ScoreA(startA);
            ScoreB(startB);
            exit(0);
            break;
        }
    }
}

// //Save Function
void Save()
{
    // Save Cells Array
    // For CellsA
    FILE *SaveCellA = fopen("SAVE_MULTI\\SavedCellsA.data", "wb+");
    fwrite(cellsA, sizeof(char), sizeof(cellsA), SaveCellA);
    fclose(SaveCellA);
    // For CellsB
    FILE *SaveCellB = fopen("SAVE_MULTI\\SavedCellsB.data", "wb+");
    fwrite(cellsB, sizeof(char), sizeof(cellsB), SaveCellB);
    fclose(SaveCellB);
    // Save EnergyBlocks Array
    FILE *SaveBlockE = fopen("SAVE_MULTI\\SavedEblock.data", "wb+");
    fwrite(EnergyBlocks, sizeof(char), sizeof(EnergyBlocks), SaveBlockE);
    fclose(SaveBlockE);
    // Save Linkedlist
    WriteListToFileA(startA);
    WriteListToFileB(startB);
    //Save Map
    FILE *SaveMAP = fopen("SAVE_MULTI\\SavedMAP.bin", "wb+");
    fwrite(&n, sizeof(int), 1, SaveMAP);
    fwrite(grid, sizeof(char), sizeof(grid), SaveMAP);
    fclose(SaveMAP);
    //Save CellID
    // Cell ID A
    FILE *SaveIDA = fopen("SAVE_MULTI\\SaveIDA", "w");
    fprintf(SaveIDA, "%d\n", CellID_A);
    fclose(SaveIDA);
    // Cell ID B
    FILE *SaveIDB = fopen("SAVE_MULTI\\SaveIDB", "w");
    fprintf(SaveIDB, "%d\n", CellID_B);
    fclose(SaveIDB);
}

// // Load Function
void load()
{
    // Load Cells Array
    // For CellsA
    FILE *SaveCellA = fopen("SAVE_MULTI\\SavedCellsA.data", "rb");
    fread(cellsA, sizeof(char), sizeof(cellsA), SaveCellA);
    fclose(SaveCellA);
    // For CellsB
    FILE *SaveCellB = fopen("SAVE_MULTI\\SavedCellsB.data", "rb");
    fread(cellsB, sizeof(char), sizeof(cellsB), SaveCellB);
    fclose(SaveCellB);
    // Load EnergyBlocks Array
    FILE *SaveBlockE = fopen("SAVE_MULTI\\SavedEblock.data", "rb");
    fread(EnergyBlocks, sizeof(char), sizeof(EnergyBlocks), SaveBlockE);
    fclose(SaveBlockE);
    //Load Linked list
    startA = ReadListInA(startA);
    startB = ReadListInB(startB);
    // Load MAP
    FILE *SaveMAP = fopen("SAVE_MULTI\\SavedMAP.bin", "rb");
    fread(&n, sizeof(int), 1, SaveMAP);
    fread(grid, sizeof(char), sizeof(grid), SaveMAP);
    fclose(SaveMAP);
    // Load Cell ID
    FILE *SaveIDA = fopen("SAVE_MULTI\\SaveIDA", "r");
    fscanf(SaveIDA, "%d", &CellID_A);
    fclose(SaveIDA);
    FILE *SaveIDB = fopen("SAVE_MULTI\\SaveIDB", "r");
    fscanf(SaveIDB, "%d", &CellID_B);
    fclose(SaveIDB);
    while (1)
    {
        RoundA(0);
        RoundB(0);
    }
}

// MAIN FUNCTION
int main()
{
    srand(time(0));
    int option;
    int flag = 1;
    enum blocks road;
    PutINGride();
    menuMulti();
    printf("Please Select Your Mode: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        //New Game
        while (1)
        {
            RoundA(flag);
            RoundB(flag);
            flag = 0;
        }
        break;
    case 2:
        // Load game
        load();
        break;
    case 3:
        //Exit
        exit(0);
        break;
    }
}