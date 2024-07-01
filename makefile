CC = g++
SRC_DIR := src
OBJ_DIR:= obj
INCLUDE := include
BIN_PATH := bin
PROJECT := GtkCalc
GTK_FLAG := `pkg-config --cflags gtk4`
GTK_LIB := `pkg-config --libs gtk4`

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o,$(SRC_FILES))
OUT := $(BIN_PATH)/$(PROJECT)

all: clean $(OUT)
	@gtk-update-icon-cache -f -t $(BIN_PATH)/GtkCalc_Files/
	@printf "Building Project %s Completed.\nOutput : %s\nTo run : make run\n" $(PROJECT) $(OUT)

$(OUT): $(OBJ_FILES)
	@printf "Linking Up... : %s\n" $@
	@$(CC) $(GTK_FLAG) -I$(INCLUDE) -o $@ $^ $(GTK_LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "%s %s %s %s\n" $(CC) "O" $@ $<
	@$(CC) $(GTK_FLAG)  -I$(INCLUDE) -c -o $@ $^ $(GTK_LIB)
clean:
	@printf "Cleaning Up...\n"
	@rm -rf $(OBJ_DIR)/*
run:
	@exec $(OUT)

install:
	@sudo cp -r $(BIN_PATH)/* /usr/bin
	@sudo cp -r $(BIN_PATH)/* /usr/share
	@cp -r desktop/GtkCalc.desktop $(HOME)/Desktop