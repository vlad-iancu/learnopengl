main: main.cpp render.cpp shader.a
	g++ main.cpp render.cpp src/glad.c shader.a -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o main

shader.o: shader.cpp
	g++ -c shader.cpp

shader.a: shader.o
	ar rvs shader.a shader.o
