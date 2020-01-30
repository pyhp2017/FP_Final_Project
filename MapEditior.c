#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ADDRESS "CreateMAP\\New_Map.bin"

int n;
char map[100][100];

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
            if (map[i][j] == '1')
            {
                printf("\x1b[42m");
            }
            else if (map[i][j] == '4')
            {
                printf("\x1b[30;47m");
            }
            else if (map[i][j] == '3')
            {
                printf("\x1b[41m");
            }
            else if (map[i][j] == '2')
            {
                printf("\x1b[44m");
            }
            else
            {
                printf("\x1b[0m");
            }
            printf("|   |");
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

void TakeNormal()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[i][j] = '4';
        }
    }
}

void SaveMap()
{

    FILE *fptr = fopen(ADDRESS, "wb");
    int size = n;
    fwrite(&size, sizeof(int), 1, fptr);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            char c = map[i][j];
            fwrite(&c, sizeof(char), 1, fptr);
        }
    }
    fclose(fptr);
}

void Menu()
{
    system("color a");
    system("cls");
    printf("\n\t\t\t [1] Create New MAP");
    printf("\n\t\t\t [2] Edit MAP");
    printf("\n\t\t\t [3] EXIT");
}

void MenuChange()
{
    printf("\n\n\t\t\t[1] ENERGY");
    printf("\n\n\t\t\t[2] MITOSIS");
    printf("\n\n\t\t\t[3] FORBIDDEN");
    printf("\n\n\t\t\t[4] NORMAL");
    printf("\n\n\t\t\t[5] EXIT");
}

void saveOption(int flag)
{
    int x, y, option;
    if (flag == 1)
    {
        system("cls");
        printf("\n\t\t\t Please Enter n: ");
        scanf("%d", &n);
        TakeNormal();
    }
    while (1)
    {
        system("cls");
        drawgrid(n);
        printf("\n\n\t\t\t Please Enter one of your coordinates: ");
        scanf("%d %d", &x, &y);
        MenuChange();
        printf("\n\n\t\t\t Please Enter your Option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            map[x][y] = '1';
            break;
        case 2:
            map[x][y] = '2';
            break;
        case 3:
            map[x][y] = '3';
            break;
        case 4:
            map[x][y] = '4';
            break;
        case 5:
            exit(0);
            break;
        }
        SaveMap();
    }
}

void LoadOption()
{
    char FileAddress[100];
    printf("Please Enter Your File Address: ");
    scanf("\n");
    gets(FileAddress);
    FILE *fpin = fopen(FileAddress, "rb");
    if (fpin == NULL)
    {
        printf("Error");
    }
    fread(&n, sizeof(int), 1, fpin);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fread(&map[i][j], sizeof(unsigned char), 1, fpin);
        }
    }
    fclose(fpin);
    saveOption(0);
}

int main()
{
    int option;
    Menu();
    printf("\n\n\t\t\t Please Select an Option: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        saveOption(1);
        break;
    case 2:
        LoadOption();
        break;
    case 3:
        exit(0);
        break;
    }
}