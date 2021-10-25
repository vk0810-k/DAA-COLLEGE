#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

int W = 50, value[] = {60, 100, 120}, weight[] = {10, 20, 30};

void InsertionSort(int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {
        key = value[i];
        j = i - 1;

        while (j >= 0 && value[j] > key)
        {
            value[j + 1] = value[j];
            weight[j + 1] = weight[j];
            j = j - 1;
        }

        value[j + 1] = key;
    }
}

double FractionalKnapsack(int W, int n)
{
	InsertionSort(n);

    int current_weight = 0;
	double final = 0.0;

	for (int i = 0; i < n; i++)
    {
		if (current_weight + weight[i] <= W)
        {
			current_weight += weight[i];
			final += value[i];
		}

		else
        {
			int remain = W - current_weight;
			final += value[i] * ((double)remain / (double)weight[i]);
			break;
		}
	}

	return final;
}

int main()
{
    int n = sizeof(value) / sizeof(value[0]);

	printf("Maximum value we can obtain = %f", FractionalKnapsack(W, n));

	return 0;
}