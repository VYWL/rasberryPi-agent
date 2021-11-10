#pragma once
#include "stdafx.h"
#include "CInfo.h"

std::string getNowUnixTime();

// TEST
void Debug_CInfo(CInfo *);

void osInfoGather_1();
void osInfoGather_2();
void osInfoGather_3();

void networkInfoGather_1();
void networkInfoGather_2();
void networkInfoGather_3();

void procInfoGather_1();

// Log or Terminal
std::string SendToTerminal(const char *);
std::string exec(const char *);
void SetLogger(std::string, DWORD);