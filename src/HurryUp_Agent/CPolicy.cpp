#include "CPolicy.h"

CPolicy::CPolicy(void){}
CPolicy::~CPolicy(void){}

void			CPolicy::addPolicy(const ST_POLICY_INFO*){}
ST_POLICY_INFO* CPolicy::findPolicy(int _idx){}
ST_POLICY_INFO* CPolicy::findPolicy(std::string _name){}
ST_POLICY_INFO	CPolicy::deletePolicy(int _idx){}
ST_POLICY_INFO	CPolicy::deletePolicy(std::string _name){}

std::string		CPolicy::getPolicyList(void){}
void			CPolicy::initPolicyList(void){}

// TODO :: ���� Ȥ�� ��ɾ �ް� ��å�� ���� �� �����ϴ� �Լ�
void CPolicy::enablePolicy(void){}
void CPolicy::disablePolicy(void){}

void CPolicy::refreshTimeStamp(void){}