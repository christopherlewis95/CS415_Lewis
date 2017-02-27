# set flags and compiler, as well as file var
CC=mpicc
CXXFLAGS=-Wall
LIBS=-lpmi
# feel free to either add files here (for more compilcated src's), or create more vars, or just manually type them in. Up to you.
FILE=../src/mpiPingPong.cpp
# uncomment below if/when you have a folder called include that holds potential header files
#INCLUDES=-I../include
OUTPUT=mpiPingPong 

all: $(OUTPUT)

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(FILE) $(LIBS)

# use this to run
runOne: $(OUTPUT)
	srun -n2 --time=00:05:00 $(OUTPUT) oneTossOneMachine.txt

runTwo: $(OUTPUT)
	srun -N2 --time=00:05:00 $(OUTPUT) oneTossTwoMachine.txt

runTwoTimed: $(OUTPUT)
	srun -N2 --time=00:05:00 $(OUTPUT) oneTossTwoMachineTimed.txt

clean:
	-@if rm $(OUTPUT) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
