#pragma once
#include "stdafx.h"

enum propertyIdx 
{
	D_NAME,
	D_OSNAME,
	D_MODELNUM,
	D_LOCATION,
	D_CATEGORY
};

// modelNumber는 번호 용례가 나온다면 자료형 변경
// 기존 ST_DEVICE_INFO가 사라지면 아래 구조체명 변경
struct ST_DEVICE_INFO_
{
	std::string name;
	std::string osName;
	std::string modelNumber;
	std::string location;
	std::string category;

	ST_DEVICE_INFO_& operator= (const ST_DEVICE_INFO_& t)
	{
		this->name			= t.name;
		this->osName		= t.osName;
		this->location		= t.location;
		this->modelNumber	= t.modelNumber;
		this->category		= t.category;

		return *this;
	}
};


class CInfo
{
private:
	// Identifiable Information
	std::string serialNumber;

	// Device Information
	ST_DEVICE_INFO_* deviceInfo;

	// Meta Information
	std::string timestamp;

	// Connection 
	std::string connectMethod;
	// template property; => TODO :: 템플릿화 구현 필요 (전상현 멘토님 11월 1주차 멘토링 참고)

public:

	// Constructor
	CInfo	(void);
	~CInfo	(void);

	// Getter
	std::string				getLastModifiedTime	  (void);
	std::string				getConnectionInfo	  (void); // 반환 형식 달라질 가능성 존재 (Property 때문에)
	std::string				getSerialNumber		  (void);
	std::string				getDeviceInfo		  (int); // case 분류 => string 말고 code면 좋음
	const ST_DEVICE_INFO_	getDeviceInfo		  (void);

	// Setter
	void setName			(std::string);
	void setOsName			(std::string);
	void setModelNumber		(std::string);
	void setSerialNumber	(std::string);
	void setLocation		(std::string);
	void setCategory		(std::string);
	void setDeviceInfo		(ST_DEVICE_INFO_&);

	// Other Functions
	void refreshTimeStamp	  (void);
};

