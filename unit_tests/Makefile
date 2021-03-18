CXX=g++
CXXFLAGS= -std=c++14 -lgtest -lgtest_main -pthread -g
#%.o: %.c $(DEPS)
#	$(CXX) -c -o $@ $< $(CXXFLAGS)

OBJ= test_all.o
PROGRAM_NAME = test_all

$(PROGRAM_NAME):$(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_NAME) $(OBJ)
	@echo " "
	@echo "Compiled!"
	@echo " "

