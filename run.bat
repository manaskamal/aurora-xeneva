REM edit -netdev for different nic available are -> rtl8139, e1000, pcnet, for sound --> sb16   "\\.\PhysicalDrive1"
qemu-system-x86_64.exe -m 1024M -drive if=pflash,format=raw,unit=0,file=.\uefi\OVMF-pure-efi.fd  -drive id=h_d,format=raw,file="\\.\PhysicalDrive1",if=none -soundhw hda -netdev user,id=xeneva_net -device e1000,netdev=xeneva_net -vga vmware -serial stdio -device qemu-xhci,id=xhci -device usb-mouse,bus=xhci.0 -device ahci,id=ahci -device ide-hd,drive=h_d,bus=ahci.0