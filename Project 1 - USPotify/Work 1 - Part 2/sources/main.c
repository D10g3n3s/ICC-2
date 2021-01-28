/*
 _____________________________________________________________
|     ___________________________________________________     |
|    |             Universidade de São Paulo             |    |
|    |                                                   |    |
|    | Instituto de Ciências Matemáticas e de Computação |    |
|    |                                                   |    |
|    |           Diógenes Silva Pedro BCC 020            |    |
|    |                                                   |    |
|    |                  nUSP: 11883476                   |    |
|    |                                                   |    |
|    |               diogenes.pedro@usp.br               |    |
|    |                                                   |    |
|    |            diogenes.pedro60@gmail.com             |    |
|    |                                                   |    |
|    |                    T2-USPotify                    |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <sortings.h>

int main(){
    // Allocating the heap memory
    USPOTIFY *uspotify = createUSPOTIFY();

    uspotify = createDataFrame(uspotify);

    ordenateDataFrame(uspotify, 0, uspotify->nTracks - 1, randomPivot);

    CELL **dissimilarityMatrix = createDissimilarityMatrix(uspotify);

    ordenateMatrix(dissimilarityMatrix, uspotify->nTracks);

    KNN(uspotify, dissimilarityMatrix);

    // Deallocating the heap memory
    deallocateMatrix(dissimilarityMatrix, uspotify->nTracks);
    deallocatesCSV(uspotify);

    return 0;
}