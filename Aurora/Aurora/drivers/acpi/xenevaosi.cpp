

#ifdef __ACPICA_INCLUDE_
#include <acpi.h>
//#include <acpiosxf.h>




#include <atomic\mutex.h>
#include <hal.h>
#include <arch\x86_64\mmngr\vmmngr.h>
#include <stdint.h>

ACPI_MODULE_NAME("xenevaosi.cpp")

#define ACPI_MAX_INIT_TABLES 16

#define ACPI_FILE void*
static ACPI_TABLE_DESC tables[ACPI_MAX_INIT_TABLES];

//ACPICA Helpers

ACPI_STATUS AcpiEarlyTables()
{
	//Early tables - don't even need dynamic memory
	return AcpiInitializeTables(tables, ACPI_MAX_INIT_TABLES, TRUE);
}

 ACPI_STATUS StartAcpi()
{
	ACPI_STATUS Status;
	//prepare the main subsystem
	Status = AcpiInitializeSubsystem();
	if (ACPI_FAILURE(Status))
		return Status;
	//Copy to dynamic memory
	Status = AcpiReallocateRootTable();
	if (ACPI_FAILURE(Status))
		return Status;
	//Create ACPI namespace
	//Status = AcpiLoadTables();
	if (ACPI_FAILURE(Status))
		return Status;
	//Start the hardware
	Status = AcpiEnableSubsystem(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(Status))
		return Status;
	Status = AcpiInitializeObjects(ACPI_FULL_INITIALIZATION);
	if (ACPI_FAILURE(Status))
		return Status;
	return AE_OK;
}

void AcpiPowerOff () {
	AcpiEnterSleepState(5,0);
}
//ACPICA to OS interfaces

void MpSaveGpioInfo()
{

}

void MpSaveSerialInfo()
{

}

ACPI_STATUS AcpiOsInitialize()
{
	return AE_OK;
}

ACPI_STATUS AcpiOsTerminate()
{
	return AE_OK;
}

ACPI_PHYSICAL_ADDRESS AcpiOsGetRootPointer()
{
#if (defined(X86) || defined(X64))
	ACPI_PHYSICAL_ADDRESS Ret;
	AcpiFindRootPointer(&Ret);
	return Ret;
#endif

}

ACPI_STATUS AcpiOsPredefinedOverride(const ACPI_PREDEFINED_NAMES *PredefinedObject, ACPI_STRING *NewValue)
{
	*NewValue = (ACPI_STRING)NULL;
	return AE_OK;
}

ACPI_STATUS AcpiOsTableOverride(ACPI_TABLE_HEADER *ExistingTable, ACPI_TABLE_HEADER **NewTable)
{
	*NewTable = (ACPI_TABLE_HEADER*)NULL;
	return AE_OK;
}

ACPI_STATUS
AcpiOsPhysicalTableOverride(
ACPI_TABLE_HEADER       *ExistingTable,
ACPI_PHYSICAL_ADDRESS   *NewAddress,
UINT32                  *NewTableLength)
{
	*NewAddress = (ACPI_PHYSICAL_ADDRESS)NULL;
	*NewTableLength = 0;
	return AE_OK;
}

void *AcpiOsMapMemory(ACPI_PHYSICAL_ADDRESS PhysicalAddress, ACPI_SIZE Length)
{
	void* addr = get_free_page(Length, false);
	if (Length > 4096) {
		for (int i=0; i < Length / 4096;i++) {
			map_page (PhysicalAddress, (uint64_t)addr + i * 4096,0);
		}
	}else {
		map_page (PhysicalAddress, (uint64_t)addr, 0);
	}
	return addr;
}

void AcpiOsUnmapMemory(void *where, ACPI_SIZE length)
{
	if (length > 4096) {
		for (int i = 0; i < length / 4096; i++) {
			unmap_page ((uint64_t)where + i * 4096);
		}
	} else {
		unmap_page ((uint64_t)where);
	}
}

