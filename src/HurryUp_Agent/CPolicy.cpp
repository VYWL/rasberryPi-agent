#include "CPolicy.h"
#include "utils.h"

CPolicy::CPolicy(void){ this->timestamp = getNowUnixTime(); }
CPolicy::~CPolicy(void){}

void CPolicy::addPolicy(ST_POLICY_INFO_* _policyInfo) 
{
	this->activePolicyList.push_back(_policyInfo);
	this->refreshTimestamp();
}

ST_POLICY_INFO_* CPolicy::findPolicy(int _idx)
{
	if (_idx < 0 || _idx >= this->activePolicyList.size()) return NULL;

	return this->activePolicyList[_idx];
}

ST_POLICY_INFO_* CPolicy::findPolicy(std::string _name)
{
	// 선형탐색 => Policy가 1000개를 넘지 않으므로.

	for (auto policyInfo : this->activePolicyList)
		if (policyInfo->policyName == _name) return policyInfo;

	return NULL;
}

void CPolicy::deletePolicy(int _idx)
{
	if (_idx < 0 || _idx >= this->activePolicyList.size()) return;
	
	// TODO :: vector erase의 효율성?

	this->activePolicyList.erase(this->activePolicyList.begin() + _idx);
}

void CPolicy::deletePolicy(std::string _name)
{
	// 탐색
	int _idx = -1;
	for (int i = 0; i < this->activePolicyList.size(); ++i)
	{
		auto policyInfo = this->activePolicyList[i];
		if (policyInfo->policyName == _name)
		{
			_idx = i;
		}
	}
	
	// 삭제
	this->deletePolicy(_idx);

	this->refreshTimestamp();
}

std::vector<ST_POLICY_INFO_*> CPolicy::getPolicyList(void)
{
	this->refreshTimestamp();
	return this->activePolicyList;
}

void CPolicy::initPolicyList(void)
{
	// 0. 서버에서 정보를 가져오기
	// 1. 반복문으로 applyPolicyState 실행
	// 2. timestamp 갱신 X
}

// TODO :: 파일 혹은 명령어를 받고 정책을 적용 및 해제하는 함수

void CPolicy::applyPolicyState(int _code, std::string _data)
{
	// 0. 공통
	// _data를 구조체로 전환 (파일을 담은 구조체)
	// 파일을 읽고 실행
	// activeList에 
	
	// 1. _code == ACTIVATE_POLICY
	// 실행 결과를 받고, 파일을 지우면서 ST_POLICY_INFO 구조체 할당
	// activeList에 넣기
	
	// 2. _code == DEACTIVATE_POLICY
	// 실행 결과를 받기.
	// activeList에 해당 정책 id에 해당하는 구조체 delete
	
	// 3. _code == UPDATE_POLICY
	// 실행 결과를 받기.
	// activeList에 해당 정책 id에 해당하는 구조체 timestamp 업데이트
}

void CPolicy::refreshTimestamp(void) 
{ 
	this->timestamp = getNowUnixTime(); 
}