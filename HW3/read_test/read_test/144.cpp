//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//
////�奻��� Ū���
//void test01()
//{
//	//1.�]�t�Y���
//
//	//2.�Ыجy��H
//	ifstream ifs;
//	//3.���}��� ���B�P�_�O�_���\
//	ifs.open("test.txt", ios::in);
//
//	if (!ifs.is_open())
//	{
//		cout << "��󥴶}����" << endl;
//	}
//
//	//4.Ū�ƾ�
//
//	//�Ĥ@��
//	//char buf[1024] = { 0 };
//	//while (ifs >> buf)
//	//{
//	//	cout << buf << endl;
//	//}
//
//	//�ĤG��
//	//char buf[1024] = { 0 };
//	//while (ifs.getline(buf, sizeof(buf)))
//	//{
//	//	cout << buf << endl;
//	//}
//
//	//�ĤT��
//	string buf;
//	while (getline(ifs,buf))
//	{
//		cout << buf << endl;
//	}
//
//	//�ĥ|��
//	//char c;
//	//while ((c = ifs.get()) != EOF)// EOF end of file
//	//{
//	//	cout << c;
//	//}
//
//
//	//5.�������
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