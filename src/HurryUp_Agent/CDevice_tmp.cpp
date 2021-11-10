#include "CDevice_temp.h"

// Global Variables

// Constructor & destructor

CDevice::CDevice	(void) {};
CDevice::~CDevice	(void) {};

// Getter

uint32_t	CDevice::getModuleCount(void)			{ return this->moduleCount; }

// Setter

void		CDevice::addModuleCount(void)			{ this->moduleCount++; }
void		CDevice::setModuleCount(uint32_t _cnt)	{ this->moduleCount += _cnt; }

// Other functions

void		CDevice::refreshData()
{
	// 장치의 값을 가져오는 함수이다.

	// 일단 이것도 쪼개는게 좋을것 같다
	// 1. 네트워크 정보
	// 2. OS 정보
	// 3. CPU 정보
	// 4. GPIO 정보
}