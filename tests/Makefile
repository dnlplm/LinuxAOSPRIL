SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=)

INCLUDES := -I. -I../reference-ril -I../include
CFLAGS   := -g -Wall -DRIL_SHLIB -pthread

LDFLAGS  := -lpthread

DEPS := ../reference-ril/libreference-ril.*

all: shared

shared: LDFLAGS += -L../reference-ril -lreference-ril
shared: $(OBJS)

static: LDFLAGS += -static -L.. -lreference-ril
static: $(OBJS)

% : %.c $(DEPS)
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@.o
	$(CC) $@.o $(LDFLAGS) -o $@

clean:
	rm -f $(OBJS)
	rm -f *.o
