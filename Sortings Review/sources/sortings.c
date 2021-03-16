#include <stdio.h>
#include <stdlib.h>
#include <sortings.h>

// Function that does insertion sort
void insertionSort(int *arr, int length){
    // Auxiliar variables for the sorting
    int i, j, key;
    
    // The loop that sorts the array
    for (i = 1; i < length; i++){
        // Saves the actual key
        key = arr[i]; 
        
        // Saves how much times will check on the array
        j = i - 1; 
        
        // Checking the array j times
        while ((key < arr[j]) && (j >= 0)){ 
            // Copying the value of the next value backwards
            arr[j+1] = arr[j]; 
            j--;
        }

        // After checking the array j times, we sum 1 to put the key in the righ place    
        arr[j+1] = key;
    }
}

// Function that merge the array
void merge(int *arr, int start, int mid, int end){
    // Creating the array that will be merged
    int *aux_arr = (int*) malloc (((end - start) + 1) * sizeof(int));

    int i = start; // Index of first ordenated list (goes from start to mid )
    int j = mid + 1; // Index of second ordenated list (goes from mid+1 to end)
    int k = 0; // Index of the auxiliar array (goes from k to (end - start))    

    // Merging the ordenated lists in the auxiliar array
    while (i <= mid && j <= end){
        if (arr[i] <= arr[j]){
            aux_arr[k] = arr[i];
            i++;
        }
        else {
            aux_arr[k] = arr[j];
            j++;
        }
        k++;
    }

    // Merging possible not merged number in the first list
    while (i <= mid){
        aux_arr[k] = arr[i];
        i++;
        k++;
    }

    // Merging possible not merged number in the second list
    while (j <= end){
        aux_arr[k] = arr[j];
        j++;
        k++;
    }

    // Now we copy the auxiliar array to the original array
    for (i = start, k = 0; i <= end; i++, k++){
        arr[i] = aux_arr[k];
    }

    free(aux_arr);
}

// Function that mergeSort and array
void mergeSort(int *arr, int start, int end){
    // Base Case, array of size 1
    if (end <= start)
        return;

    // Calculating the actual vector size / 2
    int mid = start + (end - start) / 2;

    // Divide
    mergeSort(arr, start, mid); // Call for the left part 
    mergeSort(arr, mid+1, end); // Call for the right part

    // Conquer - Merge
    merge(arr, start, mid, end);
}

// Function that does bubbleSort 
void bubbleSort(int *arr, int length){
    int swap;
    for (int i = 0; i < length - 1; i++){
        for (int j = 0; j < length - i - 1; j++){
            if (arr[j] > arr[j+1]){
                swap = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swap;
            }
        }
    }
}

// Function that does cocktailSort
void cocktailSort(int *arr, int length){
    int ready, i, swap;
    do {
        ready = 0;
        
        for (i = length - 1; i > -1; i--){
            if (arr[i-1] > arr[i]){
                swap = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = swap;
      
                ready = 1;
            }
        }
        
        for (i = 0; i < length; i++){
            if (arr[i] > arr[i+1]){
                swap = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = swap;
      
                ready = 1;
            }
        }

    } while(ready);
}

// Function that selects the start of a list and selects the first element as the pivot
int startPivot(int start, int end){
    return start;
}

// Function that selects the center of a list and selects the central element as the pivot
int centralPivot(int start, int end){
    return start + (end - start) / 2;
}

// Function that selects and random element of the list to be the pivot
int randomPivot(int start, int end){
    // return random position from [start, end]
    return (int) (rand() % (end - start)) + start;
}

