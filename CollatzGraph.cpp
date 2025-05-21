#include <cstdio>
#include <iostream>
#include <vector>

uint64_t CollatzSequence[10000];

int length;

static void GenerateCollatzSequence(uint64_t n) {

	length = 0;

	CollatzSequence[length] = n;

	while (n != 1) { 

		if (n % 2 == 0) { n = n / 2; length++; }

		else { n = n * 3 + 1; length++; }

		CollatzSequence[length] = n;
	}

	length++;

	CollatzSequence[length] = 1;
}

static inline int Max(int FirstValue, int SecondValue) {	

	return (FirstValue > SecondValue) ? FirstValue : SecondValue;
}

static int FindLongestDescendingSequenceLength() {
	
	std::vector<int> LongestDescendingSequence(length, 1);

	int LongestSequenceLength = 1;

	for (int i = 1; i < length; i++) {
		
		for (int j = 0; j < i; j++) {
			
			if (CollatzSequence[j] > CollatzSequence[i]) {

				LongestDescendingSequence[i] = Max(LongestDescendingSequence[i], LongestDescendingSequence[j] + 1);
			}
		}

		LongestSequenceLength = Max(LongestSequenceLength, LongestDescendingSequence.at(i));
	}

	return LongestSequenceLength;
}

int main() {
	
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	uint64_t n;

	while (std::cin >> n) {

		GenerateCollatzSequence(n);
		FindLongestDescendingSequenceLength();

		std::cout << FindLongestDescendingSequenceLength() << '\n';
	}
	
	return 0;
}
