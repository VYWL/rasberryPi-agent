#include "CMonitoring.h"
#include "Function.h"

CMonitoring::CMonitoring()
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Init"));

	fd = inotify_init();

	if (fd == -1)
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %d"), TEXT("Inotify Init Error"), errno);

	terminate = false;
}
CMonitoring::~CMonitoring()
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("End"));

	(void)close(fd);
}

std::tstring CMonitoring::GetDirectoryPath(std::tstring logPath)
{
	
	std::tstring parentPath = core::ExtractDirectory(logPath);

	if (core::PathFileExistsA(parentPath.c_str()))
		return parentPath;
	else
	{
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Directory Path Not Exists"), TEXT(parentPath.c_str()));
		return "";
	}
}

std::tstring CMonitoring::GetFilename(std::tstring logPath)
{
	std::tstring fileName = core::ExtractFileName(logPath);

	if (core::PathFileExistsA(fileName.c_str()))
		return fileName;
	else
	{
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("File Not Exists"), TEXT(fileName.c_str()));
		return "";
	}
}

std::tstring CMonitoring::ColumnSplit(std::tstring s, std::tstring divid)
{
	char* c = strtok((char*)s.c_str(), divid.c_str());
	c = strtok(NULL, divid.c_str());
	return c;
}

std::tstring CMonitoring::Trim(const std::tstring& s)
{
	if (s.length() == 0)
		return s;

	std::size_t beg = s.find_first_not_of(" \a\b\f\n\r\t\v");
	std::size_t end = s.find_last_not_of(" \a\b\f\n\r\t\v");
	if (beg == std::tstring::npos)
		return "";

	return std::tstring(s, beg, end - beg + 1);
}

int CMonitoring::FindFileEndPosition(std::ifstream& fileFd) {
	if (fileFd.is_open()) {
		fileFd.seekg(0, std::ios::end);
		int size = fileFd.tellg();
		return size;
	}
	else {
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s]"), TEXT("File Open Fail"));
		return -1;
	}
}

int CMonitoring::AddMonitoringTarget(ST_MONITOR_TARGET target)
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("MonitoringTarget Add Start"), TEXT(target.logPath.c_str()));

	sleep(0);
	std::lock_guard<std::mutex> lock_guard(monitoringMutex);
	std::tstring originalPath = target.logPath;

	std::tstring directoryPath = GetDirectoryPath(originalPath);
	std::tstring fileName = GetFilename(originalPath);
	
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("GetDirectoryPath Result"), TEXT(directoryPath.c_str()));
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("GetFilename Result"), TEXT(fileName.c_str()));


	if (directoryPath == "" || fileName == "") 
	{
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Path Not Valid."), TEXT(originalPath.c_str()));
		return -1;
	}

	int wd = wdCountLists.count(directoryPath) ? wdCountLists[directoryPath] : -1;
	ST_MONITORING_EVENT* monitoringEvent = monitoringLists.count(originalPath) ? monitoringLists[originalPath] : NULL;

	if (wd != -1 && monitoringEvent == NULL)
	{
		core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Directory Path Already Being Watched."), TEXT(directoryPath.c_str()));
		wdCountLists[directoryPath]++;
	}

	if (wd == -1)
	{
		wd = inotify_add_watch(fd, directoryPath.c_str(), IN_MODIFY | IN_MOVE);
		if (wd == -1)
		{
			core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %d"), TEXT("Watching Add/Update Error Code"), errno);
			return -1;
		}
		wdCountLists.insert(std::pair<std::tstring, int>(TEXT(directoryPath), 1));
		wdKeyPathLists.insert(std::pair<int, std::tstring>(wd, TEXT(directoryPath)));
		core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Directory Path Start New Watch."), TEXT(directoryPath.c_str()));
	}

	if (monitoringEvent == NULL)
	{
		ST_MONITORING_EVENT* monitoringEvent = new ST_MONITORING_EVENT();
		monitoringEvent->processName = target.processName;
		monitoringEvent->orignalPath = originalPath;
		monitoringEvent->directoryPath = directoryPath;
		monitoringEvent->fileName = fileName;
		monitoringEvent->fd = std::ifstream(originalPath);
		monitoringEvent->wd = wd;
		monitoringEvent->size = FindFileEndPosition(monitoringEvent->fd);

		monitoringLists.insert(std::pair<std::tstring, struct ST_MONITORING_EVENT*>(TEXT(originalPath), monitoringEvent));
	}
	
	core::Log_Info(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("MonitoringTarget Add Complete"), TEXT(target.logPath.c_str()));
	return 0;
}
int CMonitoring::RemoveMonitoringTarget(ST_MONITOR_TARGET target)
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("MonitoringTarget Remove Start"), TEXT(target.logPath.c_str()));
	sleep(0);
	std::lock_guard<std::mutex> lock_guard(monitoringMutex);

	std::tstring originalPath = target.logPath;

	std::tstring directoryPath = GetDirectoryPath(originalPath);
	std::tstring fileName = GetFilename(originalPath);

	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("GetDirectoryPath Result"), TEXT(directoryPath.c_str()));
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("GetFilename Result"), TEXT(fileName.c_str()));

	if (directoryPath == "" || fileName == "")
	{
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Path Not Valid."), TEXT(originalPath.c_str()));
		return -1;
	}

	ST_MONITORING_EVENT* monitoringEvent = monitoringLists.count(originalPath) ? monitoringLists[originalPath] : NULL;

	if (monitoringEvent != NULL)
	{
		monitoringEvent->fd.close();

		if (wdCountLists[monitoringEvent->directoryPath] > 1)
		{
			core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Remove Target From The List."), TEXT(originalPath.c_str()));
			wdCountLists[monitoringEvent->directoryPath]--;
		}
		else if (wdCountLists[monitoringEvent->directoryPath] == 1)
		{
			core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Stop Directory Path Monitoring"), TEXT(monitoringEvent->directoryPath.c_str()));
			int result = inotify_rm_watch(fd, monitoringEvent->wd);
			
			if (result == -1)
			{
				core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %d"), TEXT("Watching Remove Error Code"), errno);
				return -1;
			}

			wdCountLists.erase(monitoringEvent->directoryPath);
			wdKeyPathLists.erase(monitoringEvent->wd);
		}

		free(monitoringEvent);
		monitoringLists.erase(originalPath);
	}
	else
	{
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Target Does Not Exist In The List"), TEXT(originalPath.c_str()));
		return -1;
	}

	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("MonitoringTarget Remove Complete"), TEXT(target.logPath.c_str()));
	return 0;
}

