CXX = clang++-6.0
CXXFLAGS += -Wall -Wextra -Werror -ggdb -std=c++17

SRC_DIR = ./src
BIN_DIR = ./bin


main: init $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main

test: init $(SRC_DIR)/test.cpp
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/test.cpp -o $(BIN_DIR)/test

# urghhhh
singlefile: init 
	echo "// You are NOT supposed to look at this automatically generated file!!!\n"\
		> $(BIN_DIR)/main.cpp
	cat $(SRC_DIR)/Network.hpp $(SRC_DIR)/Network.tpp\
		$(SRC_DIR)/EdgeListNetwork.hpp $(SRC_DIR)/EdgeListNetwork.tpp\
		$(SRC_DIR)/NetworkBuilder.hpp $(SRC_DIR)/NetworkBuilder.tpp\
		$(SRC_DIR)/MaxFlowAlgorithm.hpp $(SRC_DIR)/MaxFlowAlgorithm.tpp\
		$(SRC_DIR)/BlockingFlowAlgorithm.hpp $(SRC_DIR)/BlockingFlowAlgorithm.tpp\
		$(SRC_DIR)/MalhotraKumarMaheshvari.hpp $(SRC_DIR)/MalhotraKumarMaheshvari.tpp\
		$(SRC_DIR)/Dinic.hpp $(SRC_DIR)/Dinic.tpp\
		$(SRC_DIR)/PreflowPush.hpp $(SRC_DIR)/PreflowPush.tpp\
		$(SRC_DIR)/main.cpp >> $(BIN_DIR)/main.cpp

	sed -i '/#include "/d' $(BIN_DIR)/main.cpp
	sed -i '/#pragma once/d' $(BIN_DIR)/main.cpp
	sed -i '/#ifndef/d' $(BIN_DIR)/main.cpp
	sed -i '/#define/d' $(BIN_DIR)/main.cpp
	sed -i '/#endif/d' $(BIN_DIR)/main.cpp


singlefileTest: init
	cat $(SRC_DIR)/Network.hpp $(SRC_DIR)/Network.tpp\
		$(SRC_DIR)/EdgeListNetwork.hpp $(SRC_DIR)/EdgeListNetwork.tpp\
		$(SRC_DIR)/NetworkBuilder.hpp $(SRC_DIR)/NetworkBuilder.tpp\
		$(SRC_DIR)/MaxFlowAlgorithm.hpp $(SRC_DIR)/MaxFlowAlgorithm.tpp\
		$(SRC_DIR)/PreflowPush.hpp $(SRC_DIR)/PreflowPush.tpp\
		$(SRC_DIR)/BlockingFlowAlgorithm.hpp $(SRC_DIR)/BlockingFlowAlgorithm.tpp\
		$(SRC_DIR)/MalhotraKumarMaheshvari.hpp $(SRC_DIR)/MalhotraKumarMaheshvari.tpp\
		$(SRC_DIR)/Dinic.hpp $(SRC_DIR)/Dinic.tpp\
		$(SRC_DIR)/test.cpp > $(BIN_DIR)/test.cpp

	sed -i '/#include "/d' $(BIN_DIR)/test.cpp
	sed -i '/#pragma once/d' $(BIN_DIR)/test.cpp
	sed -i '/#ifndef/d' $(BIN_DIR)/test.cpp
	sed -i '/#define/d' $(BIN_DIR)/test.cpp
	sed -i '/#endif/d' $(BIN_DIR)/test.cpp



init:
	mkdir -p $(BIN_DIR)