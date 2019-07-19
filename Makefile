NAME = FloRel

TESTING = Florel.test

CC = gcc

SRC_DIR = src

CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

INCL = -I includes -pthread -lrt -lm sx1278-LoRa-RaspberryPi/LoRa.h

GPIOLIB = pigpio/
LORALIB = sx1278-LoRa-RaspberryPi/

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
		$(MAKE) -C $(GPIOLIB)
		$(MAKE) -C $(LORALIB)
		$(CC) $(CFLAGS) $(INCL) $(SRC) sx1278-LoRa-RaspberryPi/LoRa.c -o $(NAME)

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