# set flags and compiler, as well as file var
CC=mpic++
CXXFLAGS=-Wall
LIBS=-lpmi
INDLUDES=-I../includes

FILE=../src/parBucketSort.cpp
#FILE2=
#FILE3=

OUTPUT=parBucket
#OUTPUT2=
#OUTPUT3=


all: $(OUTPUT)

$(OUTPUT): $(FILE)
	$(CC) $(CXXFLAGS) -o $(OUTPUT) $(FILE) $(LIBS)

#$(OUTPUT2): $(FILE2)
#	$(CC) $(CXXFLAGS) -o $(OUTPUT2) $(FILE2) $(LIBS)

#$(OUTPUT3): $(FILE3)
#	$(CC) $(CXXFLAGS) -o $(OUTPUT3) $(FILE3) $(LIBS)


clean:
	-@if rm $(OUTPUT) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
#	-@if rm $(OUTPUT2) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
#	-@if rm $(OUTPUT3) 2>/dev/null || true; then echo "Cleaned"; else echo "Nothing to clean"; fi
