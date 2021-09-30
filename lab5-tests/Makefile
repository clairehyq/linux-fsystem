# produces test-piazza-lab5: runs all tests on piazza

include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_LAB5_PIAZZA_TEST}

${FULL_PATH_LAB5_PIAZZA_TEST}: PiazzaTests.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_LAB5_PIAZZA_TEST} 
