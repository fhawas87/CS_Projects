/* TRAVELING SALESMAN PROBLEM, RETURNING SHORTEST PATH LENGTH USING HELD-KARP ALGORITHM WITH CUSTOM INPUT READING FOR OPTIMIZATION */



#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>

#define BUFFER_SIZE 100000
#define MAX_NUMBER_OF_VILLAGES 13
#define INF 999999999

char Buffer[BUFFER_SIZE];

int VillagesLocationsWithPossibleDuplicates[MAX_NUMBER_OF_VILLAGES];
int VillagesLocations[MAX_NUMBER_OF_VILLAGES];

int NumberOfUniqueVillages;

double AdjacencyMatrix[MAX_NUMBER_OF_VILLAGES][MAX_NUMBER_OF_VILLAGES];

std::vector<int> Villages;
std::vector<int> Duplicates;

static void ReadInputBytes() {

    size_t BytesRead = fread(Buffer, sizeof(char), BUFFER_SIZE, stdin);

    Buffer[BytesRead] = '\0';
}

static inline int ReadInt(char** CharPointer) {

    int num = 0;

    while (**CharPointer < '0' || **CharPointer > '9') { (*CharPointer)++; }

    while (**CharPointer >= '0' && **CharPointer <= '9') {

        num = num * 10 + (**CharPointer - '0');

        (*CharPointer)++;
    }

    return num;
}

static void FillArray(char** CharPointer, int NumberOfVillages) {

    for (int i = 0; i < (2 * NumberOfVillages); i += 2) {

        VillagesLocationsWithPossibleDuplicates[i] = ReadInt(CharPointer);
        VillagesLocationsWithPossibleDuplicates[i + 1] = ReadInt(CharPointer);
    }
}

static void RemoveDuplicates(int NumberOfVillages) {

    NumberOfUniqueVillages = 0;

    Villages.clear();
    Duplicates.clear();

    int NumberOfDuplicates = 0;

    for (int i = 0; i < NumberOfVillages; i++) {

        for (int j = 0; j < NumberOfVillages; j++) {

            if (i != j && VillagesLocationsWithPossibleDuplicates[2 * i] != (-1) && VillagesLocationsWithPossibleDuplicates[(2 * i) + 1] != (-1) &&
                          VillagesLocationsWithPossibleDuplicates[2 * j] != (-1) && VillagesLocationsWithPossibleDuplicates[(2 * j) + 1] != (-1)) {

                if (VillagesLocationsWithPossibleDuplicates[2 * i] == VillagesLocationsWithPossibleDuplicates[2 * j] &&
                    VillagesLocationsWithPossibleDuplicates[(2 * i) + 1] == VillagesLocationsWithPossibleDuplicates[(2 * j) + 1]) {

                    Duplicates.emplace_back(VillagesLocationsWithPossibleDuplicates[2 * j]);
                    Duplicates.emplace_back(VillagesLocationsWithPossibleDuplicates[(2 * j) + 1]);

                    VillagesLocationsWithPossibleDuplicates[2 * j] = (-1);
                    VillagesLocationsWithPossibleDuplicates[(2 * j) + 1] = (-1);

                    NumberOfDuplicates++;
                }
            }

            else { continue; }
        }
    }

    NumberOfUniqueVillages = (NumberOfVillages - NumberOfDuplicates);

    for (int i = 0; i < NumberOfVillages; i++) {

        if (VillagesLocationsWithPossibleDuplicates[2 * i] != (-1) && VillagesLocationsWithPossibleDuplicates[(2 * i) + 1] != (-1)) {

            Villages.emplace_back(VillagesLocationsWithPossibleDuplicates[2 * i]);
            Villages.emplace_back(VillagesLocationsWithPossibleDuplicates[(2 * i) + 1]);
        }
    }

    for (int i = 0; i < NumberOfUniqueVillages; i++) {

        VillagesLocations[2 * i] = Villages[2 * i];
        VillagesLocations[(2 * i) + 1] = Villages[(2 * i) + 1];
    }
}

static inline double EuclideanLength(int FirstVillageCoordinateX, int FirstVillageCoordinateY,
                                     int SecondVillageCoordinateX, int SecondVillageCoordinateY) {

    return sqrt((SecondVillageCoordinateX - FirstVillageCoordinateX) * (SecondVillageCoordinateX - FirstVillageCoordinateX) +
                (SecondVillageCoordinateY - FirstVillageCoordinateY) * (SecondVillageCoordinateY - FirstVillageCoordinateY));

}

static inline double DistanceFromRiver(int FirstVillageCoordinateX, int FirstVillageCoordinateY,
                                       int SecondVillageCoordinateX, int SecondVillageCoordinateY) {

    double TotalDistance = 0;

    if (FirstVillageCoordinateY == SecondVillageCoordinateY) {                                

        TotalDistance = fabs(FirstVillageCoordinateX - SecondVillageCoordinateX);                                                           // CASE WHERE Y COORDINATES OF TWO VILLAGES ARE THE SAME
    }                                                                                                                                       // AND WHILE TRAVELLING TO THE RIVER WE FIND SECOND VILLAGE

    else {

        double  DistanceToRiver = FirstVillageCoordinateX;
        double  DistanceToSecondVillageCoordinateY = fabs(SecondVillageCoordinateY - FirstVillageCoordinateY);
        double  DistanceToSecondVillageCoordinateX = SecondVillageCoordinateX;                                                              // IF DISTANCE BETWEEN TWO VILLAGES IS GREATER THAN 1000
                                                                                                                                            // TARZAN DOESN'T KNOW THE PATH SO HE USES SHORTEST PATH 
        TotalDistance = DistanceToRiver + DistanceToSecondVillageCoordinateY + DistanceToSecondVillageCoordinateX;                          // TO THE RIVER ( RIVER :  x = 0 ), THEN ALONG THE RIVER
    }                                                                                                                                       // UNTILL HE REACHES y COORDINATE LVL OF THE FINAL VILLAGE

    return TotalDistance;
}