void CMonitoring::StartMonitoring()
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Working Monitoring In Thread"));

	char buffer[BUF_LEN];
	while (!terminate) {
		sleep(0);

		int length = read(fd, buffer, BUF_LEN);
		int i = 0;

		if (length < 0) {
			core::Log_Warn(TEXT("CMonitoring.cpp - [%s]"), TEXT("Monitoring Error"));
		}

		while (i < length) {
			struct inotify_event* event = (struct inotify_event*)&buffer[i];

			if (event->len) 
			{
				if (event->mask & IN_MOVE)
				{
					if (!(event->mask & IN_ISDIR))
					{
						// vi, nano editor가 저장과 동시 종료시에는 수정된 내용이 반영되지만
						// 파일을 열어놓은 상태에서 저장하고, 나중에 종료하면 연결이 끊어진다. (조치 필요)

						std::tstring directoryPath = TEXT(wdKeyPathLists[event->wd]);
						std::tstring fullPath = TEXT(directoryPath) + TEXT("/") + TEXT(event->name);

						ST_MONITORING_EVENT* monitoringEvent = monitoringLists.count(fullPath) ? monitoringLists[fullPath] : NULL;

						if (monitoringEvent != NULL) {
							core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("File Descriptor Update"), TEXT(fullPath.c_str()));
							monitoringEvent->fd.close();
							monitoringEvent->fd = std::ifstream(monitoringEvent->orignalPath);
						}
					}
				}

				if (event->mask & IN_MODIFY) 
				{
					if (!(event->mask & IN_ISDIR)) 
					{
						std::tstring directoryPath = TEXT(wdKeyPathLists[event->wd]);
						std::tstring fullPath = TEXT(directoryPath) + TEXT("/") + TEXT(event->name);
						std::tstring message;

						ST_MONITORING_EVENT* monitoringEvent = monitoringLists.count(fullPath) ? monitoringLists[fullPath] : NULL;

						if (monitoringEvent != NULL) {
							int re_size = monitoringEvent->size;
							monitoringEvent->fd.seekg(0, std::ios::end);

							int size = monitoringEvent->fd.tellg();
							message.resize(size - re_size);

							monitoringEvent->fd.seekg(re_size);
							monitoringEvent->size = size;
							monitoringEvent->fd.read(&message[0], size - re_size);
							core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s, %d -> %d"), TEXT("File Size"), TEXT(fullPath.c_str()), re_size, size);
							core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %s, %s"), TEXT("FileModify Content"), TEXT(fullPath.c_str()), TEXT(message.c_str()));

							func::CollectMonitoringLog(monitoringEvent->processName, fullPath, message);
						}
					}
				}
			}
			
			i += EVENT_SIZE + event->len;
		}
	}
}

