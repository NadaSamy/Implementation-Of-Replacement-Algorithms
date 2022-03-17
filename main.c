#include <stdlib.h>
#include <stdio.h>

/* GLOBAL VARIABLES */
int streamSize = 0;
int sizeLRU = 0, Index = 0;

/* STRUCTS */
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};
 
struct Node {
	int number;
	int rank;
};
/* STRUCT VARIABLES */
struct Queue* q_buffer;
struct  Node* n_buffer;

/* FUNCTION PROTOTYPES */
void FIFO(int stream[]);
void CLOCK(int stream[], int pageFrames);
void LRU(int stream[], int pageFrames);
void OPTIMAL();
int* readFile(int* frames, int* stream, char* policy);
void createQueue(unsigned capacity);
int enqueue(int item);
int dequeue();
int checkElement(int x);

/* MAIN */
int main()
{
	int pageFrames, *stream, sizeStream;
	char policy[8];
	stream = malloc(sizeof(int) * 4099);
	int i = 0, j = 0;
	// scan
	scanf("%d",&pageFrames);
	scanf("%s",policy);
	while(i != -1)
	{
		scanf("%d",&stream[j]);
		i = stream[j];
		j++;
	}
	
	streamSize = j-1;
	stream = realloc(stream, sizeof(int)* streamSize);
	
	// end read
	//stream = readFile(&pageFrames, stream, policy);
	createQueue(pageFrames);
	
	switch(policy[0])
	{
		case 'F':
		{
			printf("Replacement Policy = FIFO\n");
			printf("-------------------------------------\n");
			printf("Page   Content of Frames\n");
			printf("----   -----------------\n");
			FIFO(stream);
			break;
		}
		case 'L':
		{
			printf("Replacement Policy = LRU\n");
			printf("-------------------------------------\n");
			printf("Page   Content of Frames\n");
			printf("----   -----------------\n");
			LRU(stream, pageFrames);
			break;
		}
		case 'C':
		{
			printf("Replacement Policy = CLOCK\n");
			printf("-------------------------------------\n");
			printf("Page   Content of Frames\n");
			printf("----   -----------------\n");
			CLOCK(stream, pageFrames);
			break;
		
		}
		default:
		break;
	}
	
	return 0;
}


/* FUNCTION DEFINITONS */



int checkLRU(int x, int pageFrames)
{
	for(int i = 0; i < sizeLRU ; i++)
	{
		if(x == n_buffer[i].number)
		{
			Index = i;
			return 0;
		}
	}
	
	return 1;
}



