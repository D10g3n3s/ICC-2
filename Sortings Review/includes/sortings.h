#ifndef SORTS_H
    #define SORTS_H
    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct _record{
        int key;
        char *string;
    } RECORD;

    typedef struct _node NODE;

    struct _node{
        NODE *next;
        RECORD elem;
    };

    typedef struct {
        NODE *head;
        NODE *tail;
    } BUCKET;

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
    void countingSort(RECORD *records, int length);
    void bucketSort(RECORD *records, int length);
    void radixSort256(RECORD *records, int length);

#endif
