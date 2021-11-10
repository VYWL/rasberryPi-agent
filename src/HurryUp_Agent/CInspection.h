#pragma once
#include "stdafx.h"

// TODO :: �ܰ躰 ������ ���� �����, �ɺ� ��ũ�� �ִ���.
// TODO :: ���� �׸��� ���� �ڵ� �߰�(��ũ��)
struct ST_STAGE_INFO
{
	// FILE* executableFile;
	uint32_t nowStage;
	std::string stageDescription;
	std::string timestamp;
	uint32_t isSuccess;
};

struct ST_INSPECTION_INFO
{
	std::string inspectionName;
	std::string inspectionID;
	std::string inspectionDescription;
	uint32_t totalSequence;
	uint32_t nowSequence;
	std::vector<ST_STAGE_INFO*> stageList;
	std::string timestamp;
};


class CInspection
{
private:
	// TODO :: queue�� Thread safe ���� �˾ƺ����Ѵ�.
	std::queue<ST_INSPECTION_INFO*> taskQueue;

public:
	static ST_INSPECTION_INFO* nowTask;
	
	CInspection(void);
	~CInspection(void);

	void clearTaskQueue(void);
	uint32_t getTaskQueueLength(void);
	ST_INSPECTION_INFO* getNowTaskInfo(void);
	
	// TODO :: Message�κ��� ���� ������ �����Ͽ� Queue�� �߰�. => ���� ������ �ڷ��� void
	static void addTask(void);
	static void execTask(void);
};