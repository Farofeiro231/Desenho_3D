#include "voxel.h"
#include <iostream>

using namespace std;

Voxel::Voxel(): r(0), g(0), b(0), o(0) {}
Voxel::~Voxel() {}

Voxel_coordenadas::Voxel_coordenadas(): x(0), y(0), z(0) {}
Voxel_coordenadas::~Voxel_coordenadas() {}

void Voxel_coordenadas::operator=(const Voxel_coordenadas &X)
{
	x=X.x;
	y=X.y;
	z=X.z;
}

float Voxel_coordenadas::get_x(){return x;}
float Voxel_coordenadas::get_y(){return y;}
float Voxel_coordenadas::get_z(){return z;}

void Voxel::set_rgbo(const float red, const float green, const float blue, const float opacity)
{
	r=red;
	g=green;
	b=blue;
	o=opacity;
}

float Voxel::get_red(){return r;}
float Voxel::get_blue(){return b;}
float Voxel::get_green(){return g;}
float Voxel::get_opacity(){return o;}


ostream & operator<<(ostream &C, Voxel_coordenadas &V)
{
	C<<"Coordenada x: "<<V.x<<endl;
	C<<"Coordenada y: "<<V.y<<endl;
	C<<"Coordenada z: "<<V.z<<endl;
	
	return C;
}


istream &operator>>(istream &C, Voxel_coordenadas &V)
{
        cout<<"Informe a coordenada x: ";
        cin>>V.x;
        cout<<endl;
        cout<<"Informe a coordenada y: ";
        cin>>V.y;
        cout<<endl;
        cout<<"Informe a coordenada z: ";
        cin>>V.z;
        cout<<endl;
        return C;
}

Voxel_coordenadas Voxel_coordenadas::operator+(const Voxel_coordenadas &Y)
{
	Voxel_coordenadas soma;
	soma.x=x+Y.x;
	soma.y=y+Y.y;
	soma.z=z+Y.z;
	
	return soma;
}
