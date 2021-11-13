#pragma once
#include "stdafx.h"

// TODO :: �ܰ躰 ������ ���� �����, �ɺ� ��ũ�� �ִ���.
// TODO :: ���� �׸��� ���� �ڵ� �߰�(��ũ��)
struct ST_STAGE_INFO
{
	uint32_t isFail;
	uint32_t nowStage;
	std::string filePath;
	std::string stageDescription;
	std::string timestamp;
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
	// TODO :: queue�� Thread safe ���� �˾ƺ����Ѵ�. �ƴ϶�� �Ѵ�....
	ST_INSPECTION_INFO*				nowTask;
	std::queue<ST_INSPECTION_INFO*> taskQueue;

public:
	
	CInspection(void);
	~CInspection(void);

	void				clearTaskQueue(void);
	int					getTaskQueueLength(void);
	ST_INSPECTION_INFO* getNowTaskInfo(void);
	
	// TODO :: Message�κ��� ���� ������ �����Ͽ� Queue�� �߰�. => ���� ������ �ڷ��� void�� �����ʿ�
	static void addTask(std::string);
	static void execTask(void);
};