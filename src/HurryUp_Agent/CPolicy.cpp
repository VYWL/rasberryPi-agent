#include "CPolicy.h"

CPolicy::CPolicy(void){}
CPolicy::~CPolicy(void){}

void			 CPolicy::addPolicy(const ST_POLICY_INFO_*){}
ST_POLICY_INFO_* CPolicy::findPolicy(int _idx){}
ST_POLICY_INFO_* CPolicy::findPolicy(std::string _name){}
ST_POLICY_INFO_	 CPolicy::deletePolicy(int _idx){}
ST_POLICY_INFO_	 CPolicy::deletePolicy(std::string _name){}

std::string		CPolicy::getPolicyList(void){}
void			CPolicy::initPolicyList(void){}

// TODO :: ���� Ȥ�� ��ɾ �ް� ��å�� ���� �� �����ϴ� �Լ�
void CPolicy::enablePolicy(void){}
void CPolicy::disablePolicy(void){}

void CPolicy::refreshTimeStamp(void){}