#include "../include/matrix.h"

// Default constructor
matrix::matrix() {
  rows = 0;
  cols = 0;
  data = NULL;
}

// Copy constructor
matrix::matrix(const matrix &matrix_b) {
  int row_index, col_index;

  rows = 0;
  cols = 0;
  data = NULL;

  // resize matrix to match size of matrix_b
  resize(matrix_b.rows, matrix_b.cols);

  // copy data from matrix_b
  for ( row_index = 0; row_index < rows; row_index++ ) {
    for ( col_index = 0; col_index < cols; col_index++ ) {
      data[row_index][col_index] = matrix_b.data[row_index][col_index];
    }
  }
}

// Destructor
matrix::~matrix() {
  empty();
}

// Overloaded addition operator
// Arguments:
//   matrix_b - const matrix to add with
// Returns:
//   resultant sum of the two matrices
matrix matrix::operator+ (const matrix &matrix_b) {
  int row_index, col_index;
  matrix matrix_c;

  matrix_c.resize(matrix_b.rows, matrix_b.cols);

  for ( row_index = 0; row_index < this->rows; row_index++ ) {
    for ( col_index = 0; col_index < this->cols; col_index++ ) {
      matrix_c.data[row_index][col_index] = this->data[row_index][col_index] + matrix_b.data[row_index][col_index];
    }
  }

  return matrix_c;
}

// Overloaded multiplication operator
// Arguments:
//   matrix_b - const matrix to multiply with
// Returns:
//   resultant product of the two matrices
matrix matrix::operator* (const matrix &matrix_b) {
  int row_index, col_index, inner_index;
  int result = 0;
  matrix matrix_c;

  // size matrix_c to fit the product of the two matrices
  matrix_c.resize(matrix_b.rows, matrix_b.cols);

  // perform calculations
  for ( row_index = 0; row_index < this->rows; row_index++ ) {
    for ( col_index = 0; col_index < matrix_b.cols; col_index++ ) {
      for ( inner_index = 0; inner_index < this->cols; inner_index++ ) {
        result = result + this->data[row_index][inner_index] * matrix_b.data[inner_index][col_index];
      }
      matrix_c.data[row_index][col_index] = result;
      result = 0;
    }
  }

  return matrix_c;
}

// Overloaded assignment operator
// Arguments:
//   matrix_b - const matrix to assign from
// Returns:
//   new matrix matching the details from matrix a
matrix matrix::operator= (const matrix &matrix_b) {
  int row_index, col_index;

  if ( this == &matrix_b ) {
    return *this;
  }

  // empty the destination matrix if it isn't empty
  if ( !is_empty() ) {
    empty();
  }

  // resize the matrix to matrix that of matrix_b
  resize(matrix_b.rows, matrix_b.cols);

  // copy the data
  for ( row_index = 0; row_index < rows; row_index++ ) {
    for ( col_index = 0; col_index < cols; col_index++ ) {
      data[row_index][col_index] = matrix_b.data[row_index][col_index];
    }
  }

  return *this;
}

// Resizes a given matrix to the dimensions specified
// Arguments:
//   num_rows - the number of rows to resize to
//   num_cols - the number of columns to resize to
// Returns:
//   N/A
// Notes:
//   all data in the matrix prior to resizing is erased
void matrix::resize(int num_rows, int num_cols) {
  int index;

  // de-allocate if necessary
  if ( !is_empty() ) {
    empty();
  }

  rows = num_rows;
  cols = num_cols;

  // allocate memory for the size specified
  data = new int* [rows];
  for ( index = 0; index < rows; index++ ) {
    data[index] = new int [cols];
  }
}

// Checks to see if the matrix is empty
// Arguments:
//   N/A
// Returns:
//   True if it is empty, false if it is not
bool matrix::is_empty() {
  if ( data == NULL ) {
    return true;
  } else {
    return false;
  }
}

// Empties the matrix
// Arguments:
//   N/A
// Returns:
//   N/A
void matrix::empty() {
  int index;

  if ( data != NULL ) {
    for ( index = 0; index < rows; index++ ) {
      delete[] data[index];
      data[index] = NULL;
    }
    delete[] data;
    data = NULL;
  }

  rows = 0;
  cols = 0;
}

// Gets the number of rows in the matrix
// Arguments:
//   N/A
// Returns:
//   the number of rows in the array
int matrix::get_rows() {
  return rows;
}

// Gets the number of columns in the matrix
// Arguments:
//   N/A
// Returns:
//   the number of columns in the array
int matrix::get_cols() {
  return cols;
}

// Fills a matrix full of random generated numbers
// Arguments:
//   row_num - the row to set the value in
//   col_num - the column to set the value in
//   value   - the value to set at the specified point
// Returns:
//   true if the matrix was successfully updated
bool matrix::set_element(int row_num, int col_num, int value) {
  if ( is_empty() ) {
    std::cerr << "set_element: matrix is empty" << std::endl;
    return false;
  } else if ( row_num >= rows || col_num >= cols ) {
    std::cerr << "set_element: invalid locations supplied" << std::endl;
    return false;
  } else {
    data[row_num][col_num] = value;
    return true;
  }
}

