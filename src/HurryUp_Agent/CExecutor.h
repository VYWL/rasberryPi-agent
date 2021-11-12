#pragma once
#include "stdafx.h"
#include "CPolicy.h"
#include "CInspection.h"

class CExecutor
{
private:
	
	CPolicy*		policy;
	CInspection*	inspection;

public:
	
	CExecutor(void);
	~CExecutor(void);

	std::vector<ST_POLICY_INFO_*>	getPolicyListInfo(void);
	int								getNowTaskQueueLength(void);

	void clearPolicyList();
	void clearInspectionQueue();

};