#ifndef SORTING_H
    #define SORTING_H

    #include <uspotify.h>

    int startPivot(int start, int end);
    int centralPivot(int start, int end);
    int randomPivot(int start, int end);
    void ordenateDataFrame(USPOTIFY *uspotify, int start, int end, int (*choosePivotFunction)());
    void ordenateMatrix(CELL **matrix, int length);

#endif