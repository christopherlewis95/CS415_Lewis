//.h file for struct and fill matrix rfunction
typedef struct {
        unsigned int rows;
        unsigned int cols;
        double **matrixData;
} matrix_struct;

matrix_struct *get_matrix_struct(char matrix[]);
void print_matrix(matrix_struct *matrix_to_print);

