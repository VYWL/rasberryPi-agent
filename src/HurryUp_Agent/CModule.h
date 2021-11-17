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

	CModule(void)
	{
		this->metaInfo					= new ST_MODULE_INFO_;
		this->metaInfo->pinNum			= 0;
		this->metaInfo->isLive			= false;
		this->metaInfo->connectionType	= 0;
	}

	~CModule(void)
	{
		delete (this->metaInfo);
	}

	// Getter

	uint32_t		 getPinNum(void)			{ return this->metaInfo->pinNum; }
	bool			 getIsLive(void)			{ return this->metaInfo->isLive; }
	uint32_t		 getConnectionType(void)	{ return this->metaInfo->connectionType; }
	ST_MODULE_INFO_* getMetaInfo(void)			{ return this->metaInfo; } // ��ü ����ü ��ȯ

	// Setter

	void setStatus(bool _status)				{ this->metaInfo->isLive			= _status; }
	void setPinNum(uint32_t _pinNum)			{ this->metaInfo->pinNum			= _pinNum; }
	void setConnectionType(uint32_t _cType)		{ this->metaInfo->connectionType	= _cType; }
	void setMetaInfo(ST_MODULE_INFO_& _m)		{ *this->metaInfo					= _m; }

	// Other Functions

	void checkStatus(void)
	{
		// PinNum�� ��ȿ������ �˾Ƴ��� �Լ�
	}
};

void Debug_CModule(CModule*);