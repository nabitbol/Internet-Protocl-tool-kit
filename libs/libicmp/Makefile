LIBICMP = libcmp.a

DIR_SRC = src
DIR_INCLUDES = inc
DIR_OBJ = bin/obj

SRC = $(DIR_SRC)/logs_utils.c \
      $(DIR_SRC)/transcode_utils.c \
      $(DIR_SRC)/checksum.c

OBJ = $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

CC = gcc
AR = ar rcs

CFLAGS = -I$(DIR_INCLUDES)

.PHONY: all clean re test

all: $(LIBICMP)

test: $(LIBICMP)
	$(CC) $(CFLAGS) tests/test_checksum.c $(LIBICMP) -o checksum_test
	./checksum_test
	@rm -f checksum_test

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
