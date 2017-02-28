# set flags and compiler, as well as file var
CC=mpicc
CXXFLAGS=-Wall
LIBS=-lpmi
# feel free to either add files here (for more compilcated src's), or create more vars, or just manually type them in. Up to you.
FILE= src/mpiPingPong.cpp
# uncomment below if/when you have a folder called include that holds potential header files
#INCLUDES=-I../include
OUTPUT1 = One_box
OUTPUT2 = Two_box
OUTPUT3 = Timing

all: $(OUTPUT1) $(OUTPUT2) $(OUTPUT3)

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT1) $(FILE) $(LIBS)

$(OUTPUT2): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT2) $(FILE) $(LIBS)

$(OUTPUT3): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT3) $(FILE) $(LIBS)

singleBox: &(OUTPUT1)
	srun -n2 $(OUTPUT1) One_box.txt 2

TwoBox: &(OUTPUT2)
	srun -N2 $(OUTPUT2) Two_box.txt 2

Timed: &(OUTPUT3)
	srun -N2 $(OUTPUT3) Timed.txt 10000

clean:
	rm $(OUTPUT1) $(OUTPUT2) $(OUTPUT3)
