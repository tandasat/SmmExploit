#pragma once
#include "Demo.hpp"

class PhysicalMemory
{
public:
    NTSTATUS
    Initialize (
        );

    NTSTATUS
    Read (
        PVOID Buffer,
        ULONG64 SourceAddress,
        SIZE_T BytesToRead
        ) const;

    NTSTATUS
    Write (
        ULONG64 DestinationAddress,
        PVOID Buffer,
        SIZE_T BytesToWrite
        ) const;

    ~PhysicalMemory (
        );

private:
    enum class OPERATION_TYPE
    {
        Read,
        Write,
    };

    NTSTATUS
    Copy (
        ULONG64 AddressToMap,
        PVOID Buffer,
        SIZE_T BytesToCopy,
        OPERATION_TYPE Operation
        ) const;

    HANDLE m_SectionHandle = {};
};
