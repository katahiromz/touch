// touch.c in C/Win32
// License: MIT
#include <windows.h>
#include <stdio.h>

int wmain(int argc, LPWSTR *argv)
{
    HANDLE hFile;
    SYSTEMTIME st;
    FILETIME ft;

    if (argc <= 1 || 3 <= argc)
    {
        fprintf(stderr, "touch: invalid number of arguments\n");
        return 1;
    }

    hFile = CreateFileW(argv[1],
                        GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        NULL,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING,
                        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "touch: cannot open file '%s'\n", argv[1]);
        return 1;
    }

    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);

    SetFileTime(hFile, NULL, NULL, &ft);

    CloseHandle(hFile);
    return 0;
}

int main(void)
{
    int argc;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    int ret = wmain(argc, argv);
    LocalFree(argv);
    return ret;
}
