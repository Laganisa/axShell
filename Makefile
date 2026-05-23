CROSS_COMPILE := aarch64-linux-gnu-
CC            := $(CROSS_COMPILE)gcc
LD            := $(CROSS_COMPILE)ld
OBJCOPY       := $(CROSS_COMPILE)objcopy

MYLIB_DIR     ?= ../myLib
BUILD_DIR     ?= build
OBJ_DIR       := $(BUILD_DIR)/obj

TARGET_NAME   ?= SHELL
TARGET_ELF    := $(BUILD_DIR)/$(TARGET_NAME).elf
TARGET_IMAGE  := $(BUILD_DIR)/$(TARGET_NAME).bin
TARGET_BIN    := $(TARGET_NAME).BIN

SRC_DIRS      := Shell compiler editor
SRC_C         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC_S         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.S))
OBJS          := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_C)) \
                 $(patsubst %.S,$(OBJ_DIR)/%.o,$(SRC_S))

CPPFLAGS      += -Iinclude -I$(MYLIB_DIR)/include
CFLAGS        += -mcpu=cortex-a72 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -O2
LDFLAGS       += -T linker.ld
LDLIBS        += $(MYLIB_DIR)/build/libmylib.a

FM_EXEC_MAGIC ?= 0x4D594F535441534B
FM_EXEC_MODE  ?= 1

MKDIR_P       ?= mkdir -p
RM_RF         ?= rm -rf

.PHONY: all clean mylib

all: $(TARGET_BIN)

mylib:
	@$(MAKE) -C $(MYLIB_DIR) --no-print-directory

$(OBJ_DIR):
	@$(MKDIR_P) $@

$(BUILD_DIR):
	@$(MKDIR_P) $@

$(OBJ_DIR)/Shell $(OBJ_DIR)/compiler $(OBJ_DIR)/editor:
	@$(MKDIR_P) $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(OBJ_DIR)/Shell $(OBJ_DIR)/compiler $(OBJ_DIR)/editor
	@echo "CC  $<"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.S | $(OBJ_DIR) $(OBJ_DIR)/Shell $(OBJ_DIR)/compiler $(OBJ_DIR)/editor
	@echo "AS  $<"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET_ELF): mylib $(OBJS) | $(BUILD_DIR)
	@echo "LD  $@"
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(TARGET_IMAGE): $(TARGET_ELF)
	@echo "OBJCOPY  $@"
	$(OBJCOPY) $< -O binary $@

$(TARGET_BIN): $(TARGET_IMAGE)
	@echo "PACK  $@"
	@python3 -c "from pathlib import Path; import struct; image = Path(r'$(TARGET_IMAGE)').read_bytes(); hdr = struct.pack('<QQQQ', int('$(FM_EXEC_MAGIC)', 0), int('$(FM_EXEC_MODE)', 0), 0, len(image)); Path(r'$(TARGET_BIN)').write_bytes(hdr + image)"

clean:
	$(RM_RF) $(BUILD_DIR) $(TARGET_BIN)
