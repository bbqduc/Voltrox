CXX=g++
CXXFLAGS=-O3 -std=c++0x -DTROL_USE_OLD_OPENGL
INCLUDE=-I ext/include
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lPolyVoxCore -lz -lpng

SRC=shader.cpp glutils.cpp shapes.cpp
HEADERS=shader.h voxelmodel.h glutils.h shapes.h model.h
MAIN=main.cpp
EXENAME=main

OBJ=$(SRC:.cpp=.o)

all: $(MAIN) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) $(MAIN) $(INCLUDE) $(OBJ) pnglite.o -o $(EXENAME)
$(OBJ) : $(SRC) $(HEADERS)
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD $< -o $@ $(INCLUDE) $(LIBS)
clean:
	-rm $(EXENAME)
	-rm *.d *.o
.PHONY: all clean
