NAME = FloRel

# TESTING = shell42.test

CC = gcc

SRC_DIR = src

CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

INCL = -I includes

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
		$(CC) $(CFLAGS) $(INCL) $(SRC) -o $(NAME)

$(TESTING):
		$(CC) $(CFLAGS) $(INCL) $(SRC) -D TESTING -o $(NAME)

all: $(NAME)

test: $(TESTING)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)