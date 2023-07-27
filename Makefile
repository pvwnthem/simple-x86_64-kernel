x86_64_asm_src_files := $(shell find src/impl/x86_64 -name '*.s')
x86_64_asm_obj_files := $(patsubst src/impl/x86_64/%.s, build/x86_64/%.o, $(x86_64_asm_src_files))

$(x86_64_asm_obj_files): build/x86_64/%.o: src/impl/x86_64/%.s
	@mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/impl/x86_64/%.s, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_64_asm_obj_files)
	mkdir -p dist/x86_64 && .
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(x86_64_asm_obj_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso

