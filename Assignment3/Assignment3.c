#include <pthread.h>
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>

void accept(int *matrix,int row,int col)
{
	int i,j;
	printf("Enter the Elements of the matrix \n");
	for(i=0;i<row;i++)
	{
		printf("Enter Row %d\n",(i+1));
		for(j=0;j<col;j++)
			scanf("%d",(matrix + col*i + j));
		printf("Row %d complete\n",(i+1));
	}
  printf("\n\n" );
}

void display(int *matrix,int row,int col)
{
	int i,j;
		for(i=0;i<row*col;i++)
		{
			if (i%col == 0)
				printf("\n");
			printf("%d ",matrix[i]);
		}
    printf("\n\n");
}

void *compute_element(void *args)
{
	int *ans = malloc(sizeof(int));
	*ans = 0;
	int *ptr = args;
	int cols = *ptr;
	
	for (int i = 0; i < cols; i++)
		*ans+= ptr[1 +i] * ptr[1 +cols +i];
	
	return (void*) ans;
}

int main()
{
  int i1,j1,i2,j2;
  int *matrixA,*matrixB,*resultant;
  printf("Enter Rows of Matrix A:");
	scanf("%d",&i1);
  printf("Enter Columns of Matrix A:");
  scanf("%d",&j1);
  matrixA = malloc(sizeof(int) *i1*j1);
  accept(matrixA,i1,j1);
  printf("Enter Rows of Matrix B:");
  scanf("%d",&i2);
  printf("Enter Columns of Matrix B:");
  scanf("%d",&j2);
  matrixB = malloc(sizeof(int) *i2*j2);
  accept(matrixB,i2,j2);
  printf("Matrix A is\n");
  display(matrixA,i1,j1);
  printf("Matrix B is\n");
  display(matrixB,i2,j2);
  int pos =0;
  if(j1==i2)
  {
    resultant=(int *)malloc(sizeof(int)*i1*j2);
    int *param;
    //Argumnents needed for multiplication
  
    pthread_t *thread_id = malloc(sizeof(int)*i1*j2);
    int t = 0;
    
    for (int k = 0; k < i1 *j2; k++) {
    	param = (int*)malloc(sizeof(int) * (1+2*j1) );
    	
    	param[0] = j1;
      //Creating row Arguments
      	int i = 1;
			int f= k/i1;
			
      for (int m = 0; m < j1; m++)
        param[i++] = *(matrixA + f*j1 + m);

		  for (int n = 0; n < i2; n++)
        param[i++] = *(matrixB +j2*n +k%j2);
      
			
			pthread_create((thread_id +t),NULL,compute_element,param);
			t++;
    }
    printf("Multiplication Complete\nRetrieving Arguments\n");

    void *status;
	int *value;

    for(int k = 0;k<i1*j2;k++)
    {
      pthread_join(thread_id[k], &status);
	  value = status ;
      printf("For thread [%li] recieved answer %d\n",*(thread_id + k),*value);
      resultant[pos++] = *value;
    }
    printf("\nA*B is\n");
    display(resultant,i1,j2);
  }
  else
    printf("Matrix cannot be multiplied");
  return 0;
}
