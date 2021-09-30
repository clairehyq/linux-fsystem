# produces liblab5: a static library with everything excluding main()
# also produces lab5: a lab5 executable 

include ../config.mk

ABSTRACT=AbstractCommand \
				 AbstractFileFactory \
				 AbstractFile \
				 AbstractFileSystem \
				 AbstractFileVisitor \
				 AbstractParsingStrategy

CONCRETE=BasicDisplayVisitor \
				 MetadataDisplayVisitor \
				 UnformattedDisplayVisitor \
				 CommandPrompt \
				 CommandTest \
				 ErrorCodes \
				 ImageFile \
				 TextFile \
				 PasswordProxy \
				 SimpleFileFactory \
				 SimpleFileSystem \
				 FileExtensions \
				 TouchCommand \
				 LSCommand \
				 RemoveCommand \
				 CatCommand \
				 DisplayCommand \
				 CopyCommand \
				 MacroCommand \
				 RenameCommand \
				 GrepCommand \
				 GrepVisitor \
				 RenameParsingStrategy \
				 CloseGuard \
				 util

ALL_MODULES=${ABSTRACT} ${CONCRETE}

WIP=DirectoryFile \
HierarchicalFileFactory \
HierarchicalFileSystem

HEADERS=$(addsuffix .h,${ALL_MODULES})
OBJECTS=$(addsuffix .o,${CONCRETE}) 




all: ${FULL_PATH_LIB} ${FULL_PATH_LAB5}

${FULL_PATH_LAB5}: lab5.cpp ${FULL_PATH_LIB} 
	${CXX} $^ -o $@ ${CXXFLAGS}

${FULL_PATH_LIB}: ${OBJECTS}
	ar rvs $@ $^

TouchCommand.o: TouchCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

SimpleFileSystem.o: SimpleFileSystem.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

TextFile.o: TextFile.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

SimpleFileFactory.o: SimpleFileFactory.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

PasswordProxy.o: PasswordProxy.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

MetadataDisplayVisitor.o: MetadataDisplayVisitor.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

UnformattedDisplayVisitor.o: UnformattedDisplayVisitor.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

ImageFile.o: ImageFile.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

ErrorCodes.o: ErrorCodes.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

CommandTest.o: CommandTest.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

CommandPrompt.o: CommandPrompt.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

BasicDisplayVisitor.o: BasicDisplayVisitor.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

FileExtensions.o: FileExtensions.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

LSCommand.o: LSCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

RemoveCommand.o: RemoveCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

CatCommand.o: CatCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

CopyCommand.o: CopyCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

DisplayCommand.o: DisplayCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

RenameCommand.o: RenameCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

MacroCommand.o: MacroCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

RenameParsingStrategy.o: RenameParsingStrategy.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

CloseGuard.o: CloseGuard.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

GrepVisitor.o: GrepVisitor.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

GrepCommand.o: GrepCommand.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

util.o: util.cpp ${HEADERS}
	${CXX} $< -c ${CXXFLAGS}

clean: 	
	rm -f *.o *.gch ${FULL_PATH_LIB} ${FULL_PATH_LAB5}
