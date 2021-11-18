#include "CMessage.h"
#include "CTcpClient.h"
#include "Function.h"

CMessage::CMessage()
{
}

CMessage::~CMessage()
{  
	ClientManager()->Disconnet();
}

void CMessage::Init() 
{
	core::Log_Debug(TEXT("CMessage.cpp - [%s]"), TEXT("Init"));

	ClientManager()->Connect();

	std::future<void> a = std::async(std::launch::async, &CMessage::MatchReceiveMessage, this);
	std::future<void> b = std::async(std::launch::async, &CMessage::ReceiveMessage, this);
	std::future<void> c = std::async(std::launch::async, &CMessage::SendMessage, this);
}

void CMessage::SendMessage()
{
	core::Log_Debug(TEXT("CMessage.cpp - [%s]"), TEXT("Working SendMessage In Thread"));
	ST_NEW_PACKET_INFO* stPacketSend;

	while (1) {
		sleep(0);
		{
			std::lock_guard<std::mutex> lock_guard(sendMessageMutex);

			if (sendMessage.empty())
				continue;

			stPacketSend = sendMessage.front();
			sendMessage.pop();
		}

		std::tstring jsPacketSend;
		core::WriteJsonToString(stPacketSend, jsPacketSend);
		ClientManager()->Send(TEXT("BOBSTART") + jsPacketSend + TEXT("BOBEND"));
		free(stPacketSend);
		core::Log_Debug(TEXT("CMessage.cpp - [%s] : %s"), TEXT("Send Message"), TEXT(jsPacketSend.c_str()));
	}
}

void CMessage::ReceiveMessage()
{
	core::Log_Debug(TEXT("CMessage.cpp - [%s]"), TEXT("Working ReceiveMessage In Thread"));
	while(1){
		sleep(0);
		ClientManager()->Recv();
	}
}

void CMessage::PushSendMessage(PacketType type, OPCODE opcode, std::tstring message)
{
	sleep(0);
	std::lock_guard<std::mutex> lock_guard(sendMessageMutex);
	ST_NEW_PACKET_INFO* stPacketSend = new ST_NEW_PACKET_INFO(opcode, message);
	sendMessage.push(stPacketSend);
}

void CMessage::PushReceiveMessage(ST_NEW_PACKET_INFO* stPacketInfo)
{
	sleep(0);
	std::lock_guard<std::mutex> lock_guard(receiveMessageMutex);
	receiveMessage.push(stPacketInfo);
}

void CMessage::MatchReceiveMessage()
{
	core::Log_Debug(TEXT("CMessage.cpp : %s"), TEXT("Working MatchReceiveMessage In Thread"));
	std::future<void> result;
	ST_NEW_PACKET_INFO* stPacketRevc;
	while(1)
	{
		sleep(0);

		{
			std::lock_guard<std::mutex> lock_guard(receiveMessageMutex);

			if (receiveMessage.empty())
				continue;

			stPacketRevc = receiveMessage.front();
			receiveMessage.pop();
		}

		switch (stPacketRevc->opcode) {
		case PROCESS_LIST:
			result = std::async(std::launch::async, func::GetProcessList);
			break;
		case FD_LIST:
			result = std::async(std::launch::async, func::GetFileDescriptorList, stPacketRevc->data);
			break;
		case MONITORING_ACTIVATE:
			result = std::async(std::launch::async, func::StartMonitoring, stPacketRevc->data);
			break;
		case MONITORING_INACTIVATE:
			result = std::async(std::launch::async, func::StopMonitoring, stPacketRevc->data);
			break;
		case DEVICE:
			result = std::async(std::launch::async, func::GetDeviceInfo);
			break;
		/*case MODULE_INFO:
			result = std::async(std::launch::async, func::GetModuleInfo);
			break;*/
		/*case CHECK_ACTIVATE:
			result = std::async(std::launch::async, func::ActivateCheck, stPacketRevc->data);
			break;*/
		case CHANGE_INTERVAL:
			result = std::async(std::launch::async, func::ChangeInterval, stPacketRevc->data);
		default:
			core::Log_Error(TEXT("CMessage.cpp - [%s] : %s "), TEXT("Packet Type Error"), TEXT(stPacketRevc->data.c_str()));
			break;
		}
	}
}

CMessage* CMessage::GetInstance()
{
	static CMessage instance;
	return &instance;
}