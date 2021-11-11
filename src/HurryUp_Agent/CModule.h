#pragma once
#include "CInfo.h"

struct ST_MODULE_INFO_
{
	uint32_t pinNum;
	bool isLive;
	uint32_t connectionType;
	// template ����ü => ��� ��Ŀ� ���� property�� ���� ����ü TODO

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

	// TODO :: PinNum�� ������ GPIO ���� ���̺귯�� ����� ����α�
	ST_MODULE_INFO_* metaInfo;

public:

	CModule(void);
	~CModule(void);

	// Getter

	uint32_t		 getPinNum			(void);
	bool			 getIsLive			(void);
	uint32_t		 getConnectionType	(void);
	ST_MODULE_INFO_* getMetaInfo		(void); // ��ü ����ü ��ȯ

	// Setter

	void setStatus			(bool);
	void setPinNum			(uint32_t);
	void setConnectionType	(uint32_t);
	void setMetaInfo		(ST_MODULE_INFO_&);

	// Other Functions

	void checkStatus	(void);

};