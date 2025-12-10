# Nome do executável final
PROJ_NAME=ordenacao

# Encontra todos os arquivos .c na pasta
C_SOURCE=$(wildcard *.c)

# Encontra todos os arquivos .h na pasta
H_SOURCE=$(wildcard *.h)

# Define os objetos (.o) baseados nos arquivos .c
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -Wall      \
         -Wextra    \
         -g         \
         -pedantic

#########################
# Compilação e linkagem #
#########################

all: $(PROJ_NAME)

# Linkagem: Cria o executável a partir dos objetos
# ATENÇÃO: A linha abaixo deve começar com um TAB
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

# Compilação: Cria os objetos (.o) a partir dos fontes (.c)
# ATENÇÃO: A linha abaixo deve começar com um TAB
%.o: %.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

# Limpeza
clean:
	$(CC) rm -rf *.o $(PROJ_NAME).exe