#pragma once
#include "CDevice_temp.h"
#include "CModule.h"
#include "CMonitoring.h"
#include "stdafx.h"

enum ModuleErrorCode
{
	VAILD,
	NO_PINNUM,
	NO_CONNECTTION_TYPE,
};

struct ST_INTERVAL_INFO : public core::IFormatterObject
{
	int interval;

	ST_INTERVAL_INFO(void)
	{}
	ST_INTERVAL_INFO(int _interval) : interval(_interval)
	{}

	void OnSync(core::IFormatter& formatter)
	{
		formatter
			+ core::sPair(TEXT("Interval"), interval)
			;
	}
};

class CCollector
{
private:

	CDevice_* device;
	std::vector<CModule*> moduleList;
	CMonitoring* monitor;

	std::atomic_bool cancelIntervalBoolean;
	int interval;

	CCollector(void);
	~CCollector	(void);


public:
	// Constructor
	
	static CCollector* getInstance(void);

	// Getter

	CDevice_*				getDeviceInstance		(void);
	CModule*				getModuleInstance		(int);
	CModule*				getModuleInstance		(std::string);
	CMonitoring*			getMonitoringInstance	(void);
	std::vector<CModule*>	getModuleListInfo		(void);

	// Setter

	void		addModule		(CModule*);
	void		deleteModule	(int);
	void		deleteModule	(std::string);

	// Other functions

	void refreshDeviceInfo	(void);
	void refreshModuleList	(void);
	void refreshModuleInfo	(int);

	// Interval

	void init();
	void startInterval();
	void changeInterval(int);

	// API > CCollector <=> CMessage

};

int isValidModuleData(CModule*);
void collectInfo(void);

inline CCollector* CCollectorManager(void)
{
	return CCollector::getInstance();
}
