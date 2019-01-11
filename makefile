CXX		  := g++
CXX_FLAGS := -std=gnu++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
INCLUDE_EXPRESSIONS := $(addprefix -I,$(INCLUDE))
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= colang

.PHONY: run clean flex bison


ifeq ($(OS),Windows_NT)
    MV = cmd \/C >nul move /Y
	FLEX = win_flex
	BISON = win_bison
	MKBIN = CMD \/C if not exist $(BIN) mkdir $(BIN)
else
    MV = mv -f
	FLEX = flex
	BISON = bison
	MKBIN = mkdir -p $(BIN)
endif


all: $(BIN)/$(EXECUTABLE)

run:
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SRC)/*/*.cpp
	@$(MKBIN)
	$(CXX) $(CXX_FLAGS) $(INCLUDE_EXPRESSIONS) -L$(LIB) $^ -o $@ $(LIBRARIES)



flexbison:
	@make flex
	@make bison
flex:
	$(FLEX) ./raw/lex.l
	@$(MV) ./lex.yy.c ./src/scanner.c
bison:
	$(BISON) -v -d --defines=parser.h --output=parser.c ./raw/grammar.y
	@$(MV) ./parser.h ./include/parser.h
	@$(MV) ./parser.c ./src/parser.c
