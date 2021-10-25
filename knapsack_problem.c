#include<stdio.h>
#include<time.h>
#include<conio.h>
void knapsack(float cap,int n,float weight[],float profit[])
{
    int i,j;
    float x[100],tp,y;
    y = cap;
    tp = 0;
    for(i = 0;i < n;i++)
    {
        x[i] = 0.00;
    }
    for(i = 0;i < n;i++)
    {
        if(weight[i] > y)
        {
            break;
        }
        else
        {
            x[i] = 1.00;
            tp = tp + profit[i];
            y = y - weight[i];
        }
    }
    if(i<n)
    {
        x[i] = y/weight[i];
    }
    tp = tp + (x[i] * profit[i]);
    printf("\n\nThe Selected Items Are ::");
    for(i = 0; i < n; i++)
    {
        if(x[i] == 1.00)
        {
            printf("\nProfit is %f with weight %f ", profit[i], weight[i]);
        }
        else if (x[i] > 0.00)
        {
            printf("\n%f part of Profit %f with weight %f", x[i], profit[i], weight[i]);
        }
        printf("\nTotal profit for %d objects with capacity %f = %f\n\n", n, cap,tp);
    }
}
void main()
{
	float weight[20],profit[20],ratio[20], s1,s2,s3;
	int n;
	time_t start,stop;
	float cap;
	int i,j;
	printf("Enter number of objects:  ");
	scanf("%d", &n);
	printf("\nEnter the capacity of knapsack: ");
	scanf("%f", &cap);
	for(i = 0;i < n;i++)
	{
		printf("\nEnter profit for %d : ", (i+1));
		scanf("%f", &profit[i]);
		printf("Enter weight for %d : ", (i+1));
		scanf("%f", &weight[i]);
		ratio[i]=profit[i]/weight[i];
	}
	start=time(NULL);
	for(i = 0;i < n;i++)
		for(j = 0;j < n;j++)
		{
			if(ratio[i] > ratio[j])
			{
				s1 = ratio[i];
				ratio[i] = ratio[j];
				ratio[j] = s1;
				s2 = weight[i];
				weight[i] = weight[j];
				weight[j] = s2;
				s3 = profit[i];
				profit[i] = profit[j];
				profit[j] = s3;
			}
		}
	knapsack(cap,n,weight,profit);
	stop=time(NULL);
	printf("\nKnapsack = %f\n", difftime(stop,start));
	getch();
}
