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
	// ����Ž�� => Policy�� 1000���� ���� �����Ƿ�.

	for (auto policyInfo : this->activePolicyList)
		if (policyInfo->policyName == _name) return policyInfo;

	return NULL;
}

void CPolicy::deletePolicy(int _idx)
{
	if (_idx < 0 || _idx >= this->activePolicyList.size()) return;
	
	// TODO :: vector erase�� ȿ����?

	this->activePolicyList.erase(this->activePolicyList.begin() + _idx);
}

void CPolicy::deletePolicy(std::string _name)
{
	// Ž��
	int _idx = -1;
	for (int i = 0; i < this->activePolicyList.size(); ++i)
	{
		auto policyInfo = this->activePolicyList[i];
		if (policyInfo->policyName == _name)
		{
			_idx = i;
		}
	}
	
	// ����
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
	// 0. �������� ������ ��������
	// 1. �ݺ������� applyPolicyState ����
	// 2. timestamp ���� X
}

// TODO :: ���� Ȥ�� ��ɾ �ް� ��å�� ���� �� �����ϴ� �Լ�

void CPolicy::applyPolicyState(int _code, std::string _data)
{
	// 0. ����
	// _data�� ����ü�� ��ȯ (������ ���� ����ü)
	// ������ �а� ����
	// activeList�� 
	
	// 1. _code == ACTIVATE_POLICY
	// ���� ����� �ް�, ������ ����鼭 ST_POLICY_INFO ����ü �Ҵ�
	// activeList�� �ֱ�
	
	// 2. _code == DEACTIVATE_POLICY
	// ���� ����� �ޱ�.
	// activeList�� �ش� ��å id�� �ش��ϴ� ����ü delete
	
	// 3. _code == UPDATE_POLICY
	// ���� ����� �ޱ�.
	// activeList�� �ش� ��å id�� �ش��ϴ� ����ü timestamp ������Ʈ
}

void CPolicy::refreshTimestamp(void) 
{ 
	this->timestamp = getNowUnixTime(); 
}