#pragma once
#include "stdafx.h"

struct ST_POLICY_INFO_
{
	std::string timestamp;
	std::string policyName;
	std::string policyID;
	std::string policyDescription;
	bool isFile;

	ST_POLICY_INFO_& operator= (const ST_POLICY_INFO_& t)
	{
		this->policyName = t.policyName;
		this->policyID = t.policyID;
		this->policyDescription = t.policyDescription;
		this->isFile = t.isFile;

		return *this;
	}
};

class CPolicy
{

private:

	std::vector<ST_POLICY_INFO_*> activePolicyList;

public:

	CPolicy(void);
	~CPolicy(void);

	void addPolicy(const ST_POLICY_INFO_*);
	ST_POLICY_INFO_* findPolicy(int);
	ST_POLICY_INFO_* findPolicy(std::string);
	ST_POLICY_INFO_	deletePolicy(int);
	ST_POLICY_INFO_	deletePolicy(std::string);

	std::string		getPolicyList(void);
	void			initPolicyList(void);

	// TODO :: 파일 혹은 명령어를 받고 정책을 적용 및 해제하는 함수
	void enablePolicy(void);
	void disablePolicy(void);

	void refreshTimeStamp(void);
};