#include "CModule.h"

void Debug_CModule(CModule* tmp)
{
	std::cout << ":: CModule Create Test ::" << '\n';
	std::cout << ":: serialNum = " << tmp->getSerialNumber() << '\n';

	ST_MODULE_INFO_* tmp_minfo = tmp->getMetaInfo();
	std::cout << ":: metaInfo->pinNum = " << tmp_minfo->pinNum << '\n';
	std::cout << ":: metaInfo->isLive = " << tmp_minfo->isLive << '\n';
	std::cout << ":: metaInfo->connectionType = " << tmp_minfo->connectionType << '\n';
	std::cout << ":: timestamp = " << tmp->getLastModifiedTime() << '\n';
}

/*

CModule::CModule(void)
{
	this->metaInfo = new ST_MODULE_INFO_;
	this->metaInfo->pinNum = 0;
	this->metaInfo->isLive = false;
	this->metaInfo->connectionType = 0;
}

CModule::~CModule(void)
{
	delete (this->metaInfo);
}

// Getter

uint32_t		 CModule::getPinNum(void)			{ return this->metaInfo->pinNum; }
bool			 CModule::getIsLive(void)			{ return this->metaInfo->isLive; }
uint32_t		 CModule::getConnectionType(void)	{ return this->metaInfo->connectionType; }
ST_MODULE_INFO_* CModule::getMetaInfo(void)			{ return this->metaInfo; } // 전체 구조체 반환

// Setter

void CModule::setStatus(bool _status)				{ this->metaInfo->isLive = _status; }
void CModule::setPinNum(uint32_t _pinNum)			{ this->metaInfo->pinNum = _pinNum; }
void CModule::setConnectionType(uint32_t _cType)	{ this->metaInfo->connectionType = _cType; }
void CModule::setMetaInfo(ST_MODULE_INFO_& _m)		{ *this->metaInfo = _m; }

// Other Functions

void CModule::checkStatus(void)
{
	// PinNum이 유효한지를 알아내는 함수
}
*/