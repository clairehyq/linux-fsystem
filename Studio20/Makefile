include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_STUDIO20} ${FULL_PATH_STUDIO20TEST}

${FULL_PATH_STUDIO20}: Studio20.cpp ${FULL_PATH_LIB}  
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_STUDIO20TEST}: UnitTest.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_STUDIO20} ${FULL_PATH_STUDIO20TEST} 

