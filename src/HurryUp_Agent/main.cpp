#include "stdafx.h"
#include "CMessage.h"
#include "CMonitoring.h"
#include "Function.h"
#include "utils.h"
#include "CInfo.h"


#define BUFFER_SIZE 1024

ST_ENV env;





#ifndef __cplusplus
#define _GNU_SOURCE
#endif

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#ifdef __cplusplus
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#endif


#define PROC_DIRECTORY "/proc/"
#define CASE_SENSITIVE    1
#define CASE_INSENSITIVE  0
#define EXACT_MATCH       1
#define INEXACT_MATCH     0


int IsNumeric(const char* ccharptr_CharacterList)
{
    for (; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}


int strcmp_Wrapper(const char* s1, const char* s2, int intCaseSensitive)
{
    if (intCaseSensitive)
        return !strcmp(s1, s2);
    else
        return !strcasecmp(s1, s2);
}

int strstr_Wrapper(const char* haystack, const char* needle, int intCaseSensitive)
{
    if (intCaseSensitive)
        return (int)strstr(haystack, needle);
    else
        return (int)strcasestr(haystack, needle);
}


#ifdef __cplusplus
pid_t GetPIDbyName(const char* cchrptr_ProcessName, int intCaseSensitiveness, int intExactMatch)
#else
pid_t GetPIDbyName_implements(const char* cchrptr_ProcessName, int intCaseSensitiveness, int intExactMatch)
#endif
{
    char chrarry_CommandLinePath[100];
    char chrarry_NameOfProcess[300];
    char* chrptr_StringToCompare = NULL;
    pid_t pid_ProcessIdentifier = (pid_t)-1;
    struct dirent* de_DirEntity = NULL;
    DIR* dir_proc = NULL;

    int (*CompareFunction) (const char*, const char*, int);

    if (intExactMatch)
        CompareFunction = &strcmp_Wrapper;
    else
        CompareFunction = &strstr_Wrapper;


    dir_proc = opendir(PROC_DIRECTORY);
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory");
        return (pid_t)-2;
    }

    // Loop while not NULL
    while ((de_DirEntity = readdir(dir_proc)))
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY);
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name);
                strcat(chrarry_CommandLinePath, "/cmdline");
                FILE* fd_CmdLineFile = fopen(chrarry_CommandLinePath, "rt");  // open the file for reading text
                if (fd_CmdLineFile)
                {
                    fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess); // read from /proc/<NR>/cmdline
                    fclose(fd_CmdLineFile);  // close the file prior to exiting the routine

                    if (strrchr(chrarry_NameOfProcess, '/'))
                        chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') + 1;
                    else
                        chrptr_StringToCompare = chrarry_NameOfProcess;

                    //printf("Process name: %s\n", chrarry_NameOfProcess);
                    //printf("Pure Process name: %s\n", chrptr_StringToCompare );

                    if (CompareFunction(chrptr_StringToCompare, cchrptr_ProcessName, intCaseSensitiveness))
                    {
                        pid_ProcessIdentifier = (pid_t)atoi(de_DirEntity->d_name);
                        closedir(dir_proc);
                        return pid_ProcessIdentifier;
                    }
                }
            }
        }
    }
    closedir(dir_proc);
    return pid_ProcessIdentifier;
}

#ifdef __cplusplus
pid_t GetPIDbyName(const char* cchrptr_ProcessName)
{
    return GetPIDbyName(cchrptr_ProcessName, CASE_INSENSITIVE, EXACT_MATCH);
}
#else
// C cannot overload functions - fixed
pid_t GetPIDbyName_Wrapper(const char* cchrptr_ProcessName, ...)
{
    int intTempArgument;
    int intInputArguments[2];
    // intInputArguments[0] = 0 ;
    // intInputArguments[1] = 0 ;
    memset(intInputArguments, 0, sizeof(intInputArguments));
    int intInputIndex;
    va_list argptr;

    va_start(argptr, cchrptr_ProcessName);
    for (intInputIndex = 0; (intTempArgument = va_arg(argptr, int)) != 15; ++intInputIndex)
    {
        intInputArguments[intInputIndex] = intTempArgument;
    }
    va_end(argptr);
    return GetPIDbyName_implements(cchrptr_ProcessName, intInputArguments[0], intInputArguments[1]);
}

#define GetPIDbyName(ProcessName,...) GetPIDbyName_Wrapper(ProcessName, ##__VA_ARGS__, (int) 15)

#endif


int main(int argc, char *argv[]) {
	/*
	if (argc != 4) {
		printf("syntax : ./agent.out <server ip> <server port> <logger name>\n");
		printf("sample : ./agent.out 192.168.10.1 5000 logger-test\n");
		return -1;
	}

	env.ip = argv[1];
	env.port = argv[2];
	env.loggerName = argv[3];
	*/

    pid_t pid = GetPIDbyName("bash"); // If -1 = not found, if -2 = proc fs access error
    printf("PID %d\n", pid);
    return EXIT_SUCCESS;




	/*
#ifdef DEBUG
	SetLogger(env.loggerName, core::LOG_INFO | core::LOG_WARN | core::LOG_ERROR | core::LOG_DEBUG);
	core::Log_Info(TEXT("main.cpp - [%s]"), TEXT("Program is Debug Mode"));
#else
	SetLogger(env.loggerName, core::LOG_INFO | core::LOG_WARN | core::LOG_ERROR);
	core::Log_Info(TEXT("main.cpp - [%s]"), TEXT("Program is Release Mode"));
#endif
	core::Log_Info(TEXT("main.cpp - [%s]"), TEXT("Start Agent Program!"));
	try
	{
		std::future<void> a = std::async(std::launch::async, &CMessage::Init, MessageManager());
		std::future<void> b = std::async(std::launch::async, &CMonitoring::StartMonitoring, MonitoringManager());
	}
	catch (std::exception& e)
	{
		core::Log_Error(TEXT("main.cpp - [%s]"), TEXT(e.what()));
	}

	core::Log_Info(TEXT("main.cpp - [%s]"), TEXT("Terminate Agent Program!"));
	*/
	return 0;
}










