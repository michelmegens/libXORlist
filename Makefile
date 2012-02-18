#
# (C) Michel Megens, 2012
#

CC=gcc
LD=gcc
CCFLAGS=-c -m32
LDFLAGS=-m32

#TARGET
TARGET=xorll

SRCF = main.c list.c
OBJS = $(SRCF:.c=.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

%o: %c
	$(CC) $(CCFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -fv $(OBJS) $(TARGET)
