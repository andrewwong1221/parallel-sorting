CC = gcc
CCFLAGS = -O0 -pg -Wall -g
LDFLAGS = -pg -lm -g

SRCDIR = src/
OBJDIR = obj/
EXEDIR = bin/

SRCS = bitonic.c
OBJS = $(OBJDIR)$(SRCS:.c=.o)

BITONIC = $(EXEDIR)bitonic_sort


################################################################################
# Run all and clean if "targets" exist
################################################################################
.PHONY: all clean
################################################################################

all: $(BITONIC)

$(BITONIC): $(OBJDIR)bitonic.o $(OBJDIR)main.o 
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CCFLAGS) $< -o $@

run:
	./$(BITONIC)
clean:
	-@rm $(EXEDIR)bitonic_sort $(OBJDIR)*
