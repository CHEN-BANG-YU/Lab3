//#include <iostream>
//#include <fstream>
//using namespace std;
//
//
////�G�i���� Ū���
//class Person
//{
//public:
//	char m_Name[64]; //�m�W
//	int m_Age; //�~��
//};
//
//void test01()
//{
//	//1.�]�t�Y���
//
//	//2.�Ыجy��H
//	ifstream ifs;
//
//	//3.���}���
//	ifs.open("person.txt", ios::in | ios::binary);
//	if (!ifs.is_open())
//	{
//		cout << "��󥴶}����" << endl;
//	}
//
//	//4.�g���
//	//Person p = { "���J", 18 };
//	//ofs.write((const char *)&p, sizeof(Person));
//	Person p;
//	ifs.read((char *)&p, sizeof(Person));
//	cout << "�m�W: " << p.m_Name << " �~��: " << p.m_Age << endl;
//
//	//5.�������
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