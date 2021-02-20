#pragma once
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
#include<Eigen/Dense>
#include<Eigen/Sparse>
#include <vector>

using namespace glm;
using namespace Eigen;
using namespace std;

#define HEIGHT 500 //the height of the show window
#define WIDTH 500 //the WIDTH of the show window
#define PI 3.1415926
Vector3d  Eye_coordinates;
Vector3d  Obj_coordinates;
Vector3d z_axis_eye_direction;

class Cube
{
public:

#pragma region Obj to world
Matrix4d ObjtoWorld_matrix(double x_position, double y_position, double z_position)
{
	Matrix4d  ObjtoWorld_result;
	ObjtoWorld_result.setIdentity();
	ObjtoWorld_result.block(0, 3, 1, 1) << x_position;
	ObjtoWorld_result.block(1, 3, 1, 1) << y_position;
	ObjtoWorld_result.block(2, 3, 1, 1) << z_position;
	//cout << ObjtoWorld_result << endl;
	return ObjtoWorld_result;
}
#pragma endregion

#pragma region world to Eye
Matrix4d  WorldtoEye_matrix(double X_eye_coordinates, double Y_eye_coordinates, double Z_eye_coordinates, double X_obj_coordinates, double Y_obj_coordinates, double Z_obj_coordinates)
{
	Matrix4d  WorldtoEye_result;
	WorldtoEye_result.setIdentity();
	//eye position (20,10,10)
	Eye_coordinates.x() = X_eye_coordinates;
	Eye_coordinates.y() = Y_eye_coordinates;
	Eye_coordinates.z() = Z_eye_coordinates;
	//Obj position (10,0,0)
	Obj_coordinates.x() = X_obj_coordinates;
	Obj_coordinates.y() = Y_obj_coordinates;
	Obj_coordinates.z() = Z_obj_coordinates;


    z_axis_eye_direction = -(Obj_coordinates - Eye_coordinates);//z�b�V�q�C�����������ȡA��z�b�b�᭱�n�[�t���C 
	z_axis_eye_direction.normalize();//z�b���W��
	Vector3d Up_vector(0, 1, 0);  //�O�by��V�A���F�D�Xx�V�q�ݭncross

	Vector3d x_axis_eye_direction = Up_vector.cross(z_axis_eye_direction);//x�b�V�q�C y�b cross z�b
	x_axis_eye_direction.normalize();//x�b���W��

	Vector3d y_axis_eye_direction = z_axis_eye_direction.cross(x_axis_eye_direction);//y�b�V�q

	Matrix3d RRR;
	RRR << x_axis_eye_direction,
		y_axis_eye_direction,
		z_axis_eye_direction;
	//	cout << RRR << endl<<endl;
	//	cout << RRR.inverse()*RRR << endl << endl;
	//	cout << RRR.transpose()*RRR << endl << endl;

	Vector3d R_T_displacement;
	R_T_displacement = -RRR.transpose()*Eye_coordinates;

	WorldtoEye_result.block(0, 0, 3, 3) = RRR.transpose();
	WorldtoEye_result.block(0, 3, 3, 1) = R_T_displacement;

	return  WorldtoEye_result;
	//	cout << WorldtoEye_result << endl;
}
#pragma endregion

#pragma region Eye to Perspective
Matrix4d  EyetoPerspective_matrix(double alpha, double Hither, double Yon)
{
	double A, B;
	A = Yon / (Yon - Hither);
	B = -(Yon*Hither) / (Yon - Hither);
	double AR_aspect_ratio = WIDTH / HEIGHT;
	/*Matrix4d  EyetoPerspective_result;
	EyetoPerspective_result.setIdentity();*/
	MatrixXd  EyetoPerspective_result = MatrixXd::Identity(4, 4);
	EyetoPerspective_result.block(0, 0, 1, 1) << 1 / tan(alpha / 2);
	EyetoPerspective_result.block(1, 1, 1, 1) << AR_aspect_ratio * (1 / tan(alpha / 2));
	EyetoPerspective_result.block(2, 2, 2, 2) << -A, B,
												-1, 0;

	return EyetoPerspective_result;
	//cout << EyetoPerspective_result << endl;
}
#pragma endregion


#pragma region Perspective to View Port
Matrix4d  PerspectivetoViewport_matrix()
{
	//Matrix4d PerspectivetoViewport_result;
	//PerspectivetoViewport_result.setIdentity();//�]�w���x�}4X4

	MatrixXd  PerspectivetoViewport_result = MatrixXd::Identity(4, 4);//�]�w���x�}4X4
	Vector3d  x_axis_view_direction(WIDTH / 2, 0, 0);
	Vector3d  y_axis_view_direction(0, HEIGHT / 2, 0);//z���ε��A�ù�2D
	Vector3d  z_axis_view_direction(0, 0, 1);
	Vector3d  w_axis_view_direction(WIDTH / 2, HEIGHT / 2, 0);//w�`��

	PerspectivetoViewport_result.block(0, 0, 3, 1) = x_axis_view_direction;
	PerspectivetoViewport_result.block(0, 1, 3, 1) = y_axis_view_direction;
	PerspectivetoViewport_result.block(0, 2, 3, 1) = z_axis_view_direction;
	PerspectivetoViewport_result.block(0, 3, 3, 1) = w_axis_view_direction;

	return PerspectivetoViewport_result;
	//cout << PerspectivetoViewport_result << endl;
}
#pragma endregion


private:
	/*Vector4d P[10];	*/

	
	
};

