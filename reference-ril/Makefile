NAME    := reference-ril

SHARED := lib$(NAME).so
STATIC := lib$(NAME).a

INCLUDES:= -I../include/ -I.

CFLAGS := -g -Wall -fPIC $(INCLUDES) -DLINUX -DRIL_SHLIB -D_GNU_SOURCE -pthread

LDFLAGS :=  $(LIBUDEV_LDFLAG) $(LIBUSB_LDFLAG) -lpthread -lbsd

PREFIX  := /usr

SRC := \
	at_tok.c \
	atchannel.c \
	misc.c \
	reference-ril.c \
	ril_linux.c

OBJ := $(SRC:%.c=%.o)

default: $(SHARED)
static: $(STATIC)

# Link shared library
$(SHARED): $(OBJ)
	$(CC) -shared -Wl,-soname,$(SHARED) $^ -o $@ $(LDFLAGS)

# Link static library
$(STATIC): $(OBJ)
	$(AR) -rcs $@ $^

# Other targets
clean:
	$(RM) *.a $(OBJ) *.so

install:
	cp -av $(SHARED) $(PREFIX)/lib

uninstall:
	$(RM) $(PREFIX)/lib/lib$(NAME).*
