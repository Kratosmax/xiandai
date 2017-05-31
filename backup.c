#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
double hanglieshi(double *h, int i, int j)
{
	double *A = (double *)malloc(sizeof(double)*i*j);
	int k, l, s;
	double t = 1.0;
	int count = 0;//因为可能出现除数为0的情况，所以需要换行
	for (k = 0; k<i; k++)
	{
		for (l = 0; l<j; l++)
		{
			*(A + k*j + l) = *(h + k*j + l);
		}
	}
	if (i != j)
	{
		printf("错误！");
		return 0;
	}
	if (i == 1 && j == 1)
	{
		return *(A);
	}
	else
	{
		for (k = 1; k<i; k++)
		{
			for (s = k; s < i; s++)
			{
				int tag = 0;
				if (*(A + (k - 1)*j + k - 1) == 0)
				{
					for (l = k; l<i; l++)
					{
						if (*(A + l*j) != 0)
							break;
					}
					if (l == i)
					{
						return 0;
					}
					tag = l;
					for (l = k - 1; l<j; l++)
					{
						double B = 0.0;
						B = *(A + (k - 1)*j + l);
						*(A + (k - 1)*j + l) = *(A + tag*j + l);
						*(A + tag*j + l) = B;
						count++;
					}
				}
				double B = *(A + s*j + k - 1);
				for (l = k - 1; l <j; l++)
				{
					*(A + s*j + l) = *(A + s*j + l) - B*(*(A + (k - 1)*j + l)) / (*(A + (k - 1)*j + k - 1));
				}
			}

		}
	}
	/*for(k = 0;k < i;k++)
	{
	for(l = 0;l < j; l++)
	{
	printf("%lf   ",*(A+k*j+l));
	}
	printf("\n");
	}*/
	for (k = 0, l = 0; k<i&&l<j; k++, l++)
	{
		t = t*(*(A + k*j + l));
	}
	free(A);
	if (count % 2 == 0)
		return t;
	else
		return -t;
}
/*利用行列式求值函数。
其中i和j为矩阵的行和列。
m和n为求要求的余子式。*/

double yuzishi(double *h, int i, int j, int m, int n)
{
	int k, l, x, y;
	double q;
	double *b = (double *)malloc(sizeof(double)*(i - 1)*(j - 1));
	if (i != j || i<2)
	{
		return 0;
	}
	else
	{
		for (k = 0, x = 0; k<i - 1 && x<i; k++, x++)
			for (l = 0, y = 0; l<j - 1 && y<j; l++, y++)
			{
				if (m != k&&n != l)
				{
					*(b + k*(j - 1) + l) = *(h + x*j + y);
				}
				else if (m == k&&n != l)
				{
					*(b + k*(j - 1) + l) = *(h + (++x)*j + y);
				}
				else if (m != k&&n == l)
				{
					*(b + k*(j - 1) + l) = *(h + x*j + (++y));
				}
				else if (m == k&&n == l)
				{
					*(b + k*(j - 1) + l) = *(h + (++x)*j + (++y));
				}
			}


		q = hanglieshi(b, i - 1, j - 1);
	}
	free(b);
	return q;


}

int nijuzhen(double *w, double *iw, int i, int j)
{
	int k, l;
	if (hanglieshi(w, i, j) == 0)
	{
		printf("行列式值为0，逆矩阵不存在\n");
		return 0;
	}
	else
	{
		for (k = 0; k<i; k++)
		{
			for (l = 0; l<j; l++)
			{
				if ((k + l) % 2 == 0)
					*(iw + k*j + l) = yuzishi(w, i, j, l, k) / hanglieshi(w, i, j);
				else
					*(iw + k*j + l) = (-1)*yuzishi(w, i, j, l, k) / hanglieshi(w, i, j);

			}
			printf("\n");
		}
		return 1;
	}
}

int main()
{
	float *a;
	int n, i, b;
	printf("请输入所求矩阵的阶数:");
	scanf_s("%d",  &n);
	b = n*n;
	a = (float *)calloc(b ,sizeof(float));
	printf("请输入矩阵:\n");
	for (i = 0; i<b; i++)
	{
		scanf_s("%f", &a[i]);
	}
	nijuzhen( a, n,n,n);

	return 0;
}

/*int main()
{
	int i, j;
	int num;
	double *arr = NULL;
	double *result = NULL;
	int flag;

	printf("请输入矩阵维数：\n");
	scanf_s("%d", &num);
	arr = (double *)malloc(sizeof(double)*num*num);
	result = (double *)malloc(sizeof(double)*num*num);

	printf("请输入%d*%d矩阵：\n", num, num);
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < num; j++)
		{
			scanf_s("%lf", &arr[i * num + j]);
		}
	}

	flag = matrix_inv(arr, num, result);

	if (flag == 0)
	{
		printf("逆矩阵为：\n");
		for (i = 0; i < num * num; i++)
		{
			printf("%lf\t ", *(result + i));
			if (i % num == (num - 1))
				printf("\n");
		}
	}
	else if (flag == 1)
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
}*/
