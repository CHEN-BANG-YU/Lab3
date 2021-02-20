#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <fstream>
#include <iostream>
#include <array>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <vector>
#include <algorithm>

//#include "Header.h"
#include "ReadFile.h"
#include "Lab3_Transform_Matrix.h"

using namespace glm;
using namespace Eigen;
using namespace std;

#define HEIGHT 500 //the height of the show window
#define WIDTH 500 //the WIDTH of the show window
#define PI 3.1415926
 

void init();
void display();
Object obj;
Lab3 C3;

Vector3d Rd_calculation(int x, int y, Lab3 &C3);
void sphere(int x, int y, Vector3d Rd_unitvector, double &t_compare);
double simplified_illumination_model(Vector3d normalvector, Vector3d Ray_result);

void RayCasting_mesh(int x, int y, Object obj, Vector3d Rd_unitvector, double &t_compare);
Object O_to_W(double x_position, double y_position, double z_position, Object obj);

#pragma region Cube input
Object Cube_1 = Modle("Cube.txt");
#pragma endregion

#pragma region QuadrangularCone input
Object QuadrangularCone = Modle("Quadrangularcone.txt");
#pragma endregion

#pragma region Cylinder input
//Object Cylinder = Modle("Cylinder.txt");
#pragma endregion
//Object Twisted_Vase_Basic = Modle("Twisted_Vase_Basic.txt");


double ray_R[WIDTH][HEIGHT] = { 0 };//Red，初始化
double ray_G[WIDTH][HEIGHT] = { 0 };
double ray_B[WIDTH][HEIGHT] = { 0 };

void RayCasting_Background_Color(float Red, float Green, float Blue)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			glColor3f(ray_R[i][j] = Red, ray_G[i][j] = Green, ray_B[i][j] = Blue);
			glVertex2d(i, j);
		}
	}
}
Vector3d Eye_position = { 50, 50, 50 };//眼睛方向
Vector3d Ray_result_mesh, Rd_unitvector;
Vector4d Rd_Ray_transform_world;
double f = 10;//z
double Alpha = 20;
double Aspect_ratio = WIDTH / HEIGHT;
double h = 2 * f *tan(Alpha*PI / (2*180));//y
double w = 2 * f *tan(Alpha*PI / (2 * 180))*Aspect_ratio;//x
double delta_h = h/ HEIGHT;//y
double delta_w = w / WIDTH;//x

Object O_to_W(double x_position,double y_position, double z_position, Object obj)//物件移動函式
{
	for (int i = 0; i < obj.poly.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			obj.poly[i].vertex[j] = C3.ObjtoWorld_matrix(x_position, y_position, z_position) * (obj.poly[i].vertex[j]);
		}
	}
	return obj;
}


Vector3d Rd_calculation(int x, int y, Lab3 &C3)
{
	Vector4d Ray = { (x - WIDTH / 2) * delta_w, (y - HEIGHT / 2) * delta_h, -f, 0 };
	Ray.normalize();
	//EyetoWorld_matrix(Vector3d Eye_position,double X_coi,double Y_coi,double Z_coi)
	Rd_Ray_transform_world = C3.EyetoWorld_matrix(Eye_position, 0, 0, 0) * Ray;
	Rd_unitvector = Rd_Ray_transform_world.head(3).normalized();
	return  Rd_unitvector;
}

Vector3d Ray_result_sphere, sphere_normalvector;

void sphere(int x,int y, Vector3d Rd_unitvector,double &t_compare)
{
	double L_scalar;
	Vector3d L_vector, Eye_to_ballCenter, D;
	double D_scalar, a;
	Sphere s1;
	s1.center = {0,0,0};
	s1.radius = 5.0;

	Eye_to_ballCenter = s1.center - Eye_position;
	L_scalar = Eye_to_ballCenter.dot(Rd_unitvector);//純量
	L_vector = L_scalar * Rd_unitvector;//向量

	D = Eye_to_ballCenter - L_vector;//鄰邊 = 斜邊 - 底邊
	D_scalar = sqrt(pow(D.x(), 2) + pow(D.y(), 2) + pow(D.z(), 2));//鄰邊取大小


	if (D_scalar < s1.radius)//小於圓半徑，才放入buffer
	{
		a = sqrt(pow(s1.radius, 2) - (D_scalar, 2));//三角形底邊 純量
		double sphere_t = sqrt(pow(L_vector.x(), 2) + pow(L_vector.y(), 2) + pow(L_vector.z(), 2)) - a;//射線射到物體最短距離t (純量)
		Ray_result_sphere = Eye_position + sphere_t * Rd_unitvector;//碰到球射線

		if (t_compare >= sphere_t)
		{
			t_compare = sphere_t;
			//Ray_result_sphere = Eye_position + t_compare * Rd_unitvector;//碰到球射線
			sphere_normalvector = (Ray_result_sphere - s1.center).normalized(); //球法向量
			double photomask = simplified_illumination_model(sphere_normalvector, Ray_result_sphere);
			if (photomask == 1)
			{
				ray_R[x][y] = 1.0;
				ray_G[x][y] = 1.0;
				ray_B[x][y] = 1.0;
			}
			else {
				ray_R[x][y] = 0.0;
				ray_G[x][y] = photomask;
				ray_B[x][y] = 0.0;
			}
		}
	}
}

