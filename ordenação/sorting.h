#ifndef SORTING_H
#define SORTING_H

#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void countingSort(int arr[], int n);

void bucketSort(int arr[], int n);

void radixSort(int arr[], int n);

#endif