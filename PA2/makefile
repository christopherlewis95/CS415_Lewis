# set flags and compiler, as well as file var
CC=mpic++
CXXFLAGS=-Wall
LIBS=-lpmi
# feel free to either add files here (for more compilcated src's), or create more vars, or just manually type them in. Up to you.
FILE=../src/seqMan.cpp PIM.o
#FILE2=../src/staticAssMan.cpp PIM.o
FILE3=../src/dynAssMan.cpp PIM.o



# uncomment below if/when you have a folder called include that holds potential header files
INCLUDE=-I../include
OUTPUT=seqMan
#OUTPUT2=staticMan
OUTPUT3=dynMan

all: $(OUTPUT) $(OUTPUT2) #$(OUTPUT3) 

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) $(FILE) -o $(OUTPUT) $(INCLUDE) $(LIBS)
	
#$(OUTPUT2): $(FILE2)
#	$(CC) $(CXXFLAGS) $(FILE2) -o $(OUTPUT2) $(INCLUDE) $(LIBS)
	
$(OUTPUT3): $(FILE3)
	$(CC) $(CXXFLAGS) $(FILE3) -o $(OUTPUT3) $(INCLUDE) $(LIBS)

PIM.o: ../src/pimfunctions.cpp
	$(CC) $(CXXFLAGS) -c ../src/pimfunctions.cpp -o PIM.o $(INCLUDE) $(LIBS)


#$(OUTPUT3): $(FILE3)
#	$(CC) $(CXXFLAGS) -o $(OUTPUT3) $(FILE3) $(LIBS)

# use this to run
#runOne: $(OUTPUT)
#	srun -n2 $(OUTPUT1)

#runTwo: $(OUTPUT2)
#	srun -N2 $(OUTPUT2)

#timed: $(OUTPUT3)
#	srun -N2 $(OUTPUT3) times.txt

clean:
	-@if rm $(OUTPUT) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
