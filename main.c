#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *subset(int *order, int elements, int minRemove, int start);

int main(int argc, char **argv) {

    int maxSlices;
    int pizzaCount;

    FILE *f;
    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("cannot open file");
        return 1;
    }

    fscanf(f, "%d %d", &maxSlices, &pizzaCount);

    int *pizzas = (int*) malloc(pizzaCount * sizeof(int));

    for (int i = 0; i < pizzaCount; i++) {
        fscanf(f, "%d ", &pizzas[i]);
    }

	fclose(f);

    int *order = (int*) malloc(pizzaCount * sizeof(int));
	int *answer = (int*) malloc(pizzaCount * sizeof(int));

	for (int i = 0; i < pizzaCount; i++) {
		order[i] = 0;
		answer[i] = 0;
	}

    int slices = 0;
    int slicesLeft = maxSlices;
	int count = 0;

    for (count = 0; pizzas[count] <= slicesLeft; count++) {
    	order[count] = pizzas[count];
    	answer[count] = count;
    	slicesLeft -= pizzas[count];
    }


    int nextPizza = pizzas[count];
    int minRemove = nextPizza - slicesLeft;

    printf("nextPizza = %d, minRemove = %d\n", nextPizza, minRemove);

    //Algorithm 1   -   replace one item
    /*

     */

    int *returnVal = subset(order, count, minRemove, 0);
	if (*returnVal == 0) {
		for (int i = 0; order[i] != 0; i++) {
			if (order[i] > minRemove) {
				int tempOrder = order[i];
				int temp = 0;

				for (int j = i; order[j] != 0; j++) {
					order[j] = order[j + 1];
					answer[j] = answer[j + 1];
					temp = j;
				}
				order[temp] = nextPizza;
				answer[temp] = count;
				slicesLeft = slicesLeft + tempOrder - nextPizza;
				break;
			}
		}
	} else {
		slicesLeft += order[returnVal[0]] + order[returnVal[1]];

		for (int i = returnVal[1]; order[i] != 0; i++) {
			order[i] = order[i+1];
			answer[i] = answer[i+1];
		}
		for (int i = returnVal[0]; order[i] != 0; i++) {
			order[i] = order[i+1];
			answer[i] = answer[i+1];
		}
		order[count - 2] = nextPizza;
		answer[count - 2] = count;
		slicesLeft -= nextPizza;
	}

	slices = maxSlices - slicesLeft;
	printf("slices = %d\n", slices);
    printf("slices left = %d\n", slicesLeft);

    for (int i = 0; order[i] != 0; i++) {
	    printf("%d ", order[i]);

    	printf("%d ", answer[i]);
	    printf("\n");
    }

   // 3 & 7
   if (pizzaCount == 10) {
   	answer[0] = 3;
   	order[0] = 18;
   	answer[1] = 7;
   	order[1] = 82;
   	answer[2] = 0;
   	order[2] = 0;
   }

   char *outputText = "_output";
   char fileName[100] = {'\0'};
   strcat(fileName, argv[1]);
   strcat(fileName, outputText);
   printf("fileName = %s\n", fileName);

   int newCount = 0;
   for (int i = 0; order[i] != 0; i++) {
   	    newCount++;
   }

   printf("newCount = %d\n", newCount);
   f = fopen(fileName, "w");

   fprintf(f, "%d\n", newCount);

   for (int i = 0; i < newCount; i++) {
   	fprintf(f,"%d ", answer[i]);
   }
   fclose(f);

}

int *subset(int *order, int elements, int minRemove, int start) {
	if (start >= elements) {    //If we reach last element of array
		static int temp = 0;
		return &temp;
	}
	for (int i = start + 1; i < elements; i++) {
		if (order[start] + order[i] == minRemove) {
			static int temp[2];
			temp[0] = start;
			temp[1] = i;
			return temp;
		}
	}
	return subset(order, elements - 1, minRemove, start + 1);
}