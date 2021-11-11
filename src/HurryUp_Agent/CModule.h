#pragma once
#include "CInfo.h"

class CModule : public CInfo<>
{
private:
	// Module Info => PinNum == serialNumber
	// TODO :: PinNum의 형식을 GPIO 관련 라이브러리 명세대로 맞춰두기
	uint32_t pinNum;
	bool isLive;

public:
	CModule(void);
	~CModule(void);

	// Getter

	//std::string getCollectedData	(void);
	uint32_t	getPinNum			(void);
	bool		getIsLive			(void);

	// Setter

	//void setCollectedData	(std::string); // 이어 붙이는 형식
	void setPinNum			(uint32_t);
	void setStatus			(bool);

	// Other Functions

	void checkStatus			(void);

};