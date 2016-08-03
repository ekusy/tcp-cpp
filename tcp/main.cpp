#include <iostream>
#include "tcp.h"
#define DEBUG
#define IP "127.0.0.1"
#define PORT 10000

inline void debugPrint(char* message){
//#ifndef DEBUG
	std::cout << message << std::endl;
//#endif
}

inline int charSize(){}

int main()
{
	tcp test;

	if (!test.Connect(IP, PORT)){
		debugPrint("サーバへの接続に失敗しました");
		return -1;
	}
	char data[64] = "テストデータ送信";
	//test.Send(data, sizeof(data));
	
	int size;
	int count = 0;
	while (count != 100){
		char s[10];
		char buff[64];
		itoa(count, s, 10);
		test.Send(s, sizeof(s));
		if (test.Recv(buff, sizeof(buff), &size)){
			debugPrint(buff);
			count++;
		}
	}
	return 0;

}