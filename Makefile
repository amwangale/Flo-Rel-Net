NAME = FloRel

TESTING = Florel.test

CC = gcc

SRC_DIR = src

#CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

LIBGPIO = pigpio/

DIRLORA = sx1278-LoRa-RaspberryPi/
LIBLORA = $(DIRLORA)liblora.a

INCL = -I includes -pthread -lrt -lm -L$(LIBGPIO) -lpigpio

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
		$(MAKE) -C $(DIRLORA)
		$(MAKE) -C $(LIBGPIO)
		$(CC) $(CFLAGS) $(INCL) $(SRC) $(LIBLORA) -o $(NAME)

$(TESTING):
		$(MAKE) -C $(GPIOLIB)
		$(CC) $(CFLAGS) $(INCL) $(SRC) -D TESTING -o $(NAME)

all: $(NAME)

test: $(TESTING)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME) fclean $(DIRLORA)