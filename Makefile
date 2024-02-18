# compile settings
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lboost_system -lboost_filesystem -L/usr/lib/x86_64-linux-gnu/ -lmysqlcppconn
BUILD_BINARY = morel
TEST_BINARIES = testSetup testHelper testCalculator testDialog

# directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# file collections
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# other aliases
MKDIR_OBJ = make_object_directory

# main target
all: $(MKDIR_OBJ) $(BUILD_BINARY)
	./$(BUILD_BINARY)

# compile generated .o files
$(BUILD_BINARY): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# compile cpp files in the /src directory recursively
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# create build directories
$(MKDIR_OBJ):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/entities $(BUILD_DIR)/setup $(BUILD_DIR)/utils

# tests
test: $(TEST_BINARIES)
	./testSetup
	./testHelper
	./testCalculator
	./testDialog

# compile generated .o files
test%: test%.o
	$(GCC) test$*.o -o test$* $(BOOST) $(MY_SQL)

# compile cpp files in the /test directory
test%.o: $(TEST_DIR)/test%.cpp
	$(GCC) -c $(TEST_DIR)/test$*.cpp

# cleans
clean:
	rm -rf $(BUILD_DIR) $(BUILD_BINARY)

cleanTests:
	rm $(TEST_BINARIES)
	rm $(TEST_DIR)/testConfig.txt
