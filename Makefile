# compile settings
GCC = g++ -std=c++17
BUILD_BINARY = morel
TEST_BINARIES = testSetup testHelper testCalculator testDialog
BOOST = -lboost_system -lboost_filesystem
MY_SQL = -L/usr/lib/x86_64-linux-gnu/ -lmysqlcppconn

# directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
DATA_DIR = data
REPORT_DIR = reports

# file collections
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# other aliases
MKDIR_OBJ = make_object_directory

all: $(MKDIR_OBJ) $(BUILD_BINARY)
	./morel

$(BUILD_BINARY): $(OBJ_FILES)
	$(GCC) -o $@ $^ $(BOOST) $(MY_SQL)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(GCC) -c -o $@ $^ $(BOOST) $(MY_SQL)

$(MKDIR_OBJ):
	mkdir -p $(BUILD_DIR) $(DATA_DIR) $(REPORT_DIR)
 
test: $(TEST_BINARIES)
	./testSetup
	./testHelper
	./testCalculator
	./testDialog

test%: test%.o
	$(GCC) test$*.o -o test$* $(BOOST) $(MY_SQL)

test%.o: $(TEST_DIR)/test%.cpp
	$(GCC) -c $(TEST_DIR)/test$*.cpp

clean:
	rm -r $(OBJ_FILES) $(BUILD_DIR)
	rm $(BUILD_BINARY)

cleanTests:
	rm $(TEST_BINARIES)
	rm $(TEST_DIR)/testConfig.txt