ACPI_STATUS AcpiOsGetPhysicalAddress(void *LogicalAddress, ACPI_PHYSICAL_ADDRESS *PhysicalAddress)
{
	*PhysicalAddress = (ACPI_PHYSICAL_ADDRESS)get_physical_address ((uint64_t)LogicalAddress);
	return AE_OK;
}

 void *AcpiOsAllocate(ACPI_SIZE Size)
{
	return malloc (Size);
}

//TODO: Slab allocator. For now, we just use the heap
 ACPI_STATUS
AcpiOsCreateCache(
char                    *CacheName,
UINT16                  ObjectSize,
UINT16                  MaxDepth,
ACPI_CACHE_T            **ReturnCache)
{
	/* *ReturnCache = (ACPI_CACHE_T*)new char[ObjectSize*MaxDepth];
	if (!*ReturnCache)
		return AE_NO_MEMORY;*/
	*ReturnCache = (ACPI_CACHE_T*)ObjectSize;
	return AE_OK;
}

ACPI_STATUS
AcpiOsDeleteCache(
ACPI_CACHE_T            *Cache)
{
	/*
	delete[] (char*)Cache;
	*/
	return AE_OK;
}

ACPI_STATUS
AcpiOsPurgeCache(
ACPI_CACHE_T            *Cache)
{
	/*
	delete[](char*)Cache;
	*/
	return AE_OK;
}

void *
AcpiOsAcquireObject(
ACPI_CACHE_T            *Cache)
{
	size_t size = (size_t)Cache;
	return (void*)malloc(size);
}

ACPI_STATUS
AcpiOsReleaseObject(
ACPI_CACHE_T            *Cache,
void                    *Object)
{
	//delete [](char*)Object;
	mfree(Object);
	return AE_OK;
}

void AcpiOsFree(void *Memory)
{
	//delete[] Memory;
	mfree(Memory);
}

BOOLEAN AcpiOsReadable(void *Memory, ACPI_SIZE Length)
{
	//Should check the pages are readable (i.e. present). BUT WE'RE THE KERNEL!
	return TRUE;
}

BOOLEAN AcpiOsWritable(void *Memory, ACPI_SIZE Length)
{
	return AcpiOsReadable(Memory, Length);		//If we can read it, we can write it, we're the kernel
}

ACPI_THREAD_ID AcpiOsGetThreadId()
{
	return 0;
}

ACPI_STATUS AcpiOsExecute(ACPI_EXECUTE_TYPE Type, ACPI_OSD_EXEC_CALLBACK Function, void *Context)
{
	//Should create a new thread. For now, just execute it.
	//UNUSED(Type);
	Function(Context);
	return AE_OK;
}

void AcpiOsSleep(UINT64 Milliseconds)
{
	//A crude implementation that just trys a bit of loop waiting
	auto lambda = [](int x) {
		x += 1;
	};
	for (int n = 0; n < Milliseconds * 10000; n++)
		lambda(n);
}

void AcpiOsStall(UINT32 Microseconds)
{
	//A crude implementation that just trys a bit of loop waiting
	auto lambda = [](int x) {
		x += 1;
	};
	for (int n = 0; n < Microseconds * 10; n++)
		lambda(n);
}

 ACPI_STATUS AcpiOsCreateSemaphore(UINT32 MaxUnits, UINT32 InitialUnits, ACPI_SEMAPHORE *OutHandle)
{
	*OutHandle = new ACPI_SEMAPHORE;
	if (!*OutHandle)
		return AE_NO_MEMORY;
	*OutHandle = (ACPI_SEMAPHORE)InitialUnits;
	return AE_OK;
}

ACPI_STATUS AcpiOsDeleteSemaphore(ACPI_SEMAPHORE Handle)
{
	delete Handle;
	return AE_OK;
}

ACPI_STATUS AcpiOsWaitSemaphore(ACPI_SEMAPHORE Handle, UINT32 Units, UINT16 Timeout)
{
	//TODO: when we have threads, implement these
	return AE_OK;
}

ACPI_STATUS
AcpiOsSignalSemaphore(
ACPI_SEMAPHORE          Handle,
UINT32                  Units)
{
	return AE_OK;
}

