#include <Windows.h>
#include <fstream>
#include <Psapi.h>

DWORD ScanPattern(const char* szPattern, const char* szMask)
{
    // MODULEINFO: load address, size, and entry point.
    MODULEINFO mInfo;

    // Assigning mInfo the module information of the process.
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &mInfo, sizeof(MODULEINFO));

    // dwBase holds the address of the module.
    DWORD dwBase = (DWORD)mInfo.lpBaseOfDll;

    // dwSize holds the linear space that the module occupies.
    DWORD dwSize = (DWORD)mInfo.SizeOfImage;

    // dwPatternLength holds the length of szPattern string.
    DWORD dwPatternLength = strlen(szPattern);

    for (DWORD i = 0; i < dwSize - dwPatternLength; i++)
    {
        bool bFound = true;

        // Searching for the address.
        for (DWORD j = 0; j < dwPatternLength; j++)
        {
            bFound &= szMask[j] == '?' || szPattern[j] == *(char*)(dwBase + i + j);
        }

        // Returning the address if its found.
        if (bFound) {
            return dwBase + i;
        }
    }

    // Returning NULL if the address is not found.
    return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    // Checking if the injection was successfull.
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Getting the first address.
        DWORD address_one = ScanPattern((char*)"\x83\xC4\x08\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00", (char*)"xxxx????x????") + 0x3;
        // Getting the second address.
        DWORD address_two = ScanPattern((char*)"\x83\xC4\x08\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00", (char*)"xxxx????x????") + 0x8;

        // Creating the file entry.
        std::ofstream myfile;

        // Creating/Opening the addr.txt file.
        myfile.open("addr.txt");

        // Writing the address_one and address_two inside the add.txt file.
        myfile << "address_one: " << "0x0" << std::hex << address_one << "\n";
        myfile << "address_two: " << "0x0" << std::hex << address_two << "\n";

        // Closing the file after use.
        myfile.close();
    }

    return true;
}