#include<stdio.h>
int main(void)
{
    int changeOwed;
    int check;
    char invisibleChar;
    int count = 0;
	int numQ=0, numD=0, numN=0, numP=0;
    do{
          printf("How much change is owed (in cents)?\n");
        check = scanf("%d", &changeOwed);
        do{
            scanf("%c",&invisibleChar);
        }while(invisibleChar != '\n');

    }while(check == 0 || !(changeOwed >=0 ));


    int c = changeOwed;
	while(c > 0){

		while(c >= 25){
			count ++;
			numQ++;
			c = c - 25;
		}
		while(c >= 10){
			count ++;
			numD++;
			c = c - 10;
		}
		while(c >= 5){
			count ++;
			numN++;
			c = c - 5;
		}
		while(c >= 1){
			count ++;
			numP++;
		c = c - 1;
		}

	}

 	printf("Quarters: %d, Dimes: %d, Nickels: %d, Pennies: %d\nNumber of coins used= %d", numQ, numD, numN, numP, count);
}
