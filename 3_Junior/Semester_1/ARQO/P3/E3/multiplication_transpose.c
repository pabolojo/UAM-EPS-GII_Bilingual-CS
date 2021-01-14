//P3 arq 2019-2020
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

void compute(tipo **matrix1, tipo **matrix2, tipo **result, int n);
void transpose(tipo **matrix, tipo **matrixT, int n);

int main(int argc, char *argv[])
{
    int n, i, j;
    tipo **m = NULL, **k = NULL, **r = NULL, **mt = NULL;
    struct timeval fin, ini;

    printf("Word size: %ld bits\n", 8 * sizeof(tipo));

    if (argc != 2)
    {
        printf("Error: ./%s <matrix size>\n", argv[0]);
        return -1;
    }
    n = atoi(argv[1]);
    m = generateMatrix(n);
    if (!m)
    {
        return -1;
    }

    k = generateMatrix(n);
    if (!k)
    {
        free(m);
        return -1;
    }
    mt = generateEmptyMatrix(n);
    if (!mt)
    {
        free(m);
        free(k);
        return -1;
    }

    r = generateEmptyMatrix(n);
    if (!k)
    {
        free(mt);
        free(m);
        free(k);
        return -1;
    }

    gettimeofday(&ini, NULL);

    /* Main computation */
    transpose(m, mt, n);
    compute(k, mt, r, n);
    /* End of computation */

    gettimeofday(&fin, NULL);
    printf("Execution time: %f\n", ((fin.tv_sec * 1000000 + fin.tv_usec) - (ini.tv_sec * 1000000 + ini.tv_usec)) * 1.0 / 1000000.0);
    printf("Product:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%lf ", r[i][j]);
        }
        printf("\n");
    }

    free(m);
    free(k);
    free(mt);
    free(r);
    return 0;
}

void compute(tipo **matrix1, tipo **matrix2, tipo **result, int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[j][k];
            }
        }
    }
}

void transpose(tipo **matrix, tipo **matrixT, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrixT[j][i] = matrix[i][j];
        }
    }
}
