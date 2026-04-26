# Project: Internet-Protocol-tool-kit

NAME = ft_ping

# Directories
DIR_PING = apps/ping
DIR_LIBICMP = libs/libicmp
DIR_LIBNET = libs/libnet

DIR_PING_SRC = $(DIR_PING)/scrs
DIR_PING_OBJ = $(DIR_PING)/bin/obj

# Libraries
LIBICMP = $(DIR_LIBICMP)/libcmp.a
LIBNET = $(DIR_LIBNET)/libnet.a

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(DIR_LIBICMP)/inc -I$(DIR_LIBNET)/Inc -I$(DIR_PING_SRC)

# Sources
SRC_FILES = main.c parsing.c packet.c engine.c
OBJ = $(SRC_FILES:%.c=$(DIR_PING_OBJ)/%.o)

# Rules
.PHONY: all libs clean fclean re test

all: libs $(NAME)

libs:
	@$(MAKE) -C $(DIR_LIBICMP)
	@$(MAKE) -C $(DIR_LIBNET)

$(NAME): $(OBJ) $(LIBICMP) $(LIBNET)
	$(CC) $(CFLAGS) $(OBJ) $(LIBICMP) $(LIBNET) -o $(NAME)

$(DIR_PING_OBJ)/%.o: $(DIR_PING_SRC)/%.c
	@mkdir -p $(DIR_PING_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

test: libs
	@$(MAKE) -C $(DIR_LIBICMP) test

clean:
	@$(MAKE) -C $(DIR_LIBICMP) clean
	@$(MAKE) -C $(DIR_LIBNET) clean
	rm -rf $(DIR_PING)/bin

fclean: clean
	@$(MAKE) -C $(DIR_LIBICMP) fclean
	@$(MAKE) -C $(DIR_LIBNET) fclean
	rm -f $(NAME)

re: fclean all