double Ka = 0.4 ,Ia=0.8;
double Kd = 0.6, I;
double Ks = 0.9, Is;
Vector3d Lightsource = { 50.0, 50.0, -50.0 };//光源方向
Vector3d Light, Mirror_Light, Eye_vector, H;
Vector3d id_normal;
double simplified_illumination_model(Vector3d normalvector, Vector3d Ray_result)
{

	id_normal = normalvector;
	id_normal.normalize();
	Light = Lightsource - Ray_result;//光源 減 每個有在圓內點
	Light.normalize();
	double result = id_normal.dot(Light);

	Mirror_Light = Lightsource - Ray_result;
	Eye_vector = Eye_position - Ray_result;
	H = Mirror_Light + Eye_vector;
	H.normalize();
	
	Is = pow(H.dot(normalvector.normalized()), 900);//次方越大，打到物體的反光圈越小

	I = std::min(1.0, Ka*Ia + Kd * std::max(0.0, result) + Ks * Is);//如果大於1，取最小值1，I介於0~1之間
	return I;	
}

void RayCasting_mesh(int x, int y, Object obj, Vector3d Rd_unitvector, double &t_compare)
{
	Vector3d triangleMesh_normal, triangleMesh_vertex;
	double d;
	double t;
	for (int a = 0; a < obj.poly.size(); a++)
	{
		double front_or_back_judge = Rd_unitvector.dot(obj.poly[a].normal);
		if (front_or_back_judge > 0)//大於0在背面，則不做
		{
			continue;
		}
		int condition = 0;
		triangleMesh_normal = obj.poly[a].normal;
		triangleMesh_vertex = obj.poly[a].vertex[0].head(3);

		d = triangleMesh_normal.dot(triangleMesh_vertex);
		t = (d - triangleMesh_normal.dot(Eye_position)) / triangleMesh_normal.dot(Rd_unitvector);

		Ray_result_sphere = Eye_position + t * Rd_unitvector;//向量

		for (int b = 0; b < 3; b++)
		{
			Vector3d A1, A2;
			Vector3d p0, p1, p2;
			p0 = obj.poly[a].vertex[b].head(3);//當前點
			p1 = obj.poly[a].vertex[(b + 1) % 3].head(3);//下一個點
			p2 = obj.poly[a].vertex[(b + 2) % 3].head(3);//另外組合 下一個點

			A1 = (p1 - p0).cross(Ray_result_sphere - p0);
			A2 = (Ray_result_sphere - p0).cross(p2 - p0);
			double A3;
			A3 = A1.dot(A2);
			if (A3 >= 0)//判斷是否在三角形內
			{
				condition++;//b要跑3次，都成立才能存到 buffer
			}
		}
		if (condition == 3 )
		{
			Ray_result_sphere = Eye_position + t * Rd_unitvector;//向量
			if (t_compare > t)//比較深度
			{
				t_compare = t;//更新到=>最小值
				
				double photomask = simplified_illumination_model(triangleMesh_normal, Ray_result_sphere);
				if (photomask == 1)
				{
					ray_R[x][y] = 1.0;
					ray_G[x][y] = 1.0;
					ray_B[x][y] = 1.0;
				}
				else {
					ray_R[x][y] = photomask * obj.poly[a].color.x();
					ray_G[x][y] = photomask * obj.poly[a].color.y();
					ray_B[x][y] = photomask * obj.poly[a].color.z();
				}
			}
		}
	}
}





int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);

	glutCreateWindow("OpenGL 3D View");
	init();

	RayCasting_Background_Color(1.0, 1.0, 1.0);//R G B

	for (int i = 0; i < Cube_1.poly.size(); i++)//遍歷，初始化顏色poly
	{
		Cube_1.poly[i].color.x() = 0.0;
		Cube_1.poly[i].color.y() = 0.0;
		Cube_1.poly[i].color.z() = 0.0;
	}

	for (int i = 0; i < QuadrangularCone.poly.size(); i++)//遍歷，初始化顏色poly
	{
		QuadrangularCone.poly[i].color.x() = 0.0;
		QuadrangularCone.poly[i].color.y() = 0.0;
		QuadrangularCone.poly[i].color.z() = 1.0;
	}

	QuadrangularCone = O_to_W(0.0, 0.0, 0.0, QuadrangularCone);//物件移動函式(x,y,z)
	Cube_1 = O_to_W(0.0, 0.0, 0.0, Cube_1);//物件移動函式(x,y,z)

	for (int x = 0; x < WIDTH; x++)//把所有Z-buffer存好的值繪出，遍歷所有pixel
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			//O_to_W(10, 0, 0);
			double t_compare = 1000.0;//深度比較初始化
			Rd_calculation(x, y, C3);
			//sphere
			//mesh
			sphere(x, y, Rd_unitvector, t_compare);
			RayCasting_mesh(x, y, Cube_1, Rd_unitvector, t_compare);
			RayCasting_mesh(x, y, QuadrangularCone, Rd_unitvector, t_compare);
		}
	}

	glutDisplayFunc(display);
	glutMainLoop();
	system("pause");
	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//the background color
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

}

Vector3d normal[7];


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.6, 1.0, 0);//紅線畫
	glBegin(GL_POINTS);

	for (int x = 0; x < WIDTH; x++)//把所有Z-buffer存好的值繪出，遍歷所有pixel
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			glColor3f(ray_R[x][y], ray_G[x][y], ray_B[x][y]);
			glVertex2d(x, y);
		}
	}

	glEnd();//end of drawlines
	glFlush();
}
