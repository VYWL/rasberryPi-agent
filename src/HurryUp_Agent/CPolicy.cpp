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

// TODO :: 파일 혹은 명령어를 받고 정책을 적용 및 해제하는 함수
void CPolicy::enablePolicy(void){}
void CPolicy::disablePolicy(void){}

void CPolicy::refreshTimeStamp(void){}