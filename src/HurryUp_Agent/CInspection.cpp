#include "CInspection.h"

CInspection::CInspection(void){}
CInspection::~CInspection(void){}

void CInspection::clearTaskQueue(void){}
uint32_t CInspection::getTaskQueueLength(void){}
ST_INSPECTION_INFO* CInspection::getNowTaskInfo(void){}

// TODO :: Message�κ��� ���� ������ �����Ͽ� Queue�� �߰�. => ���� ������ �ڷ��� void�� �����ʿ�
void CInspection::addTask(void){}
void CInspection::execTask(void){}