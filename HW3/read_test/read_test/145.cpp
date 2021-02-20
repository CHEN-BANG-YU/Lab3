//#include <iostream>
//#include <fstream>
//using namespace std;
//
//
////二進制文件 寫文件
//class Person
//{
//public:
//	char m_Name[64]; //姓名
//	int m_Age; //年齡
//};
//
//void test01()
//{
//	//1.包含頭文件
//
//	//2.創建流對象
//	ofstream ofs("person.txt", ios::out | ios::binary);;
//
//	//3.打開文件
//	//ofs.open("person.txt", ios::out | ios::binary);
//	
//	//4.寫文件
//	Person p = { "邦寓", 18 };
//	ofs.write((const char *)&p, sizeof(Person));
//
//	//5.關閉文件
//	ofs.close();
//
//}
//
//
//int main()
//{
//	test01();
//
//	system("pause");
//	return 0;
//}