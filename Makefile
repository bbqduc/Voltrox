CXX=g++
CXXFLAGS=-Os -std=c++0x -DTROL_USE_OLD_OPENGL
INCLUDE=-I ext/include -I . -I /usr/local/include/bullet -I /usr/local/include/PolyVoxCore -I /usr/include/freetype2 -I /usr/include/libpng -I /usr/include
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lPolyVoxCore -lz -lpng -lfreetype -lBulletCollision -lBulletDynamics -lBulletSoftBody -lLinearMath

SRC=TROLGraphics/shader.cpp TROLGraphics/glutils.cpp TROLGraphics/Voxel/shapes.cpp TROLGraphics/textrenderer.cpp TROLGraphics/Data/model.cpp TROLGraphics/renderer.cpp TROLGraphics/Managers/modelmanager.cpp TROLGraphics/Managers/texturemanager.cpp TROLGraphics/Managers/shadermanager.cpp TROLConsole/console.cpp TROLGraphics/camera.cpp TROLLogic/engine.cpp TROLLogic/entity.cpp
HEADERS=TROLGraphics/shader.h TROLGraphics/glutils.h TROLGraphics/Voxel/shapes.h TROLGraphics/Data/model.h TROLGraphics/textrenderer.h TROLGraphics/renderer.h TROLGraphics/Managers/modelmanager.h TROLGraphics/Managers/texturemanager.h TROLGraphics/Managers/shadermanager.h TROLConsole/console.h TROLGraphics/camera.h TROLLogic/engine.h
MAIN=main.cpp
EXENAME=main

OBJ=$(SRC:.cpp=.o)

all: $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) $(MAIN) $(INCLUDE) $(OBJ) -o $(EXENAME)
$(OBJ) : $(SRC) $(HEADERS)
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD $< -o $@ $(INCLUDE) $(LIBS)
clean:
	-rm $(EXENAME)
	-rm $(shell find TROL* -iname '*.o')
	-rm $(shell find TROL* -iname '*.d')
.PHONY: all clean
