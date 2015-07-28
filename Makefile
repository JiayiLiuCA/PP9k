CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = chess
OBJECTS = Rook.o Knight.o Bishop.o King.o Queen.o Pawn.o controller.o human.o view.o textdisplay.o main.o pieces.o board.o computer1.o computer2.o computer3.o computer4.o graphicdisplay.o window.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
