//#include <iostream>
//#include <fstream>
//#include <cstdlib>
//#include <string>
//#include <iomanip>
//#include <stdlib.h>
//#include <vector>
//#include <sstream>
//
//
//void loadAsciiSTL(std::string path, std::vector<FACET> &facetVec);
//
//int main()
//{
//
//
//}
//
//void Widget::loadAsciiSTL(std::string path, std::vector<FACET> &facetVec)
//{
//	/* ASCII STL 格式 * * * solid * facet normal +0.0000000E+00 +1.0000000E+00 +0.0000000E+00 outer loop vertex +8.0000000E+01 +1.0000000E+02 +6.0000000E+01 vertex +8.0000000E+01 +1.0000000E+02 +0.0000000E+00 vertex +0.0000000E+00 +1.0000000E+02 +0.0000000E+00 endloop endfacet ...... endsolid * 共计7行 * * * * * * */
//
//	FILE* file = fopen(path.c_str(), "r");
//
//	//把文件指针移动到文件末尾,并计算文件大小
//	fseek(file, 0L, SEEK_END);
//	long fileSize = ftell(file);
//
//	fclose(file);
//
//	file = fopen(path.c_str(), "r");
//	//计算文件有多少行
//	int fileLines = 0;
//
//	for (long i = 0; i < fileSize; i++)
//		//一个字符一个字符的读取 当读到换行符说明读到了一行 直到结束
//		if (getc(file) == '\n')
//			fileLines++;
//
//	//计算三角形的个数
//	int triangleCount = 0;
//	//一段三角形的描述是7行 stl文件格式决定的
//	triangleCount = fileLines / 7;
//
//	//文件指针移到文件头
//	rewind(file);
//
//	//跳过文件头 solid
//	while (getc(file) != '\n');
//
//
//	for (auto i = 0; i < triangleCount; i++)
//	{
//		FACET temp;
//
//		//读法向量
//		fscanf(file, "%*s %*s %f %f %f\n", &temp.normal[0], &temp.normal[1], &temp.normal[2]);
//		//跳过 outer loop
//		fscanf(file, "%*s %*s");
//		//读顶点数据
//		fscanf(file, "%*s %f %f %f\n", &temp.vertex[0][0], &temp.vertex[0][1], &temp.vertex[0][2]);
//		fscanf(file, "%*s %f %f %f\n", &temp.vertex[1][0], &temp.vertex[1][1], &temp.vertex[1][2]);
//		fscanf(file, "%*s %f %f %f\n", &temp.vertex[2][0], &temp.vertex[2][1], &temp.vertex[2][2]);
//		//跳过 endloop
//		fscanf(file, "%*s");
//		//跳过 endfacet
//		fscanf(file, "%*s");
//
//		facetVec.push_back(temp);
//	}
//	//跳过文件尾部 endsolid
//	while (getc(file) != '\n');
//
//	fclose(file);
//
//	delete file;
//
//}