ACPI_STATUS AcpiOsCreateLock(ACPI_SPINLOCK *OutHandle)
{
	return AE_OK;
	//CREATE A LOCK HERE
	//after creating return AE_OK
}

void AcpiOsDeleteLock(void* Handle)
{
	return;
//	free the lock here
}

ACPI_CPU_FLAGS AcpiOsAcquireLock(ACPI_SPINLOCK Handle)
{
	return AE_OK;
	//ACQUIRE THE LOCK HERE
}

void AcpiOsReleaseLock(ACPI_SPINLOCK Handle, ACPI_CPU_FLAGS Flags)
{
	return;
	/*CSpinlock* spnlk = (CSpinlock*)Handle;
	spnlk->releaseSpinlock();*/
}

static void __fastcall InterruptHelper(uint32_t vect, size_t context, size_t handler)
{
	((ACPI_OSD_HANDLER)handler)((void*)context);
}

ACPI_STATUS AcpiOsInstallInterruptHandler(UINT32 InterruptLevel, ACPI_OSD_HANDLER Handler, void *Context)
{
	/*size_t pars[2] = { (size_t)Context, (size_t)Handler };
	size_t vect = getHal()->getIrqChip()->getInterruptVect(InterruptLevel);
	if (!getHal()->getInterruptManager()->addVect(vect, &InterruptHelper, pars))
		return AE_ERROR;*/
	return AE_OK;
}

ACPI_STATUS AcpiOsRemoveInterruptHandler(UINT32 InterruptNumber, ACPI_OSD_HANDLER Handler)
{
	/*size_t vect = getHal()->getIrqChip()->getInterruptVect(InterruptNumber);
	getHal()->getInterruptManager()->releaseVect(vect);*/
	return AE_OK;
}

void
AcpiOsWaitEventsComplete(void)
{
	return;
}

ACPI_STATUS
AcpiOsReadMemory(
ACPI_PHYSICAL_ADDRESS   Address,
UINT64                  *Value,
UINT32                  Width)
{
	UINT64* mapped = (UINT64*)AcpiOsMapMemory(Address, 8);
	if (!mapped)
		return AE_ERROR;
	if (Width == 64)
		*Value = *mapped;
	else
		*Value = *mapped & (((UINT64)1 << Width) - 1);
	return AE_OK;
}

ACPI_STATUS
AcpiOsWriteMemory(
ACPI_PHYSICAL_ADDRESS   Address,
UINT64                  Value,
UINT32                  Width)
{
	UINT64* mapped = (UINT64*)AcpiOsMapMemory(Address, 8);
	if (!mapped)
		return AE_ERROR;
	if (Width == 64)
		*mapped = Value;
	else if (Width == 32)
		*(UINT32*)mapped = Value;
	else if (Width == 16)
		*(UINT16*)mapped = Value;
	else if (Width == 8)
		*(UINT8*)mapped = Value;
	else
		return AE_BAD_PARAMETER;
	return AE_OK;
}

ACPI_STATUS
AcpiOsReadPort(
ACPI_IO_ADDRESS         Address,
UINT32                  *Value,
UINT32                  Width)
{
	switch (Width)
	{
	case 32:
		*Value = inportd(Address);
		break;
	case 16:
		*Value = inportw(Address);
		break;
	case 8:
		*Value = inportb(Address);
		break;
	default:
		return AE_BAD_PARAMETER;
		break;
	}
	return AE_OK;
}

ACPI_STATUS
AcpiOsWritePort(
ACPI_IO_ADDRESS         Address,
UINT32                  Value,
UINT32                  Width)
{
	switch (Width)
	{
	case 32:
		outportd(Address, Value);
		break;
	case 16:
		outportw(Address, Value);
		break;
	case 8:
		outportb(Address, Value);
		break;
	default:
		return AE_BAD_PARAMETER;
		break;
	}
	return AE_OK;
}

