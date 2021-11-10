#include "stdafx.h"
#include "CMessage.h"
#include "CMonitoring.h"
#include "Function.h"
#include "utils.h"
#include "CInfo.h"


#define BUFFER_SIZE 1024

ST_ENV env;

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

	CInfo* tmp = new CInfo;

	Debug_CInfo(tmp);

	delete tmp;

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