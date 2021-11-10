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
	// ��ġ�� ���� �������� �Լ��̴�.

	// �ϴ� �̰͵� �ɰ��°� ������ ����
	// 1. ��Ʈ��ũ ����
	// 2. OS ����
	// 3. CPU ����
	// 4. GPIO ����
}