#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define NMAX 10

// Setup item list
void list_setup(int *nitems, int count[], int index[])
{
	printf("Setup item list\n");
	*nitems = 0;
	for(int i = 0; i < NMAX; i++)
	{
		count[i] = 5;
		index[i] = i;
		*nitems += 1;
		printf("%d %d %d\n",i,count[i],index[i]);
	}
}

// Use all the items @ cursorIndex
void use_item(int *nitems, int cursorIndex, int count[], int index[])
{
	int itemIndex = index[cursorIndex];

	while(count[itemIndex] > 0) count[itemIndex]--;

	if(count[itemIndex] == 0)
	{
		*nitems -= 1;
		for(int i = cursorIndex; i < *nitems; i++)
		{
			index[i] = index[i + 1];
			count[i] = count[i + 1];
		}
	}
}

// Print current list
void list_print(int nitems, int count[], int index[])
{
	printf("\nCurrent item list\n");
	for(int i = 0; i < nitems; i++) printf("%d %d %d\n",i,count[i],index[i]);
}

int main(void)
{
	int nitems, cursorIndex;
	int count[NMAX], index[NMAX];

	// Setup item list
	list_setup(&nitems, count, index);

	// Use all the items @ cursorIndex
	cursorIndex = 2;
	use_item(&nitems, cursorIndex, count, index);

	// Print current list
	list_print(nitems, count, index);
	
	// Use all the items @ cursorIndex
	cursorIndex = 6;
	use_item(&nitems, cursorIndex, count, index);

	// Print current list
	list_print(nitems, count, index);
}
