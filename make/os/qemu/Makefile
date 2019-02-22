MOUNT:=tools/qemu/rawmount
UMOUNT:=sudo umount
CP=sudo cp
TMPDIR=/tmp/qemu
DEV:="bin/default.rawdisk"
QARCH?=i386
QEMU?=qemu-system-$(QARCH)
PART=1
CURSES=1

install: os_binary
	$(MKDIR) $(TMPDIR) && \
	$(MOUNT) $(DEV) $(TMPDIR) $(PART) && \
	$(MKDIR) $(TMPDIR)/kos/ && \
	$(CP) $(kkrn_exe) $(TMPDIR)/kos/ && \
	$(UMOUNT) $(TMPDIR) && \
	$(RMDIR) $(TMPDIR)

DBG_CMD=echo "No Debugging."
DBG_FLAGS=
RUN_CMD=${QEMU}
RUN_FLAGS=
WAIT_CMD=echo -n

ifdef DEBUG
DBG_CMD=gdb
DBG_FLAGS+=-x tools/qemu/qemu-gdb.scripts
RUN_FLAGS+=-s -S -d in_asm,cpu,pcall,int,cpu_reset
#out_asm,op,op_opt,exec
WAIT_CMD=sleep 2
endif

RUN_FLAGS+=-hda $(DEV)
ifdef CURSES
RUN_FLAGS+=-curses
else
RUN_FLAGS+=>/dev/null 2>&1
endif

tests: install
	$(RUN_CMD) $(RUN_FLAGS) & \
	$(WAIT_CMD) && \
	$(DBG_CMD) $(DBG_FLAGS)
