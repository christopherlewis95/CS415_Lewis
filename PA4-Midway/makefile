CC=mpic++
CXXFLAGS=-Wall
LIBS=-lpmi
INDLUDES=-I../includes

FILE=../src/seqMatrix.cpp
FILE2=../src/parMatrix.cpp
#FILE3=../src/randNumGen.cpp

OUTPUT=seqMatrix
OUTPUT2=parMatrix
#OUTPUT3=randGen


all: $(OUTPUT) $(OUTPUT2)

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(FILE) $(LIBS)

$(OUTPUT2): $(FILE2)
	$(CC) $(CXXFLAGS) -o $(OUTPUT2) $(FILE2) $(LIBS)

#$(OUTPUT3): $(FILE3)
#	$(CC) $(CXXFLAGS) -o $(OUTPUT3) $(FILE3) $(LIBS)


clean:
	-@if rm $(OUTPUT) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
	-@if rm $(OUTPUT2) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
#	-@if rm $(OUTPUT3) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
