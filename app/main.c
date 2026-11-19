#include <xecore/xam.h>

static char msg[] = "Hello from my own XEX\r\n";
static char p0[] = "\\Device\\Mass0\\hello.txt";
static char p1[] = "\\Device\\Mass1\\hello.txt";
static char p2[] = "\\Device\\Mass0Part1\\hello.txt";

static int write_file(char *path, char *data, uint32_t len)
{
    HANDLE h = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
                           FILE_ATTRIBUTE_NORMAL, 0);
    if (h == INVALID_HANDLE_VALUE || h == 0)
        return 0;
    uint32_t written = 0;
    bool ok = WriteFile(h, data, len, &written, 0);
    CloseHandle(h);
    return ok && written == len;
}

int _start(void)
{
    uint32_t n = sizeof(msg) - 1;
    if (write_file(p0, msg, n)) return 0;
    if (write_file(p1, msg, n)) return 0;
    write_file(p2, msg, n);
    return 0;
}
