CXX=g++
CXXFLAGS=-Os -std=c++0x -DMAX_ENTITIES=512
INCLUDE=-I ext/include -I . -I /usr/include/bullet -I/usr/include/freetype2 -I/usr/include/libpng -I .
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lz -lpng -lfreetype -lBulletCollision -lBulletDynamics -lBulletSoftBody -lLinearMath -lGLU -lGL -ldl

SRC=TROLGraphics/shader.cpp TROLGraphics/glutils.cpp TROLGraphics/Data/model.cpp TROLGraphics/Managers/modelmanager.cpp TROLGraphics/Managers/texturemanager.cpp TROLGraphics/Managers/shadermanager.cpp TROLLogic/physicssystem.cpp TROLCommon/root.cpp TROLLogic/inputhandler.cpp TROLGraphics/rendersystem.cpp TROLUtil/error.cpp TROLCommon/entitysystem.cpp TROLGraphics/openglwindow.cpp TROLCommon/positionsystem.cpp
HEADERS=TROLGraphics/shader.h TROLGraphics/glutils.h TROLGraphics/Data/model.h TROLGraphics/Managers/modelmanager.h TROLGraphics/Managers/texturemanager.h TROLGraphics/Managers/shadermanager.h TROLCommon/root.h TROLUtil/memorypool.h TROLUtil/memorypool.inl TROLGraphics/rendersystem.h TROLCommon/system.h TROLCommon/types.h TROLCommon/entitysystem.h TROLGraphics/openglwindow.h TROLCommon/positionsystem.h
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
