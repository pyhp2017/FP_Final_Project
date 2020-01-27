#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include ".\Menu.h"
#include ".\RandString.h"

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
    FILE *fpin = fopen("map6.bin", "rb");
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
        printf("\n[%d] %s (%d,%d) - Energy = %d", trace->id, trace->Name, trace->x, trace->y, trace->EnergyCell);
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

            printf("| %c |", cells[i][j]);
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

