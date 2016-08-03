#include "tcp.h"
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 

tcp::tcp():m_DstSocket(INVALID_SOCKET)
{
	// Windows の場合
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
}


tcp::~tcp()
{
	if (m_DstSocket != INVALID_SOCKET)
		closesocket(m_DstSocket);
	// Windows でのソケットの終了
	WSACleanup();

}

// 接続
bool tcp::Connect(const char* IP, u_short PORT)
{
	struct addrinfo hints, *res0, *res;
	// sockaddr_in 構造体のセット
	struct sockaddr_in dstAddr;
	memset(&dstAddr, 0, sizeof(dstAddr));
	dstAddr.sin_port = htons(PORT);
	dstAddr.sin_family = AF_INET;
	//dstAddr.sin_addr.s_addr = inet_addr(IP);
	int n = inet_pton(AF_INET, "127.0.0.1", &dstAddr.sin_addr.s_addr);
	//std::cout << "getaddrinfo()" << std::endl;
	
	

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
	//パケットの送信
	if (send(m_DstSocket, pData, DataSize, 0) == SOCKET_ERROR){
		return false;
	}

	return true;
}