// Function that does quickSort
void quickSort(int *arr, int start, int end, int (*choosePivotFunction)()){
    // Base casem arrays of size 1
    if (end <= start)
        return;

    // Choosing the pivot where [--- l1 ---] <= p < [--- l2 ---]
    // Iterating through the l1 to ensure <= pivot
    // Iterating through the l2 to ensure > pivot
    int pivot = choosePivotFunction(start, end);

    // Change pivot with the first element of the array, this ensures that our code will work
    int tmp = arr[pivot];
    arr[pivot] = arr[start];
    arr[start] = tmp;

    pivot = start;
    // Iterates through the l1 <= pivot doing i++
    int i = start + 1;
    // Iterates through the l2 > pivot doing j--
    int j = end;

    while (i <= j){
        while (i <= end && arr[i] <= arr[pivot])
            i++;

        while (arr[j] > arr[pivot])
            j--;

        if (j > i){
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    // Posicioting the array in it's ordenated position, the position of the pivot is going to be j
    tmp = arr[pivot];
    arr[pivot] = arr[j];
    arr[j] = tmp;
    pivot = j;

    // Doing the recursive calls
    quickSort(arr, start, pivot - 1, choosePivotFunction);
    quickSort(arr, pivot + 1, end, choosePivotFunction);
}

// Function that ensures a node is in maxheap condition
void maxHeapify(int *arr, int nodePos, int length){
    // Initialize smallest as root
    int biggest = nodePos;
    // Left and right son;
    int left = (2 * nodePos) + 1;
    int right = (2 * nodePos) + 2;

    // Checking who is the biggest son
    if (left < length && arr[left] > arr[biggest])
        biggest = left;

    if (right < length && arr[right] > arr[biggest])
        biggest = right;

    // If the biggest isn't the root
    if (biggest != nodePos){
        // Swaping root for the biggest
        int temp = arr[nodePos];
        arr[nodePos] = arr[biggest];
        arr[biggest] = temp;

        // Recursively heapify the affected sub-tree
        maxHeapify(arr, biggest, length);
    }
}

// Function that builds a maxheap
void buildMaxHeap(int *arr, int length){
    // Executes from the center to the start (length / 2)
    for (int i = length / 2; i >= 0; i--)
        maxHeapify(arr, i, length);
}

// Function that does heapSort in ascending order
void ascendingHeapSort(int *arr, int length){
    buildMaxHeap(arr, length);

    for (int i = length; i >= 0; i--){
        // Selecting the bigger node (root)
        int bigger = arr[0];

        // Moving the root to the end
        arr[0] = arr[i];
        arr[i] = bigger;

        // Remounts the maxheap, always from the root
        maxHeapify(arr, 0, i);
    }
}

// Function that ensures a node is in minheap condition
void minHeapify(int *arr, int nodePos, int length){
    // Initialize smallest as root
    int smallest = nodePos;
    // Left and right son;
    int left = (2 * nodePos) + 1;
    int right = (2 * nodePos) + 2;

    // Checking who is the smallest son
    if (left < length && arr[left] < arr[smallest])
        smallest = left;

    if (right < length && arr[right] < arr[smallest])
        smallest = right;

    // If the smallest isn't the root
    if (smallest != nodePos){
        // Swaping root for the smallest
        int temp = arr[nodePos];
        arr[nodePos] = arr[smallest];
        arr[smallest] = temp;

        // Recursively heapify the affected sub-tree
        minHeapify(arr, smallest, length);
    }
}

// Function that builds a minheap
void buildMinHeap(int *arr, int length){
    // Executes from center to the start (length / 2)
    for (int i = length / 2; i >= 0; i--)
        minHeapify(arr, i, length);
}

// Function that does heapSort in descing order
void descendingHeapSort(int *arr, int length){
    buildMinHeap(arr, length);

    for (int i = length; i >= 0; i--){
        // Selecting the smallest node (root)
        int smallest = arr[0];

        // Moving the root to the end
        arr[0] = arr[i];
        arr[i] = smallest;

        // Remounts the maxheap, always from the root
        minHeapify(arr, 0, i);
    }
}

// Function that does coutingSort with records
void countingSort(RECORD *records){
    
}

// Function that does bucketSort with records
void BucketSort(RECORD *records){

}

// Function that does radixSort using as a sub routine countingSort or bucketSort and using 256 base
void radixSort256(){

}
