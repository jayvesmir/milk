DEBUG = 0
GDB_PORT = 1234

LINK = clang --target=riscv64 -march=rv64gc
CC = clang --target=riscv64 -march=rv64gc
ASM = clang --target=riscv64 -march=rv64gc

ifeq ($(DEBUG), 1)
	OPT_FLAGS = -fno-inline -Og -ggdb
	VM_OPT_FLAGS = -S -gdb tcp::$(GDB_PORT)
else
	OPT_FLAGS = -O3
	VM_OPT_FLAGS = ""
endif

COMMONFLAGS = -nostdlib
LINKFLAGS = $(COMMONFLAGS) -ffreestanding -static -T src/linker.ld
CCFLAGS = $(COMMONFLAGS) -ffreestanding -fno-exceptions -r -I src/ -mcmodel=medany -std=c++20 -Wall -Wextra -Wpedantic $(OPT_FLAGS)
ASMFLAGS = $(COMMONFLAGS) -r

BUILD_DIR = build
OUTPUT_NAME = $(BUILD_DIR)/milk

asm_obj = $(patsubst src/%.asm, $(BUILD_DIR)/obj/%.asm.o, $(shell find src -name *.asm))
cpp_obj = $(patsubst src/%.cpp, $(BUILD_DIR)/obj/%.cpp.o, $(shell find src -name *.cpp))

$(asm_obj): $(BUILD_DIR)/obj/%.asm.o : src/%.asm
	@mkdir -p $(dir $@) #
	@echo ASM $@ #
	@$(ASM) $(ASMFLAGS) -o $@ $(patsubst $(BUILD_DIR)/obj/%.asm.o, src/%.asm, $@)

$(cpp_obj): $(BUILD_DIR)/obj/%.cpp.o : src/%.cpp
	@mkdir -p $(dir $@) #
	@echo CPP $@ #
	@$(CC) $(CCFLAGS) -o $@ $(patsubst $(BUILD_DIR)/obj/%.cpp.o, src/%.cpp, $@)

build: $(asm_obj) $(cpp_obj)
	@mkdir -p $(dir $(OUTPUT_NAME)) #
	@echo LINK $(OUTPUT_NAME) #
	@$(LINK) $(LINKFLAGS) -o $(OUTPUT_NAME) $(asm_obj) $(cpp_obj)

VM = qemu-system-riscv64
VMFLAGS = -nographic -m 512M -smp 1 -machine virt -bios none -kernel $(OUTPUT_NAME)

run: build
	@$(VM) $(VMFLAGS) $(VM_OPT_FLAGS)

clean:
	@rm -rf $(BUILD_DIR) #