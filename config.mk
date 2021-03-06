CXX?=g++
CXXFLAGS?=-std=c++11 -Wall -Wextra -Wpedantic -O3

# include paths
INCLUDE_HEADERS?=-I../unit-test-lib -I../lab5
TARGET_PATH?=../targets/

# all the files in lab5 folder will be compiled in to a library 
#  (excluding the main function)
# link this with any main function
LIB?=liblab5.a
FULL_PATH_LIB=${TARGET_PATH}${LIB}

# executable for lab5
LAB5?=lab5
FULL_PATH_LAB5?=${TARGET_PATH}${LAB5}
LAB5_PIAZZA_TEST?=test-piazza-lab5
FULL_PATH_LAB5_PIAZZA_TEST?=${TARGET_PATH}${LAB5_PIAZZA_TEST}

# executable for studio
STUDIO16?=studio16
FULL_PATH_STUDIO16?=${TARGET_PATH}${STUDIO16}
STUDIO16TEST?=test-studio16
FULL_PATH_STUDIO16TEST?=${TARGET_PATH}${STUDIO16TEST}

STUDIO17?=studio17
FULL_PATH_STUDIO17?=${TARGET_PATH}${STUDIO17}
STUDIO17TEST?=test-studio17
FULL_PATH_STUDIO17TEST?=${TARGET_PATH}${STUDIO17TEST}

STUDIO18?=studio18
FULL_PATH_STUDIO18?=${TARGET_PATH}${STUDIO18}
STUDIO18TEST?=test-studio18
FULL_PATH_STUDIO18TEST?=${TARGET_PATH}${STUDIO18TEST}

STUDIO19?=studio19
FULL_PATH_STUDIO19?=${TARGET_PATH}${STUDIO19}
STUDIO19TEST?=test-studio19
FULL_PATH_STUDIO19TEST?=${TARGET_PATH}${STUDIO19TEST}

STUDIO20?=studio20
FULL_PATH_STUDIO20?=${TARGET_PATH}${STUDIO20}
STUDIO20TEST?=test-studio20
FULL_PATH_STUDIO20TEST?=${TARGET_PATH}${STUDIO20TEST}

STUDIO21?=studio21
FULL_PATH_STUDIO21?=${TARGET_PATH}${STUDIO21}
STUDIO21TEST?=test-studio21
FULL_PATH_STUDIO21TEST?=${TARGET_PATH}${STUDIO21TEST}

