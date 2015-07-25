CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = chess
OBJECTS = Rook.o Knight.o Bishop.o King.o Queen.o Pawn.o controller.o human.o view.o textdisplay.o main.o pieces.o board.o computer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