static void InitializeMatrixWithEuclideanLength() {

    for (int row = 0; row < NumberOfUniqueVillages; row++) {

        for (int col = 0; col < NumberOfUniqueVillages; col++) {

            if (row != col) {

                double Distance = EuclideanLength(VillagesLocations[2 * row], VillagesLocations[(2 * row) + 1],                                             // INITIALIZING ADJACENCY MATRIX WITH DISTANCES BETWEEN VILLAGES
                                                  VillagesLocations[2 * col], VillagesLocations[(2 * col) + 1]);

                if (Distance < 1000) { *(*(AdjacencyMatrix + row) + col) = Distance; }
                                                                                                                                                            // EXAMPLE OF ADJACENCY MATRIX FOR INPUT : 5 ((82, 18)(575, 211)(433, 1)(318, 5)(521, 391)) 
                else {                                                                                                                                                                                                                                                   
                    *(*(AdjacencyMatrix + row) + col) = DistanceFromRiver(VillagesLocations[2 * row], VillagesLocations[(2 * row) + 1],                     //  0.00 529.431771 351.411440 236.357780 576.064233
                                                                          VillagesLocations[2 * col], VillagesLocations[(2 * col) + 1]);                
                }                                                                                                                                           //  529.431771 0.00 253.503452 329.370612 187.925517
            }                                                                                                                                                                                                                                                                       
                                                                                                                                                            //  351.411440 253.503452 0.00 115.069544 399.804952
            else { *(*(AdjacencyMatrix + row) + col) = 0; }                                                                                                                                                                          
        }                                                                                                                                                   //  236.357780 329.370612 115.069544 0.00 436.124982
    }                                                                                                                                                                                                                                                                                       
}                                                                                                                                                           //  576.064233 187.925517 399.804952 436.124982 0.00

static double ShortestPathLength() {                                                                 // HELD-KARP ALGORITHM

    double Distance[1 << MAX_NUMBER_OF_VILLAGES][MAX_NUMBER_OF_VILLAGES];

    for (int i = 0; i < (1 << NumberOfUniqueVillages); i++) {

        for (int j = 0; j < NumberOfUniqueVillages; j++) {

            Distance[i][j] = INF;
        }
    }

    Distance[1][0] = 0;

    for (int i = 0; i < (1 << NumberOfUniqueVillages); i++) {

        for (int j = 0; j < NumberOfUniqueVillages; j++) {

            if (!(i & (1 << j))) { continue; }

            for (int k = 0; k < NumberOfUniqueVillages; k++) {

                if (i & (1 << k)) { continue; }

                int NextMask = i | (1 << k);

                Distance[NextMask][k] = std::min(Distance[NextMask][k], Distance[i][j] + AdjacencyMatrix[j][k]);
            }
        }
    }

    double ShortestDistance = INF;

    for (int i = 0; i < NumberOfUniqueVillages; i++) {

        ShortestDistance = std::min(ShortestDistance, Distance[(1 << NumberOfUniqueVillages) - 1][i] + AdjacencyMatrix[i][0]);
    }

    return floor(ShortestDistance);
}

int main() {

    ReadInputBytes();

    char* CharPointer = Buffer;

    int NumberOfInstances = ReadInt(&CharPointer);

    while (NumberOfInstances > 0) {

        int NumberOfVillages = ReadInt(&CharPointer);

        FillArray(&CharPointer, NumberOfVillages);
        RemoveDuplicates(NumberOfVillages);
        InitializeMatrixWithEuclideanLength();
/*
______________________________________________________________________________________________________________________________    
|        printf("%d, %d\n", NumberOfVillages, NumberOfUniqueVillages);                                                       |
|                                                                                                                            |
|        for (const auto& d : Duplicates) {                                                                                  |
|                                                                                                                            |
|            printf("%d, ", d);                                                                                              |
|        }                                                                                                                   |
|                                                                                                                            |
|        printf("\n");                                                                                                       |
|                                                                                                                            |
|        for (int i = 0; i < NumberOfUniqueVillages; i++) {                                                                  |
|                                                                                                                            |
|            printf("(%d, %d), ", VillagesLocations[2 * i], VillagesLocations[(2 * i) + 1]);                                 |     THIS PART IS ONLY FOR DEBUGGING
|        }                                                                                                                   |
|                                                                                                                            |
|        printf("\n");                                                                                                       |
|                                                                                                                            |
|        for (int i = 0; i < NumberOfUniqueVillages; i++) {                                                                  |
|                                                                                                                            |
|            for (int j = 0; j < NumberOfUniqueVillages; j++) {                                                              |
|                                                                                                                            |
|                printf("%.0f ", AdjacencyMatrix[i][j]);                                                                     |
|            }                                                                                                               |
|                                                                                                                            |
|            printf("\n");                                                                                                   |    
|        }                                                                                                                   |
|                                                                                                                            |
|        printf("\n");                                                                                                       |
|____________________________________________________________________________________________________________________________|
*/
        printf("%.0f\n", ShortestPathLength());

        NumberOfInstances--;
    }

    return 0;
}
