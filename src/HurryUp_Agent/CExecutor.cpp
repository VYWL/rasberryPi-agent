#include "CExecutor.h"

CExecutor::CExecutor(void)
{
	this->policy		= new CPolicy;
	this->inspection	= new CInspection;
}

CExecutor::~CExecutor(void)
{
	delete(this->policy);
	delete(this->inspection);
}

std::vector<ST_POLICY_INFO_*> CExecutor::getPolicyListInfo(void)
{
	// ��å ����Ʈ ������ ��ȯ => ����� �׳� ����Ʈ ��ȯ
	this->policy->refreshTimestamp();

	return this->policy->getPolicyList();
}

int CExecutor::getNowTaskQueueLength()
{
	return this->inspection->getTaskQueueLength();
}
	
void CExecutor::clearPolicyList()
{
	// vector Ŭ����
	// timestamp ����
	// db ���� ��û �޽��� �۽�.
}

void CExecutor::clearInspectionQueue()
{
	//  Ŭ����
	// timestamp ����	
}