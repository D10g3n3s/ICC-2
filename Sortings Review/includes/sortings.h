#ifndef SORTS_H
    #define SORTS_H
    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct _record{
        int key;
        char *string;
    } RECORD;

    void insertionSort(int *array, int length);
    void mergeSort(int *array, int start, int end);
    int startPivot(int start, int end);
    int centralPivot(int start, int end);
    int randomPivot(int start, int end);
    void quickSort(int *array, int start, int end, int (*choosePivotFunction)());
    void ascendingHeapSort(int *array, int length);
    void descendingHeapSort(int *array, int length);
    void bubbleSort(int *array, int length);
    void cocktailSort(int *array, int length);
    void countingSort();
    void bucketSort();
    void radixSort256();

#endif
