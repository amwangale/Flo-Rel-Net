NAME = FloRel

TESTING = Florel.test

CC = gcc

SRC_DIR = src

CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

DIRGPIO = pigpio/
LIBGPIO = libpigpio.so

DIRLORA = sx1278-LoRa-RaspberryPi/
LIBLORA = $(DIRLORA)liblora.a

INCL = -I includes
LIBS = $(LIBLORA) -pthread -lrt -lm -lpigpio

SRC_DIR = src
SRC_FILES = main.c \
			hash.c \
			init.c \
			queue.c \
			node.c \
			receive.c \
			result.c \
			send.c \
			simulate.c \
			threads.c \
			utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

RM = rm -fr

$(NAME):
		$(MAKE) -C $(DIRGPIO)
		$(MAKE) -C $(DIRLORA) re
		$(CC) $(CFLAGS) $(INCL) $(SRC) $(LIBS) -o $(NAME)

$(TESTING):
		$(MAKE) -C $(GPIOLIB)
		$(CC) $(CFLAGS) $(INCL) $(SRC) -D TESTING -o $(NAME)

all: $(NAME)

test: $(TESTING)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)