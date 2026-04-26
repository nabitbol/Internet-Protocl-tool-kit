LIBNET = libnet.a

DIR_SRC = .
DIR_INCLUDES = Inc
DIR_OBJ = bin/obj

SRC = $(DIR_SRC)/net.c

OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

CC = gcc
AR = ar rcs

CFLAGS = -I$(DIR_INCLUDES)

.PHONY: all clean fclean re

all: $(LIBNET)

# ---------------- LIBRARY ----------------

$(LIBNET): $(OBJ)
	$(AR) $@ $^

# ---------------- OBJECT FILES ----------------

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------- CLEAN ----------------

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(LIBNET)

re: fclean all
