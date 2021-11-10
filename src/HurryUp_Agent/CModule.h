#pragma once
#include "CInfo.h"

class CModule : public CInfo
{
private:
	// Module Info
	// TODO :: PinNum�� ������ GPIO ���� ���̺귯�� ����� ����α�
	uint32_t pinNum;
	bool isLive;

	// Collected Data
	std::string collectedData;

public:
	CModule(void);
	~CModule(void);

	// Getter
	std::string getCollectedData(void);
	uint32_t	getPinNum(void);
	bool		getIsLive(void);

	// Setter
	void setCollectedData(std::string);
	void setPinNum(uint32_t);
	void setStatus(void);

	// Other Functions
	void checkStatus();
	void refreshData();
};