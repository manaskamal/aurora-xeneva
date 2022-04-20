## Creating and using Drivers inside Aurora Kernel
To create drivers for Aurora Kernel, one must create a visual studio c/c++ empty project and chose target extension as DLL _'.dll'_ file. There is a testdriver project to see as an example.

To test the driver inside Aurora Kernel, the _dll_ file must be copied to the _'root folder'_ of FAT32 formated boot device. An entry must be created inside _'audrv.cnf'_ file with full _dll_ file path. See next section, to create a _'audrv.cnf'_ file.

## __Creating _'audrv.cnf'_ file__
The file contains the entries for required drivers to be loaded while booting the kernel. Aurora searches driver using PCI detect methods, which scans the entries inside _'audrv.cnf'_ file for specific vendor_id and device_id. To create an entry, one must use simple brackets and entries begins with 1, __For Example__: (1) _//entry one_, (2) _//entry two_. 
After the entry number, one must add vendor id and product id within '[ ]' sqare brackets for that specific driver, __NOTE: Vendor ID and Device ID must be integer numbers not hexadecimal number and should be of 5 digit numbers__. After the device id and vendor id, one can add the full path of the driver, __NOTE: path should be begin with "/".__

__Example__: <br>
(1)[32902,4663 ]/test.dll  |
(0)