void CMonitoring::EndMonitoring()
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Termiate Monitoring In Thread"));
	terminate = true;
}

std::vector<ST_PROCESS_INFO> CMonitoring::GetProcessLists()
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Get ProcessList Start"));

	std::tstring path = TEXT("/proc");
	std::vector<ST_PROCESS_INFO> processLists;

	int i = 0;

	DIR* dir = opendir(path.c_str());
	if (dir == NULL)
	{
		core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Directory Open Fail"));
		return processLists;
	}

	struct dirent* de = NULL;

	while ((de = readdir(dir)) != NULL)
	{
		if (strtol(de->d_name, NULL, 10) > 0) {
			ST_PROCESS_INFO pinfo;
			std::tstring next;

			std::tstring path("/proc/" + TEXT(std::string(de->d_name)));
			std::ifstream status(path + "/status");
			std::tstring buffer;

			while (buffer.find("Name:") == std::tstring::npos)
				std::getline(status, buffer);
			core::Split(buffer, ":", &next);
			pinfo.name = core::Trim(next.c_str(), " \t");

			while (buffer.find("State:") == std::tstring::npos)
				std::getline(status, buffer);
			core::Split(buffer, ":", &next);
			pinfo.state = core::Trim(next.c_str(), " \t");

			while (buffer.find("Pid:") == std::tstring::npos)
				std::getline(status, buffer);
			core::Split(buffer, ":", &next);
			pinfo.pid = strtol(core::Trim(next.c_str(), " \t").c_str(), NULL, 10);

			while (buffer.find("PPid:") == std::tstring::npos)
				std::getline(status, buffer);
			core::Split(buffer, ":", &next);
			pinfo.ppid = strtol(core::Trim(next.c_str(), " \t").c_str(), NULL, 10);

			status.close();

			std::ifstream cmdLine(path + "/cmdline");
			std::getline(cmdLine, buffer);
			pinfo.cmdline = core::Trim(buffer.c_str(), " \t").c_str();
			cmdLine.close();

			std::ifstream timeInfo(path + "/sched");

			while (buffer.find("se.exec_start") == std::tstring::npos)
				std::getline(timeInfo, buffer);
			timeInfo.close();

			core::Split(buffer, ":", &next);
			time_t curr_time = strtol(core::Trim(next.c_str(), " \t").c_str(), NULL, 10);
			pinfo.startTime = std::asctime(std::localtime(&curr_time));

			i++;
			processLists.push_back(pinfo);
		}
	}

	closedir(dir);
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %d"), TEXT("Get ProcessList End"), i);
	return processLists;
}

std::vector<ST_FD_INFO> CMonitoring::GetFdLists(std::tstring pid)
{
	core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Get ProcessFileDescriptorList Start"));

	std::tstring path = TEXT("/proc/") + TEXT(pid) + TEXT("/fd");
	std::vector<ST_FD_INFO> fdLists;

	if (!core::PathFileExistsA(path.c_str())){
		core::Log_Warn(TEXT("CMonitoring.cpp - [%s] : %s"), TEXT("Process Is Not Valid."), TEXT(path.c_str()));
		return fdLists;
	}

	int i = 0;
	DIR* dir = opendir(path.c_str());
	
	if (dir == NULL)
	{
		core::Log_Debug(TEXT("CMonitoring.cpp - [%s]"), TEXT("Directory Open Fail"));
		return fdLists;
	}

	struct dirent* de = NULL;

	while ((de = readdir(dir)) != NULL)
	{
		char buf[1024];
		ST_FD_INFO pinfo;
		std::tstring linkPath = TEXT(path) + TEXT("/") + TEXT(de->d_name);

		int length = readlink(linkPath.c_str(), buf, sizeof(buf));
		buf[length] = '\0';

		pinfo.pid = strtol(pid.c_str(), NULL, 10);
		pinfo.fdName = de->d_name;
		pinfo.realPath = buf;

		fdLists.push_back(pinfo);
		i++;
	}

	core::Log_Debug(TEXT("CMonitoring.cpp - [%s] : %d"), TEXT("Get ProcessFileDescriptorList Start"), i);
	return fdLists;
}

CMonitoring* CMonitoring::GetInstance()
{
	static CMonitoring instance;
	return &instance;
}