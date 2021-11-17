#include "CDevice_temp.h"

/*

CDevice_::CDevice_(void)
{
	this->metaInfo					= new ST_DEVICE_INFO_;
	this->metaInfo->name			= "DName";
	this->metaInfo->osName			= "OsName";
	this->metaInfo->modelNumber		= "1234";
	this->metaInfo->location		= "location";
	this->metaInfo->category		= "category";
	this->metaInfo->connectMethod	= "NONE";
	this->metaInfo->moduleCount		= 0;
}

CDevice_::~CDevice_(void)
{
	delete (this->metaInfo);
}

// Getter

ST_DEVICE_INFO_* CDevice_::getMetaInfo(void)		{ return this->metaInfo; } // ��ü ����ü ��ȯ

// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
std::string CDevice_::getName(std::string)			{ return this->metaInfo->name; }
std::string CDevice_::getOsName(std::string)		{ return this->metaInfo->osName; }
std::string CDevice_::getModelNumber(std::string)	{ return this->metaInfo->modelNumber; }
std::string CDevice_::getLocation(std::string)		{ return this->metaInfo->location; }
std::string CDevice_::getCategory(std::string)		{ return this->metaInfo->category; }
std::string	CDevice_::getConnectionInfo(void)		{ return this->metaInfo->connectMethod; } // ��ȯ ���� �޶��� ���ɼ� ���� (Property ������)

// Setter

void CDevice_::addModuleCount(void)					{ this->metaInfo->moduleCount++; }
void CDevice_::setModuleCount(uint32_t _cnt)			{ this->metaInfo->moduleCount	= _cnt; }

// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
void CDevice_::setName(std::string _nm)				{ this->metaInfo->name			= _nm; }
void CDevice_::setOsName(std::string _osNm)			{ this->metaInfo->osName		= _osNm; }
void CDevice_::setModelNumber(std::string _mdNum)	{ this->metaInfo->modelNumber	= _mdNum; }
void CDevice_::setLocation(std::string _loc)			{ this->metaInfo->location		= _loc; }
void CDevice_::setCategory(std::string _cat)			{ this->metaInfo->category		= _cat; }
void CDevice_::setMetaInfo(ST_DEVICE_INFO_& _m)		{ *this->metaInfo				= _m; }

// Other functions

void CDevice_::collectAllData(void)
{
	this->collectNetworkInfo();
	this->collectOsInfo();
	this->collectCpuInfo();
	this->collectServiceInfo();
}

void CDevice_::collectNetworkInfo(void)
{
	// API version => �Լ� ���� ����
	// Command version => ifconfig, ip addr ���� => ���� �Լ� ���
	// File version	 => /sys/class/net ���
}

void CDevice_::collectOsInfo(void)
{
	// API version => <sys/utsname.h>
	// Command => lsb_release -a
	// File version => cat /etc/os-release Ȥ�� cat /proc/version
}

void CDevice_::collectCpuInfo(void)
{
	// Command version => lscpu Ȥ�� sudo dmicode --type processor
	// File version => cat /proc/cpuinfo
}

void CDevice_::collectServiceInfo(void)
{
	// Command version 2��
}

*/