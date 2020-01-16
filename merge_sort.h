//
// Created by ivaylo on 22.12.19.
//
#include <limits.h>
#include <stdlib.h>


void Merge(struct datapoint *unsortedField, int begin, int middle, int end, char choice) {
    int lenghtLeft = middle - begin + 1;
    int lenghtRight = end - middle;
    struct datapoint *leftField = (struct datapoint *) malloc((lenghtLeft + 2) * sizeof(struct datapoint));
    struct datapoint *rightField = (struct datapoint *) malloc ((lenghtRight + 2) * sizeof(struct datapoint));

    for (int i = 1; i <= lenghtLeft + 1; i++) {
        leftField[i] = unsortedField[begin + i - 1];
    }
    for (int j = 1; j <= lenghtRight + 1; j++) {
        rightField[j] = unsortedField[middle + j];
    }

    int i = 1;
    int j = 1;
    // printf("TEST MERGE\n");
    switch (choice) {
        case '1':
            leftField[lenghtLeft + 1].latitude = INT_MAX;
            rightField[lenghtRight + 1].latitude = INT_MAX;
            // printf("TEST MERGE 1\n");
            for (int k = begin; k <= end; k++) {
                if (leftField[i].latitude <= rightField[j].latitude) {
                    unsortedField[k] = leftField[i];
                    i++;
                } else {
                    unsortedField[k] = rightField[j];
                    j++;
                }
            }
            free(leftField);
            free(rightField);
            break;


        case '2':
            leftField[lenghtLeft + 1].longitude = INT_MAX;
            rightField[lenghtRight + 1].longitude = INT_MAX;
            for (int k = begin; k <= end; k++) {
                if (leftField[i].longitude <= rightField[j].longitude) {
                    unsortedField[k] = leftField[i];
                    i++;
                } else {
                    unsortedField[k] = rightField[j];
                    j++;
                }
            }
            free(leftField);
            free(rightField);
            break;


        case '3':
            leftField[lenghtLeft + 1].abstand = INT_MAX;
            rightField[lenghtRight + 1].abstand = INT_MAX;
            for (int k = begin; k <= end; k++) {
                if (leftField[i].abstand <= rightField[j].abstand) {
                    unsortedField[k] = leftField[i];
                    i++;
                } else {
                    unsortedField[k] = rightField[j];
                    j++;
                }
            }
            free(leftField);
            free(rightField);
            break;


        case '4':
            leftField[lenghtLeft + 1].TTT = INT_MAX;
            rightField[lenghtRight + 1].TTT = INT_MAX;
            for (int k = begin; k <= end; k++) {
                if (leftField[i].TTT <= rightField[j].TTT) {
                    unsortedField[k] = leftField[i];
                    i++;
                } else {
                    unsortedField[k] = rightField[j];
                    j++;
                }
            }
            free(leftField);
            free(rightField);
            break;
    }
}

/* Merge sort function
 * unsortedArray- the unsorted array that has to be sorted
 * begin - the position where the sorting begins i.e. choosing 5 will begin from position array[5]
 * end - the position where the sorting ends i.e. choosing 10 will end the algorithm at position array[10]
 * choice- choice for the sorting algorithm
 *          1- sort according to latitude
 *          2- sort according to longitude
 *          3- sort according to abstand
 *          4- sort according to TTT
 */
void Merge_sort(struct datapoint *unsortedArray, int begin, int end, char choice) {
    int middle;
    if (begin < end) {
        // calculation of the middle position, so that the array can be split in two
        middle = (begin + end) / 2;
        // printf("TEST MERGE SORT\n");
        // splitting the array in two and sorting the two smaller arrays (recursively)
        Merge_sort(unsortedArray, begin, middle, choice);
        Merge_sort(unsortedArray, middle + 1, end, choice);
        // merging the both already sorted arrays
        Merge(unsortedArray, begin, middle, end, choice);
    }
}

// void ausgabe(int *array, int groesse){
//     for(int i=0; i<groesse; i++){
//         printf("%d ",array[i]);
//     }
//     printf("\n");
// }
//
// void init_f(int *pointer, int groesse){
//     for(int i=0;i<groesse;i++){
//         pointer[i]=rand()%10000;
//
//     }
// }
