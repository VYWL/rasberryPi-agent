#pragma once
#include "stdafx.h"

// TODO :: 단계별 파일을 여기 담던가, 심볼 링크를 주던가.
// TODO :: 성공 그리고 실패 코드 추가(매크로)
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
	// TODO :: queue가 Thread safe 한지 알아봐야한다. 아니라고 한다....
	std::queue<ST_INSPECTION_INFO*> taskQueue;

public:
	static ST_INSPECTION_INFO* nowTask;
	
	CInspection(void);
	~CInspection(void);

	void				clearTaskQueue(void);
	uint32_t			getTaskQueueLength(void);
	ST_INSPECTION_INFO* getNowTaskInfo(void);
	
	// TODO :: Message로부터 받은 정보를 가공하여 Queue에 추가. => 아직 인자의 자료형 void라 수정필요
	static void addTask(void);
	static void execTask(void);
};