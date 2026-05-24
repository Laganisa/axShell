CROSS_COMPILE := aarch64-linux-gnu-
CC            := $(CROSS_COMPILE)gcc
LD            := $(CROSS_COMPILE)ld
OBJCOPY       := $(CROSS_COMPILE)objcopy

axLIB_DIR     ?= ../axLib
BUILD_DIR     ?= build
OBJ_DIR       := $(BUILD_DIR)/obj

# 최종 출력될 바이너리 이름을 SHELL.BIN으로 고정!
TARGET_NAME   := SHELL
TARGET_ELF    := $(BUILD_DIR)/$(TARGET_NAME).elf
TARGET_IMAGE  := $(BUILD_DIR)/$(TARGET_NAME).bin
TARGET_BIN    := $(TARGET_NAME).BIN

SRC_DIRS      := src
SRC_C         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SRC_S         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.S))
OBJS          := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_C)) \
                 $(patsubst %.S,$(OBJ_DIR)/%.o,$(SRC_S))

CPPFLAGS      += -Iinclude -I$(axLIB_DIR)/include
CFLAGS        += -mcpu=cortex-a72 -ffreestanding -fno-builtin -nostdlib -Wall -Wextra -O2
LDFLAGS       += -T linker.ld
LDLIBS        += $(axLIB_DIR)/build/libaxlib.a

FM_EXEC_MAGIC ?= 0x4D594F535441534B
FM_EXEC_MODE  ?= 1

MKDIR_P       ?= mkdir -p
RM_RF         ?= rm -rf

.PHONY: all clean axlib

all: $(TARGET_BIN)

axlib:
	@$(MAKE) -C $(axLIB_DIR) --no-print-directory

$(OBJ_DIR):
	@$(MKDIR_P) $@

$(BUILD_DIR):
	@$(MKDIR_P) $@

# build/obj/src 하위 디렉토리 자동 생성 규칙 포함
$(OBJ_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "CC  $<"
	@$(MKDIR_P) $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.S | $(BUILD_DIR)
	@echo "AS  $<"
	@$(MKDIR_P) $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET_ELF): axlib $(OBJS) | $(BUILD_DIR)
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