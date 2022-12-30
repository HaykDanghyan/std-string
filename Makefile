all: str
	./str

str: *.cpp *.hpp *.h
	g++ main.cpp -o str

clean: 
	rm -rf str