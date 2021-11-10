#pragma once
#include "stdafx.h"

struct ST_POLICY_INFO
{
	std::string timestamp;
	std::string policyName;
	std::string policyID;
	std::string policyDescription;
	bool isFile;

	ST_POLICY_INFO& operator= (const ST_POLICY_INFO& t)
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

	std::vector<ST_POLICY_INFO*> activePolicyList;

public:

	CPolicy(void);
	~CPolicy(void);

	void addPolicy(const ST_POLICY_INFO*);
	ST_POLICY_INFO* findPolicy(int);
	ST_POLICY_INFO* findPolicy(std::string);
	ST_POLICY_INFO	deletePolicy(int);
	ST_POLICY_INFO	deletePolicy(std::string);

	std::string		getPolicyList(void);
	void			initPolicyList(void);

	// TODO :: ���� Ȥ�� ��ɾ �ް� ��å�� ���� �� �����ϴ� �Լ�
	void enablePolicy(void);
	void disablePolicy(void);

	void refreshTimeStamp(void);
};