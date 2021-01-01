#pragma once
#include "Demo.hpp"
#include "PhysicalMemory.hpp"

struct HOOKED_SMM_LOCATE_PROTOCOL_PARAMETER_BLOCK
{
    ULONG64 Untouched;
    ULONG64 Smbase;             // IA32_SMBASE (9eh)
    ULONG64 SmmFeatureControl;  // MSR_SMM_FEATURE_CONTROL (4e0h)
    ULONG64 SmmMcaCap;          // MSR_SMM_MCA_CAP (17dh)
    ULONG64 Eptp;               // Value of EPTP VM-execution control field 7ED8h
    ULONG64 HvPatchedAddress;
};

class SmmShellCode
{
public:
    SmmShellCode (
        );

    NTSTATUS
    Install (
        const PhysicalMemory& Pm
        );

    ~SmmShellCode (
        );

private:
    static const ULONG64 k_ShellCodeEntryPoint = 0x07070707;
    static const ULONG64 k_ShellCodeAddress = 0x07070710;
    static const SIZE_T k_NopSledSize = k_ShellCodeAddress - k_ShellCodeEntryPoint;

    const SIZE_T m_FunctionSize;
    const SIZE_T m_ShellCodeSize;
    PVOID m_OriginalCode = {};
    const PhysicalMemory* m_Pm = {};
};
