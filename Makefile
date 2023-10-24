main: main.cpp render.cpp shader.a Object.o Texture.o Camera.o
	g++ main.cpp \
		render.cpp \
		src/glad.c \
		shader.a \
		Object.o \
		Texture.o \
		Camera.o \
		-lglfw \
		-lGL \
		-lX11 \
		-lpthread \
		-lXrandr \
		-lXi \
		-ldl \
		-o main

shader.o: shader.cpp
	g++ -c shader.cpp

shader.a: shader.o
	ar rvs shader.a shader.o

Object.o: Object.cpp
	g++ -c Object.cpp

Texture.o: Texture.cpp
	g++ -c Texture.cpp

Camera.o: Camera.cpp
	g++ -c Camera.cpp

clean:
	rm -f *.o *.a main

web: main.cpp
	emcc main.cpp \
		render.cpp \
		src/glad.c \
		shader.cpp\
		Object.cpp \
		Texture.cpp \
		Camera.cpp \
                -I/usr/include \
                -I/usr/local/include \
		-lglfw \
		-lGL \
		-lX11 \
		-lpthread \
		-lXrandr \
		-lXi \
		-ldl \
		
