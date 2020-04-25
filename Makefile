run: ./build/result
	./build/result

./build/result:
	mkdir -p ./build
	g++ -o ./build/result ./src/*.cpp -lncurses -lpthread