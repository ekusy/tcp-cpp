#include <iostream>
#include <string>
#include "tcp.h"
#define DEBUG
#define IP "127.0.0.1"
#define PORT 10000



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
	while (count != 10){
		std::string s(std::to_string(count) + ';');
		std::string buffer;
		char buff[64] = {};
		const char *str = s.c_str();
		int str_size = s.size();
		test.Send(str, str_size);
		if (test.Recv(buff, sizeof(buff), &size)){
			nullDelete(buff);
			buffer = buff;
			debugPrint(buff);
			//std::cout << buffer << std::endl;
			count++;
		}
	}
	
	return 0;

}