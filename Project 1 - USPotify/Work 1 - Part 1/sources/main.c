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
|    |                    T1-USPotify                    |    |
|    |___________________________________________________|    |
|_____________________________________________________________|
       |_______________________________________________|       
*/

#include <stdio.h>
#include <stdlib.h>
#include <uspotify.h>

int main(){
    // Allocating the heap memory
    USPOTIFY *uspotify = createUSPOTIFY();

    uspotify = createDataFrame(uspotify);

    ordenateDataFrame(uspotify, 0, uspotify->nArtist - 1);

    printList(uspotify);

    // Deallocating the heap memory
    deallocatesCSV(uspotify);

    return 0;
}