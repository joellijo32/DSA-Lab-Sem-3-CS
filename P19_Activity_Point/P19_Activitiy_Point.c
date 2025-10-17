#include <stdio.h>
#include <stdlib.h>


void Sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}


int main() {
    int n, k;

    printf("Enter the number of events: ");
    scanf("%d", &n);

    printf("Enter the maximum number of events you can participate in: ");
    scanf("%d", &k);

    int A[n],len=0;

    printf("Enter the activity points for each event:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
len++;
    }

    Sort(A,len);

    int max_points=0;
    for (int i = 0; i < k; i++) {
        max_points+=A[i];
    }
    printf("Maximum activity points you can earn: %d\n", max_points);
    return 0;
}