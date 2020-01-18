/**
 * Project for Grundlagen der Informatik in years 2019/2020 first semester
 * Participants in the project are: Marvin Krajewski, Ivaylo Marinov, Matviy Popovych and Simeon Antonov
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define POINTS 680000
#define RADIUS 6371
#define PI 3.14159265
#define DEGTORAD 0.01745329

struct datapoint {
    char event[30]; /// event information
    char datetime[30]; /// date and time information
    double latitude; /// latitude information (Breitengrad)
    double longitude; /// longtitude information (Laengengrad)
    double x; /// x-coordinate value
    double y; /// y-coordiante value
    double z; /// z-coordinate value
    int altitude; /// Geopotential height above sea level integrated from pressure, temperature and humidity
    int hhh; /// Geopotential height above sea level derived from GPS receiver mounted on radiosonde
    int hgeom1; //
    int hgeom2; //
    double PPPP; /// air pressure (measured in hPa, hectoPascal)
    double TTT; /// air temperatute measured in Celsius
    double RH; /// relative Humidity
    int dd; /// wind direction in degrees
    double ff; /// wind speed
    double abstand; /// distance
};

#include "C:\\Users\\Rem\\Desktop\\FH SWF\\GdI\\1. Semester\\GDI-PROJEKT\\merge_sort.h"

void xyz_calc(struct datapoint *dp);

void euclidean_dist(struct datapoint *dp1, struct datapoint *dp2);

void orthodromic_dist(struct datapoint *dp1, struct datapoint *dp2);

void Polar_coordinates(struct datapoint *dp);

/*****************************************************MAIN***********************************************************/
int main() {
    // gets time at start
    clock_t begin = clock();
    printf("Please choose user\n1 - ivaylo\n2 - simeon\n3 - matviy\n4- marvin\n");
    char chooseUser;
    char *fileNameString;
    char *writeFile;
    scanf("%c", &chooseUser);
    // asks who the user of the program is so that the paths to the files match with those on their system
    switch (chooseUser) {
        case '1': // Ivaylo
            fileNameString = "D:\\FH-SWF\\1. Semester\\Grundlagen der Informatik\\Programming Projekt\\GDI-PROJEKT\\DataToRead_without_missing_info.txt";
            writeFile = "D:\\FH-SWF\\1. Semester\\Grundlagen der Informatik\\Programming Projekt\\GDI-PROJEKT\\WriteData.txt";
            break;
        case '2': // Simeon
            fileNameString = "/home/simeon/Desktop/GDI-PROJEKT/DataToRead.tab";
            writeFile = "/home/simeon/Desktop/GDI-PROJEKT/WriteData.txt";
            break;
        case '3': // Matviy
            fileNameString = "C:\\Users\\matvi\\Documents\\GitHub\\GDI-PROJEKT\\DataToRead.tab";
            writeFile = "C:\\Users\\matvi\\Documents\\GitHub\\GDI-PROJEKT\\WriteData.txt";
            break;
        case '4': // Marvin
            fileNameString = "C:\\Users\\Rem\\Desktop\\FH SWF\\GdI\\1. Semester\\GDI-PROJEKT\\DataToRead.tab";
            writeFile = "C:\\Users\\Rem\\Desktop\\FH SWF\\GdI\\1. Semester\\GDI-PROJEKT\\WriteData.txt";
            break;
    }

    // opens source file
    FILE *fileToRead = fopen(fileNameString, "r");
    // if fileToRead doesn't exist print error close it and exit the program
    if (fileToRead == NULL) {
        printf("no such file found");
        return 0;
    }
    // open destination file
    FILE *fileToWrite;
    fileToWrite = fopen(writeFile, "w");

    // declaration and allocation of the container variable of all the data points
    struct datapoint *dp = (struct datapoint *) malloc(POINTS * sizeof(struct datapoint));

    int success;
    int prev = 0;
    int i = 0;
    int fail=0;
    while (!feof(fileToRead)) {
        //reads data from the file until the end of the file is reached

        success = fscanf(fileToRead, "%s\t%s\t%lf\t%lf\t%d\t%d\t%d\t%d\t%lf\t%lf\t%lf\t%d\t%lf\n", dp[i].event,
                         dp[i].datetime, &dp[i].latitude, &dp[i].longitude, &dp[i].altitude, &dp[i].hhh,
                         &dp[i].hgeom1,
                         &dp[i].hgeom2, &dp[i].PPPP, &dp[i].TTT, &dp[i].RH, &dp[i].dd, &dp[i].ff);
        /* the given file might contain incomplete data points, meaning there may be missing values,
         * therefore the data points that have missing data are not read correctly. After testing was found
         * that the following data point after a one that is incomplete is also being read false.
         * A way around this is to know if the last read was successful or not. If the last read was
         * unsuccessful, 'i' will be decremented and thus 'dp[i]' will be overwritten with the values of
         * the next read, that is successful. This done by the next two conditions.
         */
         if(success!=13) fail=1;
        if (success != 13 || prev != 0 || fail!=0) {
            i--;
            fail=0;
            prev = fail;
        }
        // at the end of the while loop 'i' will have counted the amount of data points that were read from the file
        ++i;
    }
    clock_t start_sort = clock();
    Merge_sort(dp, 0, i, '1');
    clock_t end_sort = clock();
    printf("\nSorting time: %lf sec\n", (double) (end_sort - start_sort) / CLOCKS_PER_SEC);

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
    /**
     * will only calculate the time the processor spent working i.e. if the programm
     * waits for input 15 seconds but the processor works/ticks 10 seconds the output
     * for execution time will be 10 seconds not 25 seconds
     */
    return 0;
}

