MOUNT:=tools/vbox/vdimount
UMOUNT:=sudo umount
CP=sudo cp
TMPDIR=/tmp/vdi
DEV:="bin/default.vdi"
PART=1
PATH+=:tools/vbox

install: os_binary
	$(MKDIR) $(TMPDIR) && \
	$(MOUNT) $(DEV) $(TMPDIR) $(PART) && \
	$(MKDIR) $(TMPDIR)/kos/ && \
	$(CP) $(kkrn_exe) $(TMPDIR)/kos/ && \
	$(UMOUNT) $(TMPDIR) && \
	$(RMDIR) $(TMPDIR)

tests: install
	echo "Please add "$(DEV)" and start a VM on VirtualBox"
