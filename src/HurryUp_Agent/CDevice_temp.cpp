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
	// API version => �Լ� ���� ����
	// Command version => ifconfig, ip addr ���� => ���� �Լ� ���
	// File version	 => /sys/class/net ���
}

void		CDevice::collectOsInfo(void)
{
	// API version => <sys/utsname.h>
	// Command => lsb_release -a
	// File version => cat /etc/os-release Ȥ�� cat /proc/version
}


void		CDevice::collectCpuInfo(void)
{
	// Command version => lscpu Ȥ�� sudo dmicode --type processor
	// File version => cat /proc/cpuinfo
}

void		CDevice::collectServiceInfo(void)
{
	// Command version 2��
}