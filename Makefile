CC ?= gcc
AR ?= ar

SRCDIR := src
OBJDIR := build
LIBDIR := lib

PROJECT_NAME ?= kitkit

# Install libraries and headers to directory
INSTALL_DIR ?= /usr/local

CFLAGS ?= -O2 -Wall -Wextra -fPIC -MMD -MP
LDFLAGS ?=

ARFLAGS ?= rcs

# Discover sources and headers under src
SRCS := $(shell find $(SRCDIR) -name '*.c')
HDRS := $(shell find $(SRCDIR) -name '*.h')
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

INCLUDES ?= -I$(SRCDIR) 
INCLUDES += $(patsubst %,-I%,$(sort $(dir $(SRCS))))

.PHONY: all static shared install uninstall clean

all: static shared

static: $(LIBDIR)/lib$(PROJECT_NAME).a

$(LIBDIR)/lib$(PROJECT_NAME).a: $(OBJS)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(OBJS)

shared: $(LIBDIR)/lib$(PROJECT_NAME).so

$(LIBDIR)/lib$(PROJECT_NAME).so: $(OBJS)
	@mkdir -p $(LIBDIR)
	$(CC) -shared -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

install: all
	@echo "Installing to: $(INSTALL_DIR)"
	@mkdir -p $(INSTALL_DIR)/lib
	cp -v $(LIBDIR)/lib$(PROJECT_NAME).a $(INSTALL_DIR)/lib/ || true
	cp -v $(LIBDIR)/lib$(PROJECT_NAME).so $(INSTALL_DIR)/lib/ || true
	@mkdir -p $(INSTALL_DIR)/include/$(PROJECT_NAME)
	for h in $(HDRS); do \
		cp -v $$h $(INSTALL_DIR)/include/$(PROJECT_NAME)/; \
	done

uninstall:
	-rm -f $(INSTALL_DIR)/lib/lib$(PROJECT_NAME).a
	-rm -f $(INSTALL_DIR)/lib/lib$(PROJECT_NAME).so
	-rm -f $(INSTALL_DIR)/include/$(PROJECT_NAME)/* || true

clean:
	-rm -rf $(OBJDIR) $(LIBDIR)
	-rm -f $(DEPS)

-include $(DEPS)