/***************************************************END OF MAIN******************************************************/

void Polar_coordinates(struct datapoint *dp) {
    double betaRad, alfaRad;
    double radius = sqrt(pow(dp->x, 2) + pow(dp->y, 2) + pow(dp->z, 2));
    if (dp->x != 0) alfaRad = atan(dp->y / dp->x);
    if (dp->x == 0 && dp->y == radius) alfaRad = PI / 2;
    if (dp->x == 0 && dp->y == -radius) alfaRad = -PI / 2;
    betaRad = atan(sqrt(pow(dp->x, 2) + pow(dp->y, 2)) / dp->z);
    // Formulas and conditions from the book 'Geoinformatik'
    dp->longitude = 90 - (betaRad / DEGTORAD);
    dp->latitude = alfaRad / DEGTORAD;
    // conversion to degrees from radians
}

/**
 * xyz_calc - function that calculates the x,y and z coordinates of a given data point
 *            values are saved in the x,y and z variables of the data point structure
 *
 * @param dp - the data point whose x,y and z coordinates are calculated
 */
void xyz_calc(struct datapoint *dp) {
    double betaRad, alfaRad;
    betaRad = (90 - dp->longitude) * DEGTORAD;
    alfaRad = dp->latitude * DEGTORAD;
    // trigonometric functions work with angles in radians
    // that is why alfa and beta are converted from degrees to radians
    dp->x = RADIUS * sin(betaRad) * cos(alfaRad);
    dp->y = RADIUS * sin(betaRad) * sin(alfaRad);
    dp->z = RADIUS * cos(betaRad);
    //Formulas and conditions taken from the book 'Geoinformatik'
}

/**
 * euclidean_dist - Function that calculates euclidean distance between two points.
 *                  The Distance is be saved in the "abstand" variable of the second data point(dp2).
 *
 * @param dp1 - the first of the both data points between which the distance will be calculated
 * @param dp2 - the second data point
 */
void euclidean_dist(struct datapoint *dp1, struct datapoint *dp2) {
    xyz_calc(dp1);
    xyz_calc(dp2);
    dp2->abstand = sqrt(pow(dp1->x - dp2->x, 2) + pow(dp1->y - dp2->y, 2) + pow(dp1->z - dp2->z, 2));
    /// Formula from the book "Geoinformatik"
}

/**
 * orthodromic_dist - Function that calculates the orthodromic distance between two points.
 *                    The distance is saved in the "abstand" variable of the second data point(dp2).
 *
 * @param dp1 - the first of the both data points between which the distance will be calculated
 * @param dp2 - the second data point
 */
void orthodromic_dist(struct datapoint *dp1, struct datapoint *dp2) {
    dp2->abstand = RADIUS * acos(sin(dp1->latitude * DEGTORAD) * sin(dp2->latitude * DEGTORAD) +
                                 cos(dp1->latitude * DEGTORAD) * cos(dp2->latitude * DEGTORAD) *
                                 cos((dp1->longitude - dp2->longitude) * DEGTORAD));
    /// Formula from the book "Geoinformatik"
}
