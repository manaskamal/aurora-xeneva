REM edit -netdev for different nic available are -> rtl8139, e1000, pcnet
qemu-system-x86_64.exe -M q35 -m 1024M -drive if=pflash,format=raw,unit=0,file=.\uefi\OVMF-pure-efi.fd  -drive format=raw,file="\\.\PhysicalDrive1" -soundhw hda -netdev user,id=xeneva_net -device e1000,netdev=xeneva_net -vga vmware -serial stdio -device qemu-xhci,id=xhci -device usb-mouse,bus=xhci.0 