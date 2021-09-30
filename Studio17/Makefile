include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_STUDIO17} ${FULL_PATH_STUDIO17TEST}

${FULL_PATH_STUDIO17}: Studio17.cpp ${FULL_PATH_LIB}  
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_STUDIO17TEST}: UnitTest.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_STUDIO17} ${FULL_PATH_STUDIO17TEST} 

