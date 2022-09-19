# compile settings
GCC = g++ -std=c++17
BUILD_BINARY = morel
BOOST = -lboost_system -lboost_filesystem

# directories
SRC_DIR = src
OBJ_DIR = obj

# file collections
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# other aliases
MKDIR_OBJ = make_object_directory

all: $(MKDIR_OBJ) $(BUILD_BINARY)

$(BUILD_BINARY): $(OBJ_FILES)
	$(GCC) -o $@ $^ $(BOOST)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(GCC) -c -o $@ $^ $(BOOST)

$(MKDIR_OBJ):
	mkdir -p $(OBJ_DIR)

clean:
	rm -r $(OBJ_FILES) $(OBJ_DIR)
	rm $(BUILD_BINARY)