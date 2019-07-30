#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

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

void display(int a[], int n)
{
  printf("[");
  for (int i = 0; i < n; i++) {
    printf("%d ",a[i]);
  }
  printf("]\n");
}

int main()
{
  printf("Demonstrating Zombie State\n");
  int n1,n2;
  printf("Enter number of element for the Parent Process[%d]:",getpid());
  scanf("%d",&n1);
  int i,*a1,*a2;
  a1 = malloc(n1*sizeof(int));
  for ( i = 0; i < n1; i++) {
    printf("Enter Element (%d):",(i+1));
    scanf("%d",&a1[i]);
  }
  printf("\n\nEntered Elements are :");
  display(a1,n1);
  printf("\nEnter number of element for the Child Process:");
  scanf("%d",&n2);
  a2 = malloc(n2*sizeof(int));
  for ( i = 0; i < n2; i++) {
    printf("Enter Element (%d):",(i+1));
    scanf("%d",&a2[i]);
  }
  printf("\n\nEntered Elements are :");
  display(a2,n2);
  printf("\n\nParent Process Spawing New Process[%d]\n",getpid());
  pid_t child = fork();
  if(child>0)
  {
    printf("Parent Process Starting Sorting[%d]\n\n",getpid());
    printf("Input Array is:");
    display(a1,n1);
    printf("Parent Process starting Sorting[%d]\n",getpid());
    quickSort(a1,0,n1-1);
    printf("Parent Process waiting for child Process to complete Sorting[%d] (Parent goes into sleep)\n\n",getpid());
    sleep(15);
    pid_t completed = wait(NULL);
    printf("Child Process [%d] has completed\n\n",completed);
    printf("Parent Process Result: ");
    display(a1,n1);
    printf("Parent Process [%d] has completed\n\n",getpid());
    return 0;
  }
  else
  {
    printf("Child Process Starting Sorting[%d]\n\n",getpid());
    printf("Input Array is:");
    display(a2,n2);
    quickSort(a2,0,n2-1);
    printf("\nChild Process Completed Sorting[%d]\n\n",getpid());
    printf("Child Process Result: ");
    display(a2,n2);
    printf("Child returns zero but parent is Asleep hence Zombie State\n\n\n");
    return 0;
  }
}
