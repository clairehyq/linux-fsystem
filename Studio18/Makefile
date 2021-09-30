include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_STUDIO18} ${FULL_PATH_STUDIO18TEST}

${FULL_PATH_STUDIO18}: Studio18.cpp ${FULL_PATH_LIB}  
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_STUDIO18TEST}: UnitTest.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_STUDIO18} ${FULL_PATH_STUDIO18TEST} 

