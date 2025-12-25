# Compiler and flags
CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -O2
LIBS    = -lpcap

# Directories (adjusted for ids-project nesting)
SRCDIR  = ids-project/src/ids
OBJDIR  = obj
BUILDDIR = ids-project/build

# Source files
SRC     = $(wildcard $(SRCDIR)/*.c)
# Object files in separate directory
OBJ     = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# Final executable
TARGET  = $(BUILDDIR)/ids

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create required directories if they do not exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BUILDDIR)

# Declare phony targets
.PHONY: all clean