#pragma once
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

class Lab3
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

	Vector3d  Eye_position;
	Vector3d  P_coi;
	Vector3d z_eye_direction_see_to_coi;
#pragma region Eye to world 
	// (50,50,50, 0,0,0 )
	//double X_eye_coordinates, double Y_eye_coordinates, double Z_eye_coordinates
	Matrix4d EyetoWorld_matrix(Vector3d Eye_position, double X_coi, double Y_coi, double Z_coi)//HW3 才用到
	{
		Matrix4d EyetoWorld_result;
		EyetoWorld_result.setIdentity();
		//
		//Eye_position.x() = X_eye_coordinates;
		//Eye_position.y() = Y_eye_coordinates;
		//Eye_position.z() = Z_eye_coordinates;
		//
		P_coi.x() = X_coi;
		P_coi.y() = Y_coi;
		P_coi.z() = Z_coi;

		z_eye_direction_see_to_coi = -(P_coi - Eye_position);
		z_eye_direction_see_to_coi.normalize();//z軸正規化

		Vector3d Up_vector(0, 1, 0);

		Vector3d x_eye_direction_see_to_coi = Up_vector.cross(z_eye_direction_see_to_coi);//x軸向量。 y軸 cross z軸
		x_eye_direction_see_to_coi.normalize();//x軸正規化

		Vector3d y_eye_direction_see_to_coi = z_eye_direction_see_to_coi.cross(x_eye_direction_see_to_coi);//y軸向量

		Matrix3d RRR;
		RRR << x_eye_direction_see_to_coi,
			y_eye_direction_see_to_coi,
			z_eye_direction_see_to_coi;

		Vector3d W_E_displacement;
		Vector3d World_xyz = { 0,0,0 };
		W_E_displacement = Eye_position - World_xyz;

		EyetoWorld_result.block(0, 0, 3, 3) = RRR;
		EyetoWorld_result.block(0, 3, 3, 1) = W_E_displacement;
		return EyetoWorld_result;
	}

#pragma endregion



};

