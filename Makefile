CXX=g++
CXXFLAGS=-Os -std=c++0x
INCLUDE=-I ext/include -I . -I /usr/local/include/bullet
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lPolyVoxCore -lz -lpng -lfreetype -lBulletCollision -lBulletDynamics -lBulletSoftBody -lLinearMath -lGLU

SRC=TROLGraphics/shader.cpp TROLGraphics/glutils.cpp TROLGraphics/textrenderer.cpp TROLGraphics/Data/model.cpp TROLGraphics/renderer.cpp TROLGraphics/Managers/modelmanager.cpp TROLGraphics/Managers/texturemanager.cpp TROLGraphics/Managers/shadermanager.cpp TROLConsole/console.cpp TROLGraphics/camera.cpp TROLLogic/engine.cpp TROLLogic/entity.cpp root.cpp
HEADERS=TROLGraphics/shader.h TROLGraphics/glutils.h TROLGraphics/Data/model.h TROLGraphics/textrenderer.h TROLGraphics/renderer.h TROLGraphics/Managers/modelmanager.h TROLGraphics/Managers/texturemanager.h TROLGraphics/Managers/shadermanager.h TROLConsole/console.h TROLGraphics/camera.h TROLLogic/engine.h root.h
MAIN=main.cpp
EXENAME=main

OBJ=$(SRC:.cpp=.o)

all: $(MAIN) $(OBJ)
	$(CXX) -o $(EXENAME) $(CXXFLAGS) $(MAIN) $(INCLUDE) $(OBJ) ext/gl3w.o -o $(EXENAME) $(LIBS)
$(OBJ) : $(SRC) $(HEADERS)
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD $< -o $@ $(INCLUDE) $(LIBS)
clean:
	-rm $(EXENAME)
	-rm $(shell find TROL* -iname '*.o')
	-rm $(shell find TROL* -iname '*.d')
.PHONY: all clean
