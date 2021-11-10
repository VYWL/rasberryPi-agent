#pragma once
#include "stdafx.h"
#include "CPolicy.h"
#include "CInspection.h"

class CExecutor
{
private:
	
	CPolicy* policy;
	CInspection* inspection;

public:
	
	CExecutor(void);
	~CExecutor(void);

	void refreshPolicyList();
	std::string getActivatedPoliciesInfo();

	void clearPolicyList();
	void clearInspectionQueue();

};