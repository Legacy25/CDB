CC=g++
CFLAGS= -std=c++11 -g

cdb: 
	$(CC) $(CFLAGS) -o build/llvmruntime src/*.cpp
	./build/llvmruntime

run: 
	./build/llvmruntime

clean:
	rm build/llvmruntime