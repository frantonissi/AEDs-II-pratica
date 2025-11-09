#include "sorting.h"
#include <stdlib.h>

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

struct Node* insertionSortList(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct Node* sorted = NULL;
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

void countingSortForRadix(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    free(output);
}

void countingSort(int arr[], int n) {
    if (n <= 1) return;
    int max = getMax(arr, n);
    int* count = (int*)calloc(max + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
    free(count);
}

void bucketSort(int arr[], int n) {
    if (n <= 1) return;
    
    int numBuckets = 10;
    struct Node** buckets = (struct Node**)calloc(numBuckets, sizeof(struct Node*));

    int max = getMax(arr, n);
    if (max == 0) max = 1; 

    for (int i = 0; i < n; i++) {
        long long val = (long long)arr[i];
        long long max_val = (long long)max;
        int bucketIndex = (int)((val * numBuckets) / (max_val + 1));
        
        if(bucketIndex >= numBuckets) bucketIndex = numBuckets - 1;
        if(bucketIndex < 0) bucketIndex = 0;

        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = buckets[bucketIndex];
        buckets[bucketIndex] = newNode;
    }

    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = insertionSortList(buckets[i]);
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}

void radixSort(int arr[], int n) {
    if (n <= 1) return;
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}
#include <stdio.h>
#include <string.h>
#include "sorting.h"

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

