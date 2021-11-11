#pragma once
#include "CInfo.h"

// modelNumber�� ��ȣ ��ʰ� ���´ٸ� �ڷ��� ����
// ���� ST_DEVICE_INFO�� ������� �Ʒ� ����ü�� ����
// metaInfo�� �� �ֱ� => 11/12 �� �ݿ�
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

	ST_DEVICE_INFO_* getMetaInfo(void); // ��ü ����ü ��ȯ

	// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
	std::string getName(std::string); 
	std::string getOsName(std::string);
	std::string getModelNumber(std::string);
	std::string getLocation(std::string);
	std::string getCategory(std::string);
	std::string	getConnectionInfo(void); // ��ȯ ���� �޶��� ���ɼ� ���� (Property ������)

	// Setter
	
	void addModuleCount(void);
	void setModuleCount(uint32_t);

	// TODO :: ����ü Ȯ���Ǹ� ���� �߰�
	void setName			(std::string);
	void setOsName			(std::string);
	void setModelNumber		(std::string);
	void setLocation		(std::string);
	void setCategory		(std::string);
	void setMetaInfo		(ST_DEVICE_INFO_&);

	// Other functions

	void collectAllData(void); // Callback �Լ� ���ɼ�
	void collectNetworkInfo(void);
	void collectOsInfo(void);
	void collectCpuInfo(void);
	void collectServiceInfo(void);

};