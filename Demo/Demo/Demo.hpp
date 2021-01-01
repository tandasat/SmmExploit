#pragma once
#include <ntddk.h>
#include <ntstrsafe.h>
#include <ntintsafe.h>
#include <intrin.h>

#ifndef Add2Ptr
#define Add2Ptr(P,I) ((PVOID)((PUCHAR)(P) + (I)))
#endif

constexpr ULONG k_PoolTag = 'OMED';

#define DEMO_INFO(Format, ...) \
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, \
               DPFLTR_ERROR_LEVEL, \
               "[+] %s: " Format "\n", \
               __FUNCTION__, \
               __VA_ARGS__)

#define DEMO_ERROR(Format, ...) \
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, \
               DPFLTR_ERROR_LEVEL, \
               "[-] %s: " Format "\n", \
               __FUNCTION__, \
               __VA_ARGS__)

//
// EDK2 things
//
#define EFIAPI __cdecl
typedef UINT64 UINTN;
typedef UINTN RETURN_STATUS;
typedef RETURN_STATUS EFI_STATUS;
typedef GUID EFI_GUID;
typedef HANDLE EFI_HANDLE;
typedef PHYSICAL_ADDRESS EFI_PHYSICAL_ADDRESS;
typedef wchar_t CHAR16;
#define EFI_SECURITY_VIOLATION    (0x8000000000000000ULL | 26)

typedef struct
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef struct
{
    void* Read;
    void* Write;
} EFI_MM_IO_ACCESS;

typedef struct
{
    EFI_MM_IO_ACCESS Mem;
    EFI_MM_IO_ACCESS Io;
} EFI_SMM_CPU_IO2_PROTOCOL;

//
// https://github.com/tianocore/edk2/blob/stable/202011/MdePkg/Include/Pi/PiSmmCis.h#L107
//
typedef struct
{
    EFI_TABLE_HEADER Hdr;
    CHAR16* SmmFirmwareVendor;
    UINT32 SmmFirmwareRevision;
    void* SmmInstallConfigurationTable;
    EFI_SMM_CPU_IO2_PROTOCOL SmmIo;
    void* SmmAllocatePool;
    void* SmmFreePool;
    void* SmmAllocatePages;
    void* SmmFreePages;
    void* SmmStartupThisAp;
    UINTN CurrentlyExecutingCpu;
    UINTN NumberOfCpus;
    UINTN* CpuSaveStateSize;
    void** CpuSaveState;
    UINTN NumberOfTableEntries;
    void* SmmConfigurationTable;
    void* SmmInstallProtocolInterface;
    void* SmmUninstallProtocolInterface;
    void* SmmHandleProtocol;
    void* SmmRegisterProtocolNotify;
    void* SmmLocateHandle;
    void* SmmLocateProtocol;
    void* SmiManage;
    void* SmiHandlerRegister;
    void* SmiHandlerUnRegister;
} EFI_SMM_SYSTEM_TABLE2;
static_assert(FIELD_OFFSET(EFI_SMM_SYSTEM_TABLE2, SmmLocateProtocol) == 0xd0);

//
// https://github.com/tianocore/edk2/blob/stable/202011/MdeModulePkg/Core/PiSmmCore/PiSmmCorePrivateData.h#L117
//
typedef struct
{
    UINTN Signature;
    EFI_HANDLE SmmIplImageHandle;
    UINTN SmramRangeCount;
    void* SmramRanges;
    void* SmmEntryPoint;
    BOOLEAN SmmEntryPointRegistered;
    BOOLEAN InSmm;
    EFI_SMM_SYSTEM_TABLE2* Smst;
    void* CommunicationBuffer;
    UINTN BufferSize;
    EFI_STATUS ReturnStatus;
    EFI_PHYSICAL_ADDRESS PiSmmCoreImageBase;
    UINT64 PiSmmCoreImageSize;
    EFI_PHYSICAL_ADDRESS PiSmmCoreEntryPoint;
} SMM_CORE_PRIVATE_DATA;
static_assert(FIELD_OFFSET(SMM_CORE_PRIVATE_DATA, Smst) == 0x30);
