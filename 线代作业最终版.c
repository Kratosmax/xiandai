#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int qiuni(float a[], int n)
{
	int *is, *js, i, j, k, l, u, v;
	float d, p;
	is = (int *)malloc(n * sizeof(int));
	js = (int *)malloc(n * sizeof(int));
	for (k = 0; k <= n - 1; k++)
	{
		d = 0.0;
		for (i = k; i <= n - 1; i++)
		{
			for (j = k; j <= n - 1; j++)
			{
				l = i*n + j;
				p = fabs(a[l]);
				if (p>d) //记录绝对值最大的元素位置
				{
					d = p;
					is[k] = i;
					js[k] = j;
				}
			}
		}
		if (d + 1.0 == 1.0) //检测矩阵是否为奇异矩阵
		{
			free(is);
			free(js);
			printf("此矩阵无逆矩阵\n");
			return(0);
		}
		if (is[k] != k) //绝对值最大元素不在k行
		{
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j;
				v = is[k] * n + j;
				p = a[u]; //行元素交换
				a[u] = a[v];
				a[v] = p;
			}
		}
		if (js[k] != k) //绝对值最大元素不在k列
		{
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k;
				v = i*n + js[k];
				p = a[u]; //列元素交换
				a[u] = a[v];
				a[v] = p;
			}
		}
		l = k*n + k; //对角线元素
		a[l] = 1.0 / a[l];
		for (j = 0; j <= n - 1; j++)
		{
			if (j != k) //所在行操作
			{
				u = k*n + j;
				a[u] = a[u] * a[l];
			}
		}
		for (i = 0; i <= n - 1; i++) //除去该对角线元素外其余元素的变换
		{
			if (i != k)
			{
				for (j = 0; j <= n - 1; j++)
				{
					if (j != k)
					{
						u = i*n + j;
						a[u] = a[u] - a[i*n + k] * a[k*n + j];
					}
				}
			}
		}
		for (i = 0; i <= n - 1; i++) //所在列操作
		{
			if (i != k)
			{
				u = i*n + k;
				a[u] = -a[u] * a[l];
			}
		}
	}
	for (k = n - 1; k >= 0; k--) //恢复，先交换的行（列）后恢复
	{
		if (js[k] != k)
		{
			for (j = 0; j <= n - 1; j++)
			{
				u = k*n + j;
				v = js[k] * n + j;
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}
		}
		if (is[k] != k)
		{
			for (i = 0; i <= n - 1; i++)
			{
				u = i*n + k;
				v = i*n + is[k];
				p = a[u];
				a[u] = a[v];
				a[v] = p;
			}
		}
	}
	free(is);
	free(js);
	l = 0;
	printf("该矩阵的逆为:\n");
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			printf("%0.1lf ", a[l]);
			l++;
		}
		printf("\n");
	}
	return(1);
}



int main()
{
	float *a;
	int n, i, b;
	printf("请输入所求矩阵的阶数:");
	scanf_s("%d", &n);
	b = n*n;
	a = (float *)malloc(b * sizeof(float));
	printf("请输入矩阵:\n");
	for (i = 0; i<b; i++)
	{
		scanf_s("%f", &a[i]);
	}
	qiuni(a, n);

	return 0;
}
