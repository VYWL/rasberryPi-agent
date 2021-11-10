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

// modelNumber�� ��ȣ ��ʰ� ���´ٸ� �ڷ��� ����
// ���� ST_DEVICE_INFO�� ������� �Ʒ� ����ü�� ����
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
	// template property; => TODO :: ���ø�ȭ ���� �ʿ� (������ ����� 11�� 1���� ���丵 ����)

public:

	// Constructor
	CInfo	(void);
	~CInfo	(void);

	// Getter
	std::string				getLastModifiedTime	  (void);
	std::string				getConnectionInfo	  (void); // ��ȯ ���� �޶��� ���ɼ� ���� (Property ������)
	std::string				getSerialNumber		  (void);
	std::string				getDeviceInfo		  (int); // case �з� => string ���� code�� ����
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

