#OBJS : file to compile as part of the project
OBJS = TextureManager.cpp Vector2D.cpp LoaderParams.cpp GameObject.cpp SDLGameObject.cpp Player.cpp Enemy.cpp AnimatedGraphic.cpp MenuButton.cpp InputHandler.cpp GameStateMachine.cpp GameState.cpp PauseState.cpp PlayState.cpp MenuState.cpp GameOverState.cpp Game.cpp main.cpp

#CC compiler to be used
CC = g++-7

#INCLUDE_PATHS : addtional include paths needed
INCLUDE_PATHS = `sdl2-config --cflags`

#LIBRARY_PATHS : addtional library paths needed
LIBRARY_PATHS = `sdl2-config --libs`


#COMPILER_FLAGS
COMPILER_FLAGS = -Wall --std=c++14 -g

#LINKER_FLAGS : libraries we're linking against
LINKER_FLAGS = -lSDL2_image

#OBJ_NAME : executable name
OBJ_NAME = Jam

#Target that compiles the executable

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm Jam