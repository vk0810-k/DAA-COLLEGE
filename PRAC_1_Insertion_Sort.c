#include <stdio.h>

int insertionSort(int size, int *array);

int main()
{
	int size, i , array[21];
	printf("Enter total number of elements: ");
	scanf("%d", &size);
	printf("Enter %d elements: ", size);
	for(i=0; i<size; i++)
	   scanf("%d", &array[i]);
	insertionSort(size, array);
	printf("The Sorted Array is :: ");
	for(i=0; i<size; i++)
	   printf(" %d", array[i]);
	printf("\n");
	return 0;
}

int insertionSort(int size, int *array)
{
	int i, j;
	int temp;
	for(i=1; i<size; i++){
		temp=array[i];
		j= i-1;
		while((temp < array[j])&&(j >= 0))
        {
			array[j+1] = array[j];
			j= j-1;
		}
		array[j+1] = temp;
	}
	return 1;
}
