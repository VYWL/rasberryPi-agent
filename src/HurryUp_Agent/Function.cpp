#include "Function.h"
#include "CMessage.h"
#include "CMonitoring.h"
#include "CDevice.h"
#include "CCollector.h"
#include "utils.h"

void func::GetProcessList()
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Get Process List"));
	
	ST_NEW_VECTOR_DATABASE<ST_NEW_PROCESS_INFO> processList;
	processList.metaInfo = MonitoringManager()->GetProcessLists();
	processList.key = TEXT("MetaInfo");

	std::tstring jsProcessList;
	core::WriteJsonToString(&processList, jsProcessList);
	MessageManager()->PushSendMessage(RESPONSE, PROCESS_LIST, jsProcessList);

	for (auto pInfo : processList.metaInfo) {
		GetFileDescriptorList(std::to_string(pInfo.pid));
		core::Log_Debug(TEXT("========================================"));
		core::Log_Debug(TEXT("Function.cpp - [pid] : %d"), pInfo.pid);
		core::Log_Debug(TEXT("Function.cpp - [ppid] : %d"), pInfo.ppid);
		core::Log_Debug(TEXT("Function.cpp - [name] : %s"), TEXT(pInfo.name.c_str()));
		core::Log_Debug(TEXT("Function.cpp - [state] : %s"), TEXT(pInfo.state.c_str()));
		core::Log_Debug(TEXT("Function.cpp - [cmdline] : %s"), TEXT(pInfo.cmdline.c_str()));
		core::Log_Debug(TEXT("Function.cpp - [sTime] : %s"), TEXT(pInfo.startTime.c_str()));
		core::Log_Debug(TEXT("========================================"));
	}
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Get Process List Complete"));
}

void func::GetFileDescriptorList(std::tstring pid)
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Get Process File Descriptor List"));
	
	ST_NEW_VECTOR_DATABASE<ST_NEW_FD_INFO> fdList;

	/*fdList.metaInfo.pid = strtol(pid.c_str(), NULL, 10);*/
	fdList.metaInfo = MonitoringManager()->GetFdLists(pid);

	std::tstring jsFdList;
	core::WriteJsonToString(&fdList, jsFdList);
	MessageManager()->PushSendMessage(RESPONSE, FD_LIST, jsFdList);

	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Get Process File Descriptor List Complete"));
#ifdef DEBUG
	for (auto fInfo : fdList.fdLists) {
		core::Log_Debug(TEXT("========================================"));
		core::Log_Debug(TEXT("Function.cpp - [pid] : %d"), fInfo.pid);
		core::Log_Debug(TEXT("Function.cpp - [fdName] : %s"), TEXT(fInfo.fdName.c_str()));
		core::Log_Debug(TEXT("Function.cpp - [realPath] : %s"), TEXT(fInfo.realPath.c_str()));
		core::Log_Debug(TEXT("========================================"));
	}
#endif
}

void func::StartMonitoring(std::tstring data)
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Monitoring Target Added"));

	ST_NEW_MONITOR_TARGET monitorTarget;
	core::ReadJsonFromString(&monitorTarget, data);

	core::Log_Debug(TEXT("Function.cpp - [%s] : %s"), TEXT("Monitoring Add Target"), TEXT(monitorTarget.logPath.c_str()));
	int result = MonitoringManager()->AddMonitoringTarget(monitorTarget);

	ST_NEW_MONITOR_RESULT monitorResult;

	monitorResult.processName = monitorTarget.processName;
	monitorResult.logPath = monitorTarget.logPath;
	monitorResult.result = result == 0 ? true : false;

	std::tstring jsMessage;
	core::WriteJsonToString(&monitorResult, jsMessage);

	MessageManager()->PushSendMessage(RESPONSE, MONITORING_RESULT, jsMessage);
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Monitoring Target Added Complete"));
}

void func::StopMonitoring(std::tstring data)
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Monitoring Target Remove"));

	ST_NEW_MONITOR_TARGET monitorTarget;
	core::ReadJsonFromString(&monitorTarget, data);

	core::Log_Debug(TEXT("Function.cpp - [%s] : %s"), TEXT("Monitoring Remove Target"), TEXT(monitorTarget.logPath.c_str()));
	int result = MonitoringManager()->RemoveMonitoringTarget(monitorTarget);

	ST_NEW_MONITOR_RESULT monitorResult;

	monitorResult.processName = monitorTarget.processName;
	monitorResult.logPath = monitorTarget.logPath;
	monitorResult.result = result == 0 ? false : true;

	std::tstring jsMessage;
	core::WriteJsonToString(&monitorResult, jsMessage);

	MessageManager()->PushSendMessage(RESPONSE, MONITORING_RESULT, jsMessage);

	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Monitoring Target Remove Complete"));
}

