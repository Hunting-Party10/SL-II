#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void display(int *a,int n)
{
  printf("\n[" );
  for (int i = 0; i < n; i++) {
    printf(" %d ",a[i]);
  }
  printf("]\n\n" );
}

int main(int argc, char const *argv[]) {
  int n;
  printf("Enter the size of the array:");
  scanf("%d",&n );
  int *a = malloc(n*sizeof(int));
  for (int i = 0; i < n; i++) {
    printf("Enter number [%d] :",(i+1));
    scanf("%d",&a[i] );
  }
  printf("Parent Process Sorting the array\n");
  display(a,n);
  quickSort(a,0,n-1);
  printf("Parent Process has completed Sorting\n");
  display(a,n);
  char *args[n+1];
  printf("Parent process converting array to string\n");
  int i;
  for (i = 0; i < n; i++) {
    char *buffer;
    buffer = malloc(sizeof(a[i]));
    sprintf(buffer,"%d",a[i]);
    args[i] = malloc(sizeof(char));
    *args[i] = *buffer;
  }
  args[i] = NULL;

  printf("Array has been converted to string\n");
  int pid = fork();
  if (pid == 0) {
    printf("Child Process starting binary search\nChild Process is calling external file\n");
    execvp("./binsearch",args);
  }
  else
  {
    printf("Parent Process waiting for child to complete\n");
    wait(NULL);
    printf("Child Process has completed,Exiting\n");
  }
  return 0;
}
