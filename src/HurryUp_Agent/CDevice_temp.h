#pragma once
#include "CInfo.h"

// modelNumber는 번호 용례가 나온다면 자료형 변경
// 기존 ST_DEVICE_INFO가 사라지면 아래 구조체명 변경
// metaInfo에 더 넣기
struct ST_DEVICE_INFO_
{
	std::string name;
	std::string osName;
	std::string modelNumber;
	std::string location;
	std::string category;
	std::string connectMethod;
	uint32_t moduleCount = 0;
	// template property; => TODO :: 템플릿화 구현 필요 (전상현 멘토님 11월 1주차 멘토링 참고)

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

	std::string		 getMetaInfo(int);  // case 분류 => string 말고 code면 좋음
	ST_DEVICE_INFO_* getMetaInfo(void); // 전체 구조체 반환

	std::string		 getConnectionInfo(void); // 반환 형식 달라질 가능성 존재 (Property 때문에)
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

	void collectAllData(void); // Callback 함수 가능성
	void collectNetworkInfo(void);
	void collectOsInfo(void);
	void collectCpuInfo(void);
	void collectServiceInfo(void);
	void collectProcessInfo(void);

};