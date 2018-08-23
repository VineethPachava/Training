CC=gcc
CFLAGS=-I. -ftest-coverage -fprofile-arcs
all:sensor-demo

sensor-demo: build/main.o build/sensor.o build/accelerometer.o  build/magnetometer.o build/gps.o build/functions.o
	g++ $^ -o $@ -ftest-coverage -fprofile-arcs
	
build/sensor.o: src/sensor.cpp include/sensor.h
	$(CC) -c src/sensor.cpp -o build/sensor.o $(CFLAGS)

build/accelerometer.o: src/accelerometer.cpp include/accelerometer.h
	$(CC) -c src/accelerometer.cpp -o build/accelerometer.o $(CFLAGS)

build/magnetometer.o: src/magnetometer.cpp include/magnetometer.h
	$(CC) -c src/magnetometer.cpp -o build/magnetometer.o $(CFLAGS)

build/gps.o: src/gps.cpp include/gps.h
	$(CC) -c src/gps.cpp -o build/gps.o $(CFLAGS)

build/functions.o: src/functions.cpp include/functions.h
	$(CC) -c src/functions.cpp -o build/functions.o $(CFLAGS)

build/main.o: src/main.cpp 
	$(CC) -c src/main.cpp -o build/main.o $(CFLAGS)

clean:
	rm -rf build/*.o sensor-demo