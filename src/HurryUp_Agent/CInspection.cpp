#include "CInspection.h"

CInspection::CInspection(void){}
CInspection::~CInspection(void){}

void CInspection::clearTaskQueue(void){}
uint32_t CInspection::getTaskQueueLength(void){}
ST_INSPECTION_INFO* CInspection::getNowTaskInfo(void){}

// TODO :: Message로부터 받은 정보를 가공하여 Queue에 추가. => 아직 인자의 자료형 void라 수정필요
void CInspection::addTask(void){}
void CInspection::execTask(void){}