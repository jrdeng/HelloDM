#include "widget.h"
#include <QApplication>

#include <Windows.h>

static void raisePrivilege()
{
    // to read memory of some processes, we need this
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) {
        if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
            AdjustTokenPrivileges(hToken, FALSE, &tp, NULL, NULL, 0);
        }
    }
    if(hToken) {
        CloseHandle(hToken);
    }
}

int main(int argc, char *argv[])
{
    raisePrivilege();

    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
