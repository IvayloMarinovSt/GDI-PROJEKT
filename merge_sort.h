//
// Created by ivaylo on 22.12.19.
//
#include <limits.h>
#include <stdlib.h>

/**
 * Merge - splits the given unsorted array in two and then merges both smaller arrays into one
 *         whilst sorting them
 * @param unsortedField - the unsorted field
 * @param begin - the position where the sorting begins i.e. choosing 5 will begin from position unsortedArray[5]
 * @param middle - middle point of the unsorted array that is to be sorted
 * @param end - the position where the sorting ends i.e. choosing 10 will end the algorithm at position unsortedArray[10]
 * @param choice - choice for the sorting algorithm
 *              1- sort according to latitude
 *              2- sort according to longitude
 *              3- sort according to abstand
 *              4- sort according to TTTs
 */
void Merge(struct datapoint *unsortedField, int begin, int middle, int end, char choice) {
    int lenghtLeft = middle - begin + 1;
    int lenghtRight = end - middle;
    struct datapoint *leftField = (struct datapoint *) malloc((lenghtLeft + 2) * sizeof(struct datapoint));
    struct datapoint *rightField = (struct datapoint *) malloc((lenghtRight + 2) * sizeof(struct datapoint));

    for (int i = 1; i <= lenghtLeft + 1; i++) {
        leftField[i] = unsortedField[begin + i - 1];
    }
    for (int j = 1; j <= lenghtRight + 1; j++) {
        rightField[j] = unsortedField[middle + j];
    }

    int i = 1;
    int j = 1;
    switch (choice) {
        // Sort according to the latitude of the point
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
            break;

            //Sort according to longitude of the point
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
            break;

            // sort according to distance(abstand)
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
            break;

            // sort according to temperature (TTT)
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
            break;
    }
    free(leftField);
    free(rightField);
}


/**
 * Merge_sort - sort the data points according to a chosen parameter, possible choices listed under choice parameter
 * @param unsortedArray - the unsorted array that has to be sorted
 * @param begin - the position where the sorting begins i.e. choosing 5 will begin from position unsortedArray[5]
 * @param end - the position where the sorting ends i.e. choosing 10 will end the algorithm at position unsortedArray[10]
 * @param choice - choice for the sorting algorithm
 *              1- sort according to latitude
 *              2- sort according to longitude
 *              3- sort according to abstand
 *              4- sort according to TTT
 */
void Merge_sort(struct datapoint *unsortedArray, int begin, int end, char choice) {
    int middle;
    if (begin < end) {
        middle = (begin + end) / 2;
        /// calculation of the middle position, so that the array can be split in two
        Merge_sort(unsortedArray, begin, middle, choice);
        Merge_sort(unsortedArray, middle + 1, end, choice);
        /// splitting the array in two and sorting the two smaller arrays (recursively)
        Merge(unsortedArray, begin, middle, end, choice);
        /// merging the both already sorted arrays
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
