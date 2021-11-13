#pragma once
#include "CInfo.h"

struct ST_NETWORK_INTERFACE_INFO
{
	std::string if_name;
	std::string m_addr;
	std::string inet_addr;
	std::string inet6_addr;

	bool operator== (const ST_NETWORK_INTERFACE_INFO& t)
	{
		return this->if_name == t.if_name &&
			this->m_addr == t.m_addr &&
			this->inet_addr == t.inet_addr &&
			this->inet6_addr == t.inet6_addr;
	}
};

struct ST_OS_INFO
{
	std::string osName;
	std::string osRelease;

	ST_OS_INFO* operator= (const ST_OS_INFO* t)
	{
		this->osName = t->osName;
		this->osRelease = t->osRelease;
	}

	bool operator== (const ST_OS_INFO& t)
	{
		return this->osName == t.osName &&
			this->osRelease == t.osRelease;
	}
}; 

struct ST_SERVICE_INFO
{
	std::string serviceName;
	bool isActive;

	bool operator== (const ST_SERVICE_INFO& t)
	{
		return this->serviceName == t.serviceName &&
			this->isActive == t.isActive;
	}
};


// modelNumber는 번호 용례가 나온다면 자료형 변경
// 기존 ST_DEVICE_INFO가 사라지면 아래 구조체명 변경
// metaInfo에 더 넣기 => 11/12 더 반영
struct ST_DEVICE_INFO_
{
	std::string name;
	ST_OS_INFO	osInfo;
	std::string modelNumber;
	std::string connectMethod; // 구분자 ','
	std::vector<ST_NETWORK_INTERFACE_INFO> networkInfo;

	uint32_t moduleCount = 0;

	std::vector<ST_SERVICE_INFO> serviceList;

	// template property; => TODO :: 템플릿화 구현 필요 (전상현 멘토님 11월 1주차 멘토링 참고)

	ST_DEVICE_INFO_& operator= (const ST_DEVICE_INFO_& t)
	{
		this->name = t.name;
		this->osInfo = t.osInfo;
		this->modelNumber = t.modelNumber;
		this->connectMethod = t.connectMethod;
		this->moduleCount = t.moduleCount;

		this->networkInfo.clear();
		for (auto it : t.networkInfo)
			this->networkInfo.push_back(it);

		this->serviceList.clear();
		for (auto it : t.serviceList)
			this->serviceList.push_back(it);
		
		return *this;
	}

	bool operator== (const ST_DEVICE_INFO_& t)
	{
		return this->name == t.name &&
			this->osInfo == t.osInfo &&
			this->modelNumber == t.modelNumber &&
			this->connectMethod == t.connectMethod &&
			this->moduleCount == t.moduleCount;
	}

};

class CDevice_ : public CInfo<ST_DEVICE_INFO_>
{
private:

	ST_DEVICE_INFO_* metaInfo;

public:

	CDevice_(void)
	{
		this->metaInfo						= new ST_DEVICE_INFO_;
		this->metaInfo->name				= "DName";
		this->metaInfo->osInfo.osName		= "OsName";
		this->metaInfo->osInfo.osRelease	= "OsRelease";
		this->metaInfo->modelNumber			= "1234";
		this->metaInfo->connectMethod		= "NONE";
		this->metaInfo->moduleCount			= 0;
		this->metaInfo->networkInfo.clear();
		this->metaInfo->serviceList.clear();
	}

	~CDevice_(void)
	{
		delete (this->metaInfo);
	}

	// Getter

	ST_DEVICE_INFO_* getMetaInfo(void)		{ return this->metaInfo; } // 전체 구조체 반환

	// TODO :: 구조체 확정되면 추후 추가
	std::string getName(void)				{ return this->metaInfo->name; }
	std::string getOsName(void)				{ return this->metaInfo->osInfo.osName; }
	std::string getOsRelease(void)			{ return this->metaInfo->osInfo.osRelease; }
	std::string getModelNumber(void)		{ return this->metaInfo->modelNumber; }
	std::string	getConnectionInfo(void)		{ return this->metaInfo->connectMethod; } // 반환 형식 달라질 가능성 존재 (Property 때문에)
	std::vector<ST_NETWORK_INTERFACE_INFO>
				getNetworkInfo(void)		{ return this->metaInfo->networkInfo; }
	std::vector<ST_SERVICE_INFO>
				getServiceList(void)		{ return this->metaInfo->serviceList; }

	// Setter

	void addModuleCount(void)				{ this->metaInfo->moduleCount++; }
	void setModuleCount(uint32_t _cnt)		{ this->metaInfo->moduleCount	= _cnt; }

	// TODO :: 구조체 확정되면 추후 추가
	void setName(std::string _nm)			{ this->metaInfo->name				= _nm; }
	void setOsName(std::string _osNm)		{ this->metaInfo->osInfo.osName		= _osNm; }
	void setReleaseName(std::string _osRls)		{ this->metaInfo->osInfo.osRelease	= _osRls; }
	void setModelNumber(std::string _mdNum)	{ this->metaInfo->modelNumber		= _mdNum; }
	void setMetaInfo(ST_DEVICE_INFO_& _m)	{ *this->metaInfo					= _m; }

	void addNetworkInfo(ST_NETWORK_INTERFACE_INFO& _nInfo)
	{
		// 예외 => 이미 존재하는 Network info인 경우
		for (auto it : this->metaInfo->networkInfo)
			if (it == _nInfo) return;

		this->metaInfo->networkInfo.push_back(_nInfo);
	}


