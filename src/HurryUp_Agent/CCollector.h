#pragma once
#include "CDevice_temp.h"
#include "CModule.h"
#include "stdafx.h"

class CCollector
{
private:
	CDevice device;
	std::vector<CModule> moduleList;
	
public:
	// Constructor
	CCollector	(void);
	~CCollector	(void);

	// Getter
	const CDevice	getDeviceInstance	(void);
	const CModule	getModuleInstance	(int);
	std::string		getModuleListInfo	(void);

	// Setter
	void addModule		(const CModule &);
	void deleteModule	(int);

	// Other functions
	void refreshDeviceInfo	(void);
	void refreshModuleList	(void);
	void refreshModuleInfo	(int);
};