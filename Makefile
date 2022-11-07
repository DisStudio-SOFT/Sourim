kernel_src := $(shell find src/kernel -name *.c)
kernel_obj := $(patsubst src/kernel/%.c, out/kernel/%.o, $(kernel_src))

os_src := $(shell find src/os -name *.c)
os_obj := $(patsubst src/os/%.c, out/os/%.o, $(os_src))

$(kernel_obj): out/kernel/%.o : src/kernel/%.c
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -ffreestanding $(patsubst out/kernel/%.o, src/kernel/%.c, $@) -o $@
$(os_obj): out/os/%.o : src/os/%.c
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -ffreestanding $(patsubst out/os/%.o, src/os/%.c, $@) -o $@ 

.PHONY: build
build: $(kernel_obj) $(os_obj)
	@mkdir -p out/bootloader
	@nasm -f elf64 src/bootloader/header.s -o out/bootloader/header.o
	@nasm -f elf64 src/bootloader/main.s -o out/bootloader/main.o
	@nasm -f elf64 src/bootloader/main64.s -o out/bootloader/main64.o

	@x86_64-elf-ld -n -o targets/iso/boot/kernel.bin -T targets/linker.ld out/bootloader/*.o $(kernel_obj) ${os_obj} && \
	grub-mkrescue /usr/lib/grub/i386-pc -o build.iso targets/iso
	@echo Deleting .o files...
	@rm -rf out
	@echo Success!