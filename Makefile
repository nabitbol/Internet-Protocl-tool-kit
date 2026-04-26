# Project: Internet-Protocol-tool-kit

NAME = ft_ping

# Directories
DIR_PING = apps/ping
DIR_LIBICMP = libs/libicmp
DIR_LIBNET = libs/libnet

# Libraries
LIBICMP = $(DIR_LIBICMP)/libcmp.a
LIBNET = $(DIR_LIBNET)/libnet.a

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(DIR_LIBICMP)/inc -I$(DIR_LIBNET)/Inc -I$(DIR_PING)/scrs

# Sources
SRC = $(DIR_PING)/scrs/main.c \
      $(DIR_PING)/scrs/parsing.c \
      $(DIR_PING)/scrs/packet.c
OBJ = $(SRC:.c=.o)

# Rules
.PHONY: all libs clean fclean re test

all: libs $(NAME)

libs:
	@$(MAKE) -C $(DIR_LIBICMP)
	@$(MAKE) -C $(DIR_LIBNET)

$(NAME): $(OBJ) $(LIBICMP) $(LIBNET)
	$(CC) $(CFLAGS) $(OBJ) $(LIBICMP) $(LIBNET) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: libs
	@$(MAKE) -C $(DIR_LIBICMP) test

clean:
	@$(MAKE) -C $(DIR_LIBICMP) clean
	@$(MAKE) -C $(DIR_LIBNET) clean
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C $(DIR_LIBICMP) fclean
	@$(MAKE) -C $(DIR_LIBNET) fclean
	rm -f $(NAME)

re: fclean all
