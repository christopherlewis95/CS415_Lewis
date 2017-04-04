#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{
    FILE *fp;
    int num = 0;
    int size = atoi(argv[1]);

    fp = fopen("../src/data.txt", "w");

    fprintf(fp, "%d\n", size );
    for(int i = 0; i < size; i++)
    {
        num = rand() % 501;
        fprintf(fp, "%d\n", num );
    }
}
