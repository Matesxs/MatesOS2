OSNAME = MatesOS2

LDS = kernel/kernel.ld
CC = gcc
ASMC = nasm
LD = ld

CFLAGS = -ffreestanding -fshort-wchar -mno-red-zone -fno-exceptions -Wall -Wfatal-errors -fno-stack-protector -Iinclude -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fzero-initialized-in-bss
ASMFLAGS =
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := kernel/src
OBJDIR := kernel/obj
BUILDDIR := kernel/bin
ISO_IMAGE := $(OSNAME).iso

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
ASMSRC = $(call rwildcard,$(SRCDIR),*.asm)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(ASMSRC))

#$(OBJDIR)/interrupts/interrupts.o: $(SRCDIR)/interrupts/interrupts.cpp | $(OBJDIR)
#	@ echo !======= COMPILING $^
#	@ mkdir -p $(@D)
#	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@ echo !======= COMPILING $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm | $(OBJDIR)
	@ echo !======= COMPILING $^
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@

$(BUILDDIR)/kernel.elf: $(OBJS) | $(BUILDDIR)
	@ echo !======= LINKING $^
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

$(BUILDDIR):
	@echo !======= Creating build directory
	@mkdir $(BUILDDIR)

$(OBJDIR):
	@echo !======= Creating build object
	@mkdir $(OBJDIR)

.PHONY: debug clean $(ISO_IMAGE) init clean_kernel

all: $(ISO_IMAGE)

init:
	sudo apt-get install gcc nasm gdb
	sudo apt-get install qemu qemu-system-common

debug: CFLAGS += -g
debug: clean kernel

kernel: $(BUILDDIR)/kernel.elf

rebuildkernel: clean_kernel kernel

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.4-binary --depth=1
	$(MAKE) -C limine

image: $(ISO_IMAGE)

$(ISO_IMAGE): limine kernel
	rm -rf iso_root

	mkdir -p iso_root
	mkdir -p iso_root/boot
	mkdir -p iso_root/static_data

	cp limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-eltorito-efi.bin startup.nsh iso_root/
	cp static_data/bg.bmp iso_root/static_data/
	cp $(BUILDDIR)/kernel.elf limine/BOOTX64.EFI iso_root/boot/

	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-eltorito-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(ISO_IMAGE)

	limine/limine-install $(ISO_IMAGE)

	rm -rf iso_root

run: image
	qemu-system-x86_64 -M q35 -m 2G -cdrom $(ISO_IMAGE)

run_debug: debug image
	qemu-system-x86_64 -s -S -M q35 -m 2G -cdrom $(ISO_IMAGE)

clean_kernel:
	rm -rf $(BUILDDIR)
	rm -rf $(OBJDIR)

clean: clean_kernel
	rm -rf limine
	rm -rf $(ISO_IMAGE)