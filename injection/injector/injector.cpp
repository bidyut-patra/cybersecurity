#include "stdafx.h"

void help()
{
    std::cout << "************************ HELP *************************" << std::endl;
    std::cout << "Specify valid target process ID and DLL Path to inject." << std::endl;
    std::cout << "process_injector.exe <procId> <dllPath>" << std::endl;
    std::cout << "*******************************************************" << std::endl;    
    exit(-1);
}

/*
 * Injects the dll into the target process
 * 
 * procId: a valid target process ID
 * dllPath: A valid dll path
 */
void injectDll(DWORD procId, LPCSTR dllPath) 
{
    // Open a handle to the target process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);

    if (hProcess == NULL) 
    {
        std::cout << "The specified process ID " << procId << " is not valid" << std::endl;
    }
    else
    {
        // Allocate memory for the dllpath in the target process
        // Length of the path string + null terminator
        LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

        // Write the path to the address of the memory allocated above
        WriteProcessMemory(hProcess, pDllPath, (LPVOID)dllPath, strlen(dllPath) + 1, 0);

        // Create a remote thread in the target process which calls the LoadLibraryA to load the malicious dll
        HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0, 
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), 
        "LoadLibraryA"), pDllPath, 0, 0);

        // Wait for execution of our loader thread to finish
        WaitForSingleObject(hLoadThread, INFINITE);

        std::cout << "DLL path allocated at: " << pDllPath << std::endl;
        std::cin.get();

        // Free the memory allocated for our dll path
        VirtualFreeEx(hProcess, pDllPath, strlen(dllPath) + 1, MEM_RELEASE);
    }
}

bool isNumber(char *str)
{
    bool isStrANumber = true;
    for (int i = 0; (i < strlen(str)) && isStrANumber; i++)
    {
        if (isdigit(str[i]) == false) isStrANumber = false;
    }
    return isStrANumber;
}

DWORD convertFrom(char *str)
{
    DWORD number = 0;
    bool isStrANumber = true;
    DWORD multiplier = 10;
    for (int i = 0; (i < strlen(str)) && isStrANumber; i++)
    {
        if (isdigit(str[i]))
        {
            unsigned int digit = (unsigned int)str[i] - 48;
            number = multiplier * number + digit;
        }
        else
        {
            isStrANumber = false;
        }
    }
    return number;
}

bool fileExists(const char *filePath)
{
    bool validFilePath = true;
    FILE *filePtr = fopen(filePath, "r");    
    if (filePtr == NULL) 
    {
        validFilePath = false;
    }
    else 
    {
        fclose(filePtr);
        validFilePath = true;
    }
    return validFilePath;
}

bool hasExtension(const char *filePath, const char *extn)
{
    return endsWith(filePath, extn, true);
}

bool endsWith(const char *str1, const char *str2, bool caseInsensitive) 
{
    size_t str1_length = strlen(str1);
    size_t str2_length = strlen(str2);

    if (str1_length >= str2_length) 
    {
        bool str1EndsWithStr2 = true;
        for (int i = str1_length - 1, j = str2_length - 1; (i >= 0) && (j >= 0) && str1EndsWithStr2; i--, j--) 
        {
            str1EndsWithStr2 = compChars(str1[i], str2[j], caseInsensitive);        
        }
        return str1EndsWithStr2;
    }
    else 
    {
        return false;
    }
}

bool compChars(const char c1, const char c2, bool caseInsensitive)
{
    bool charsEqual = false;
    bool isAlphabet_c1 = isAlphabet(c1);
    bool isAlphabet_c2 = isAlphabet(c2);
    if (isAlphabet_c1 && isAlphabet_c2) 
    {
        if (caseInsensitive) 
        {
            int diff = abs(c1 - c2);
            return diff == 0 ? true : (diff == 32) ? true : false;            
        }
        else
        {
            return c1 == c2;
        }
    }
    else
    {
        return c1 == c2;
    }
}

bool isAlphabet(const char c) 
{
    int character = (int)c;
    return isCapitalLetter(character) || isSmallLetter(character);
}

bool isCapitalLetter(int character) 
{
    return ((character >= 65) && (character <= 90));
}

bool isSmallLetter(int character) 
{
    return ((character >= 97) && (character <= 122));
}