#pragma once
#include "stdafx.h"

struct ST_DEVICE_INFO
{
	std::string name;
	std::string osName;
	std::string modelNumber;
	std::string location;
	std::string category;
};


class CInfo
{
private:
	// Identifiable Information
	std::string serialNumber;

	// Device Information
	ST_DEVICE_INFO deviceInfo;

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
	std::string				getSerialNumber		(void);
	const ST_DEVICE_INFO	getDeviceInfo		(void);
	std::string				getDeviceInfo		(std::string); // case �з� => string ���� code�� ����
	std::string				getLastModifiedTime	(void);
	std::string				getConnectionInfo	(void);

	// Setter
	void setName		(std::string);
	void setOsName		(std::string);
	void setModelNumber	(std::string);
	void setLocation	(std::string);
	void setCategory	(std::string);
	void setDeviceInfo	(ST_DEVICE_INFO);

	// Other Functions
	void refreshTimeStamp	();

};