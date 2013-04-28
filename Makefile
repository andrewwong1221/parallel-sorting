CC = gcc
CCFLAGS = -O3 -pg -Wall -g -pthread
LDFLAGS = -pg -lm -g -pthread

SRCDIR = src
OBJDIR = obj
EXEDIR = bin

# SRCS = bitonic.c radix.c
SRCS = main.c utils.c bitonic.c radix.c sample.c merge.c hrtimer_x86.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

SORT = $(EXEDIR)/sort


################################################################################
# Run all and clean if "targets" exist
################################################################################
.PHONY: all clean
################################################################################

all: $(SORT)


# Create output directories
$(OBJDIR):
	-mkdir -p $(OBJDIR)
$(EXEDIR):
	-mkdir -p $(EXEDIR)

$(OBJS): | $(OBJDIR)
$(SORT): | $(EXEDIR)


$(SORT): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CCFLAGS) $< -o $@

run:
	./$(SORT)
clean:
	-rm $(EXEDIR)/*
	-rm $(OBJDIR)/*
