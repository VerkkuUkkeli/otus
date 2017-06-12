UNAME := $(shell uname)

headers = helpers.hpp Camera.hpp ODE.hpp
sources = main.cpp helpers.cpp Camera.cpp callbacks.cpp ODE.cpp

CPPFLAGS = -std=c++11 -Wno-deprecated -lm

ifeq ($(UNAME), Darwin)
	CPPFLAGS += -I /usr/local/include -I /usr/include -framework GLUT -framework OpenGL -lGLEW
endif

ifeq ($(UNAME), Linux)
	CPPFLAGS += -lglut -lGLEW -lGL -lGLU 
endif

all:
	g++ $(sources) $(headers) $(CPPFLAGS)
