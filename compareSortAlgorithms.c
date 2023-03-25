#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//had to copy and paste from my VSC bc my changes werent showing up after commiting on my desktop github

int extraMemoryAllocated;

void merge(int pData[], int l, int r, int m)
{

	int i, j, k;
	int n1 = m - l + 1; // creates size of one part of the array
	int n2 = r - m;

	// allocating temp memory 
	int *L = (int*)malloc(n1*sizeof(int));
	int *R = (int*)malloc(n2*sizeof(int));

	//copying values from each side into their own arrays 
	for (i = 0; i < n1; i++)
	{
		L[i] = pData[l +i]; // starts from full left side to the end of the array size
	}
	for(j = 0; j < n2; j++)
	{
		R[i] = pData[m + 1 + j]; // starts from the middle (adds 1 to go the start of 2nd arr) then goes to end of arr
	}
	
	// merging them back together 
	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			pData[k] = L[i];
			i++;
		}
		else 
		{
			pData[k] = R[j];
			j++;
		}
		k++;

	}

	// copying over left over elements from L and R
	while(i < n1)
	{
		pData[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		pData[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);

	
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int m = (l + r)/2; // middle value of the array

		//sorting both halves
		mergeSort(pData, l, m); // keeps splitting the halves 
		mergeSort(pData, m+1, r);

		merge(pData, l, m, r); // merges them back together 
	}
	
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, item;

	for (i = 1; i < n; i++)
	{
		item = pData[i];

		for(j = i -1; j >= 0 ; j--)
		{
			if (pData[j] > item)
				pData[j+1] = pData[j];
			else
				break;
		}
		pData[j+1] = item;

	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j, temp;

	for (i = 0; i <= n-1; i++)
	{
		for(j = i+1; j <= n; j++)
		{
			if (pData[i] >= pData[j])
			{
				temp =  pData[j];
				pData[j] = pData[i];
				pData[i] = temp;
			}

		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min_idx, temp;

	for (i = 0; i < n-1; i++)
	{
		min_idx = i; 
		for (j = i+1; j < n; j++)
		{
			if (pData[j] < pData[min_idx])
				min_idx = j;
		}
		temp = pData[i];
		pData[i] = pData[min_idx];
		pData[min_idx] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		
		for(int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", (*ppData + i));
		}
		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
