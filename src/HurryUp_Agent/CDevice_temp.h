#pragma once
#include "CInfo.h"

// modelNumber�� ��ȣ ��ʰ� ���´ٸ� �ڷ��� ����
// ���� ST_DEVICE_INFO�� ������� �Ʒ� ����ü�� ����
// metaInfo�� �� �ֱ� => 11/12 �� �ݿ�
struct ST_DEVICE_INFO_
{
	std::string name;
	std::string osName;
	std::string modelNumber;
	std::string location;
	std::string category;
	std::string connectMethod;
	uint32_t moduleCount = 0;
	// template property; => TODO :: ���ø�ȭ ���� �ʿ� (������ ����� 11�� 1���� ���丵 ����)

	ST_DEVICE_INFO_& operator= (const ST_DEVICE_INFO_& t)
	{
		this->name = t.name;
		this->osName = t.osName;
		this->location = t.location;
		this->modelNumber = t.modelNumber;
		this->category = t.category;
		this->connectMethod = t.connectMethod;
		this->moduleCount = t.moduleCount;

		return *this;
	}
};

class CDevice_ : public CInfo<ST_DEVICE_INFO_>
{
private:

	ST_DEVICE_INFO_* metaInfo;

public:

	CDevice_(void)
	{
		this->metaInfo = new ST_DEVICE_INFO_;
		this->metaInfo->name			= "DName";
		this->metaInfo->osName			= "OsName";
		this->metaInfo->modelNumber		= "1234";
		this->metaInfo->location		= "location";
		this->metaInfo->category		= "category";
		this->metaInfo->connectMethod	= "NONE";
		this->metaInfo->moduleCount		= 0;

		std::cout << ":: serialNum = " << this->serialNumber << '\n';
	}

	~CDevice_(void)
	{
		delete (this->metaInfo);
	}

	// Getter

	ST_DEVICE_INFO_* getMetaInfo(void)		{ return this->metaInfo; } // ��ü ����ü ��ȯ

	// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
	std::string getName(void)				{ return this->metaInfo->name; }
	std::string getOsName(void)				{ return this->metaInfo->osName; }
	std::string getModelNumber(void)		{ return this->metaInfo->modelNumber; }
	std::string getLocation(void)			{ return this->metaInfo->location; }
	std::string getCategory(void)			{ return this->metaInfo->category; }
	std::string	getConnectionInfo(void)		{ return this->metaInfo->connectMethod; } // ��ȯ ���� �޶��� ���ɼ� ���� (Property ������)


	// Setter

	void addModuleCount(void)				{ this->metaInfo->moduleCount++; }
	void setModuleCount(uint32_t _cnt)		{ this->metaInfo->moduleCount	= _cnt; }

	// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
	void setName(std::string _nm)			{ this->metaInfo->name			= _nm; }
	void setOsName(std::string _osNm)		{ this->metaInfo->osName		= _osNm; }
	void setModelNumber(std::string _mdNum)	{ this->metaInfo->modelNumber	= _mdNum; }
	void setLocation(std::string _loc)		{ this->metaInfo->location		= _loc; }
	void setCategory(std::string _cat)		{ this->metaInfo->category		= _cat; }
	void setMetaInfo(ST_DEVICE_INFO_& _m)	{ *this->metaInfo				= _m; }

	// Other functions

	void collectAllData(void)
	{
		this->collectNetworkInfo();
		this->collectOsInfo();
		this->collectCpuInfo();
		this->collectServiceInfo();
	}

	void collectNetworkInfo(void)
	{
		// API version => �Լ� ���� ����
		// Command version => ifconfig, ip addr ���� => ���� �Լ� ���
		// File version	 => /sys/class/net ���
	}

	void collectOsInfo(void)
	{
		// API version => <sys/utsname.h>
		// Command => lsb_release -a
		// File version => cat /etc/os-release Ȥ�� cat /proc/version
	}

	void collectCpuInfo(void)
	{
		// Command version => lscpu Ȥ�� sudo dmicode --type processor
		// File version => cat /proc/cpuinfo
	}

	void collectServiceInfo(void)
	{
		// Command version 2��
	}

};

void Debug_CDevice(CDevice_*);