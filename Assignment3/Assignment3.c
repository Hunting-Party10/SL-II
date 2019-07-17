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
			scanf("%d",(matrix + row*i + j));
		printf("Row %d complete\n",(i+1));
	}
  printf("\n\n" );
}

void display(int *matrix,int row,int col)
{
	int i,j;
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
				printf("%d ",*(matrix + row*i + j));
			printf("\n");
		}
    printf("\n\n");
}

void *compute_element(void *args)
{
  return (void *)0;
}

int main()
{
  int i1,j1,i2,j2;
  int *matrixA,*matrixB,*resultant;
  printf("Enter Rows of Matrix A\n");
	scanf("%d",&i1);
  printf("Enter Columns of Matrix A\n");
  scanf("%d",&j1);
  matrixA = malloc(sizeof(int) *i1*j1);
  accept(matrixA,i1,j1);
  printf("Enter Rows of Matrix B\n");
  scanf("%d",&i2);
  printf("Enter Columns of Matrix B\n");
  scanf("%d",&j2);
  matrixB = malloc(sizeof(int) *i2*j2);
  accept(matrixB,i2,j2);
  display(matrixA,i1,j1);
  display(matrixB,i2,j2);
  if(j1==i2)
  {
    resultant=(int *)malloc(sizeof(int)*i1*j2);
    int param[2+j1+i2];
    //Argumnents needed for multiplication
    param[0] = j1;
    param[1] = i2;
    pthread_t *thread_id = malloc(sizeof(int)*i1*j2);
    int t = 0;
    for (int k = 0; k < i1; k++) {

      //Creating row Arguments
      int i = 2;
      for (int m = 0; m < j1; m++)
        param[i++] = *(matrixA + k +m);

      for (int l = 0; l < j2; l++) {

      //Creating Column Arguments
        int t = i;
        for (int n = 0; n < i2; n++)
          param[t] = *(matrixA + i2*n +l);
        pthread_create((thread_id +t),NULL,compute_element,param);

      }
    }
    printf("Multiplication Complete\nRetrieving Arguments\n");

    void *status =0;
    for(int k = 0;k<i1*j2;k++)
    {
      pthread_join(thread_id[k], &status);
      printf("For thread [%li] recieved answer\n",*(thread_id + k));//,(int)result);
    }

  }
  else
    printf("Matrix cannot be multiplied");


  return 0;
}
