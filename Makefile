COMPILADOR = gcc
CFLAGS = -Iinclude

OBJ_DIR = obj

_OBJ = definitions.o inicializacoes.o sprites.o auxiliares.o cutscenes.o main.o allmain.o  
OBJ = $(patsubst %.o,$(OBJ_DIR)/%.o,$(_OBJ))

CABECALHOS = include/auxiliares.h \
             include/cutscenes.h \
             include/inicializacoes.h \
             include/main.h \
             include/settings.h \
             include/sprites.h

$(OBJ_DIR)/%.o: source/%.c $(CABECALHOS)
	mkdir -p $(OBJ_DIR)
	$(COMPILADOR) -c -o $@ $< $(CFLAGS)

acecombat: $(OBJ)
	$(COMPILADOR) -o $@ $^

.PHONY: clean

clean:
	rm -f $(OBJ_DIR)/*.o acecombat