#pragma once
#include "CDevice_temp.h"
#include "CModule.h"
#include "stdafx.h"

class CCollector
{
private:
	CDevice* device;
	std::vector<CModule*> moduleList;
	
public:
	// Constructor

	CCollector	(void);
	~CCollector	(void);

	// Getter

	CDevice*		getDeviceInstance	(void);
	CModule*		getModuleInstance	(int);
	std::string		getModuleListInfo	(void);

	// Setter

	void		addModule		(const CModule &);
	CModule		deleteModule	(int);

	// Other functions

	void refreshDeviceInfo	(void);
	void refreshModuleList	(void);
	void refreshModuleInfo	(int);
};