#include <stdio.h>
#include <algorithm>
#include <unordered_set>
#include <vector>

#define BUFFER_SIZE 15000000
#define MAX_VERTICES 1000

char Buffer[BUFFER_SIZE];

int AdjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
int EachRowDegree[MAX_VERTICES];

int NumberOfLeaves;
int NumberOfBranches;
int NumberOfRoots;
int BranchIndex;

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

static void ConvertInputToAdjacencyMatrix(const int& NumberOfVertices, char** CharPointer) {

    for (int i = 0; i < NumberOfVertices; i++) {

        EachRowDegree[i] = 0;

        for (int j = 0; j < NumberOfVertices; j++) {

            while (**CharPointer != '0' && **CharPointer != '1') { (*CharPointer)++; }

            AdjacencyMatrix[i][j] = (**CharPointer - '0');

            (*CharPointer)++;

            if (AdjacencyMatrix[i][j]) { (EachRowDegree[i])++; } 
        }
    }
}

static bool IsTree(const int& NumberOfVertices) {

    NumberOfLeaves = 0;
    NumberOfBranches = 0;
    NumberOfRoots = 0;
    BranchIndex = 0;

    std::vector<int> LeavesIndices;

    std::unordered_set<int> UniqueDegreeValues;

    for (int i = 0; i < NumberOfVertices; i++) {

        UniqueDegreeValues.insert(EachRowDegree[i]);

        if (EachRowDegree[i] == 1) { NumberOfLeaves++; LeavesIndices.push_back(i); }
    }

    if (UniqueDegreeValues.size() > 3) { return false; }

    if (UniqueDegreeValues.size() == 3) {

        int MainRootDegree = *std::max_element(EachRowDegree, EachRowDegree + NumberOfVertices);
        int BranchDegree = 0;

        for (int i = 0; i < NumberOfVertices; i++) {

            if (EachRowDegree[i] == 0) { return false; }

            if (EachRowDegree[i] > 1 && EachRowDegree[i] < MainRootDegree) { NumberOfBranches++; BranchDegree = EachRowDegree[i]; BranchIndex = i; }

            if (EachRowDegree[i] == MainRootDegree) { NumberOfRoots++; }
        }

        if (NumberOfRoots > 1) {                                                                    // CASE WHERE MAIN ROOT DEGREE & BRANCH DEGREE IS THE SAME
                                                                                                    // NUMBER OF ROOTS = NUMBER OF BRANCHES IN THIS CASE SINCE
            if (NumberOfBranches > 1 && NumberOfRoots > 1) { return false; }                        // ONE OF POSSIBLE INSTANCES IS EDGE CASE WHERE WE HAVE :
                                                                                                    // 4 x LEAVES, 2 x THIRD DEGREE BRANCHES & 1 x SECOND DEGREE ROOT
            if (NumberOfLeaves == (BranchDegree * (MainRootDegree - 1))) {                          // SO IN SORTED ARRAY OF DEGREES IT LOOKS LIKE THAT : [ 1, 1, 1, 1, 2, 3, 3 ]

                for (const int& LeafRow : LeavesIndices) {

                    if (AdjacencyMatrix[LeafRow][BranchIndex] == 1) { return false; }               // THERE WAS FEW INSTANCES WHERE ARRAY LOOKED LIKE THAT : [ 1, 2, 1, 3, 1, 3, 1 ]
                }                                                                                   // AND IT LOOKS LIKE BANANA TREE BUT IN ADJACENCY MATRIX SOME LEAVES WERE CONNECTED
                                                                                                    // DIRECTLY TO A ROOT & THE ANSWER WERE 0 BANANAS SO I HAD TO LOOP THROUGH EVERY LEAF
                return true;                                                                        // ROW TO CHECK IF THERE IS A CONNECTION BETWEEN LEAF AND MAIN ROOT
            }

            else { return false; }
        }

        if (NumberOfBranches != MainRootDegree) { return false; }

        if (NumberOfLeaves != (MainRootDegree * (BranchDegree - 1))) { return false; }

        else { return true; }
    }

    if (UniqueDegreeValues.size() == 2) {

        int BranchDegree = 0;

        for (int i = 0; i < NumberOfVertices; i++) {

            if (EachRowDegree[i] == 0) { return false; }

            if (EachRowDegree[i] > 1) { NumberOfBranches++; BranchDegree = EachRowDegree[i]; }

        }

        if (NumberOfLeaves == BranchDegree) {

            if (BranchDegree == NumberOfBranches - 1) { return true; }

            if (NumberOfBranches > NumberOfLeaves) { return false; }

            if (BranchDegree == NumberOfLeaves + 1 && NumberOfBranches == 1) { return false; }

            if (NumberOfVertices > NumberOfLeaves + 1) { return false; }

            else { return true; }
        }

        if (NumberOfLeaves == (BranchDegree * (BranchDegree - 1))) { return true; }

        else { return false; }
    }

    if (UniqueDegreeValues.size() == 1) {                                                           // THERE IS ONLY ONE INSTANCE WHERE NUMBER OF UNIQUE DEGREES
                                                                                                    // EQUALS TO 1 AND GRAPH STILL QUALIFIES FOR A BANANA TREE 
        if (AdjacencyMatrix[0][1] == AdjacencyMatrix[1][0]) { return true; }                        // 0 1
                                                                                                    // 1 0
        else { return false; }                                                                      // I BELIEVE
    }

    return false;
}

int main() {

    ReadInputBytes();

    char* CharPointer = Buffer;

    int NumberOfInstances = ReadInt(&CharPointer);
    
    while (NumberOfInstances-- > 0) {

        int NumberOfVertices = ReadInt(&CharPointer);

        ConvertInputToAdjacencyMatrix(NumberOfVertices, &CharPointer);

        if (IsTree(NumberOfVertices)) { printf("%d bananas :)\n", NumberOfLeaves); }

        else { printf("0 bananas :(\n"); }
    }

    return 0;
}
