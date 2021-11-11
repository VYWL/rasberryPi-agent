#pragma once
#include "CInfo.h"

struct ST_MODULE_INFO_
{
	uint32_t pinNum;
	bool isLive;
	uint32_t connectionType;
	// template 구조체 => 통신 방식에 따른 property를 담은 구조체 TODO

	ST_MODULE_INFO_& operator= (const ST_MODULE_INFO_& t)
	{
		this->pinNum = t.pinNum;
		this->isLive = t.isLive;
		this->connectionType = t.connectionType;

		return *this;
	}
};


class CModule : public CInfo<ST_MODULE_INFO_>
{
private:

	// TODO :: PinNum의 형식을 GPIO 관련 라이브러리 명세대로 맞춰두기
	ST_MODULE_INFO_* metaInfo;

public:

	CModule(void);
	~CModule(void);

	// Getter

	uint32_t		 getPinNum			(void);
	bool			 getIsLive			(void);
	uint32_t		 getConnectionType	(void);
	ST_MODULE_INFO_* getMetaInfo		(void); // 전체 구조체 반환

	// Setter

	void setStatus			(bool);
	void setPinNum			(uint32_t);
	void setConnectionType	(uint32_t);
	void setMetaInfo		(ST_MODULE_INFO_&);

	// Other Functions

	void checkStatus	(void);

};