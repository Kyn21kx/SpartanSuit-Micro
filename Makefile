all: testLinux

testLinux: test.o Logging.o MicroStringUtils.o Vector3.o
	g++ -g -o testLinux test.o Logging.o MicroStringUtils.o Vector3.o

test.o: test.cpp
	g++ -g -c test.cpp -o test.o

Logging.o: MicroUtils/Logging.cpp
	g++ -g -c MicroUtils/Logging.cpp -o Logging.o


MicroStringUtils.o: MicroUtils/MicroStringUtils.cpp
	g++ -g -c MicroUtils/MicroStringUtils.cpp -o MicroStringUtils.o

Vector3.o: Vector3.cpp
	g++ -g -c Vector3.cpp -o Vector3.o

clean:
	rm -f testLinux test.o Logging.o MicroStringUtils.o Vector3.o
