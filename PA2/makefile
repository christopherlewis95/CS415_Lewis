# set flags and compiler, as well as file var
CC=mpicc
CXXFLAGS=-Wall
LIBS=-lpmi
# feel free to either add files here (for more compilcated src's), or create more vars, or just manually type them in. Up to you.
FILE=../src/mpiPingPongOneBox.cpp
FILE2=../src/mpiPingPongTwoBox.cpp
FILE3=../src/mpiPingPongTimed.cpp
# uncomment below if/when you have a folder called include that holds potential header files
#INCLUDES=-I../include
OUTPUT=mpiPingPong1
OUTPUT2=mpiPingPong2
OUTPUT3=mpiPingPongT

all: $(OUTPUT) $(OUTPUT2) $(OUTPUT3) 

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(FILE) $(LIBS)

$(OUTPUT2): $(FILE2)
	$(CC) $(CXXFLAGS) -o $(OUTPUT2) $(FILE2) $(LIBS)

$(OUTPUT3): $(FILE3)
	$(CC) $(CXXFLAGS) -o $(OUTPUT3) $(FILE3) $(LIBS)

# use this to run
runOne: $(OUTPUT)
	srun -n2 $(OUTPUT1)

runTwo: $(OUTPUT2)
	srun -N2 $(OUTPUT2)

timed: $(OUTPUT3)
	srun -N2 $(OUTPUT3) times.txt

clean:
	-@if rm $(OUTPUT) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