void func::CollectMonitoringLog(std::tstring processName, std::tstring path, std::tstring data)
{
	core::Log_Info(TEXT("Function.cpp - [%s] : %s"), TEXT("Request Monitoring Info"), TEXT(path.c_str()));

	ST_NEW_MONITOR_INFO monitorInfo;

	monitorInfo.processName = processName;
	monitorInfo.logPath = path;
	monitorInfo.changeData = data;

	std::tstring jsMonitorInfo;
	core::WriteJsonToString(&monitorInfo, jsMonitorInfo);

	MessageManager()->PushSendMessage(RESPONSE, MONITORING_LOG, jsMonitorInfo);
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Request Monitoring Info Complete"));
}

void func::GetDeviceInfo()
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Device Info"));

	// 보낼 데이터를 수집하고, 메시지를 만든다.
	CCollectorManager()->getDeviceInstance()->collectAllData();
	ST_NEW_DEVICE_INFO sendData = *(CCollectorManager()->getDeviceInstance()->getMetaInfo());

	ST_NEW_INFO<ST_NEW_DEVICE_INFO> deviceInfo;

	deviceInfo.serialNumber = "SERIALNUMBER";
	deviceInfo.timestamp = getNowUnixTime();
	deviceInfo.metaInfo = sendData;

	std::tstring jsDeviceInfo;
	core::WriteJsonToString(&deviceInfo, jsDeviceInfo);
	
	MessageManager()->PushSendMessage(RESPONSE, DEVICE, jsDeviceInfo);

	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Device Info Complete"));
}

void func::GetModuleInfo()
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Module Info"));
	ST_MODULE_INFO moduleInfo;

	CDevice* device = new CDevice();
	moduleInfo.deviceSerialNumber = device->getDeviceSerialNum();
	moduleInfo.deviceMac = device->getDeviceMacAddr();
	moduleInfo.name = "test";
	moduleInfo.modelNumber = "MD-1234";
	moduleInfo.serialNumber = "SN-1234-1234";
	moduleInfo.mac = "11:22:33:44:55:66";

	free(device);
	std::tstring jsModuleInfo;
	core::WriteJsonToString(&moduleInfo, jsModuleInfo);

	//MessageManager()->PushSendMessage(RESPONSE, MODULE_INFO, jsModuleInfo);
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Response Module Info Complete"));
}

void func::ActivateCheck(std::string data)
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Request Policy Check"));
	ST_CHECK_INFO checkInfo;

	core::ReadJsonFromString(&checkInfo, data);

	ST_MESSAGE message;

	/*message.opcode = CHECK_ACTIVATE;
	message.status = true;
	message.data = data;*/

	std::tstring jsMessage;
	core::WriteJsonToString(&message, jsMessage);

	//MessageManager()->PushSendMessage(RESPONSE, MESSAGE, jsMessage);
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Request Policy Check Complete"));
}
void func::GetCheckStatus()
{
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Request Checklist Status"));

	ST_CHECK_RESULT checkResult;

	checkResult.logID = 1;
	checkResult.result = false;
	checkResult.step = 1;
	checkResult.time = "2021-12-12";

	std::tstring jsCheckResult;
	core::WriteJsonToString(&checkResult, jsCheckResult);

	//MessageManager()->PushSendMessage(RESPONSE, CHECK_STATE, jsCheckResult);
	core::Log_Info(TEXT("Function.cpp - [%s]"), TEXT("Request Checklist Status Complete"));

}

void func::ChangeInterval(std::string data)
{
	// 데이터 변환

	ST_INTERVAL_INFO newData;

	core::ReadJsonFromString(&newData, data);

	// 적용

	CCollectorManager()->interval = newData.interval;
	CCollectorManager()->cancelIntervalBoolean.store(false);

	// 알림

	ST_MESSAGE message;

	message.opcode = CHANGE_INTERVAL;
	message.status = true;
	message.data = data;

	std::tstring jsMessage;
	core::WriteJsonToString(&message, jsMessage);

	MessageManager()->PushSendMessage(RESPONSE, DEVICE, jsMessage);
}