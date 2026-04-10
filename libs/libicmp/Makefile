LIBICMP = libcmp.a

DIR_SRC = src
DIR_INCLUDES = inc
DIR_OBJ = bin/obj

SRC = $(DIR_SRC)/logs_utils.c \
      $(DIR_SRC)/transcode_utils.c

OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

CC = gcc
AR = ar rcs

CFLAGS = -I$(DIR_INCLUDES)

.PHONY: all clean re

all: $(LIBICMP)

# ---------------- LIBRARY ----------------

$(LIBICMP): $(OBJ)
	$(AR) $@ $^

# ---------------- OBJECT FILES ----------------

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------- CLEAN ----------------

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f $(LIBICMP)

re: fclean all
