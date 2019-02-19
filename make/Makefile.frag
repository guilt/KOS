RM:=rm -f
CP:=cp
MV:=mv
CHDIR:=cd
MKDIR:=mkdir -p
RMDIR:=rmdir
FIND:=find

#TC_PREFIX=i386-elf-
#TC_SUFFIX=-4.3.2

CC=$(TC_PREFIX)gcc$(TC_SUFFIX)
AS=$(CC)
LD=$(CC)
STRIP=$(TC_PREFIX)strip -s

ifdef DEBUG
  CFLAGS+=-g3
  ASFLAGS+=-g3
  LDFLAGS+=-g3
endif

ifndef TARGET
  TARGET=clib
endif
ifndef ARCH
  ARCH=x86
  TARGET_CFLAGS+=-m32
endif
ifndef PLAT
  PLAT=qemu
endif

include make/$(TARGET)/Makefile.pre
include make/$(TARGET)/$(ARCH)/Makefile
include make/$(TARGET)/$(PLAT)/Makefile
include make/$(TARGET)/Makefile.post

cleansrc:
	$(FIND) . -iname \*~ -exec rm \{\} \;
	$(FIND) . -iname \*- -exec rm \{\} \;
	$(FIND) . -iname \*.bk -exec rm \{\} \;
	$(FIND) . -iname \*.bak -exec rm \{\} \;
	$(FIND) . -iname \*.old -exec rm \{\} \;
	$(FIND) . -iname \*.save -exec rm \{\} \;

obj/%.o: $(TARGET)/src/%.c
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) -o "$@" -c "$<"

$(TARGET)/src/$(PLAT)/%.S: tools/$(TARGET)/$(PLAT)/%.S_gen
	"$<" > "$@"

obj/$(PLAT)/%.o: $(TARGET)/src/$(PLAT)/%.S
	$(AS) $(TARGET_ASFLAGS) $(ASFLAGS) -o "$@" -c "$<"

obj/$(PLAT)/%.o: $(TARGET)/src/$(PLAT)/%.c
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) -o "$@" -c "$<"

$(TARGET)/src/$(ARCH)/%.S: tools/$(TARGET)/$(ARCH)/%.S_gen
	"$<" > "$@"

obj/$(ARCH)/%.o: $(TARGET)/src/$(ARCH)/%.S
	$(AS) $(TARGET_ASFLAGS) $(ASFLAGS) -o "$@" -c "$<"

obj/$(ARCH)/%.o: $(TARGET)/src/$(ARCH)/%.c
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) -o "$@" -c "$<"

.PHONY: target

clean: target_clean cleansrc

tests: target
