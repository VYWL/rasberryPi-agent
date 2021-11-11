#include "stdafx.h"
#include "CMessage.h"
#include "CMonitoring.h"
#include "Function.h"
#include "utils.h"
#include "CInfo.h"


#define BUFFER_SIZE 1024

ST_ENV env;
int main(int argc, char *argv[]) {

	// :: PID TEST::
    // pid_t pid = GetPIDbyName("bash"); // If -1 = not found, if -2 = proc fs access error
    // printf("PID %d\n", pid);
    // return EXIT_SUCCESS;

	// :: NETINFO TEST ::
	// std::cout << ":: Method 1 ::" << "\n";
	// networkInfoGather_1();
	// std::cout << ":: Method 2 ::" << "\n";
	// networkInfoGather_2();

	// :: SERVICEINFO TEST ::
	// std::cout << ":: Method 1 ::" << "\n";
	// serviceInfoGather_1();



	return 0;
}





/* LEGACY Code

	
	if (argc != 4) {
		printf("syntax : ./agent.out <server ip> <server port> <logger name>\n");
		printf("sample : ./agent.out 192.168.10.1 5000 logger-test\n");
		return -1;
	}

	env.ip = argv[1];
	env.port = argv[2];
	env.loggerName = argv[3];
	


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