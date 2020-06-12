# $@ = target file
# $< = first dependency
# $^ = all dependencies
#

C_SOURCES = $(wildcard Math/*.c Math/Crypto/*.c *.c)
HEADERS = $(wildcard Math/*.h Math/Crypto/*.h *.c)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = gcc

# First rule is run by default
build: ${OBJ}
	gcc -o $@ $^

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} -c $< -o $@

clean:
	rm -rf *.o build
	rm -rf Math/*.o Math/Crypto/*.o

.PHONY: clean

#backup: os-image.bin
#	cp -r ./ ../backups_LogOS.d
