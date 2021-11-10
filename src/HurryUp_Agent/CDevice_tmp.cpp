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
	// API version
}

void		CDevice::collectOsInfo(void)
{

}


void		CDevice::collectCpuInfo(void)
{

}

void		CDevice::collectServiceInfo(void)
{

}