ACPI_STATUS
AcpiOsReadPciConfiguration(
ACPI_PCI_ID             *PciId,
UINT32                  Reg,
UINT64                  *Value,
UINT32                  Width)
{
#if defined X86 || defined X64
	const UINT32 CONFIG_ADDRESS = 0xCF8;
	const UINT32 CONFIG_DATA = 0xCFC;

	uint32_t address = (uint32_t)((PciId->Bus << 16) | (PciId->Device << 11) |
		(PciId->Function << 8) | (Reg & 0xfc) | ((uint32_t)0x80000000));

	outportd(CONFIG_ADDRESS, address);
	*Value = inportd(CONFIG_DATA);

	switch (Width)
	{
	case 64:
		outportd(CONFIG_ADDRESS, address+4);
		*Value |= (((UINT64)inportd(CONFIG_DATA))<<32);
		break;
	case 16:
		*Value &= 0xFFFF;
		break;
	case 8:
		*Value &= 0xFF;
		break;
	default:
		return AE_BAD_PARAMETER;
	}
	return AE_OK;
#endif
}

ACPI_STATUS AcpiOsWritePciConfiguration(
	ACPI_PCI_ID             *PciId,
	UINT32                  Reg,
	UINT64                  Value,
	UINT32                  Width)
{
#if defined X86 || defined X64
	const UINT32 CONFIG_ADDRESS = 0xCF8;
	const UINT32 CONFIG_DATA = 0xCFC;

	uint32_t address = (uint32_t)((PciId->Bus << 16) | (PciId->Device << 11) |
		(PciId->Function << 8) | (Reg & 0xfc) | ((uint32_t)0x80000000));

	switch (Width)
	{
	case 64:
		outportd(CONFIG_ADDRESS, address);
		outportd(CONFIG_DATA, Value);
		outportd(CONFIG_ADDRESS, address + 4);
		outportd(CONFIG_DATA, Value >> 32);
		break;
	case 32:
		outportd(CONFIG_ADDRESS, address);
		outportd(CONFIG_DATA, Value);
	case 16:
		outportd(CONFIG_ADDRESS, address);
		outportw(CONFIG_DATA, Value);
	case 8:
		outportd(CONFIG_ADDRESS, address);
		outportb(CONFIG_DATA, Value);
		break;
	default:
		return AE_BAD_PARAMETER;
	}
	return AE_OK;
#endif
}

UINT64
AcpiOsGetTimer(
void)
{
	return 0; //READ_TSC();
}

ACPI_STATUS AcpiOsSignal(UINT32 Function, void* Info)
{
	return AE_MISSING_ARGUMENTS;
}

//TODO: do stuff beyond here

void ACPI_INTERNAL_VAR_XFACE AcpiOsPrintf(
	const char              *Format,
	...)
{
	return;
}

void AcpiOsVprintf(
const char              *Format,
va_list                 Args)
{
	return;
}

void AcpiOsRedirectOutput(void *Destination)
{
	return;
}

 ACPI_STATUS
AcpiOsGetLine(
char                    *Buffer,
UINT32                  BufferLength,
UINT32                  *BytesRead)
{
	return AE_OK;
}

void *
AcpiOsOpenDirectory(
char                    *Pathname,
char                    *WildcardSpec,
char                    RequestedFileType)
{
	return NULL;
}

char *
AcpiOsGetNextFilename(
void                    *DirHandle)
{
	return (char*)NULL;
}

void
AcpiOsCloseDirectory(
void                    *DirHandle)
{
	return;
}

ACPI_FILE
AcpiOsOpenFile(
const char              *Path,
UINT8                   Modes)
{
	return NULL;
}

void
AcpiOsCloseFile(
ACPI_FILE               File)
{
	return;
}

int
AcpiOsWriteFile(
ACPI_FILE               File,
void                    *Buffer,
ACPI_SIZE               Size,
ACPI_SIZE               Count)
{
	return -1;
}

long
AcpiOsGetFileOffset(
ACPI_FILE               File)
{
	return 0;
}

ACPI_STATUS
AcpiOsSetFileOffset(
ACPI_FILE               File,
long                    Offset,
UINT8                   From)
{
	return AE_NOT_FOUND;
}


#endif