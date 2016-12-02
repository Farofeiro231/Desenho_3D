#ifndef voxel_h
#define voxel_h
#include <iostream>
using namespace std;




struct Voxel
{
	float r,g,b,o;
	Voxel();
	~Voxel();
	void set_rgbo(const float red, const float green, const float blue, const float opacity);
	float get_red();
	float get_blue();
	float get_green();
	float get_opacity();
};


struct Voxel_coordenadas
{
	float x,y,z;
	Voxel_coordenadas();
	~Voxel_coordenadas();
	void operator=(const Voxel_coordenadas &X);
	float get_x();
	float get_y();
	float get_z();
	Voxel_coordenadas operator+(const Voxel_coordenadas &Y);
	friend istream & operator>>(istream &C, Voxel_coordenadas &V);
	friend ostream & operator<<(ostream &C, Voxel_coordenadas &V);
};




	
#endif
