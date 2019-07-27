NAME = FloRel

TESTING = Florel.test

CC = g++

SRC_DIR = src

CFLAGS  = -Wall -Werror -Wextra -g
#-fsanitize=address

DIR_BASE = cooking/
DIR_LIB = $(DIR_BASE)libraries/

DIR_LORA = $(DIR_BASE)libraries/arduiPiLora/
LIB_LORA = $(DIR_BASE)arduPiLoRa.o

DIR_ARDU = $(DIR_BASE)arduPi/
LIB_ARDU = $(DIR_ARDU)arduPi.o

DIR_ARDU_API = $(DIR_BASE)arduPi-api/
LIB_ARDU_API_UART = $(DIR_ARDU_API)arduPiUART.o
LIB_ARDU_API_UTIL = $(DIR_ARDU_API)arduPiUtils.o
LIB_ARDU_API_MULT = $(DIR_ARDU_API)arduPiMultiprotocol.o

INCL = -I includes
LIBS = 	$(LIB_LORA) \
		$(LIB_ARDU) \
		$(LIB_ARDU_API) \
		$(LIB_ARDU_API_UART) \
		$(LIB_ARDU_API_UTIL) \
		$(LIB_ARDU_API_MULT) \
		-I $(DIR_ARDU) \
		-I $(DIR_ARDU_API) \
		-I $(DIR_LIB) \
		-pthread -lrt -lstdc++

#  "$1" \
#       "$LIBRARY_DIR/arduPiLoRa.o" \
#       "$ARDUPIAPI_DIR/arduPiUART.o" \
#       "$ARDUPIAPI_DIR/arduPiUtils.o" \
#       "$ARDUPIAPI_DIR/arduPiMultiprotocol.o" \
#       "$ARDUPI_DIR/arduPi.o" \
#       -I"$ARDUPI_DIR" \
#       -I"$ARDUPIAPI_DIR" \
#       -I"$LIBRARY_DIR



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
		sudo $(MAKE) install -C $(DIR_ARDU)bcm2835-1.46/
		$(CC) $(CFLAGS) $(INCL) $(SRC) $(LIBS) -o $(NAME)

$(TESTING):
		sudo $(MAKE) install -C $(DIR_ARDU)bcm2835-1.46/
		$(CC) $(CFLAGS) $(INCL) $(SRC) $(LIBS) -D TESTING -o $(NAME)

all: $(NAME)

test: $(TESTING)

clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)