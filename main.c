#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define POINTS 680000
#define RADIUS 6371
#define PI 3.14159265
#define DEGTORAD 0.01745329

struct datapoint {
    char event[30]; // event information
    char datetime[30]; // date and time information
    double latitude; // latitude information (Breitengrad)
    double longitude; // longtitude information (Laengengrad)
    double x;
    double y;
    double z;
    int altitude; // Geopotential height above sea level integrated from pressure, temperature and humidity
    int hhh; // Geopotential height above sea level derived from GPS receiver mounted on radiosonde
    int hgeom1; //
    int hgeom2; //
    double PPPP; // air pressure (measured in hPa, hectoPascal)
    double TTT; // air temperatute measured in Celsius
    double RH; // relative Humidity
    int dd; // wind direction in degrees
    double ff; // wind speed
    double abstand;
};

#include "merge_sort.h"

void xyz_calc(struct datapoint *dp);

void euclidean_dist(struct datapoint *dp1, struct datapoint *dp2);

void orthodromic_dist(struct datapoint *dp1, struct datapoint *dp2);

/*****************************************************MAIN***********************************************************/
int main() {
    // gets time at start
    clock_t begin = clock();
    printf("Please choose user\n1 - ivaylo\n2 - simeon\n3 - matviy\n4- marvin\n");
    char choice;
    char *fileNameString;
    char *writeFile;
    scanf("%c", &choice);
    switch (choice) {
        case '1': // ivaylo
            fileNameString = "D:\\FH-SWF\\1. Semester\\Grundlagen der Informatik\\Programming Projekt\\GDI-PROJEKT\\DataToRead_without_missing_info.txt";
            writeFile = "D:\\FH-SWF\\1. Semester\\Grundlagen der Informatik\\Programming Projekt\\GDI-PROJEKT\\WriteData.txt";
            break;
        case '2': // simeon
            fileNameString = "/home/simeon/Desktop/GDI-PROJEKT/DataToRead.tab";
            writeFile = "/home/simeon/Desktop/GDI-PROJEKT/WriteData.txt";
            break;
        case '3': // matviy
            fileNameString = "C:\\Users\\matvi\\Documents\\GitHub\\GDI-PROJEKT\\DataToRead.tab";
            writeFile = "C:\\Users\\matvi\\Documents\\GitHub\\GDI-PROJEKT\\WriteData.txt";
            break;
        case '4': // Marvin
            fileNameString = "C:\\Users\\Rem\\Desktop\\FH SWF\\GdI\\1. Semester\\GDI-PROJEKT\\DataToRead.tab";
            writeFile = "C:\\Users\\Rem\\Desktop\\FH SWF\\GdI\\1. Semester\\GDI-PROJEKT\\WriteData.txt";
            break;
    }

    FILE *fileToRead = fopen(fileNameString, "r");
    // open source file
    // if fileToRead doesn't exist print error close it and exit the program
    if (fileToRead == NULL) {
        printf("no such file found");
        return 0;
    }
    // open destination file
    FILE *fileToWrite;
    fileToWrite = fopen(writeFile, "w");

    struct datapoint *dp = (struct datapoint *) malloc(POINTS * sizeof(struct datapoint));

    int fail = 0;
    int success;
    int prev = 0;
    int i = 0;
    // reads the chosen amount of data points and deletes any points with missing values
    //for (i = 0; i < POINTS; i++) {
    while (!feof(fileToRead)) {
        success = fscanf(fileToRead, "%s\t%s\t%lf\t%lf\t%d\t%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\t%lf\n", dp[i].event,
                         dp[i].datetime, &dp[i].latitude, &dp[i].longitude, &dp[i].altitude, &dp[i].hhh,
                         &dp[i].hgeom1,
                         &dp[i].hgeom2, &dp[i].PPPP, &dp[i].TTT, &dp[i].RH, &dp[i].dd, &dp[i].ff);
        if (success != 13)fail = 1;
        if (success != 13 || fail != 0 || prev != 0) {
            i--;
            prev = fail;
            fail = 0;
        }
        ++i;
    }

    Merge_sort(dp, 0, i, '1');

    // puts all of the read data in a new file with the number of the point in front of the values
    for (int l = 0; l < i; l++) {
        fprintf(fileToWrite, "%s\t%s\t%.5lf\t%.5lf\t%d\t%d\t%d\t%d\t%.2lf\t%.2lf\t%.1lf\t%d\t%.1lf\n",
                dp[l].event,
                dp[l].datetime, dp[l].latitude, dp[l].longitude,
                dp[l].altitude, dp[l].hhh, dp[l].hgeom1, dp[l].hgeom2, dp[l].PPPP, dp[l].TTT, dp[l].RH, dp[l].dd,
                dp[l].ff);
    }

    fclose(fileToRead);
    fclose(fileToWrite);
    free(dp);

    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\nExecution time: %lf sec\n", time_spent);
    /* will only calculate the time the processor spent working i.e. if the programm
     * waits for input 15 seconds but the processor calculates 10 seconds the output
     * for execution time will be 10 seconds not 25
     */
    return 0;
}

/***************************************************END OF MAIN******************************************************/

void xyz_calc(struct datapoint *dp) {
    double betaRad, alfaRad;
    betaRad = (90 - dp->longitude) * DEGTORAD;
    alfaRad = dp->latitude * DEGTORAD;
    dp->x = RADIUS * sin(betaRad) * cos(alfaRad);
    dp->y = RADIUS * sin(betaRad) * sin(alfaRad);
    dp->z = RADIUS * cos(betaRad);
}

/* Function to calculate euclidean distance between two points.
 * Distance will be saved in the abstand value of the first data point(dp1)
 * dp1 - the first of the both data points between which the distance will be calculated
 * dp2 - the second data point */
void euclidean_dist(struct datapoint *dp1, struct datapoint *dp2) {
    xyz_calc(dp1);
    xyz_calc(dp2);
    /*printf("(x1 - x2)² = (%lf - %lf)² = %lf\n",dp1->x,dp2->x,pow(dp1->x-dp2->x,2) );
     * printf("(x1 - x2)² = (%lf - %lf)² = %lf\n",dp1->y,dp2->y,pow(dp1->y-dp2->y,2) );
     * printf("(x1 - x2)² = (%lf - %lf)² = %lf\n",dp1->z,dp2->z,pow(dp1->z-dp2->z,2) );
     */
    dp1->abstand = sqrt(pow(dp1->x - dp2->x, 2) + pow(dp1->y - dp2->y, 2) + pow(dp1->z - dp2->z, 2));
}


void orthodromic_dist(struct datapoint *dp1, struct datapoint *dp2) {
    dp2->abstand = RADIUS * acos(sin(dp1->latitude * DEGTORAD) * sin(dp2->latitude * DEGTORAD) +
                                 cos(dp1->latitude * DEGTORAD) * cos(dp2->latitude * DEGTORAD) *
                                 cos((dp1->longitude - dp2->longitude) * DEGTORAD));
}
