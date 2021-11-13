#pragma once
#include "utils.h"

enum propertyIdx 
{
	D_NAME,
	D_OSNAME,
	D_MODELNUM,
	D_LOCATION,
	D_CATEGORY,
};


template <typename ST_INFO>
class CInfo
{
private:

	ST_INFO* metaInfo;

protected:

	std::string serialNumber;
	std::string timestamp;

public:

	// Constructor
	CInfo	(void)
	{
		this->serialNumber = "0000";
		this->metaInfo = new ST_INFO;
		this->timestamp = getNowUnixTime();
	}  

	~CInfo	(void)
	{
		delete (this->metaInfo);
	}

	// Getter

	std::string	getLastModifiedTime(void)	{ return this->timestamp; }
	std::string	getSerialNumber(void)		{ return this->serialNumber; }
	ST_INFO*	getMetaInfo(void)			{ return this->metaInfo; }

	// Setter

	void setSerialNumber(std::string _num)	{ this->refreshTimeStamp(); this->serialNumber = _num; }
	void setMetaInfo(ST_INFO& _info)		{ this->refreshTimeStamp(); *this->deviceInfo = _info; }

	// Other Functions

	void refreshTimeStamp(void)				{ this->timestamp = getNowUnixTime(); }

};