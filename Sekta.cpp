#include <stdio.h>
#include <vector>
#include <cstring>


#define BUFFER_SIZE 1000000


char Buffer[BUFFER_SIZE];

std::vector<long long> Victims;

int NumberOfLines;
long long n;
long long k;

static void ReadInputBytes() {

    size_t BytesRead = fread(Buffer, sizeof(char), BUFFER_SIZE, stdin);

    Buffer[BytesRead] = '\0';
}

static inline long long ReadInt(char** CharPointer) {

    long long num = 0;

    bool isNegative = false;

    while (**CharPointer < '0' || **CharPointer > '9') { 
        
        if ((**CharPointer) == '-') { (*CharPointer)++; isNegative = true; }

        else { (*CharPointer)++; }
    }

    while (**CharPointer >= '0' && **CharPointer <= '9') {

        num = num * 10 + (**CharPointer - '0');

        (*CharPointer)++;
    }

    if (isNegative) { num *= (-1); }

    return num;
}

static void GenerateVictimsSequence() {
    
    Victims.clear();

    std::vector<long long> People;

    for (long long i = 1; i <= n; i++) { People.emplace_back(i); }
    
    long long CurrentCirclePlace = 1 % n;

    while (People.size() > 1) {

        CurrentCirclePlace %= People.size();

        Victims.emplace_back(People[CurrentCirclePlace]);
        People.erase(People.begin() + CurrentCirclePlace);

        if (People.empty()) { break; }

        CurrentCirclePlace = (CurrentCirclePlace + 1) % People.size();
    }

    Victims.emplace_back(People[0]);
}

int main() {
    
    ReadInputBytes();

    char* CharPointer = Buffer;

    NumberOfLines = ReadInt(&CharPointer);

    while (NumberOfLines > 0) {

        n = ReadInt(&CharPointer);
        k = ReadInt(&CharPointer);

        if (k < 0) { k = n + k + 1; }

        GenerateVictimsSequence();

        long long Victim = Victims[k - 1];

        printf("%lld\n", Victim);
        
        Victims.clear();

        NumberOfLines--;
    }

    return 0;
}
