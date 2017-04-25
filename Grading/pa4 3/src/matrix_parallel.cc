#include "../include/matrix_parallel.h"

int main(int argc, char* argv[]) {
  int world_size, world_rank;
  int mesh_index, calc_index;
  int a_size, b_size;
  int mesh_size, mesh_start;
  double elapsed_time;
  struct timeval timer;
  matrix matrix_a, matrix_b, matrix_c;
  matrix *matrices_a, *matrices_b, *matrices_c;

  if ( argc != 3 ) {
    std::cerr << PROG_NAME << ": Invalid number of arguments supplied" << std::endl;
    return 1;
  }

  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // verify a valid world size
  if ( !is_perfect_square(world_size) ) {
    std::cerr << PROG_NAME << ": Invalid world size supplied" << std::endl;
    return 1;
  }

  // read in the sizes
  a_size = atoi(argv[1]);
  b_size = atoi(argv[2]);

  // scale the matrices to size
  matrix_a.resize(a_size, a_size);
  matrix_b.resize(b_size, b_size);
  matrix_c.resize(b_size, a_size);

  // verify that the matrices can be multiplied
  if ( matrix_a.get_cols() != matrix_b.get_rows() ) {
    std::cerr << PROG_NAME << ": matrices cannot be multiplied" << std::endl;
    return 1;
  }

  // generate the two matrices
  matrix_a.generate(42);
  matrix_b.generate(420);

  // Print initial matrices
  // if ( world_rank == 0 ) {
  //   std::cout << "Matrix A:" << std::endl;
  //   matrix_a.print();
  //   std::cout << std::endl;
  //   std::cout << "Matrix B:" << std::endl;
  //   matrix_b.print();
  //   std::cout << std::endl;
  // }

  // perform initial shift
  mesh_size = a_size / sqrt(world_size);
  mesh_start = (a_size / sqrt(world_size)) * (sqrt(world_size) - 1);
  for ( mesh_index = 0; mesh_index < mesh_size; mesh_index++ ) {
    matrix_a.shift_row(mesh_start + mesh_index, (-1) * mesh_size);
    matrix_b.shift_col(mesh_start + mesh_index, (-1) * mesh_size);
  }

  // split the matrices into sub-matrices
  matrices_a = matrix_a.split(world_size);
  matrices_b = matrix_b.split(world_size);
  matrices_c = matrix_c.split(world_size);

  // verify the success of the split
  if ( matrices_a == NULL || matrices_b == NULL ) {
    std::cerr << "failed to split one of the matrices" << std::endl;
    return 1;
  }

  // initialize counter
  calc_index = 0;

  // wait for everyone to catch up
  MPI_Barrier(MPI_COMM_WORLD);

  // start timer
  if ( world_rank == 0 ) {
    gettimeofday(&timer, NULL);
  }

  // calculate initial result
  matrices_c[calc_index] = matrices_a[world_rank] * matrices_b[world_rank];
  matrix_c = matrices_c[calc_index];
  calc_index++;

  // shift the sub matrices and calculate
  while ( calc_index < sqrt(world_size) ) {
    for ( mesh_index = 0; mesh_index < a_size; mesh_index++ ) {
      matrix_a.shift_row(mesh_index, (-1) * mesh_size);
      matrix_b.shift_col(mesh_index, (-1) * mesh_size);
    }
    delete [] matrices_a;
    delete [] matrices_b;
    matrices_a = matrix_a.split(world_size);
    matrices_b = matrix_b.split(world_size);

    // sum new product
    matrices_c[calc_index] = matrices_a[world_rank] * matrices_b[world_rank];
    matrix_c = matrix_c + matrices_c[calc_index];
    calc_index++;
  }

  // end timer
  if ( world_rank == 0 ) {
    elapsed_time = get_time(timer);
    std::cout << elapsed_time;
  }

  // print result
  // for ( world_index = 0; world_index < world_size; world_index++ ) {
  //   if ( world_rank == world_index ) {
  //     std::cout << std::endl << "Matrix C:" << std::endl;
  //     matrix_c.print();
  //     std::cout << std::endl;
  //   }
  //   MPI_Barrier(MPI_COMM_WORLD);
  // }


  MPI_Finalize();

  delete [] matrices_a;
  delete [] matrices_b;
  delete [] matrices_c;
  matrices_a = matrices_b = matrices_c = NULL;

  return 0;
}
