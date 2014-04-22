CFLAGS = `pkg-config --cflags --libs sdl2`
LIB = -lglut -lGLU -lGLEW -lGL -lSOIL

run: curveball.cpp
	g++ curveball.cpp environment.cpp ball.cpp -g $(LIB) $(CFLAGS) -o curveball
        
clean: 
	rm -f *.out *~ run
