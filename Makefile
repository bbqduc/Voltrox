CXX=g++
CXXFLAGS=-ggdb -std=c++0x -DTROL_USE_OLD_OPENGL
INCLUDE=-I ext/include
LIBS=-L ext/lib -Wl,-rpath,ext/lib -lGLEW -lglfw -lPolyVoxCore -lz -lpng -lfreetype

SRC=shader.cpp glutils.cpp shapes.cpp gltext.cpp model.cpp renderer.cpp
HEADERS=shader.h voxelmodel.h glutils.h shapes.h model.h gltext.h renderer.h
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
