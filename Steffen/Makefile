run: build/main.exe
	./build/main

build/main.exe: src/main.cc build build/Makefile
	cd build && make -s -j4

build/Makefile: CMakeLists.txt
	cd build && cmake -G "MinGW Makefiles" ..

build:
	mkdir build

clear:
	rmdir build /S /Q
