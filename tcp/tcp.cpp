#include "tcp.h"
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 

tcp::tcp()//:m_DstSocket(INVALID_SOCKET)
{
	// Windows の場合
	//initialize();
}


tcp::~tcp()
{
	finalize();

}

void tcp::initialize(){

	m_DstSocket = INVALID_SOCKET;
	// Windows の場合
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);

}

void tcp::finalize(){
	if (m_DstSocket != INVALID_SOCKET)
		closesocket(m_DstSocket);
	// Windows でのソケットの終了
	WSACleanup();

}

void tcp::setAddress(const char* IP, u_short PORT){
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_port = htons(PORT);
	dstAddr.sin_family = AF_INET;
	//dstAddr.sin_addr.s_addr = inet_addr(IP);
	inet_pton(AF_INET, IP, &dstAddr.sin_addr.s_addr);
}

// 接続
bool tcp::Connect(const char* IP, u_short PORT)
{
	setAddress(IP, PORT);

	// ソケットの生成
	m_DstSocket = socket(AF_INET, SOCK_STREAM, 0);

	// 接続
	if (connect(m_DstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr))
		== SOCKET_ERROR){
		return false;
	}
	// ソケットを非同期モードにする
	u_long val = 1;
	ioctlsocket(m_DstSocket, FIONBIO, &val);
	return true;
}

bool tcp::Connect()
{
	//setAddress(IP, PORT);
	// ソケットの生成
	m_DstSocket = socket(AF_INET, SOCK_STREAM, 0);

	// 接続
	if (connect(m_DstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr))
		== SOCKET_ERROR){
		return false;
	}
	// ソケットを非同期モードにする
	u_long val = 1;
	ioctlsocket(m_DstSocket, FIONBIO, &val);
	return true;
}

// 受信
RECVSTATUS tcp::Recv(char* pData, int DataSize, int *pRecvSize)
{

	int n = recv(m_DstSocket, pData, DataSize, 0);
	if (n < 1) {
		// データが来ていない
		if (WSAGetLastError() == WSAEWOULDBLOCK) {
			return RECV_STILL;
			// 切断orエラー
		}
		else {
			return RECV_FAILED;
		}
	}
	*pRecvSize = n;	// 受信データ長取得
	return RECV_SUCCESSED;
}

// 送信
bool tcp::Send(const char* pData, int DataSize)
{
	if (Connect()){
		//パケットの送信
		if (send(m_DstSocket, pData, DataSize, 0) == SOCKET_ERROR){
			return false;
		}
	}
	else{
		debugPrint("connect error");
		false;
	}

	return true;
}

bool tcp::Send(const char* pData, int DataSize, const char* IP, u_short PORT)
{
	bool success = false;
	initialize();
	if (Connect(IP, PORT)){
		//パケットの送信
		if (send(m_DstSocket, pData, DataSize, 0) == SOCKET_ERROR){
			debugPrint("send error");
		}
		else{
			success = true;
		}
	}
	else{
		debugPrint("connect2 error");
		
	}

	finalize();
	return success;
}
