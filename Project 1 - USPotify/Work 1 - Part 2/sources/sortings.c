#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sortings.h>

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
    // return random position from range [start, end]
    return (int) (rand() % (end - start)) + start;
}
 
// Function that ordenates the data set using quickSort
void ordenateDataFrame(USPOTIFY *uspotify, int start, int end, int (*choosePivotFunction)()){
    // Base case, arrays of size 1
    if (end <= start)
        return;

    // Chossing the pivot and changing it with the first element of the array
    int pivot = choosePivotFunction(start, end);

    INFO *tmp = uspotify->infos[pivot];
    uspotify->infos[pivot] = uspotify->infos[start];
    uspotify->infos[start] = tmp;

    pivot = start;
    int i = start + 1;
    int j = end;

    while (i <= j){
        while (i <= end && strcmp(uspotify->infos[i]->tracks->trackID, uspotify->infos[pivot]->tracks->trackID) <= 0)
            i++;
        
        while (strcmp(uspotify->infos[j]->tracks->trackID, uspotify->infos[pivot]->tracks->trackID) > 0)
            j--;

        if (j > i){
            tmp = uspotify->infos[i];
            uspotify->infos[i] = uspotify->infos[j];
            uspotify->infos[j] = tmp;
        }
    }

    // Positioning the array in it's ordenated position, j is the pivot position
    tmp = uspotify->infos[pivot];
    uspotify->infos[pivot] = uspotify->infos[j];
    uspotify->infos[j] = tmp;
    pivot = j;

    // Doing the recursive calls
    ordenateDataFrame(uspotify, start, pivot - 1, choosePivotFunction);
    ordenateDataFrame(uspotify, pivot + 1, end, choosePivotFunction);
}

// Function that ordenates a line of the dissimilarity matrix
void ordenateMatrixLine(CELL *matrixLine, int length){
    // Allocate the counting and the auxiliar array
    int counting[256] = {0}; // Counting array
    int positions[256]; // Accumulated count (positions)
    CELL *lineCopy = malloc(length * sizeof(CELL));
    
    // Value to discretize keys to ordenate
    int P = 1000000;

    // Parcionating the key in digits using base 256
    // 32 bits, 4 blocks of 8 bits
    for (int shift = 0; shift <= 24; shift += 8){
        // Counting + copy
        for (int j = 0; j < length; j++){
            // Extracting a block of 8 bits
            int keyPosition = ((int) (matrixLine[j].distance * P) >> shift) & 255;
            // Counting
            counting[keyPosition]++;
            lineCopy[j] = matrixLine[j];
        }

        // Accumulated count
        positions[0] = 0;
        for (int i = 1; i < 256; i++){
            positions[i] = positions[i - 1] + counting[i - 1];
            counting[i - 1] = 0;
        }

        // Copying the elements in the right position
        for (int j = 0; j < length; j++){
            // Extracting the key (8 bits)
            int keyPosition = ((int) (lineCopy[j].distance * P) >> shift) & 255;
            // Ordenate in the position keyPosition
            matrixLine[positions[keyPosition]] = lineCopy[j];
            // Increment the position
            positions[keyPosition]++;
        }
    }

    // Deallocating the records copy
    free(lineCopy);
}

// Function that ordenates the dissimilarity matrix using base 256
void ordenateMatrix(CELL **matrix, int length){
    for (int i = 0; i < length; i++)
        ordenateMatrixLine(matrix[i], length);
}