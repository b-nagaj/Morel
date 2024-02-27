# compile settings
CXX = g++
CXXFLAGS = -std=c++17 -Wno-deprecated-declarations
LDFLAGS = -lboost_system -lboost_filesystem -I/usr/include/mysql -lmysqlclient

# binaries
BUILD_BINARY = bin/morel
TEST_BINARY = bin/tests

# directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# file collections
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp) $(wildcard $(TEST_DIR)/**/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))

# other aliases
MKDIR = create_build_directories

# main target
all: $(MKDIR) $(BUILD_BINARY)
	./$(BUILD_BINARY)

# compile generated output files
$(BUILD_BINARY): $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# compile cpp files in the /src directory recursively
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# main target
test: $(MKDIR) $(TEST_BINARY)
	./$(TEST_BINARY)

# compile generated output files
$(TEST_BINARY): $(TEST_OBJ_FILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# compile cpp files in the /src directory recursively
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# # test target
# test: $(MKDIR) $(TEST_BINARY)
# 	./$(TEST_BINARY)

# $(TEST_BINARY): $(TEST_OBJ_FILES)
# 	$(CXX) -o $@ $< $(BOOST) $(MY_SQL)

# $(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
# 	$(CXX) $(CXXFLAGS) -c -o $< $@

# create build directories
$(MKDIR):
	mkdir -p $(BUILD_DIR) $(BUILD_DIR)/entities $(BUILD_DIR)/operations $(BUILD_DIR)/setup $(BUILD_DIR)/utils bin

# cleans
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
