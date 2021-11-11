#include "utils.h"

std::string getNowUnixTime() 
{
    std::time_t t = std::time(0);  // t is an integer type
    std::stringstream ss;
    ss << t;
    std::string ts = ss.str();

    return ts;
}

std::vector<std::string> split(std::string input, char delimiter)
{
	std::vector<std::string> answer;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}

std::string trim(const std::string& s)
{
	if (s.length() == 0)
		return s;

	std::size_t beg = s.find_first_not_of(" \a\b\f\n\r\t\v");
	std::size_t end = s.find_last_not_of(" \a\b\f\n\r\t\v");
	if (beg == std::string::npos) // No non-spaces
		return "";

	return std::string(s, beg, end - beg + 1);
}

std::string SendToTerminal(const char* ShellCommand)
{
	std::ostringstream	ShellCommandTemp;
	FILE* SendShellCommand = popen(ShellCommand, "r");

	while (!feof(SendShellCommand) && !ferror(SendShellCommand))
	{
		char ShellCommandBuf[128];
		int ShellBytesRead = fread(ShellCommandBuf, 1, 128, SendShellCommand);
		ShellCommandTemp.write(ShellCommandBuf, ShellBytesRead);
	}

	std::string RecievedData = ShellCommandTemp.str();
	pclose(SendShellCommand);


	std::string::size_type pos = 0;
	std::string::size_type offset = 0;
	const std::string SpacePattern = "\n";
	const std::string Replace = "";

	while ((pos = RecievedData.find(SpacePattern, offset)) != std::string::npos)
	{
		RecievedData.replace(RecievedData.begin() + pos, RecievedData.begin() + pos + SpacePattern.size(), Replace);
		offset = pos + Replace.size();
	}

	return RecievedData;
}

std::string exec(const char* cmd) {
	std::array<char, 256> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	return result;
}

void SetLogger(std::string name, DWORD inputOption)
{
	std::tstring strModuleFile = core::GetFileName();
	std::tstring strModuleDir = core::ExtractDirectory(strModuleFile);
	std::tstring strModuleName = core::ExtractFileNameWithoutExt(strModuleFile);
	std::tstring strLogFile = strModuleDir + TEXT("/") + strModuleName + TEXT(".log");

	core::ST_LOG_INIT_PARAM_EX init;
	init.strLogFile = strLogFile;
	init.strID = TEXT(name);
	init.dwInputFlag = inputOption;
	init.dwOutputFlag = core::LOG_OUTPUT_FILE | core::LOG_OUTPUT_CONSOLE | core::LOG_OUTPUT_DBGWND;
	init.dwMaxFileSize = 10 * 1000 * 1000;
	init.dwMaxFileCount = 10;
	init.nLogRotation = core::LOG_ROTATION_SIZE;
	core::InitLog(init);
}

// Debug

void Debug_CInfo(CInfo* tmp) 
{

	std::cout << ":: CInfo Create Test ::" << '\n';
	std::cout << ":: serialNum = " << tmp->getSerialNumber() << '\n';

	ST_DEVICE_INFO_* tmp_dinfo = tmp->getDeviceInfo();
	std::cout << ":: deviceInfo->name = " << tmp_dinfo->name << '\n';
	std::cout << ":: deviceInfo->osName = " << tmp_dinfo->osName << '\n';
	std::cout << ":: deviceInfo->modelNumber = " << tmp_dinfo->modelNumber << '\n';
	std::cout << ":: deviceInfo->location = " << tmp_dinfo->location << '\n';
	std::cout << ":: deviceInfo->category = " << tmp_dinfo->category << '\n';
	std::cout << ":: timestamp = " << tmp->getLastModifiedTime() << '\n';
	std::cout << ":: connectionInfo = " << tmp->getConnectionInfo() << '\n';
}

// 1. API 이용 => UNIX TimeSharing 서비스 이용
void osInfoGather_1()
{
	struct utsname buf;

	if (uname(&buf) == -1)
	{
		printf("uname Error! \n");
		exit(1);
	}

	std::cout << "domainName : " << buf.domainname << '\n';
	std::cout << "machine : " << buf.machine << '\n';
	std::cout << "nodename : " << buf.nodename << '\n';
	std::cout << "release : " << buf.release << '\n';
	std::cout << "sysname : " << buf.sysname << '\n';
	std::cout << "version : " << buf.version << '\n';
}

// 2. 명령어로 조회하는 경우이다.
void osInfoGather_2()
{
	std::string temp = exec("lsb_release -a");
	std::cout << temp << '\n';
}

// 3. 설정 파일에 접근하는 경우이다
void osInfoGather_3()
{
	std::string temp = exec("cat /etc/os-release");
	std::cout << temp << '\n';

	temp = exec("cat /proc/version");
	std::cout << temp << '\n';
}

