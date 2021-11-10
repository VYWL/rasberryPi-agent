#pragma once
#include "stdafx.h"
#include "CInfo.h"

std::string getNowUnixTime();

// TEST
void Debug_CInfo(CInfo *);

// Log or Terminal
std::string SendToTerminal(const char *);
void SetLogger(std::string, DWORD);