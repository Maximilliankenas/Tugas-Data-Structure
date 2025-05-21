#include<stdio.h>

//MaxHeap
int maxHeap[100];
int dataCount = 1;

int getParentIndex(int index)
{
	return index/2;
}

int getLeftIndex(int index)
{
	return index*2;
}

int getRightIndex(int index)
{
	return index*2 +1;
}

void viewHeap()
{
	if(dataCount<=1)
	{
		printf("Your Heap is Empty. Insert more data!\n\n");
	}
	else
	{
		for(int i=1; i<dataCount; i++)
		{
			printf("Heap[%2d] = %d\n", i, maxHeap[i]);
		}
		puts("");
	}
}

void swapValue(int parentIndex, int currIndex)
{
	int temp = maxHeap[parentIndex];
	maxHeap[parentIndex] = maxHeap[currIndex];
	maxHeap[currIndex] = temp;
}

void HeapUp(int index)
{
	if(index <=1 ) return; //kondisinya kosong
	
	int parentIndex = getParentIndex(index);
	//masih memenuhi kondisi max-heap
	if(maxHeap[parentIndex] >= maxHeap[index]) return;
	
	//kalo nggk sesuai kondisi max-heap
	swapValue(parentIndex,index);
	//pengecekan kondisi secara rekursif
	HeapUp(parentIndex);
}

void HeapDown(int index)
{
	if(index >= dataCount) return;//ketika kondisinya kosong
	
	int biggest = index;//parent
	int leftValue = getLeftIndex(index);//left child
	int rightValue = getRightIndex(index);//right child

	//jika tidak ada child
	if(leftValue >= dataCount){
		return;
	}
	//jika hanya 1 child
	else if(rightValue >= dataCount){
		if(maxHeap[leftValue] > maxHeap[biggest]){
			swapValue(biggest, leftValue);
			biggest = leftValue;
		}
	}
	//jika ada dua child
	else{
		//jika dua dua nya lebih besar
		if(maxHeap[leftValue] > maxHeap[biggest] && maxHeap[rightValue] > maxHeap[biggest]){
			if(maxHeap[leftValue] > maxHeap[rightValue]){
				swapValue(biggest, leftValue);
				biggest = leftValue;
			}
			else{
				swapValue(biggest, rightValue);
				biggest = rightValue;
			}
		}
		//jika kiri lebih besar
		else if(maxHeap[leftValue] > maxHeap[biggest]){
			swapValue(biggest, leftValue);
			biggest = leftValue;
		}
		//jika kanan lebih besar
		else if(maxHeap[rightValue] > maxHeap[biggest]){
			swapValue(biggest, rightValue);
			biggest = rightValue;
		}
	}
	
	//masih memenuhi kriteria max-heap
	if(biggest == index) return;
	
	//pengecekan kondisi secara rekursif
	HeapDown(biggest);
}

void push(int input)
{
	maxHeap[dataCount] = input;
	HeapUp(dataCount);
	dataCount++;
}

int pop()
{
	int removed = maxHeap[1];
	swapValue(1, dataCount-1);
	dataCount--;
	HeapDown(1);
	return removed;
}

void createMenu()
{
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Exit\n");
}

int main()
{
	int input = -1, num;
	do
	{
		printf("Data:\n",dataCount);
		viewHeap();
		createMenu();
		
		do
		{
			printf("input your choice: ");
			scanf("%d", &input); getchar();
		} while(input < 1 || input > 3);
	
		switch(input)
		{
			case 1: printf("What data should be inputted into the heap?");
				scanf("%d", &num);getchar();
				push(num);
				printf("%d has been inputted into the heap\n\n", num);
				getchar();
				break;
			case 2: if(dataCount<=1)
				{
					printf("Your heap is empty. Insert more data!\n\n");
				}
				else
				{
					printf("%d has been deleted\n\n", pop());
				}
				getchar();
				break;
		}
	}while (input!=3);
	
	//return 0;
}
	
