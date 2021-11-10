#include "CInfo.h"
#include "utils.h"

// Global Variables - none

// Constructor & destructor

CInfo::CInfo(void) 
{
	this->serialNumber				= "1234";
	this->deviceInfo				= new ST_DEVICE_INFO_;
	this->deviceInfo->name			= "DName";
	this->deviceInfo->osName		= "OsName";
	this->deviceInfo->modelNumber	= "1234";
	this->deviceInfo->location		= "location";
	this->deviceInfo->category		= "category";
	this->timestamp					= getNowUnixTime();
	this->connectMethod				= "connectionMethod";
};

CInfo::~CInfo(void) 
{
	delete (this->deviceInfo);
};

// Static functions - none

// Getter

std::string	CInfo::getSerialNumber(void)	{ this->refreshTimeStamp(); return this->serialNumber; }
std::string	CInfo::getLastModifiedTime(void){ this->refreshTimeStamp(); return this->timestamp; }
std::string	CInfo::getConnectionInfo(void)	{ this->refreshTimeStamp(); return this->connectMethod; }
std::string	CInfo::getDeviceInfo(int _property) 
{
	this->refreshTimeStamp();

	switch (_property) {
		case D_NAME:		return this->deviceInfo->name;
		case D_OSNAME:		return this->deviceInfo->osName;
		case D_MODELNUM:	return this->deviceInfo->modelNumber;
		case D_LOCATION:	return this->deviceInfo->location;
		case D_CATEGORY:	return this->deviceInfo->category;
	}
}
ST_DEVICE_INFO_* CInfo::getDeviceInfo(void) { this->refreshTimeStamp(); return this->deviceInfo; }

// Setter

void CInfo::setName(std::string _name)				{ this->deviceInfo->name			= _name; }
void CInfo::setOsName(std::string _osName)			{ this->deviceInfo->osName			= _osName; }
void CInfo::setLocation(std::string _name)			{ this->deviceInfo->name			= _name; }
void CInfo::setCategory(std::string _category)		{ this->deviceInfo->category		= _category; }
void CInfo::setModelNumber(std::string _num)		{ this->deviceInfo->modelNumber		= _num; }
void CInfo::setSerialNumber(std::string _num)		{ this->serialNumber				= _num; }
void CInfo::setDeviceInfo(ST_DEVICE_INFO_& _info)	{ *this->deviceInfo					= _info; }

// Other functions

void CInfo::refreshTimeStamp(void) { this->timestamp = getNowUnixTime(); }