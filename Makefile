headers = helpers.hpp Camera.hpp ODE.hpp
sources = main.cpp helpers.cpp Camera.cpp callbacks.cpp ODE.cpp

all:
	g++ -std=c++11 -Wno-deprecated $(sources) $(headers) -framework GLUT -framework OpenGL -lGLEW -lglui -lm
