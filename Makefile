# compile settings
GCC = g++ -std=c++17
BUILD_BINARY = morel
TEST_BINARIES = testSetup testHelper testCalculator
BOOST = -lboost_system -lboost_filesystem

# directories
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj

# file collections
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# other aliases
MKDIR_OBJ = make_object_directory

all: $(MKDIR_OBJ) $(BUILD_BINARY)
	./morel

$(BUILD_BINARY): $(OBJ_FILES)
	$(GCC) -o $@ $^ $(BOOST)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(GCC) -c -o $@ $^ $(BOOST)

$(MKDIR_OBJ):
	mkdir -p $(OBJ_DIR)

test: $(TEST_BINARIES)
	./testSetup
	./testHelper
	./testCalculator

test%: test%.o
	$(GCC) test$*.o -o test$* $(BOOST)

test%.o: $(TEST_DIR)/test%.cpp
	$(GCC) -c $(TEST_DIR)/test$*.cpp

clean:
	rm $(BUILD_BINARY)
	rm -r $(OBJ_FILES) $(OBJ_DIR)

cleanTests:
	rm $(TEST_BINARIES)
	rm $(TEST_DIR)/testConfig.txt