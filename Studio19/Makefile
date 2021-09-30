include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_STUDIO19} ${FULL_PATH_STUDIO19TEST}

${FULL_PATH_STUDIO19}: Studio19.cpp ${FULL_PATH_LIB}  
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_STUDIO19TEST}: UnitTest.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_STUDIO19} ${FULL_PATH_STUDIO19TEST} 

