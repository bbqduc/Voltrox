CXX=g++
CXXFLAGS=-ggdb -std=c++0x -DTROL_USE_OLD_OPENGL
INCLUDE=-I ext/include -I .
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lPolyVoxCore -lz -lpng -lfreetype

SRC=TROLGraphics/shader.cpp TROLGraphics/glutils.cpp TROLGraphics/Voxel/shapes.cpp TROLGraphics/textrenderer.cpp TROLGraphics/Data/model.cpp TROLGraphics/renderer.cpp TROLGraphics/Managers/modelmanager.cpp TROLGraphics/Managers/texturemanager.cpp
HEADERS=TROLGraphics/shader.h TROLGraphics/glutils.h TROLGraphics/Voxel/shapes.h TROLGraphics/Data/model.h TROLGraphics/textrenderer.h TROLGraphics/renderer.h TROLGraphics/Managers/modelmanager.h TROLGraphics/Managers/texturemanager.h
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
	-rm *.d *.o
.PHONY: all clean
