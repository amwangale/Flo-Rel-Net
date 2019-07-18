NAME = FloRel

TESTING = Florel.test

CC = gcc

SRC_DIR = src

CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

INCL = -I includes

GPIOLIB = pigpio/
LORALIB = sx1278-LoRa-RaspberryPi/

SRC_DIR = src
SRC_FILES = main.c \
			hash.c \
			init.c \
			queue.c \
			receive.c \
			result.c \
			send.c \
			simulate.c \
			utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

RM = rm -fr

$(NAME):
		$(MAKE) -C $(GPIOLIB)
		$(MAKE) -C $(LORALIB)
		$(CC) $(CFLAGS) $(INCL) $(SRC) -o $(NAME)

$(TESTING):
		$(MAKE) -C $(GPIOLIB)
		$(MAKE) -C $(LORALIB)
		$(CC) $(CFLAGS) $(INCL) $(SRC) -D TESTING -o $(NAME)

all: $(NAME)

test: $(TESTING)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)