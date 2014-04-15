CFLAGS = `pkg-config --cflags --libs sdl2`
LIB = -lglut -lGLU -lGL -lGLEW 

run: curveball.cpp
	g++ curveball.cpp -g $(LIB) $(CFLAGS) -o flyer
        
clean: 
	rm -f *.out *~ run
