# Things OS should do

1. Multiple schedulers (I/O drives switching, CPU drives switching, Process
   drives switching etc.)
2. Paging is optional, for performance. New hardware requires it because
   not all physical bits are addressable.
3. Always use fallback code for new hardware.
4. Very low kernel footprint. Only develop kernel and exec/kexec.
   Other user agents run as addons for the kernel.
5. Data is kernel independant. We have a stable, never changing, KDF - kernel
   data format. User agent data migration is not a kernel's responsibility. Location of
   data is relocatable, outside the kernel image itself. This allows us to kexec.
6. File System is optional. Why do we have to get stuck to filesystems at all?
   They should all be User agent driven. The User agent should use a FUSE
   like library interface and link a FS into its code.

# Real Goals

Simplicity, Perfect things, Dynamism that can benefit long term
than laziness does - work out your ideals.

# Pie in the Sky Goals

1. Run 16, 32 and 64 bit code on same image.
2. Built-in Containers or Namespaces.
3. Multi-binary and services support.
4. Enable single data image system across cluster thereby
   encouraging highly heterogenously distributed apps.
