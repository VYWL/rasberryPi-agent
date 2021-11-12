#include "CCollector.h"

CCollector::CCollector(void)
{
	// TODO :: 디바이스 이름 및 시리얼 넘버 등의 정보는 수집이 되는게 아님 => 설정필요.
	this->device = new CDevice_;
	this->device->collectAllData();
}

CCollector::~CCollector(void)
{
	delete (this->device);
}

// Getter

CDevice_*		CCollector::getDeviceInstance(void)
{
	// 가지고있는 this->Device를 리턴한다.
	return this->device;
}

CModule*		CCollector::getModuleInstance(int _idx)
{
	// 모듈 리스트중, 임의의 인덱스에 해당하는 모듈 객체를 반환
	// 인덱스가 범위를 벗어나는 경우 Null
}

std::string		CCollector::getModuleListInfo(void)
{
	// 전체 모듈 리스트 관련 정보를 반환한다. => 어떤거 반환할지 정하기
	// 대신 임의의 정보를 담아서 반환 => sstream 사용해서 문자열로 반환
}


// Setter

void CCollector::addModule(const CModule &)
{
	// 모듈 리스트에 모듈을 추가하는 과정이다.
	// 모듈이 발견되지 않았을 경우 혹은 자동등록 과정중에 호출된다.
}

CModule CCollector::deleteModule(int)
{
	// 모듈 리스트의 특정 인덱스의 모듈 객체를 메모리 해제하고 리스트에서 제거한다.
	// 제거 후 지운 객체 정보를 반환한다. (미리 복사해 두어야 겠지?)
	auto a = new CModule;
	return *a;
}

// Monitoring?

void CCollector::refreshDeviceInfo(void)
{
	// 장치 정보를 한번 갱신한다.
	this->device->collectAllData();
}

void CCollector::refreshModuleList(void)
{
	// 전체 모듈을 전부 한번씩 갱신한다.
}

void CCollector::refreshModuleInfo(int)
{
	// 특정 인덱스의 모듈 정보를 한번 갱신한다.
}