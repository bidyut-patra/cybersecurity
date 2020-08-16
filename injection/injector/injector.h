#ifndef INJECTOR_H
#define INJECTOR_H

void help();
void injectDll(DWORD procId, LPCSTR dllPath);
bool isNumber(char *str);
DWORD convertFrom(char *str);
bool fileExists(const char *filePath);
bool hasExtension(const char *filePath, const char *extn);
bool endsWith(const char *str1, const char *str2, bool caseInsensitive);
bool compChars(const char c1, const char c2, bool caseInsensitive);
bool isAlphabet(const char c);
bool isCapitalLetter(int ascii);
bool isSmallLetter(int ascii);

#endif