#include "utils.h"

std::string getNowUnixTime() 
{
    std::time_t t = std::time(0);  // t is an integer type
    std::stringstream ss;
    ss << t;
    std::string ts = ss.str();

    return ts;
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
	std::array<char, 128> buffer;
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

	ST_DEVICE_INFO_ tmp_dinfo = tmp->getDeviceInfo();
	std::cout << ":: deviceInfo->name = " << tmp_dinfo.name << '\n';
	std::cout << ":: deviceInfo->osName = " << tmp_dinfo.osName << '\n';
	std::cout << ":: deviceInfo->modelNumber = " << tmp_dinfo.modelNumber << '\n';
	std::cout << ":: deviceInfo->location = " << tmp_dinfo.location << '\n';
	std::cout << ":: deviceInfo->category = " << tmp_dinfo.category << '\n';
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
	std::string temp = exec("cat /etc/os-release ");
	std::cout << temp << '\n';

	temp = exec("cat /proc/version");
	std::cout << temp << '\n';
}

// 1. API
void networkInfoGather_1()
{

}
