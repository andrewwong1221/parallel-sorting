CC = gcc
CCFLAGS = -O3 -Wall -g -pthread
LDFLAGS = -lm -g -pthread

LIBS = $(LIBDIR)/libsort.a

SRCDIR = src
OBJDIR = obj
EXEDIR = bin
LIBDIR = lib

UTILSRC = main.c utils.c hrtimer_x86.c
SORTSRC = bitonic.c radix.c sample.c merge.c qsort.c
SRCS = $(SORTSRC) $(UTILSRC)
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
SORTOBJS = $(SORTSRC:%.c=$(OBJDIR)/%.o)

SORT = $(EXEDIR)/sort


################################################################################
# Run all and clean if "targets" exist
################################################################################
.PHONY: all clean 
################################################################################

all: $(SORT) $(LIBS)

library: $(LIBS)

# Create sorting lib
$(LIBS): $(SORTOBJS)
	ar rvcs $@ $(SORTOBJS)

# Create output directories
$(OBJDIR):
	-mkdir -p $(OBJDIR)
$(EXEDIR):
	-mkdir -p $(EXEDIR)
$(LIBDIR):
	-mkdir -p $(LIBDIR)

$(LIBS): | $(LIBDIR)
$(OBJS): | $(OBJDIR) 
$(SORT): | $(EXEDIR)


$(SORT): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CCFLAGS) $< -o $@

run:
	./$(SORT)
clean:
	-@rm $(LIBDIR)/*
	-@rm $(EXEDIR)/*
	-@rm $(OBJDIR)/*
