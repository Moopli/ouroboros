CXX = g++
CXXFLAGS = -I . -g -pedantic -Wall -Wextra -Wcast-align \
-Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self \
-Wlogical-op -Wmissing-include-dirs -Wnoexcept \
-Woverloaded-virtual -Wshadow -Wsign-promo \
-Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused \
-O2 -MMD -std=c++11 -lSDL2
OBJECTS =	main.o doodle.o ModelImport.o Mesh.o Verlet.o VerletBuilders.o VerletEdge.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = simulator

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${CXXFLAGS}

clean :
	rm -v ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}