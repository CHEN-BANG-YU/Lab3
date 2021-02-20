//#include <iostream>
//#include <fstream>
//using namespace std;
//
//
////二進制文件 讀文件
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
//	ifstream ifs;
//
//	//3.打開文件
//	ifs.open("person.txt", ios::in | ios::binary);
//	if (!ifs.is_open())
//	{
//		cout << "文件打開失敗" << endl;
//	}
//
//	//4.寫文件
//	//Person p = { "邦寓", 18 };
//	//ofs.write((const char *)&p, sizeof(Person));
//	Person p;
//	ifs.read((char *)&p, sizeof(Person));
//	cout << "姓名: " << p.m_Name << " 年齡: " << p.m_Age << endl;
//
//	//5.關閉文件
//	ifs.close();
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