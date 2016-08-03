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
// 受信状態
enum RECVSTATUS
{
	RECV_STILL,		// データが来ていない
	RECV_SUCCESSED,	// 成功
	RECV_FAILED		// 切断orエラー
};

#endif

class tcp
{
private:
	SOCKET	m_DstSocket;	// 送受信ソケット
	struct addrinfo hints, *res0, *res;
	// sockaddr_in 構造体のセット
	struct sockaddr_in dstAddr;
public:
	tcp();
	virtual ~tcp();
	void initialize();
	void finalize();
	void setAddress(const char* IP, u_short PORT);
	// 接続
	bool Connect(const char* IP, u_short PORT);
	bool Connect();
	// 受信
	RECVSTATUS Recv(char* pData, int DataSize, int *pRecvSize);
	// 送信
	bool Send(const char* pData, int DataSize);
	bool Send(const char* pData, int DataSize, const char* IP, u_short PORT);

};

