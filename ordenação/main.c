#include <stdio.h>
#include <string.h>
#include "sorting.h"

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {9, 2, 3, 4, 3, 2, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int arr2[] = {61, 42, 67, 27, 17, 75, 56, 93, 76, 46, 63, 55, 70, 59, 98, 9, 7, 67, 95, 90};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {151, 531, 121, 348, 935, 320, 988, 191, 529, 487, 170, 933, 617, 405, 232};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    int arr_copy[n2];

    printf("--- Counting Sort ---\n");
    printf("Original: ");
    printArray(arr1, n1);
    countingSort(arr1, n1);
    printf("Ordenado: ");
    printArray(arr1, n1);
    printf("\n");

    printf("--- Bucket Sort ---\n");
    printf("Original: ");
    printArray(arr2, n2);
    memcpy(arr_copy, arr2, n2 * sizeof(int));
    bucketSort(arr_copy, n2);
    printf("Ordenado: ");
    printArray(arr_copy, n2);
    printf("\n");

    printf("--- Radix Sort ---\n");
    printf("Original: ");
    printArray(arr3, n3);
    radixSort(arr3, n3);
    printf("Ordenado: ");
    printArray(arr3, n3);

    return 0;
}