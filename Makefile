EXENAME = final
OBJS = main.o PNG.o HSLAPixel.o lodepng.o parse_data.o airports_paths.o dijkstra.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: classes/main.cpp classes/airports_paths.cpp classes/parse_data.cpp classes/dijkstra.cpp
	$(CXX) $(CXXFLAGS) classes/main.cpp

dijkstra.o: classes/dijkstra.cpp
	$(CXX) $(CXXFLAGS) classes/dijkstra.cpp

airports_paths.o: classes/airports_paths.cpp
	$(CXX) $(CXXFLAGS) classes/airports_paths.cpp

parse_data.o: classes/parse_data.cpp
	$(CXX) $(CXXFLAGS) classes/parse_data.cpp

PNG.o : classes/cs225/PNG.cpp classes/cs225/PNG.h classes/cs225/HSLAPixel.h classes/cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) classes/cs225/PNG.cpp

HSLAPixel.o : classes/cs225/HSLAPixel.cpp classes/cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) classes/cs225/HSLAPixel.cpp

lodepng.o : classes/cs225/lodepng/lodepng.cpp classes/cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) classes/cs225/lodepng/lodepng.cpp



test: output_msg dijkstra.o PNG.o HSLAPixel.o lodepng.o classes/catch/catchmain.cpp classes/tests/tests.cpp classes/airports_paths.cpp classes/parse_data.cpp
	$(LD) dijkstra.o PNG.o HSLAPixel.o lodepng.o classes/catch/catchmain.cpp classes/tests/tests.cpp classes/airports_paths.cpp classes/parse_data.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test