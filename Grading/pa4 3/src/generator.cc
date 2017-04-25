#include "../include/generator.h"

// Generates a random set of integers
// Arguments:
//   count - number of integers to generate
// Returns:
//   integer pointer pointing to the generated array
// Notes:
//   function assumes random has been seeded
int* rng(int count) {
	int index;
	int* random_numbers;

	random_numbers = new int [count];

	for ( index = 0; index < count; index++ ) {
		random_numbers[index] = rand() % MAX_SIZE;
	}

 	return random_numbers;
}

// Generates a random set of integers using a specific seed
// Arguments:
//   seed - number to seed random
//   count - number of integers to generate
// Returns:
//   integer pointer pointing to the generated array
int* rngs(int seed, int count) {
	int index;
	int* random_numbers;

	random_numbers = new int [count];
	srand(seed);

	for ( index = 0; index < count; index++ ) {
		random_numbers[index] = rand() % MAX_SIZE;
	}

 	return random_numbers;
}
