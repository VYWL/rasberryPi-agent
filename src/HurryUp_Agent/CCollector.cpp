#include "CCollector.h"

CCollector::CCollector(void) 
{
	// TODO :: ����̽� �̸� �� �ø��� �ѹ� ���� ������ ������ �Ǵ°� �ƴ� => �����ʿ�.
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

// ��� ����Ʈ��, ������ �ε����� �ش��ϴ� ��� ��ü�� ��ȯ
// �ε����� ������ ����� ��� Null
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
	// ��ȿ�� ����
	auto isValid = isValidModuleData(_addT);

	// TODO : ã�� ���ߴٴ� �α� �����
	if (!isValid) return;

	// ���� �߰��� ������ check

	auto hasModule = this->getModuleInstance(_addT->getSerialNumber());

	// TODO : ã�� ���ߴٴ� �α� �����
	if (hasModule) return;

	// ���³��� => �߰�

	this->moduleList.push_back(_addT);

	// TODO :: ������ ���� ������Ʈ

}

void CCollector::deleteModule(int _idx)
{
	// ��� ����Ʈ�� Ư�� �ε����� ��� ��ü�� �޸� �����ϰ� ����Ʈ���� �����Ѵ�.

	// 1. �ּҰ� ��������

	auto removedModule = this->moduleList[_idx];

	// 2. ����Ʈ �󿡼� ����

	this->moduleList.erase(this->moduleList.begin() + _idx);

	// 3. free

	delete (removedModule);

	return;
}

void CCollector::deleteModule(std::string _mSerial)
{
	// ��� ����Ʈ�� Ư�� �ε����� ��� ��ü�� �޸� �����ϰ� ����Ʈ���� �����Ѵ�.

	// 0. find

	auto removedModule = this->getModuleInstance(_mSerial);

	// TODO : ã�� ���ߴٴ� �α� �����
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
	// ��ü ����� ���� �ѹ��� �����Ѵ�.
	for (auto _m : this->moduleList)
	{
		_m->checkStatus();
	}
}

void CCollector::refreshModuleInfo(int _idx)
{
	// TODO : ���� ���̶�� �α� ����� => �Լ�ȭ
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
	// ���� �����͸� �����ϰ�, �޽����� �����.

}