	void addServiceInfo(ST_SERVICE_INFO& _sInfo)
	{
		// 예외 => 이미 존재하는 Network info인 경우
		for (auto it : this->metaInfo->serviceList)
			if (it == _sInfo) return;

		this->metaInfo->serviceList.push_back(_sInfo);
	}

	// Other functions

	void collectAllData(void)
	{
		this->collectNameInfo();
		this->collectModelName();
		this->collectSerialNumber();
		this->collectNetworkInfo();
		this->collectOsInfo();
		this->collectCpuInfo();
		this->collectServiceInfo();
	}

	void collectNameInfo(void)
	{
		std::string deviceName = exec("hostname");

		this->setName(deviceName);
	}

	void collectModelName(void)
	{
		std::string modelName_raw = exec("cat /proc/cpuinfo | grep Model");
		std::string modelName = modelName_raw != "" ? trim(split(modelName_raw, ':')[1]) : "";


		this->setModelNumber(modelName);
	}

	void collectSerialNumber(void)
	{
		std::string serialNum_raw = exec("cat /proc/cpuinfo | grep Serial");
		std::string serialNum = serialNum_raw != "" ? trim(split(serialNum_raw, ':')[1]) : "";

		this->setSerialNumber(serialNum);
	}

	void collectNetworkInfo(void)
	{
		// API version => 함수 새로 구현
		// Command version => ifconfig, ip addr 관련 => 기존 함수 사용
		// File version	 => /sys/class/net 사용

		std::vector < ST_NETWORK_INTERFACE_INFO > result;

		// ifaddr 사용
		struct ifaddrs* ifaddr;
		int family, s;
		char host[NI_MAXHOST];

		// 에러 핸들링
		if (getifaddrs(&ifaddr) == -1) {
			perror("getifaddrs");
			exit(EXIT_FAILURE);
		}

		std::map<std::string, ST_NETWORK_INTERFACE_INFO*> checker;
		// 링크드 리스트 형식으로 되어있음. 하위 내용은 일단 출력 형식으로 구현.
		for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
			if (ifa->ifa_addr == NULL)
				continue;

			std::string temp = ifa->ifa_name;

			if (checker.find(temp) == checker.end())
			{
				auto nInfo = new ST_NETWORK_INTERFACE_INFO;
				nInfo->if_name = temp;

				checker[temp] = nInfo;
			}
			
			auto nowNetInfo = checker[temp];


			family = ifa->ifa_addr->sa_family;


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

				std::string hostTemp = host;
				if (family == AF_INET)	nowNetInfo->inet_addr  = hostTemp;
				if (family == AF_INET6) nowNetInfo->inet6_addr = hostTemp;

				//printf("\t\taddress: <%s>\n", host);

			}
			else if (family == AF_PACKET && ifa->ifa_data != NULL) {
				struct rtnl_link_stats* stats = (rtnl_link_stats*)ifa->ifa_data;

				auto s = (sockaddr_ll*)ifa->ifa_addr;
				char mac[] = "00:13:a9:1f:b0:88";

				auto a = s->sll_addr;

				sscanf(mac, "%02x:%02x:%02x:%02x:%02x:%02x", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);

				std::string macAddr = mac;
				nowNetInfo->m_addr = macAddr;

			}
		}

		freeifaddrs(ifaddr);

		for (auto it : checker)
		{
			ST_NETWORK_INTERFACE_INFO temp;
			temp.if_name	= it.second->if_name;
			temp.m_addr		= it.second->m_addr;
			temp.inet_addr	= it.second->inet_addr;
			temp.inet6_addr	= it.second->inet6_addr;

			this->metaInfo->networkInfo.push_back(temp);
		}

	}

	void collectOsInfo(void)
	{
		// API version => <sys/utsname.h>
		// Command => lsb_release -a
		// File version => cat /etc/os-release 혹은 cat /proc/version

		// osName, release가 포함됨.

		ST_OS_INFO _osInfo;

		struct utsname buf;

		if (uname(&buf) == -1)
		{
			printf("uname Error! \n");
			exit(1);
		}

		std::string os_raw = exec("lsb_release -a | grep Description");
		std::string os = trim(split(os_raw, ':')[1]);
		std::string release = buf.release;

		_osInfo.osName		= os;
		_osInfo.osRelease	= release;

		this->metaInfo->osInfo = _osInfo;

	}

	void collectCpuInfo(void)
	{
		// Command version => lscpu 혹은 sudo dmidecode --type processor
		// File version => cat /proc/cpuinfo

		// arch, core 수, vendor ID
	}

	void collectServiceInfo(void)
	{
		// serviceName, isActive 반환

		std::string serviceList_raw = exec("service --status-all");
		std::string serviceList = std::regex_replace(serviceList_raw, std::regex(" \\[ "), "");
		serviceList = std::regex_replace(serviceList, std::regex(" \\]  "), "");
		std::vector<std::string> temp = split(serviceList, '\n');

		for (auto it : temp)
		{
			ST_SERVICE_INFO _sInfo;
			char initialChar = it[0];

			_sInfo.serviceName = it.substr(1);
			_sInfo.isActive = false;

			if (initialChar == '+') _sInfo.isActive = true;

			this->metaInfo->serviceList.push_back(_sInfo);
		}
	}

};

void Debug_CDevice(CDevice_*);