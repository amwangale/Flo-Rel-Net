NAME = liblora.a

CC = gcc

OBJ = obj/*.o

CCFLAGS = -c -g -Wall -Wextra # -Werror

RM = -rm -fr

ARCHIVE = ar rc

INDEX = ranlib

DIRGPIO = ../pigpio
LIBGPIO = libpigpio.so

INCL = -I incl -lrt -pthread -lm -lpigpio

HEADER = incl/LoRa.h

FILES = LoRa.c

SRC_DIR = srcs

SRC = $(addprefix $(SRC_DIR)/, $(FILES))

$(NAME):
		$(shell mkdir obj)
		$(CC) $(CCFLAGS) $(SRC) $(INCL)
		mv *.o obj
		$(ARCHIVE) $(NAME) $(OBJ)
		$(INDEX) $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)
