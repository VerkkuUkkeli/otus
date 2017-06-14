UNAME := $(shell uname)

headers = helpers.hpp Camera.hpp callbacks.hpp ODE.hpp display.hpp globals.hpp Transform.hpp RigidBody.hpp shader.hpp
sources = main.cpp helpers.cpp Camera.cpp callbacks.cpp ODE.cpp display.cpp globals.cpp Transform.cpp RigidBody.cpp shader.cpp

CPPFLAGS = -std=c++11 -Wno-deprecated -lm

ifeq ($(UNAME), Darwin)
	CPPFLAGS += -I /usr/local/include -I /usr/include -framework GLUT -framework OpenGL -L/usr/local/Cellar/glew/2.0.0/lib -lGLEW
endif

ifeq ($(UNAME), Linux)
	CPPFLAGS += -lglut -lGLEW -lGL -lGLU 
endif

all:
	g++ $(sources) $(headers) $(CPPFLAGS)
