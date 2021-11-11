#pragma once
#include "stdafx.h"

enum propertyIdx 
{
	D_NAME,
	D_OSNAME,
	D_MODELNUM,
	D_LOCATION,
	D_CATEGORY,
};


template <typename ST_INFO>
class CInfo
{
private:

	std::string serialNumber;
	std::string timestamp;

	ST_INFO* metaInfo;

public:

	// Constructor
	CInfo	(void);
	~CInfo	(void);

	// Getter

	std::string	getLastModifiedTime	  (void);
	std::string	getSerialNumber		  (void);

	ST_INFO*	getMetaInfo	(void);

	// Setter

	void setMetaInfo		(ST_INFO&);
	void setSerialNumber	(std::string);

	// Other Functions

	void refreshTimeStamp	(void);

};