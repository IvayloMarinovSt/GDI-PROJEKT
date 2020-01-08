//
// Created by ivaylo on 22.12.19.
//
#include <limits.h>
void Merge(int* unsortedField, int begin, int middle, int end){
    int lenghtLeft= middle - begin + 1;
    int lenghtRight= end - middle;
    int leftField[lenghtLeft + 1], rightField[lenghtRight + 1];

    for(int i=1; i <= lenghtLeft + 1; i++){
        leftField[i]=unsortedField[begin + i - 1];
    }
    for(int j=1; j <= lenghtRight + 1; j++){
        rightField[j]=unsortedField[middle + j];
    }
    leftField[lenghtLeft + 1]=INT_MAX ;
    rightField[lenghtRight + 1]=INT_MAX ;
    int i=1;
    int j=1;
    for(int k=begin; k <= end; k++){
        if(leftField[i] <= rightField[j]){
            unsortedField[k]=leftField[i];
            i++;
        }else{
            unsortedField[k] = rightField[j];
            j++;
        }
    }
}
/* Merge sort function
 * unsortedArray- the unsorted array that has to be sorted
 * begin - the position where the sorting begins i.e. choosing 5 will begin from position array[5]
 * end - the position where the sorting ends i.e. choosing 10 will end the algorithm at position array[10]
 */
void Merge_sort(int* unsortedArray, int begin, int end){
    int middle;
    if(begin < end){
        // calculation of the middle position, so that the array can be split in two
        middle=(begin + end) / 2;
        // splitting the array in two and sorting the two smaller arrays (recursively)
        Merge_sort(unsortedArray, begin , middle);
        Merge_sort(unsortedArray, middle + 1, end);
        // merging the both already sorted arrays
        Merge(unsortedArray, begin, middle, end);
    }
}

void ausgabe(int *array, int groesse){
    for(int i=0; i<groesse; i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

void init_f(int *pointer, int groesse){
    for(int i=0;i<groesse;i++){
        pointer[i]=rand()%10000;

    }
}
