a.out: Main.o Distance.o InputAndValidation.o Knn.o Sample.o
	g++ -std=c++11 main.o Data.o KNN.o Calculator.o -o a.out

Main.o:
	g++ -std=c++11 -c Main.cpp Header.h Knn.h

Distance.o:
	g++ -std=c++11 -c Distance.cpp Distance.h

InputAndValidation.o:
	g++ -std=c++11 -c InputAndValidation.cpp Header.h

Knn.o:
	g++ -std=c++11 -c Knn.cpp Knn.h

Sample.o:
	g++ -std=c++11 -c Sample.cpp Sample.h

target: dependencies
	action

clean:
	rm *.o *.h.gch a.out

