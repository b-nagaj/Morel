# compile settings
CXX = g++
CXXFLAGS = -std=c++17

# libraries
BOOST = -lboost_system -lboost_filesystem
MY_SQL = -I/usr/include/mysql -lmysqlclient

# binaries
BUILD_BINARY = bin/morel
TEST_BINARIES = bin/testSetup bin/testHelper bin/testCalculator bin/testDialog

# directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# file collections
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# other aliases
MKDIR = create_build_directories

# main target
all: $(MKDIR) $(BUILD_BINARY)
	./$(BUILD_BINARY)

# compile generated output files
$(BUILD_BINARY): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(BOOST) $(MY_SQL)

# compile cpp files in the /src directory recursively
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# create build directories
$(MKDIR):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/entities $(BUILD_DIR)/operations $(BUILD_DIR)/setup $(BUILD_DIR)/utils bin

# tests
test: $(TEST_BINARIES)
	./bin/testSetup
	./bin/testHelper
	./bin/testCalculator
	./bin/testDialog

# compile generated output files
bin/test%: test%.o
	$(GCC) test$*.o -o $@ $(BOOST) $(MY_SQL)

# compile cpp files in the /test directory
test%.o: $(TEST_DIR)/test%.cpp
	$(GCC) -c $< -o $@

# cleans
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

cleanTests:
	rm $(TEST_BINARIES)
	rm $(TEST_DIR)/testConfig.txt
