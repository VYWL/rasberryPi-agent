#include "CInspection.h"

CInspection::CInspection(void)
{
	this->nowTask = new ST_INSPECTION_INFO;
}

CInspection::~CInspection(void)
{
	delete (this->nowTask);
}

void CInspection::clearTaskQueue(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// 단순 큐 비우기
}

int CInspection::getTaskQueueLength(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	return this->taskQueue.size();
}

ST_INSPECTION_INFO* CInspection::getNowTaskInfo(void)
{
	return this->nowTask;
}

// TODO :: Message로부터 받은 정보를 가공하여 Queue에 추가. => 아직 인자의 자료형 void라 수정필요
void CInspection::addTask(std::string _data)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// msg를 받기
	// 구조체로 가공
	// queue에 넣기
}

void CInspection::execTask(void)
{
	std::lock_guard<std::mutex> lock_guard(this->taskQueueMutex);
	// 0. queue에서 하나 뽑기
	// 1. 실행
	// 2. 파일 다운로드 및 실행 등등
	// 3. 끝나면 메시지 보내기
}