void LRU(int stream[], int pageFrames)
{
	// LRU
	n_buffer = malloc(sizeof(struct Node) * pageFrames);
	int temp = streamSize;
	int i = 0, K = 0;
	int max = -1000000;
	int lruINDEX, maxIndex = 0;
	int faults = 0;
	while(temp != 0)
	{
		if(checkLRU(stream[i], pageFrames) == 1)
		{
		  // element mesh mowgod abl keda
		  if(sizeLRU == pageFrames)
		  {
		  	max = -1000000;
		  	// buffer is full;
		  	for(int j = 0; j < sizeLRU; j++)
		  	{
		  		if(max < n_buffer[j].rank)
		  		{
		  			max = n_buffer[j].rank;
		  			lruINDEX= j;
		  		}
		  	}
		  	n_buffer[lruINDEX].number = stream[i];
		  	//K--;
		  	n_buffer[lruINDEX].rank = K;
		  	K--;
		  	printf("%02d F   ", stream[i]);
		  	faults++;
		  }
		  else
		  {
		  	// buffer has empty space
		  	sizeLRU++;
		  	n_buffer[maxIndex].number = stream[i];
		  	n_buffer[maxIndex].rank = K;
		  	K--;
		  	maxIndex++;
		  	printf("%02d     ", stream[i]);
		  }
		}
		else
		{
		// element mowgod abl keda
			n_buffer[Index].rank = K;
			K--;
			printf("%02d     ",stream[i]); 
		}
		for(int y  = 0; y < sizeLRU; y++)
		{
			printf("%02d ", n_buffer[y].number);
		}
		temp--;
		i++;
		printf("\n");
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
	
}

void CLOCK(int stream[], int pageFrames)
{
	sizeLRU = 0;
	//Index = 0;
	n_buffer = malloc(sizeof(struct Node) * pageFrames);
	int temp = streamSize;
	int i = 0, K = 0,j = 0;
	int faults = 0;
	int maxIndex = 0;
	while(temp != 0)
	{
		if(checkLRU(stream[i], pageFrames) == 1)
		{
		  // element mesh mowgod abl keda
		  if(sizeLRU == pageFrames)
		  {
		  	while(n_buffer[j].rank == 1)
		  	{
		  		/*if(n_buffer[j].rank == 0)
		  		{
		  			n_buffer[j].number = stream[i];
		  			n_buffer[j].rank = 1;
		  			printf("%02d F   ", stream[i]);
		  			break;
		  		}
		  		n_buffer[j].rank = 0;
		  		j++;
		  		if(j == 3)
		  		{
		  			j == 0;
		  		}*/
		  		
		  		n_buffer[j].rank = 0;
		  		j++;
		  		if( j == pageFrames)
		  		{
		  			j= 0;
		  			
		  		}
		  	}
		  	n_buffer[j].number = stream[i];
		  	n_buffer[j].rank = 1;
		  	printf("%02d F   ", stream[i]);
		  	faults++;
		  	j++;
		  	//printf("   %d",j);
		  	if( j == pageFrames)
		  		{
		  			j= 0;
		  			
		  		}
		  	
		  }
		  else
		  {
		  	sizeLRU++;
		  	// buffer has empty space
		  	n_buffer[maxIndex].number = stream[i];
		  	n_buffer[maxIndex].rank = 1;
		  	printf("%02d     ",stream[i]);
		  	maxIndex++;
		  }
		}
		else
		{
			// element mowgod abl keda
			printf("%02d     ",stream[i]);
			n_buffer[Index].rank = 1;
		}
		
		for(int y  = 0; y < sizeLRU; y++)
		{
			printf("%02d ", n_buffer[y].number);
		}
		temp--;
		i++;
		printf("\n");
	}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",faults);
}

int checkElement(int x)
{
	if (q_buffer->front == -1)
	    {
		printf("\nQueue is Empty");
		return -1;
	    }
	    
	for(int i = 0; i < q_buffer->size; i++)
	{
		if(x == q_buffer->array[i])
		{
			return 1;
		}
	}
	return 0;
}

void FIFO(int stream[])
{
		// FIFO
		int temp = streamSize;
		int result;
		int i = 0, count = 0;
		int x;
		while(temp != 0)
		{
			if(checkElement(stream[i]) == 0)
			{
				if(enqueue(stream[i]) == 0)
				{
					// feh makan fl queue
					printf("%02d     ",stream[i]);
				}
				else
				{
					x = dequeue();
					enqueue(stream[i]);
					printf("%02d F   ",stream[i]);
					count++;
					//mafesh makan fl queue
				}
			}
			else
			{
				printf("%02d     ",stream[i]);
			}
			
			
			for(int i = 0; i < q_buffer->size; i++)
			{
				printf("%02d ", q_buffer->array[i]);
			}
			printf("\n");
			i++;
			temp--;
		}
		printf("-------------------------------------\n");
		printf("Number of page faults = %d\n",count);
}

void createQueue(unsigned capacity)
{
	// allocating memory for the struct
	q_buffer = (struct Queue*)malloc(sizeof(struct Queue));
	
	// specifying array max capacity and front = size = 0
	q_buffer->capacity = capacity;
	q_buffer->front = q_buffer->size = 0;
	
	// initizaling the rear index to the end of the array
	q_buffer->rear = capacity - 1;
	
	// allocating memory for the array
	q_buffer->array = (int*)malloc(q_buffer->capacity * sizeof(int));
}
 
int enqueue(int item)
{
	if (q_buffer->size == q_buffer->capacity)
	{
	// buffer full
		return -1;
	}
        
        // this helps to make the array circular, the rear is assigned to the next available space
       
	q_buffer->rear = (q_buffer->rear + 1) % q_buffer->capacity;
	// inserting element
	q_buffer->array[q_buffer->rear] = item;
	
	// size  = number of elements inside the queue
	q_buffer->size = q_buffer->size + 1;
	
	
	
	//printf("%d enqueued to queue\n POISITON IN ARRAY: %d\n", item,q_buffer->rear);
	return 0;
}
 
int dequeue()
{
    if (q_buffer->size == 0)
    {
    	return -1;
        printf("QUEUE IS EMPTY\n\n");
    }
    // remove element by FIFO policy
    int item = q_buffer->array[q_buffer->front];
    
    // assigning the head index to the next element
    q_buffer->front = (q_buffer->front + 1) % q_buffer->capacity;
    
    // decrasing number of elements inside array
    q_buffer->size = q_buffer->size - 1;
    return 0;
}

