include ../config.mk

CXXFLAGS+=${INCLUDE_HEADERS} 

all: ${FULL_PATH_STUDIO16} ${FULL_PATH_STUDIO16TEST}

${FULL_PATH_STUDIO16}: Studio16.cpp ${FULL_PATH_LIB}  
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_STUDIO16TEST}: UnitTest.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS} -w

clean: 	
	rm -f *.gch *.o ${FULL_PATH_STUDIO16} ${FULL_PATH_STUDIO16TEST} 

