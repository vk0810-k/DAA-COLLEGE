#include <stdio.h>
#include <stdlib.h>

typedef struct Item
{
    int itemId;
    int weight;
    int profit;
    float PBW;
    float xi;
} Item;

void margeRev(Item *arr, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int c = 0;
    int temp_Arr_size = high - low + 1;
    Item *tempArr = (Item *)malloc(sizeof(arr[0]) * temp_Arr_size);

    while (i <= mid && j <= high)
        if (arr[i].PBW > arr[j].PBW)
            tempArr[c++] = arr[i++];
        else
            tempArr[c++] = arr[j++];

    while (i <= mid)
        tempArr[c++] = arr[i++];

    while (j <= high)
        tempArr[c++] = arr[j++];

    for (i = low, c = 0; i <= high; i++)
        arr[i] = tempArr[c++];
}
void margeSortRev(Item *arr, int low, int high)
{
    if (low < high)
    {
        int mid = (high + low) / 2;
        margeSortRev(arr, low, mid);
        margeSortRev(arr, mid + 1, high);
        margeRev(arr, low, mid, high);
    }
}

float fractionalknapsack(Item *items, int n, int capacity)
{
    margeSortRev(items, 0, n - 1);
    float profit = 0;
    int i = 0;
    int takenWeight = 0;
    for (i = 0; i < n; i++)
    {
        if (takenWeight + items[i].weight <= capacity)
        {
            profit += items[i].profit;
            takenWeight += items[i].weight;
            items[i].xi = 1;
        }
        else
        {
            items[i].xi = ((float)capacity - takenWeight) / items[i].weight;
            takenWeight += items[i].xi * items[i].weight;
            profit += items[i].xi * items[i].profit;
            break;
        }
    }

    return profit;
}

int main()
{
    int n, i, knapsackCapacity;
    printf("\tKNAPSACK USING GREEDY APPROACH\n");
    printf("\nEnter total number of items :: ");
    scanf("%d", &n);

    Item *items = (Item *)malloc(sizeof(Item) * n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter itemId, weight, profit for %d :: ",i+1);
        scanf("%d %d %d", &items[i].itemId, &items[i].weight, &items[i].profit);
        items[i].PBW = (float)items[i].profit / items[i].weight;
    }

    printf("\n\nEnter the Knapsack Capacity :: ");
    scanf("%d", &knapsackCapacity);
    float totalProfit = fractionalknapsack(items, n, knapsackCapacity);
    printf("\n\nTotal Profit is :: %f", totalProfit);

    return 0;
}
