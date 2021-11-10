#include "CModule.h"

// Global Variables

// Static functions

// Constructor & destructor

CModule::CModule(void) 
{
	this->pinNum = 0;
	this->isLive = false;

	this->collectedData = "";
}

CModule::~CModule(void) {}

// Getter

std::string		CModule::getCollectedData(void)
{

}

uint32_t CModule::getPinNum(void)
{

}

bool CModule::getIsLive(void)
{

}

// Setter

void CModule::setCollectedData(std::string)
{

}

void CModule::setPinNum(uint32_t)
{

}

void CModule::setStatus(bool)
{

}

// Other functions

void CModule::checkStatus(void)
{

}

void CModule::refreshCollectingData(void)
{

}