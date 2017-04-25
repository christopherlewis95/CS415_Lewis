#include "../include/cmath_extra.h"

// Verifies if a number is a perfect square
// Arguments:
//   num - number to check against
// Returns:
//   true if the number supplied is a perfect
//   square, false otherwise
bool is_perfect_square(int num) {
  int root;

  if ( num < 0 ) {
    return false;
  }

  root = round(sqrt(num));

  return (num == root * root);
}

// Returns the equivalent positive modulo
// Arguments:
//   dividend - number to mod by
//   divisor - the mod space
// Returns:
//   equivalent positive integer within divisor
int absmod(int dividend, int divisor) {
  while( dividend < 0 ) {
      dividend += divisor;
  }

  return dividend % divisor;
}