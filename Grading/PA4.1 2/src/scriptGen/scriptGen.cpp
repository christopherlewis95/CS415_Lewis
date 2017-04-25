#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{
	ofstream fout;
	string outputFile;
	for(int x = 180, t = 1; x < 2701; x = ++t * 180 ){
		for(int n = 1; n < 2;n++){
			outputFile = "../../build/scripts/";
			outputFile += to_string(x);
			outputFile += "x";
			outputFile += to_string(n);
			outputFile += ".sh";
			fout.open(outputFile.c_str(),ofstream::out | ofstream::app);
			fout << "#!/bin/bash\n" << "#SBATCH -n " << n << "\n#SBATCH --time=00:12:00\n\nsrun ~/PA4/build/Sequential " << x << " 0" << endl;
			fout.close();
			/*switch(n){
				case 1:
					n = 5;
					break;
				case 5:
					n=10;
					break;
				case 10:
					n=15;
					break;
				case 20:
					n=16;
					break;
				case 16:
					n=32;
					break;
				case 32:
					n=35;
					break;
			}*/

		}
	}
	
}