// Fills a matrix full of random generated numbers
// Arguments:
//   N/A
// Returns:
//   N/A
void matrix::generate() {
  int row_index, col_index;
  int* rand_nums;

  // allocate space for row generation
  rand_nums = new int [cols];

  // randomly generate a row and assign it into the matrix
  for ( row_index = 0; row_index < rows; row_index++ ) {
    rand_nums = rng(cols);
    for ( col_index = 0; col_index < cols; col_index++ ) {
      data[row_index][col_index] = rand_nums[col_index];
    }
  }
}

// Fills a matrix full of random generated numbers using a specified seed
// Arguments:
//   N/A
// Returns:
//   N/A
void matrix::generate(int seed) {
  int row_index, col_index;
  int* rand_nums;

  // seed srand to the specified seed
  srand(seed);

  rand_nums = new int [cols];
  for ( row_index = 0; row_index < rows; row_index++ ) {
    rand_nums = rng(cols);
    for ( col_index = 0; col_index < cols; col_index++ ) {
      data[row_index][col_index] = rand_nums[col_index];
    }
  }
}

// Shifts a specified row by a specified magnitude
// Arguments:
//   row_num - row number to shift
//   magnitude - direction and amount to shift by
// Returns:
//   true upon success, false on failure
bool matrix::shift_row(int row_num, int magnitude) {
  int col_index;
  int* buffer;

  if ( is_empty() ) {
    std::cerr << "shift_row(): cannot shift on an empty matrix" << std::endl;
    return false;
  }

  if ( row_num >= rows ) {
    std::cerr << "shift_row(): row specified is out of bounds" << std::endl;
    return false;
  }

  // store shifted into temp array
  buffer = new int [cols];
  for ( col_index = 0; col_index < cols; col_index++ ) {
    buffer[col_index] = data[row_num][absmod(col_index - magnitude, cols)];
  }

  // copy shifted array into data
  for ( col_index = 0; col_index < cols; col_index++ ) {
    data[row_num][col_index] = buffer[col_index];
  }

  // free up temp array
  delete [] buffer;
  buffer = NULL;

  return true;
}

// Shifts a specified column by a specified magnitude
// Arguments:
//   row_num - column number to shift
//   magnitude - direction and amount to shift by
// Returns:
//   true upon success, false on failure
bool matrix::shift_col(int col_num, int magnitude) {
  int row_index;
  int* buffer;

  if ( is_empty() ) {
    std::cerr << "shift_col(): cannot shift on an empty matrix" << std::endl;
    return false;
  }

  if ( col_num >= cols ) {
    std::cerr << "shift_col(): column specified is out of bounds" << std::endl;
    return false;
  }

  // store shifted into temp array
  buffer = new int [cols];
  for ( row_index = 0; row_index < rows; row_index++ ) {
    buffer[row_index] = data[absmod(row_index - magnitude, rows)][col_num];
  }

  // copy shifted array into data
  for ( row_index = 0; row_index < rows; row_index++ ) {
    data[row_index][col_num] = buffer[row_index];
  }

  // free up temp array
  delete [] buffer;
  buffer = NULL;

  return false;
}

// Attempts to split a matrix into equal square sub-matrices
// Arguments:
//   splices - number of sub matrices to create
// Returns:
//   matrix pointer to array of sub-matrices
// Notes:
//   there are many condtions that must be met before this
//   function can be performed
matrix* matrix::split(int splices) {
  int matrix_index, row_index, col_index;
  int mesh_rows, mesh_cols;
  int data_row, data_col;
  matrix* matrices;

  // perform error checks
  if ( is_empty() ) {
    return NULL;
  }

  if ( !is_perfect_square(splices) ) {
    std::cerr << "split(): cannot split into " << splices << " splices" << std::endl;
    return NULL;
  }

  if ( !is_perfect_square(rows) || !is_perfect_square(cols) ) {
    std::cerr << "split(): cannot split a " << rows << "x" << cols << " matrix" << std::endl;
    return NULL;
  }

  if ( rows * cols % splices != 0 || splices > rows * cols ) {
    std::cerr << "split(): incompatible matrix size for given number of splices" << std::endl;
    return NULL;
  }

  mesh_rows = rows / sqrt(splices);
  mesh_cols = cols / sqrt(splices);

  matrices = new matrix [splices];

  // loop for every matrix in new set of matrices
  for ( matrix_index = 0; matrix_index < splices; matrix_index++ ) {
    // allocate memory for each matrix
    matrices[matrix_index].resize(mesh_rows, mesh_cols);
    // initialize the data_row so it starts at the current mesh's respective row #
    data_row = mesh_rows * (int)(matrix_index / sqrt(splices));
    for ( row_index = 0; row_index < mesh_rows; row_index++ ) {
      // initialize the data_col so it starts at the current mesh's respective col #
      data_col = mesh_cols * (matrix_index % (int)sqrt(splices));
      for ( col_index = 0; col_index < mesh_cols; col_index++ ) {
        // assign data into new sub-matrix from the universal matrix using the separate data counters
        matrices[matrix_index].data[row_index][col_index] = data[data_row][data_col];
        data_col++;
      }
      data_row++;
    }
  }

  return matrices;
}

// Prints a matrix out row by row
// Arguments:
//   N/A
// Returns:
//   N/A
void matrix::print() {
  int row_index, col_index;

  for ( row_index = 0; row_index < rows; row_index++ ) {
    for ( col_index = 0; col_index < cols; col_index++ ) {
      std::cout << data[row_index][col_index];
      if ( col_index != cols - 1 ) {
        std::cout << " ";
      } else {
        std::cout << std::endl;
      }
    }
  }
}
