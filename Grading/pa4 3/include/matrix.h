#include <cmath>
#include <iostream>

#include "cmath_extra.h"
#include "generator.h"

class matrix
{
  public:
    matrix();
    matrix(const matrix &a);
    ~matrix();

    matrix operator+ (const matrix &matrix_b);
    matrix operator* (const matrix &a);
    matrix operator= (const matrix &a);

    void resize(int num_rows, int num_cols);
    bool is_empty();
    void empty();
    int get_rows();
    int get_cols();
    bool set_element(int row_num, int col_num, int value);

    void generate();
    void generate(int seed);
    bool shift_row(int row_num, int magnitude);
    bool shift_col(int col_num, int magnitude);
    matrix* split(int splices);
    void print();


  private:
    int rows;
    int cols;
    int** data;
};