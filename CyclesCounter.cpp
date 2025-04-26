#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

#define BUFFER_SIZE 63749961
#define MAX_VERTICES 1000

char Buffer[BUFFER_SIZE];

int Matrix[MAX_VERTICES][MAX_VERTICES];
int SquaredMatrix[MAX_VERTICES][MAX_VERTICES];

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

static void InitializeMatrix(int& NumberOfVertices, int& NumberOfFaces, char** CharPointer) {

    for (int i = 0; i < NumberOfVertices; i++) {

        for (int j = 0; j < NumberOfVertices; j++) {

            *(*(Matrix + i) + j) = (i != j) ? 1 : 0;                                                            // FILLING FIRST DEGREE MATRIX WITH ONES EXCEPT MAIN DIAGONAL
        }
    }

    while (NumberOfFaces-- > 0) {

        int EachFaceSize = ReadInt(CharPointer);

        int VerticesArray[MAX_VERTICES];

        for (int i = 0; i < EachFaceSize; i++) {

            VerticesArray[i] = ReadInt(CharPointer);
        }

        for (int i = 0; i < EachFaceSize; i++) {

            for (int j = i + 1; j < EachFaceSize; j++) {

                *(*(Matrix + VerticesArray[i]) + VerticesArray[j]) = 0;                                         // IF THERE IS AN EDGE BETWEEN 2 VERTICES, REPLACE 1 WITH 0 
                *(*(Matrix + VerticesArray[j]) + VerticesArray[i]) = 0;                                         // SINCE ONLY SPATIAL DIAGONALS HAVE TO BE CONSIDERED 
            }                                                                                                   // IN CASE OF CYCLES IN POLYHEDRON
        }
    }
}

static void MatrixMultiplication(int& NumberOfVertices) {

    for (int row = 0; row < NumberOfVertices; row++) {

        for (int col = 0; col < NumberOfVertices; col++) {

            *(*(SquaredMatrix + row) + col) = 0;

            for (int inner = 0; inner < NumberOfVertices; inner++) {

                *(*(SquaredMatrix + row) + col) += (*(*(Matrix + row) + inner) * *(*(Matrix + inner) + col));    // SQUARE ADJACENCY MATRIX TO GET NUMBER OF PATHS WITH LENGTH 2 BETWEEN TWO VERTICES
            }
        }
    }
}

static inline int BinomialCoefficients(int& Paths) {

    return (Paths < 2) ? 0 : ((Paths * (Paths - 1)) / 2);                                                        // SINCE WE LOOK FOR 4-CYCLES WE CHOOSE TWO OF THIS PATHS
}

static double CountCycles(int& NumberOfVerticies) {

    int Counter = 0;

    for (int i = 0; i < NumberOfVerticies; i++) {

        for (int j = i + 1; j < NumberOfVerticies; j++) {

            Counter += BinomialCoefficients(*(*(SquaredMatrix + i) + j));
        }
    }

    double TotalCycles = Counter / 2;

    return floor(TotalCycles);
}


int main() {

    ReadInputBytes();

    char* CharPointer = Buffer;

    int NumberOfInstances = ReadInt(&CharPointer);

    while (NumberOfInstances-- > 0) {

        int NumberOfVertices = ReadInt(&CharPointer);
        int NumberOfFaces = ReadInt(&CharPointer);

        InitializeMatrix(NumberOfVertices, NumberOfFaces, &CharPointer);
        MatrixMultiplication(NumberOfVertices);

        printf("%.0f\n", CountCycles(NumberOfVertices));
    }

    return 0;
}
