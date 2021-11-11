#include "CDevice_temp.h"

// Global Variables

// Constructor & destructor

CDevice::CDevice	(void) {};
CDevice::~CDevice	(void) {};

// Getter

uint32_t	CDevice::getModuleCount(void)			{ return this->moduleCount; }

// Setter

void		CDevice::addModuleCount(void)			{ this->moduleCount++; }
void		CDevice::setModuleCount(uint32_t _cnt)	{ this->moduleCount += _cnt; }

// Other functions

void		CDevice::collectAllData(void)
{
	this->collectNetworkInfo();
	this->collectOsInfo();
	this->collectCpuInfo();
	this->collectServiceInfo();
}

void		CDevice::collectNetworkInfo(void)
{
	// API version => 함수 새로 구현
	// Command version => ifconfig, ip addr 관련 => 기존 함수 사용
	// File version	 => /sys/class/net 사용
}

void		CDevice::collectOsInfo(void)
{
	// API version => <sys/utsname.h>
	// Command => lsb_release -a
	// File version => cat /etc/os-release 혹은 cat /proc/version
}


void		CDevice::collectCpuInfo(void)
{
	// Command version => lscpu 혹은 sudo dmicode --type processor
	// File version => cat /proc/cpuinfo
}

void		CDevice::collectServiceInfo(void)
{
	// Command version 2개
}