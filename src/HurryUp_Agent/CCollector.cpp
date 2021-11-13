#include "CCollector.h"

CCollector::CCollector(void) 
{
	// TODO :: 디바이스 이름 및 시리얼 넘버 등의 정보는 수집이 되는게 아님 => 설정필요.
	this->device = new CDevice_;
	this->device->collectAllData();

	this->interval = 500;
}

CCollector::~CCollector(void)
{
	delete (this->device);
}

// Constructor

CCollector* CCollector::getInstance(void)
{
	static CCollector instance;
	return &instance;
}

// Getter

CDevice_*		CCollector::getDeviceInstance(void)
{
	return this->device;
}

// 모듈 리스트중, 임의의 인덱스에 해당하는 모듈 객체를 반환
// 인덱스가 범위를 벗어나는 경우 Null
CModule* CCollector::getModuleInstance(int _idx)
{
	if (_idx < 0 || _idx >= this->moduleList.size()) return NULL;

	return this->moduleList[_idx];
}

CModule* CCollector::getModuleInstance(std::string _mSerial)
{
	for (auto _m : this->moduleList)
		if (_m->getSerialNumber() == _mSerial) return _m;

	return NULL;
}

std::vector<CModule*> CCollector::getModuleListInfo(void)
{
	return this->moduleList;
}

// Setter

void CCollector::addModule(CModule* _addT)
{
	// 유효성 검증
	auto isValid = isValidModuleData(_addT);

	// TODO : 찾지 못했다는 로그 남기기
	if (!isValid) return;

	// 기존 추가한 놈인지 check

	auto hasModule = this->getModuleInstance(_addT->getSerialNumber());

	// TODO : 찾지 못했다는 로그 남기기
	if (hasModule) return;

	// 없는놈임 => 추가

	this->moduleList.push_back(_addT);

	// TODO :: 서버에 정보 업데이트

}

void CCollector::deleteModule(int _idx)
{
	// 모듈 리스트의 특정 인덱스의 모듈 객체를 메모리 해제하고 리스트에서 제거한다.

	// 1. 주소값 가져오기

	auto removedModule = this->moduleList[_idx];

	// 2. 리스트 상에서 삭제

	this->moduleList.erase(this->moduleList.begin() + _idx);

	// 3. free

	delete (removedModule);

	return;
}

void CCollector::deleteModule(std::string _mSerial)
{
	// 모듈 리스트의 특정 인덱스의 모듈 객체를 메모리 해제하고 리스트에서 제거한다.

	// 0. find

	auto removedModule = this->getModuleInstance(_mSerial);

	// TODO : 찾지 못했다는 로그 남기기
	if (!removedModule) return;

	// 1. memory free

	delete (removedModule);

	return;
}

void CCollector::refreshDeviceInfo(void)
{
	this->device->collectAllData();
}

void CCollector::refreshModuleList(void)
{
	// 전체 모듈을 전부 한번씩 갱신한다.
	for (auto _m : this->moduleList)
	{
		_m->checkStatus();
	}
}

void CCollector::refreshModuleInfo(int _idx)
{
	// TODO : 범위 밖이라는 로그 남기기 => 함수화
	if (_idx < 0 || _idx >= this->moduleList.size()) return;

	this->moduleList[_idx]->checkStatus();
}

// Interval

void CCollector::init()
{
	std::future<void> dataCollector = std::async(std::launch::async, &CCollector::startInterval, CCollectorManager());
}

void CCollector::startInterval()
{
	while(1)
		setInterval(this->cancelIntervalBoolean, this->interval, collectInfo);
}

void CCollector::changeInterval(int _interval)
{
	this->interval = _interval;
	this->cancelIntervalBoolean.store(false);
}


int isValidModuleData(CModule* _t)
{
	if(_t->getPinNum() == 0)			return NO_PINNUM;
	if(_t->getConnectionType() == 0)	return NO_CONNECTTION_TYPE;

	return VAILD;
}

void collectInfo()
{
	// 보낼 데이터를 수집하고, 메시지를 만든다.

}
