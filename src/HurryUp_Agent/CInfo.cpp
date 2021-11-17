/*
#include "CInfo.h"
#include "utils.h"

// Constructor
template <typename ST_INFO>
CInfo<ST_INFO>::CInfo(void)
{
	this->serialNumber	= "0000";
	this->metaInfo		= new ST_INFO;
	this->timestamp		= getNowUnixTime();
}

template <typename ST_INFO>
CInfo<ST_INFO>::~CInfo(void)
{
	delete (this->metaInfo);
}

// Getter

template <typename ST_INFO>
std::string	CInfo<ST_INFO>::getLastModifiedTime(void)	{ return this->timestamp; }

template <typename ST_INFO>
std::string	CInfo<ST_INFO>::getSerialNumber(void)		{ return this->serialNumber; }

template <typename ST_INFO>
ST_INFO* CInfo<ST_INFO>::getMetaInfo(void)				{ return this->metaInfo; }

// Setter

template <typename ST_INFO>
void CInfo<ST_INFO>::setSerialNumber(std::string _num)	{ this->refreshTimeStamp(); this->serialNumber = _num; }

template <typename ST_INFO>
void CInfo<ST_INFO>::setMetaInfo(ST_INFO& _info)		{ this->refreshTimeStamp(); *this->deviceInfo = _info; }

// Other Functions

template <typename ST_INFO>
void CInfo<ST_INFO>::refreshTimeStamp(void)				{ this->timestamp = getNowUnixTime(); }
*/