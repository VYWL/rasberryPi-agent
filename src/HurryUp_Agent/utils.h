#pragma once
#include "stdafx.h"

std::string getNowUnixTime();


// Log or Terminal
std::string SendToTerminal(const char *);
void SetLogger(std::string, DWORD);