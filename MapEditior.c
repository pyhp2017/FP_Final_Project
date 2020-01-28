#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ADDRESS "CreateMAP\\map.bin"

int map[100][100];

void putNormal(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            map[i][j] = 4;
        }
    }
}

void saveMap(int n, int x, int y, int mod)
{
    FILE *fpin = fopen(ADDRESS, "wb");
    if (fpin == NULL)
    {
        printf("Erro");
    }

    fwrite(&n, sizeof(int), 1, fpin);

    map[x][y] = mod;
    fwrite(&map[x][y], sizeof(unsigned char), 1, fpin);

    fclose(fpin);
}

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
            if (map[i][j] == 1)
            {
                printf("\x1b[42m");
            }
            else if (map[i][j] == 4)
            {
                printf("\x1b[30;47m");
            }
            else if (map[i][j] == 3)
            {
                printf("\x1b[41m");
            }
            else if (map[i][j] == 2)
            {
                printf("\x1b[44m");
            }
            else
            {
                printf("\x1b[0m");
            }

            printf("| %d |", map[i][j]);
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

void PutINGride(int n)
{
    FILE *fpin = fopen(ADDRESS, "wb");
    if (fpin == NULL)
    {
        printf("Erro");
    }

    fwrite(&n, sizeof(int), 1, fpin);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fwrite(&map[i][j], sizeof(unsigned char), 1, fpin);
        }
    }

    fclose(fpin);
}

void menu()
{
    printf("\t\t\t\n PLEASE SELECT A MODE: ");
    printf("\t\t\t\n [1] ENERGY ");
    printf("\t\t\t\n [2] MITOSIS ");
    printf("\t\t\t\n [3] FORBIDDEN ");
    printf("\t\t\t\n [4] NORMAL ");
    printf("\t\t\t\n [5] EXIT ");
}

int main()
{
    int n;
    printf("Please Enter n: ");
    scanf("%d", &n);
    putNormal(n);
    PutINGride(n);
    drawgrid(n);
    int x, y, select;
    while (1)
    {
        printf("\n\nPleasse Enter One of coordinates: ");
        scanf("%d %d", &x, &y);
        menu();
        printf("\nEnter Mode: ");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            saveMap(n, x, y, 1);
            break;

        case 2:
            saveMap(n, x, y, 2);
            break;

        case 3:
            saveMap(n, x, y, 3);
            break;

        case 4:
            saveMap(n, x, y, 4);
            break;

        case 5:
            exit(0);
            break;
        }

        PutINGride(n);
        drawgrid(n);
    }
}