#pragma once
#include "stdafx.h"
#include <queue>
#include <protocol.h>

class CMessage
{
private:
	std::queue<ST_NEW_PACKET_INFO*> receiveMessage;
	std::queue<ST_NEW_PACKET_INFO*> sendMessage;
	std::mutex receiveMessageMutex;
	std::mutex sendMessageMutex;

	CMessage();
	~CMessage();

	void ReceiveMessage();	//�������� ���� �޽����� �����ϴ� ���
	void SendMessage();		//������ �޽����� ������ ���
	void MatchReceiveMessage();	//���� �޽���ť���� �޽����� �о�, ������Ʈ Ư�� ��ɰ� ��Ī �����ִ� ���
	
public:
	static CMessage* GetInstance(void);
	void Init();
	void PushReceiveMessage(ST_NEW_PACKET_INFO* stPacketInfo);	//���� �޽����� ���� �޽���ť�� �����ϴ� ���
	void PushSendMessage(PacketType type, OPCODE opcode, std::tstring message);	//�۽� �޽����� �۽� �޽���ť�� �����ϴ� ���
};

inline CMessage* MessageManager()
{
	return CMessage::GetInstance();
}