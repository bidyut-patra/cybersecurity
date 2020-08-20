// injector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "injector_helper.h"

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		char *procId = (char *)argv[1];
		char *dllPath = (char *)argv[2];

		if (isNumber(procId) == false)
		{
			std::cout << "Target process ID '" << procId << "' is not a number" << std::endl << std::endl;
			help();
		}

		if (fileExists(dllPath) == false)
		{
			std::cout << "The specified file '" << dllPath << "' does not exist" << std::endl << std::endl;
			help();
		}

		if (hasExtension(dllPath, "dll") == false)
		{
			std::cout << "The specified file '" << dllPath << "' is not a DLL" << std::endl << std::endl;
			help();
		}

		DWORD dwProcId = convertFrom(procId);
		injectDll(dwProcId, dllPath);
	}
	else
	{
		help();
	}
}

