#pragma once

#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

inline void debugPrint(char* message){
	//#ifndef DEBUG
	std::cout << message << std::endl;
	//#endif
}

inline std::string nullDelete(char* _data){
	char *p = _data;
	int size = 0;
	while (*_data != 0){
		_data++;
		size++;
	}
	*_data = '\n';
	char *s = p;
	std::string str = s;
	return str;
}

#ifndef _RECVSTATUS_
#define _RECVSTATUS_
// ��M���
enum RECVSTATUS
{
	RECV_STILL,		// �f�[�^�����Ă��Ȃ�
	RECV_SUCCESSED,	// ����
	RECV_FAILED		// �ؒfor�G���[
};

#endif

class tcp
{
private:
	SOCKET	m_DstSocket;	// ����M�\�P�b�g
	struct addrinfo hints, *res0, *res;
	// sockaddr_in �\���̂̃Z�b�g
	struct sockaddr_in dstAddr;
public:
	tcp();
	virtual ~tcp();
	void initialize();
	void finalize();
	void setAddress(const char* IP, u_short PORT);
	// �ڑ�
	bool Connect(const char* IP, u_short PORT);
	bool Connect();
	// ��M
	RECVSTATUS Recv(char* pData, int DataSize, int *pRecvSize);
	// ���M
	bool Send(const char* pData, int DataSize);
	bool Send(const char* pData, int DataSize, const char* IP, u_short PORT);

};

