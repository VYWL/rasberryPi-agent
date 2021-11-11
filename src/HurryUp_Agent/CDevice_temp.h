#pragma once
#include "CInfo.h"

// modelNumber�� ��ȣ ��ʰ� ���´ٸ� �ڷ��� ����
// ���� ST_DEVICE_INFO�� ������� �Ʒ� ����ü�� ����
// metaInfo�� �� �ֱ�
struct ST_DEVICE_INFO_
{
	std::string name;
	std::string osName;
	std::string modelNumber;
	std::string location;
	std::string category;
	std::string connectMethod;
	uint32_t moduleCount = 0;
	// template property; => TODO :: ���ø�ȭ ���� �ʿ� (������ ����� 11�� 1���� ���丵 ����)

	ST_DEVICE_INFO_& operator= (const ST_DEVICE_INFO_& t)
	{
		this->name = t.name;
		this->osName = t.osName;
		this->location = t.location;
		this->modelNumber = t.modelNumber;
		this->category = t.category;
		this->connectMethod = t.connectMethod;
		this->moduleCount = t.moduleCount;

		return *this;
	}
};


class CDevice : public CInfo<ST_DEVICE_INFO_>
{
private:

	ST_DEVICE_INFO_* metaInfo;

public:

	CDevice(void);
	~CDevice(void);

	// Getter

	std::string		 getMetaInfo(int);  // case �з� => string ���� code�� ����
	ST_DEVICE_INFO_* getMetaInfo(void); // ��ü ����ü ��ȯ

	std::string		 getConnectionInfo(void); // ��ȯ ���� �޶��� ���ɼ� ���� (Property ������)
	std::string		 getSerialNumber(void);

	// Setter
	
	void addModuleCount(void);
	void setModuleCount(uint32_t);
	
	void setName			(std::string);
	void setOsName			(std::string);
	void setModelNumber		(std::string);
	void setSerialNumber	(std::string);
	void setLocation		(std::string);
	void setCategory		(std::string);

	void setMetaInfo		(int);
	void setMetaInfo		(ST_DEVICE_INFO_&);

	// Other functions

	void collectAllData(void); // Callback �Լ� ���ɼ�
	void collectNetworkInfo(void);
	void collectOsInfo(void);
	void collectCpuInfo(void);
	void collectServiceInfo(void);
	void collectProcessInfo(void);

};