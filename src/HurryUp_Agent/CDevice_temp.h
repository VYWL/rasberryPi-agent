#pragma once
#include "CInfo.h"

class CDevice : public CInfo
{
private:

	uint32_t moduleCount = 0;

public:
	CDevice(void);
	~CDevice(void);

	// Getter

	uint32_t	 getModuleCount(void);

	// Setter
	
	void		 addModuleCount(void);
	void		 setModuleCount(uint32_t);

	// Other functions

	void		 collectAllData(void); // Callback 함수 가능성
	void		 collectNetworkInfo(void);
	void		 collectOsInfo(void);
	void		 collectCpuInfo(void);
	void		 collectServiceInfo(void);

};