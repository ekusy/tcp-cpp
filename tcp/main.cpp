#include <iostream>
#include <string>
#include "tcp.h"
#define DEBUG
#define IP "127.0.0.1"
#define PORT 5000



inline int charSize(){}

int main()
{
	
	/*
	if (!test.Connect(IP, PORT)){
		debugPrint("サーバへの接続に失敗しました");
		return -1;
	}
	*/
	char data[64] = "テストデータ送信";
	//test.Send(data, sizeof(data));
	
	int size;
	int count = 0;
	tcp test;
	test.setAddress(IP, PORT);
	while (count != 100){
		std::string s(std::to_string(count) + ';');
		std::string buffer;
		char buff[64] = {};
		const char *str = s.c_str();
		int str_size = s.size();
		test.Send(str, str_size,IP,PORT);
		std::cout << "count = " << count << std::endl;
 		//Sleep(60);
		
		if (test.Recv(buff, sizeof(buff), &size)){
			nullDelete(buff);
			buffer = buff;
			debugPrint(buff);
			//std::cout << buffer << std::endl;

		}
		
		count++;
	}
	
	return 0;

}