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
	// 정책 리스트 정보를 반환 => 현재는 그냥 리스트 반환
	this->policy->refreshTimestamp();

	return this->policy->getPolicyList();
}

int CExecutor::getNowTaskQueueLength()
{
	return this->inspection->getTaskQueueLength();
}
	
void CExecutor::clearPolicyList()
{
	// vector 클리어
	// timestamp 갱신
	// db 수정 요청 메시지 송신.
}

void CExecutor::clearInspectionQueue()
{
	//  클리어
	// timestamp 갱신	
}