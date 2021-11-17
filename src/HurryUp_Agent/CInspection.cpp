#include "CInspection.h"

CInspection::CInspection(void)
{
	this->nowTask = new ST_INSPECTION_INFO;
}

CInspection::~CInspection(void)
{
	delete (this->nowTask);
}

void CInspection::clearTaskQueue(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// �ܼ� ť ����
}

int CInspection::getTaskQueueLength(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	return this->taskQueue.size();
}

ST_INSPECTION_INFO* CInspection::getNowTaskInfo(void)
{
	return this->nowTask;
}

// TODO :: Message�κ��� ���� ������ �����Ͽ� Queue�� �߰�. => ���� ������ �ڷ��� void�� �����ʿ�
void CInspection::addTask(std::string _data)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// msg�� �ޱ�
	// ����ü�� ����
	// queue�� �ֱ�
}

void CInspection::execTask(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// 0. queue���� �ϳ� �̱�
	// 1. ����
	// 2. ���� �ٿ�ε� �� ���� ���
	// 3. ������ �޽��� ������
}