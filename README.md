KOS
===

A Hobby-OS to experiment with.

Running with Qemu
-----------------

1. Install qemu
2. Uncompress `tools/qemu/default.rawdisk.xz` as `tools/qemu/default.rawdisk`
3. Run: `make tests`

Running with VirtualBox
-----------------------

1. Install VirtualBox
2. Create a VM with a non-sparse VDI file
3. Symlink to this non-sparse VDI file as `tools/vbox/default.vdi`
4. Run: `PLAT=vbox make tests`
5. Run your VM on VirtualBox

Feedback
--------

Send all comments to <karthikkumar@gmail.com>
