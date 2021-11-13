#pragma once
#include "stdafx.h"
// NetInfo => ifaddr (1¹ø ¹æ½Ä)
#include <ifaddrs.h>
#include <linux/if_link.h>      

struct sockaddr_ll
{
    uint16_t sll_family;
    uint16_t sll_protocol;
    uint32_t sll_ifindex;
    uint16_t sll_hatype;
    uint8_t sll_pkttype;
    uint8_t sll_halen;
    uint8_t sll_addr[8];
};


// About String
std::string getNowUnixTime(void);
std::vector<std::string> split(std::string, char);
std::string trim(const std::string&);


// TEST

void osInfoGather_1();
void osInfoGather_2();
void osInfoGather_3();

void networkInfoGather_1();
void networkInfoGather_2();
void networkInfoGather_3();

void serviceInfoGather_1();
void serviceInfoGather_2();

// Log or Terminal
std::string SendToTerminal(const char *);
std::string exec(const char *);
void SetLogger(std::string, DWORD);
