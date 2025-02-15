CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

C_FLAG = -I $(INC_DIR)

create_objs:
	gcc -c -fPIC $(SRC_DIR)/helloA.c -o $(OBJ_DIR)/helloA.o	-I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/helloB.c -o $(OBJ_DIR)/helloB.o	-I $(INC_DIR)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o	-I $(INC_DIR)

create_shared_lib:
	gcc -shared $(OBJ_DIR)/helloA.o $(OBJ_DIR)/helloB.o -o $(LIB_SHARED_DIR)/libhello.so

create_static_lib:
	ar rcs $(LIB_STATIC_DIR)/libhello.a $(OBJ_DIR)/helloA.o $(OBJ_DIR)/helloB.o

all_shared_lib: create_objs create_shared_lib
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lhello -o $(BIN_DIR)/use-shared-library

all_static_lib: create_objs create_static_lib
	gcc $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lhello -o $(BIN_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a
	rm -rf $(BIN_DIR)/*