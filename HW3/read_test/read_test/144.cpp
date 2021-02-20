//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//
////文本文件 讀文件
//void test01()
//{
//	//1.包含頭文件
//
//	//2.創建流對象
//	ifstream ifs;
//	//3.打開文件 必且判斷是否成功
//	ifs.open("test.txt", ios::in);
//
//	if (!ifs.is_open())
//	{
//		cout << "文件打開失敗" << endl;
//	}
//
//	//4.讀數據
//
//	//第一種
//	//char buf[1024] = { 0 };
//	//while (ifs >> buf)
//	//{
//	//	cout << buf << endl;
//	//}
//
//	//第二種
//	//char buf[1024] = { 0 };
//	//while (ifs.getline(buf, sizeof(buf)))
//	//{
//	//	cout << buf << endl;
//	//}
//
//	//第三種
//	string buf;
//	while (getline(ifs,buf))
//	{
//		cout << buf << endl;
//	}
//
//	//第四種
//	//char c;
//	//while ((c = ifs.get()) != EOF)// EOF end of file
//	//{
//	//	cout << c;
//	//}
//
//
//	//5.關閉文件
//	ifs.close();
//}
//
//int main()
//{
//	test01();
//
//	system("pause");
//	return 0;
//}