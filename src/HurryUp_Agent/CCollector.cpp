#include "CCollector.h"

// Global Variables - none

// Static functions - none

// Constructor & destructor

CCollector::CCollector(void)
{
	// TODO :: ����̽� �̸� �� �ø��� �ѹ� ���� ������ ������ �Ǵ°� �ƴ� => �����ʿ�.
	this->device = new CDevice;
	this->device->collectAllData();
}

CCollector::~CCollector(void)
{
	delete (this->device);
}

// Getter

CDevice*		CCollector::getDeviceInstance(void)
{
	// �������ִ� this->Device�� �����Ѵ�.
}

CModule*		CCollector::getModuleInstance(int _idx)
{
	// ��� ����Ʈ��, ������ �ε����� �ش��ϴ� ��� ��ü�� ��ȯ
	// �ε����� ������ ����� ��� Null
}

std::string		CCollector::getModuleListInfo(void)
{
	// ��ü ��� ����Ʈ ���� ������ ��ȯ�Ѵ�. => ��� ��ȯ���� ���ϱ�
	// ��� ������ ������ ��Ƽ� ��ȯ => sstream ����ؼ� ���ڿ��� ��ȯ
}


// Setter

void CCollector::addModule(const CModule &)
{
	// ��� ����Ʈ�� ����� �߰��ϴ� �����̴�.
	// ����� �߰ߵ��� �ʾ��� ��� Ȥ�� �ڵ���� �����߿� ȣ��ȴ�.
}

CModule CCollector::deleteModule(int)
{
	// ��� ����Ʈ�� Ư�� �ε����� ��� ��ü�� �޸� �����ϰ� ����Ʈ���� �����Ѵ�.
	// ���� �� ���� ��ü ������ ��ȯ�Ѵ�. (�̸� ������ �ξ�� ����?)
}

// Monitoring?

void CCollector::refreshDeviceInfo(void)
{
	// ��ġ ������ �ѹ� �����Ѵ�.
	this->device->collectAllData();
}

void CCollector::refreshModuleList(void)
{
	// ��ü ����� ���� �ѹ��� �����Ѵ�.
}

void CCollector::refreshModuleInfo(int)
{
	// Ư�� �ε����� ��� ������ �ѹ� �����Ѵ�.
}