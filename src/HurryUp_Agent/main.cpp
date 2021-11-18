#include "stdafx.h"
#include "CMessage.h"
#include "CMonitoring.h"
#include "Function.h"
#include "utils.h"
#include "CCollector.h"
#include "CTcpClient.h"

#define BUFFER_SIZE 1024

ST_ENV env;
int main(int argc, char *argv[]) {

	env.ip = argv[1];
	env.port = argv[2];
	env.loggerName = argv[3];
	env.serialNumber = argv[4];

	// :: PID TEST::
    // pid_t pid = GetPIDbyName("bash"); // If -1 = not found, if -2 = proc fs access error
    // printf("PID %d\n", pid);
    // return EXIT_SUCCESS;
	
	// :: NETINFO TEST ::
	 //std::cout << ":: Method 1 ::" << "\n";
	 //networkInfoGather_1();
	 //std::cout << ":: Method 2 ::" << "\n";
	 //networkInfoGather_2();

	// :: SERVICEINFO TEST ::
	// std::cout << ":: Method 1 ::" << "\n";
	// serviceInfoGather_1();

	// :: CCollector Initializing test ::
	// CCollector* tmp = new CCollector;
	// Debug_CDevice(tmp->getDeviceInstance());

	// :: THREAD TEST ::

	//CCollectorManager()->init();

	// :: SOCKET COMMUNICATION TEST ::
	/*ST_NEW_DEVICE_INFO device("Device1", "111-222-333", "Bluetooth, Wire, Lan", { ST_NEW_NETWORK_INFO("1","2","3","4"), ST_NEW_NETWORK_INFO("11", "22", "33", "44") });
	ST_NEW_INFO<ST_NEW_DEVICE_INFO> info("serial", "2010-10-10 11:22:33", device);

	std::tstring jsInfo;
	core::WriteJsonToString(&info, jsInfo);
	std::cout << jsInfo << std::endl;

	ST_NEW_PACKET_INFO packet(DEVICE, jsInfo);
	std::tstring jsPacket;
	core::WriteJsonToString(&packet, jsPacket);
	ClientManager()->Connect();
	ClientManager()->Send(TEXT("BOBSTART") + jsPacket + TEXT("BOBEND"));*/
	
	// :: getNetworkInfo TEST ::
	/* auto result = CCollectorManager()->getDeviceInstance()->getNetworkInfo();
	std::cout << "TOTAL IF_CNT : " << result.size() << '\n';
	for (auto it : result)
	{
		std::cout << ":: INTERFACE INFO ::" << '\n';
		std::cout << "if_name :: " << it.if_name << '\n';
		std::cout << "m_addr :: " << it.m_addr << '\n';
		std::cout << "inet_addr :: " << it.inet_addr << '\n';
		std::cout << "inet6_addr :: " << it.inet6_addr << '\n';
	}*/

	// :: getServiceList TEST ::
	/* auto result = CCollectorManager()->getDeviceInstance()->getServiceList();

	std::cout << "TOTAL SERVICE_CNT : " << result.size() << '\n';
	for (auto it : result)
	{
		std::cout << ":: SERVICE INFO ::" << '\n';
		std::cout << "serviceName	:: " << it.serviceName << '\n';
		std::cout << "isActive	:: " << it.isActive << '\n';
	}*/

	std::future<void> a = std::async(std::launch::async, &CMessage::Init, MessageManager());
	std::future<void> b = std::async(std::launch::async, &CMonitoring::StartMonitoring, MonitoringManager());
	//std::future<void> c = std::async(std::launch::async, &CMonitoring::StartMonitoring, MonitoringManager());

	/*ClientManager()->Connect();

	CCollectorManager()->startInterval();
	MessageManager()->Init();*/

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
		std::future<void> a = std::async(std::launch::async, &CMessage::Init, //MessageManager());
		std::future<void> b = std::async(std::launch::async, &CMonitoring::StartMonitoring, MonitoringManager());
	}
	catch (std::exception& e)
	{
		core::Log_Error(TEXT("main.cpp - [%s]"), TEXT(e.what()));
	}

	core::Log_Info(TEXT("main.cpp - [%s]"), TEXT("Terminate Agent Program!"));
*/