// 1. API (ifaddr) => socket 통신을 이용하기 때문에 쉽게 가능
void networkInfoGather_1()
{
	struct ifaddrs* ifaddr;
	int family, s;
	char host[NI_MAXHOST];

	// 에러 핸들링
	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	// 링크드 리스트 형식으로 되어있음. 하위 내용은 일단 출력 형식으로 구현.
	for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		family = ifa->ifa_addr->sa_family;

		/* Display interface name and family (including symbolic
		   form of the latter for the common families). */

		printf("%-8s %s (%d)\n",
			ifa->ifa_name,
			(family == AF_PACKET) ? "AF_PACKET" :
			(family == AF_INET) ? "AF_INET" :
			(family == AF_INET6) ? "AF_INET6" : "???",
			family);

		/* For an AF_INET* interface address, display the address. */

		if (family == AF_INET || family == AF_INET6) {
			s = getnameinfo(ifa->ifa_addr,
				(family == AF_INET) ? sizeof(struct sockaddr_in) :
				sizeof(struct sockaddr_in6),
				host, NI_MAXHOST,
				NULL, 0, NI_NUMERICHOST);
			if (s != 0) {
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}

			printf("\t\taddress: <%s>\n", host);

		}
		else if (family == AF_PACKET && ifa->ifa_data != NULL) {
			struct rtnl_link_stats* stats = (rtnl_link_stats*)ifa->ifa_data;

			auto s = (sockaddr_ll*)ifa->ifa_addr;

			printf("%-8s ", ifa->ifa_name);
			for (int i = 0; i < s->sll_halen; i++)
			{
				printf("%02x%c", (s->sll_addr[i]), (i + 1 != s->sll_halen) ? ':' : '\n');
			}

			// Packet => 안쓸듯
			printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
				"\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
				stats->tx_packets, stats->rx_packets,
				stats->tx_bytes, stats->rx_bytes);
		}
	}

	freeifaddrs(ifaddr);
}

struct ST_NETWORK_INTERFACE_INFO
{
	std::string if_name;
	std::string m_addr;
	std::string inet_addr;
	std::string inet6_addr;
};

// 2. Command => ip addr / 인터페이스 리스트를 받고, 정보 조회
void networkInfoGather_2()
{
	// ip addr | awk '/^[a-z0-9]/{split($2, arr, ":"); print arr[1]}' => 인터페이스 명 (공백기준 split 해야함)
	auto if_list_raw = exec("ip addr | awk '/^[a-z0-9]/{split($2, arr, \":\"); print arr[1]}'");
	auto if_list = split(if_list_raw, '\n');

	std::vector<ST_NETWORK_INTERFACE_INFO*> result;
	for (auto if_name : if_list)
	{
		// TODO :: 인터페이스명이 바뀔일은 없는가? => 어택벡터?
		std::string command;
		auto info = new ST_NETWORK_INTERFACE_INFO;

		info->if_name = if_name;

		// ip link show {여기에 인터페이스 명} | grep link/ | awk '{print $2}' => MAC
		command = "ip link show " + if_name + " | grep link/ | awk '{print $2}'";
		info->m_addr = trim(exec(command.c_str()));


		// ip addr show {여기에 인터페이스 명} | grep -w inet | awk '{print $2}' => inet (IPv4)
		command = "ip addr show " + if_name + " | grep -w inet | awk '{print $2}'";
		info->inet_addr = trim(exec(command.c_str()));


		// ip addr show {여기에 인터페이스 명} | grep -w inet6 | awk '{print $2}' => inet6 (IPv6)
		command = "ip addr show " + if_name + " | grep -w inet6 | awk '{print $2}'";
		info->inet6_addr = trim(exec(command.c_str()));

		result.push_back(info);
	}

	// for DEBUG
	std::cout << "TOTAL IF_CNT : " << result.size() << '\n';
	for (auto it : result)
	{
		std::cout << ":: INTERFACE INFO ::" << '\n';
		std::cout << "if_name :: " << it->if_name << '\n';
		std::cout << "m_addr :: " << it->m_addr << '\n';
		std::cout << "inet_addr :: " << it->inet_addr << '\n';
		std::cout << "inet6_addr :: " << it->inet6_addr << '\n';
	}
}

// 3. file 조회 => 인터페이스 목록만 조회 가능.
void networkInfoGather_3()
{
	// https://stackoverflow.com/questions/5281341/get-local-network-interface-addresses-using-only-proc/10514995#10514995
	// 구현하진 않았음
}

struct ST_SERVICE_INFO
{
	std::string serviceName;
	bool isActive;
};

// 1. service --status-all
void serviceInfoGather_1()
{
	std::string serviceList_raw = exec("service --status-all");
	std::string serviceList = std::regex_replace(serviceList_raw, std::regex(" \\[ "), "");
	serviceList = std::regex_replace(serviceList, std::regex(" \\]  "), "");
	std::vector<std::string> temp = split(serviceList, '\n');

	std::vector< ST_SERVICE_INFO* > result;
	for (auto it : temp)
	{
		auto item = new ST_SERVICE_INFO;
		char initialChar = it[0];
		
		item->serviceName = it.substr(1);
		item->isActive = false;

		if (initialChar == '+') item->isActive = true;

		result.push_back(item);
	}

	// for DEBUG
	std::cout << "TOTAL SERVICE_CNT : " << result.size() << '\n';
	for (auto it : result)
	{
		std::cout << ":: SERVICE INFO ::" << '\n';
		std::cout << "serviceName	:: " << it->serviceName << '\n';
		std::cout << "isActive	:: " << it->isActive << '\n';
	}
}


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


pid_t GetPIDbyName(const char* cchrptr_ProcessName, int intCaseSensitiveness, int intExactMatch)
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

pid_t GetPIDbyName(const char* cchrptr_ProcessName)
{
	return GetPIDbyName(cchrptr_ProcessName, CASE_INSENSITIVE, EXACT_MATCH);
}