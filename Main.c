#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HeaderFiles\\Menu.h"
#include "HeaderFiles\\RandString.h"

//Global Variables and Arrays
char grid[100][100];
char cells[100][100];
int EnergyBlocks[100][100];
int CellID = 1;
int n;

enum blocks //Enum For Blocks
{
    ENERGY = 1,
    MITOSIS,
    FORBIDDEN,
    NORMAL
};

struct cell //Struct For cells
{
    int id;
    int x, y;
    char Name[32];
    int EnergyCell;
    struct cell *next;
};
struct cell *start = NULL, *tmp = NULL; //  start is header of linked list

void insert_end(int n) // insert to the end of Linked list
{
    char *Name;
    int x, y, xrand, yrand;
    struct cell *new_node, *ptr;
    new_node = (struct cell *)malloc(sizeof(struct cell));
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
        if (grid[xrand][yrand] != 'F' && cells[xrand][yrand] != 'X')
        {
            // Put single cell in grid
            x = xrand;
            y = yrand;
            cells[x][y] = 'X';
            break;
        }
    }
    new_node->id = CellID;
    CellID++;
    strcpy(new_node->Name, Name);
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 0;
    new_node->next = NULL;
    if (start == NULL) // FIrst time
    {
        start = new_node;
    }
    else
    {
        ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// Insert to the end of linked list when you want split (for one of the cells that dosen't change location)
void insert_split_witoutrand(int n, int x, int y)
{
    char *Name;
    struct cell *new_node, *ptr;
    new_node = (struct cell *)malloc(sizeof(struct cell));
    if (new_node == NULL)
    {
        printf("error in memory allocation !");
        exit(-1);
    }
    //Ejad name , x , y random , chidan in koskesh ha dar naghsa
    Name = rand_string(5);
    new_node->id = CellID;
    CellID++;
    strcpy(new_node->Name, Name);
    cells[x][y] = 'X';
    new_node->x = x;
    new_node->y = y;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (start == NULL) // FIrst time
    {
        start = new_node;
    }
    else
    {
        ptr = start;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }
}

// Insert to the end of the linked list when you want to split with random location around that cell
void insert_Split_RandAtraf(int n, int x, int y)
{
    char *Name;
    int xfinal, yfinal, xrand, yrand;
    struct cell *new_node, *ptr;
    new_node = (struct cell *)malloc(sizeof(struct cell));
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
        if (X1 >= 0 && X1 < n && Y1 >= 0 && Y1 < n && grid[X1][Y1] != 'F' && cells[X1][Y1] != 'X')
        {
            xfinal = X1;
            yfinal = Y1;
            cells[X1][Y1] = 'X';
            break;
        }
        else
        {
            continue;
        }
    }
    new_node->id = CellID;
    CellID++;
    strcpy(new_node->Name, Name);
    new_node->x = xfinal;
    new_node->y = yfinal;
    new_node->EnergyCell = 40;
    new_node->next = NULL;
    if (start == NULL) // FIrst time
    {
        start = new_node;
    }
    else
    {
        ptr = start;
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
    FILE *fpin = fopen("MAPS\\map6.bin", "rb");
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
int count(struct cell *start)
{
    int count;
    struct cell *trace = start;
    while (trace != NULL)
    {
        count++;
        trace = trace->next;
    }
    return count;
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
void display(struct cell *start)
{
    struct cell *trace = start;
    while (trace != NULL)
    {
        printf("\n[%d] %s (%d,%d) - Energy = %d -- BLOCK ENERGY = %d", trace->id, trace->Name, trace->x, trace->y, trace->EnergyCell, EnergyBlocks[trace->x][trace->y]);
        trace = trace->next;
    }
    printf("\n");
}

// Find and Return a Node in Linked List
struct cell *search(struct cell *begin, int id)
{
    struct cell *move = begin;
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

    for (int j = 0; j < n; j++)
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

            if (cells[i][j] == 'X')
            {
                printf("| %c |", cells[i][j]);
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
struct cell *removeFront(struct cell *A)
{
    if (A == NULL)
    {
        return NULL;
    }
    struct cell *front = A;
    A = A->next;
    front->next = NULL;
    if (A == front)
    {
        A = NULL;
    }
    free(front);
    return A;
}
struct cell *RemoveAny(struct cell *head, struct cell *temp)
{
    if (temp == NULL)
    {
        return NULL;
    }
    if (temp == head)
    {
        return removeFront(head);
    }

    struct cell *move = head;
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
        struct cell *Movagat = move->next;
        move->next = Movagat->next;
        Movagat->next = NULL;
        free(Movagat);
    }

    return head;
}

//Functions to Read Linked List from binaryFile
struct cell *ReadNextFromFile(struct cell *start, FILE *pFile)
{
    size_t returnValue;
    if (start == NULL)
    {
        start = malloc(sizeof(struct cell));
        returnValue = fread(start, sizeof(struct cell), 1, pFile);
        start->next = NULL;
    }
    else
    {
        struct cell *indexCar = start;
        struct cell *newCar = malloc(sizeof(struct cell));
        while (indexCar->next != NULL)
        {
            indexCar = indexCar->next;
        }
        returnValue = fread(newCar, sizeof(struct cell), 1, pFile);
        indexCar->next = newCar;
        newCar->next = NULL;
    }
    return start;
}
struct cell *ReadListIn(struct cell *start)
{

    FILE *pFile;
    pFile = fopen("SAVE_SINGLE\\SavedLink.data", "rb");
    if (pFile != NULL)
    {

        start = NULL;
        fseek(pFile, 0, SEEK_END);
        long fileSize = ftell(pFile);
        rewind(pFile);

        int numEntries = (int)(fileSize / (sizeof(struct cell)));
        // printf("numEntries:%d\n",numEntries);

        int loop = 0;
        for (loop = 0; loop < numEntries; ++loop)
        {
            fseek(pFile, (sizeof(struct cell) * loop), SEEK_SET);
            start = ReadNextFromFile(start, pFile);
        }
    }

    return start;
}

// Function to Write Linked list on binaryFile
void WriteListToFile(struct cell *start)
{
    FILE *pFile;
    pFile = fopen("SAVE_SINGLE\\SavedLink.data", "wb+");
    if (pFile != NULL)
    {
        struct cell *currentCar = start;
        struct cell *holdNext = NULL;
        while (currentCar != NULL)
        {
            holdNext = currentCar->next;
            currentCar->next = NULL;
            fseek(pFile, 0, SEEK_END);
            fwrite(currentCar, sizeof(struct cell), 1, pFile);
            currentCar->next = holdNext;
            holdNext = NULL;
            currentCar = currentCar->next;
        }
        fclose(pFile);
        pFile = NULL;
    }
}

// Function To move cell
void MoveUP(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        if (grid[Xbackup][Ybackup - 1] != 'F' && cells[Xbackup][Ybackup - 1] != 'X' && Ybackup - 1 >= 0 && Ybackup - 1 < n)
        {
            tmp->y = Ybackup - 1;
            cells[Xbackup][Ybackup - 1] = 'X';
            cells[Xbackup][Ybackup] = '\0';
        }
    }
}
void MovdeDown(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        if (grid[Xbackup][Ybackup + 1] != 'F' && cells[Xbackup][Ybackup + 1] != 'X' && Ybackup + 1 >= 0 && Ybackup + 1 < n)
        {
            tmp->y = Ybackup + 1;
            cells[Xbackup][Ybackup + 1] = 'X';
            cells[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveRight(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        if (grid[Xbackup + 1][Ybackup] != 'F' && cells[Xbackup + 1][Ybackup] != 'X' && Xbackup + 1 >= 0 && Xbackup + 1 < n)
        {
            tmp->x = Xbackup + 1;
            cells[Xbackup + 1][Ybackup] = 'X';
            cells[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}
void MoveLeft(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        if (grid[Xbackup - 1][Ybackup] != 'F' && cells[Xbackup - 1][Ybackup] != 'X' && Xbackup - 1 >= 0 && Xbackup - 1 < n)
        {
            tmp->x = Xbackup - 1;
            cells[Xbackup - 1][Ybackup] = 'X';
            cells[Xbackup][Ybackup] = '\0';
        }
        else
        {
            return;
        }
    }
}

// Boost Energy in Energy Blocks
void BoostEnergy(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        if (grid[Xbackup][Ybackup] == 'E')
        {
            if (tmp->EnergyCell == 100)
            {
                printf("\nYou Can Not Reach More Energy !\n");
                sleep(2);
                return;
            }
            if (EnergyBlocks[Xbackup][Ybackup] > 15)
            {
                tmp->EnergyCell += 15;
                EnergyBlocks[Xbackup][Ybackup] -= 15;
            }
            else if (EnergyBlocks[Xbackup][Ybackup] < 15 && EnergyBlocks[Xbackup][Ybackup] >= 0)
            {
                int Tahmonda = EnergyBlocks[Xbackup][Ybackup];
                tmp->EnergyCell += Tahmonda;
                EnergyBlocks[Xbackup][Ybackup] = 0;
                grid[Xbackup][Ybackup] = 'N';
            }
            else
            {
                printf("\nNo More Energy in Here - Empty Storage or Tank\n\n");
                sleep(2);
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
void SplitCell(int ChosenCell)
{
    tmp = search(start, ChosenCell);
    if (tmp != NULL)
    {
        int Xbackup = tmp->x;
        int Ybackup = tmp->y;
        int idBackup = tmp->id;
        //Check if Split is possible
        if (grid[Xbackup][Ybackup] == 'M')
        {
            //Split Code
            //check if it's possible to split
            if (tmp->EnergyCell >= 80)
            {
                start = RemoveAny(start, tmp);
                cells[Xbackup][Ybackup] = '\0';
                insert_split_witoutrand(n, Xbackup, Ybackup);
                insert_Split_RandAtraf(n, Xbackup, Ybackup);
            }
            else
            {
                printf("\nYour Fucking Cell Energy is too low !\n\n");
            }
        }
        else
        {
            printf("\nYou Can Not Split ON %c\n\n", grid[Xbackup][Ybackup]);
        }
    }
}

// Signle Player Function
void SinglePlayer(int flag)
{
    // Single player Mode
    int NumberOfCells;
    int ChosenCell;
    int OptionList2;
    int movechosen;

    if (flag == 1)
    {
        printf("Please Enter Number of Cells: ");
        scanf("%d", &NumberOfCells);
        for (int i = 0; i < NumberOfCells; i++)
        {
            insert_end(n);
        }
    }

    while (1)
    {
        system("cls");
        drawgrid(n);
        display(start);
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
                MoveUP(ChosenCell);
                break;

            case 2:
                // Down Move
                MovdeDown(ChosenCell);
                break;

            case 3:
                // Right
                MoveRight(ChosenCell);
                break;

            case 4:
                // Left
                MoveLeft(ChosenCell);
                break;
            }
            break;

        case 2:
            // Split a Cell
            SplitCell(ChosenCell);
            break;

        case 3:
            //Boost energy
            BoostEnergy(ChosenCell);
            break;

        case 4:
            //Save
            Save();
            break;

        case 5:
            exit(0);
            break;
        }
    }
}

//Save Function
void Save()
{
    // Save Cells Array
    FILE *SaveCell = fopen("SAVE_SINGLE\\SavedCells.data", "wb+");
    fwrite(cells, sizeof(char), sizeof(cells), SaveCell);
    fclose(SaveCell);
    // Save EnergyBlocks Array
    FILE *SaveBlockE = fopen("SAVE_SINGLE\\SavedEblock.data", "wb+");
    fwrite(EnergyBlocks, sizeof(char), sizeof(EnergyBlocks), SaveBlockE);
    fclose(SaveBlockE);
    // Save Linkedlist
    WriteListToFile(start);
    //Save Map
    FILE *SaveMAP = fopen("SAVE_SINGLE\\SavedMAP.bin", "wb+");
    fwrite(&n, sizeof(int), 1, SaveMAP);
    fwrite(grid, sizeof(char), sizeof(grid), SaveMAP);
    fclose(SaveMAP);
    //Save CellID
    FILE *SaveID = fopen("SAVE_SINGLE\\SaveID", "w");
    fprintf(SaveID, "%d\n", CellID);
    fclose(SaveID);
}

// Load Function
void load()
{
    // Load Cells Array
    FILE *SaveCell = fopen("SAVE_SINGLE\\SavedCells.data", "rb");
    fread(cells, sizeof(char), sizeof(cells), SaveCell);
    fclose(SaveCell);
    // Load EnergyBlocks Array
    FILE *SaveBlockE = fopen("SAVE_SINGLE\\SavedEblock.data", "rb");
    fread(EnergyBlocks, sizeof(char), sizeof(EnergyBlocks), SaveBlockE);
    fclose(SaveBlockE);
    //Load Linked list
    start = ReadListIn(start);
    // Load MAP
    FILE *SaveMAP = fopen("SAVE_SINGLE\\SavedMAP.bin", "rb");
    fread(&n, sizeof(int), 1, SaveMAP);
    fread(grid, sizeof(char), sizeof(grid), SaveMAP);
    fclose(SaveMAP);
    // Load Cell ID
    FILE *SaveID = fopen("SAVE_SINGLE\\SaveID", "r");
    fscanf(SaveID, "%d", &CellID);
    fclose(SaveID);
    // If it was Signle Player
    SinglePlayer(0);
}

// MAIN FUNCTION
int main()
{
    srand(time(0));
    int option;
    int OptionList2;
    enum blocks road;
    PutINGride();
    menu();
    printf("Please Select Your Mode: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        //Single Player
        menuSingle();
        printf("Please Select Your Mode: ");
        scanf("%d" , &OptionList2);
        switch (OptionList2)
        {
        case 1:
            // New Game
            SinglePlayer(1);
            break;
        case 2:
            // Load Old game
            load();
            break;
        case 3:
            exit(0);
            break;
        }
        break;
    case 2:
        // Multi Player
        // JUST RUN EXE FILE (REDIRECT)
        system("start MultiPlayer.exe");
        break;
    case 3:
        //Exit
        exit(0);
        break;
    }
}