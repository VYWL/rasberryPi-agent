#pragma once
#include "CInfo.h"

class CDevice : public CInfo
{
private:

	uint32_t moduleCount;

public:
	CDevice(void);
	~CDevice(void);

	// Getter
	uint32_t	getModuleCount(void);

	// Setter;
	void		addModuleCount(void);
	void		setModuleCount(uint32_t);

	// Other Functions
	// void refreshData(); => 공통 함수
};