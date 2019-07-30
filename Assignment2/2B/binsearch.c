#include <stdio.h>

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

void display(int *a,int n)
{
  printf("\n[" );
  for (int i = 0; i < n; i++) {
    printf(" %d ",a[i]);
  }
  printf("]\n\n" );
}

void main(int argc, char const *argv[]) {
  int query;
  int arr[argc];
  for (int i = 0; i < argc; i++)
    arr[i] = atoi(argv[i]);
  display(arr,argc);
  printf("Enter Number to be searched:");
  scanf("%d",&query);
  int flag = binarySearch(arr,0,argc,query);
  if (flag == -1)
    printf("Number not found\n" );
  else
    printf("Number found at %d\n",flag );
 
}
