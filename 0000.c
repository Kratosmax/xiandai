#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void MatrixOpp(double *A, int m, int n, double* invmat);
void MatrixInver(double *A, int m, int n, double* invmat);
double Surplus(double A[], int m, int n);
int matrix_inv(double* p, int num, double* invmat);

void MatrixOpp(double A[], int m, int n, double* invmat)
{
    int i, j, x, y, k;
    double *SP = NULL, *AB = NULL, *B = NULL, X;
    SP = (double *) malloc(m * n * sizeof(double));
    AB = (double *) malloc(m * n * sizeof(double));
    B = (double *) malloc(m * n * sizeof(double));
    X = Surplus(A, m, n);
    X = 1 / X;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < m * n; k++)
                B[k] = A[k];
            {
                for (x = 0; x < n; x++)
                    B[i * n + x] = 0;
                for (y = 0; y < m; y++)
                    B[m * y + j] = 0;
                B[i * n + j] = 1;
                SP[i * n + j] = Surplus(B, m, n);
                AB[i * n + j] = X * SP[i * n + j];
            }
        }
    MatrixInver(AB, m, n, invmat);
    free(SP);
    free(AB);
    free(B);
}

void MatrixInver(double A[], int m, int n, double* invmat)
{
    int i, j;
    double *B = invmat;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            B[i * m + j] = A[j * n + i];
}

double Surplus(double A[], int m, int n)
{
    int i, j, k, p, r;
    double X, temp = 1, temp1 = 1, s = 0, s1 = 0;
    if (n == 2)
    {
        for (i = 0; i < m; i++)
            for (j = 0; j < n; j++)
                if ((i + j) % 2)
                    temp1 *= A[i * n + j];
                else
                    temp *= A[i * n + j];
        X = temp - temp1;
    }
    else
    {
        for (k = 0; k < n; k++)
        {
            for (i = 0, j = k; i < m, j < n; i++, j++)
                temp *= A[i * n + j];
            if (m - i)
            {
                for (p = m - i, r = m - 1; p > 0; p--, r--)
                    temp *= A[r * n + p - 1];
            }
            s += temp;
            temp = 1;
        }

        for (k = n - 1; k >= 0; k--)
        {
            for (i = 0, j = k; i < m, j >= 0; i++, j--)
                temp1 *= A[i * n + j];
            if (m - i)
            {
                for (p = m - 1, r = i; r < m; p--, r++)
                    temp1 *= A[r * n + p];
            }
            s1 += temp1;
            temp1 = 1;
        }
        X = s - s1;
    }
    return X;
}

int matrix_inv(double* p, int num, double* invmat)
{
    if (p == NULL || invmat == NULL)
    {
        return 1;
    }
    if (num > 10)
    {
        return 2;
    }
    MatrixOpp(p, num, num, invmat);
    return 0;
}

int main()
{
    int i, j;
    int num;
    double *arr=NULL;
    double *result=NULL;
    int flag;

    printf("请输入矩阵维数：\n");
    scanf("%d",&num);
    arr=(double *)malloc(sizeof(double)*num*num);
    result=(double *)malloc(sizeof(double)*num*num);

    printf("请输入%d*%d矩阵：\n", num, num);
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < num; j++)
        {
            scanf("%lf", &arr[i * num + j]);
        }
    }

    flag = matrix_inv(arr, num, result);

    if(flag==0)
    {
        printf("逆矩阵为：\n");
        for (i = 0; i < num * num; i++)
        {
            printf("%lf\t ", *(result + i));
            if (i % num == (num - 1))
                printf("\n");
        }
    }
    else if(flag==1)
    {
        printf("p/q为空\n");
    }
    else
    {
        printf("超过最大维数\n");
    }

    system("PAUSE");
    free(arr);
    free(result);
    return 0;
}
