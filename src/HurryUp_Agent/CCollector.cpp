#include "CCollector.h"

CCollector::CCollector(void)
{
	// TODO :: ����̽� �̸� �� �ø��� �ѹ� ���� ������ ������ �Ǵ°� �ƴ� => �����ʿ�.
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
	// �������ִ� this->Device�� �����Ѵ�.
	return this->device;
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
	auto a = new CModule;
	return *a;
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