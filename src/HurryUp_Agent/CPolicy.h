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
	
	std::string timestamp;
	std::vector<ST_POLICY_INFO_*> activePolicyList;

public:

	CPolicy(void);
	~CPolicy(void);

	void addPolicy(ST_POLICY_INFO_*);
	ST_POLICY_INFO_* findPolicy(int);
	ST_POLICY_INFO_* findPolicy(std::string);
	void			deletePolicy(int);
	void			deletePolicy(std::string);

	std::vector<ST_POLICY_INFO_*>	getPolicyList(void);
	void							initPolicyList(void);

	// TODO :: ���� Ȥ�� ��ɾ �ް� ��å�� ���� �� �����ϴ� �Լ�
	static void applyPolicyState(int _code, std::string _data);

	void refreshTimestamp(void);
};
