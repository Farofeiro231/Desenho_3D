#include "escultor.h"
#include "voxel.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

#define PI 3.14159265


inline forma::forma() {}

forma::~forma() {}

void forma::test_max()
{
	if(max.x>pointer->get_dim_x()){pointer->set_dim_x(max.x);}
	if(max.y>pointer->get_dim_y()){pointer->set_dim_y(max.y);}
	if(max.z>pointer->get_dim_z()){pointer->set_dim_z(max.z);}
}

bool forma::test_nome() //verifica se o nome informado é igual ao nome da figura
{
	string name;
	cout<<"Informe o nome da figura que deseja deletar: ";
	cin>>name;
	
	return name==nome;
}

void forma::nome_figura(){cout<<nome<<endl;}

bool test_nome(ptr_forma &F){return (F->test_nome());}

void imagem::PUSH_BACK(ptr_forma &F){formas.push_back(F);}

int imagem::get_dim_x(){return dim_x;}
int imagem::get_dim_y(){return dim_y;}
int imagem::get_dim_z(){return dim_z;}
void imagem::set_dim_x(const float &x){dim_x=x+2;}
void imagem::set_dim_y(const float &y){dim_y=y+2;}
void imagem::set_dim_z(const float &z){dim_z=z+2;}

void imagem::inserir_voxel(const int x, const int y, const int z, const float red, const float green, const float blue, const float opacity)
{
	grid[x][y][z].set_rgbo(red, green, blue, opacity);
}

void imagem::gerar_OFF()
{
	cout<<"Gerando offf..."<<endl;
	FILE *ID;
	ID=fopen("text.off", "w");
	int visivel=0;	
	
	for(int i=0;i<dim_x;i++)
{
		for(int j=0;j<dim_y;j++)
{
			for(int k=0;k<dim_z;k++)
{
		if(grid[i][j][k].get_opacity()!=0 && otimizar(i,j,k)==1)visivel++;
}
}
}	
	fprintf(ID,"OFF\n%d %d %d", visivel*8, visivel*6, 0);
	for(int i=0;i<dim_x;i++)
{
		for(int j=0;j<dim_y;j++)
{
			for(int k=0;k<dim_z;k++)	//Escrita dos vértices no arquivo txt
{
	if(grid[i][j][k].get_opacity()!=0 && otimizar(i,j,k)==1)
{
	//cout<<"\n"<<i<<" "<<j<<" "<<k;
	fprintf(ID, "\n%d %d %d", i, j, k);
	//cout<<"\n"<<i<<" "<<j<<" "<<k+1;
	fprintf(ID, "\n%d %d %d", i, j, k+1);
	//cout<<"\n"<<i<<" "<<j+1<<" "<<k+1;
	fprintf(ID, "\n%d %d %d", i, j+1, k+1);
	//cout<<"\n"<<i<<" "<<j+1<<" "<<k;
	fprintf(ID, "\n%d %d %d", i, j+1, k);
	//cout<<"\n"<<i+1<<" "<<j+1<<" "<<k;
	fprintf(ID, "\n%d %d %d", i+1, j+1, k);
	//cout<<"\n"<<i+1<<" "<<j+1<<" "<<k+1;
	fprintf(ID, "\n%d %d %d", i+1, j+1, k+1);
	//cout<<"\n"<<i+1<<" "<<j<<" "<<k+1;
	fprintf(ID, "\n%d %d %d", i+1, j, k+1);
	//cout<<"\n"<<i+1<<" "<<j<<" "<<k;
	fprintf(ID, "\n%d %d %d", i+1, j, k);
}
}
}
}

	long int contador=0;
	for(int i=0;i<dim_x;i++)
{
		for(int j=0;j<dim_y;j++)
{
			for(int k=0;k<dim_z;k++)
{
	if(grid[i][j][k].get_opacity()!=0 && otimizar(i,j,k)==1)
{
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador, contador+3, contador+4, contador+7, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity());
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador+4, contador+5,contador+6, contador+7, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity()); 
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador+1, contador+6,contador+5, contador+2, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity());
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador+1, contador+2,contador+3, contador, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity());
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador+2, contador+5,contador+4, contador+3, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity());
	fprintf(ID, "\n4 %li %li %li %li %.1f %.1f %.1f %.1f", contador+1, contador,contador+7, contador+6, grid[i][j][k].get_red(), grid[i][j][k].get_green(), grid[i][j][k].get_blue(), grid[i][j][k].get_opacity());
	contador+=8;
}
}
}
}		 
	fclose(ID);
}

imagem::imagem()
{
        dim_x=0;
        dim_y=0;
        dim_z=0;
        grid=NULL;
}



imagem::imagem(const int x, const int y, const int z)
{
	dim_x=x;
        dim_y=y;
        dim_z=z;
        int i,j,k;
        grid=new Voxel **[dim_x];

        for(i=0;i<dim_x;i++)
{
        grid[i]= new Voxel *[dim_y];
{	
                for(j=0;j<dim_y;j++)
{
		grid[i][j] = new Voxel[dim_z];
		
			for(k=0;k<dim_z;k++)
{
			grid[i][j][k].set_rgbo(0.0,0.0,0.0,0.0);
}
}
}
}
}


void imagem::alocar()
{
	cout<<"Alocando..."<<endl;	
	int i,j;
	int k;
	grid=new Voxel **[dim_x];
	grid[0]=new Voxel*[(dim_x)*(dim_y)];
	for(i=1;i<dim_x;i++)grid[i]=&grid[0][i*dim_y];	
	grid[0][0]=new Voxel[(dim_x*dim_y*dim_z)];
	for(i=0;i<dim_x;i++)
{
		for(j=0;j<dim_y;j++)
{
	k=i*dim_z*dim_y+j*dim_z;
	grid[i][j]=&grid[0][0][k];
}
}	
}


imagem::~imagem()
{
        if(grid!=NULL)
{
        delete[] grid[0][0];
	delete[] grid[0];
        delete[] grid;
}
}


void imagem::desalocar()
{
	if(grid!=NULL)
{
        delete[] grid[0][0];
	delete[] grid[0];
        delete[] grid;
}
}


void check_dim(ptr_forma &F){F->test_max();}

void imagem::check_max()
{
	for_each(formas.begin(), formas.end(), check_dim);
}

void nomez(ptr_forma &F){F->nome_figura();}

void imagem::nomes()	//metodo para imprimir o nome das formas na lista
{
	for_each(formas.begin(), formas.end(),nomez); 
}

void imagem::excluir_forma()	//o metodo teste nome verifica se um nome de forma inserido pelo usuário é igual ao nome de alguma das formas na lista
{
	formas.remove_if(test_nome);
}
 
bool imagem::otimizar(const int &x, const int &y, const int &z)
{
	int i,j,k;
	bool test=true;
	for(int i=-1;i<=1;i++)
{
		for(int j=-1;j<=1;j++)
{	
			for(int k=-1;k<=1;k++)
{
	if(grid[x+i][y+j][z+k].get_opacity()==0) return test;	
}	
}
}
	return !test;
}

void desenho(ptr_forma &F)
{
	F->desenhar();
}

void imagem::formatar()
{
	cout<<"Gerando imagem..."<<endl;
	for_each(formas.begin(), formas.end(), desenho);
}

caixa::caixa(): lado(0) 
{
	red=1;
	green=1;
	blue=1;
	opacity=0;
	Voxel_coordenadas();
	pointer=NULL;
}

inline caixa::~caixa(){if(pointer!=NULL)delete[] pointer;}

caixa::caixa(const int &x, const int &y, const int &z, const float &side, imagem &I)
{
	centro.x=x;
	centro.y=y;
	centro.z=z;
	red=1;
	green=1;
	blue=1;
	opacity=1;
	this->lado=side;
	pointer=&I;
	desenhar();	
}

void caixa::desenhar()
{
        int i,j,k; 
        for(i=centro.x-lado; i<=centro.x+lado; i++)
{
                for(j=centro.y-lado;j<=centro.y+lado; j++)
{
                        for(k=centro.z-lado; k<=centro.z+lado;k++)
{
                pointer->inserir_voxel(i,j,k, red, green, blue, opacity);
}
}
}
}

void caixa::configurar(imagem &I)
{
	pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
	cin>>nome;
        cout<<"Configurando o centro..."<<endl;
        cin>>this->centro;
        cout<<"Configurando o lado_metade..."<<endl;
        cin>>lado;
        cout<<"Vermelho..."<<endl;
        do{cin>>this->red;}while(this->red<0 && this->red>1);
        cout<<"Verde..."<<endl;
        do{cin>>this->green;}while(this->green<0 && this->green>1);
        cout<<"Azul..."<<endl;
        do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
        cout<<"Opacidade..."<<endl;
        do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
        set_max();
}


void caixa::set_max()
{
	max.x=centro.x+lado;
	max.y=centro.y+lado;
	max.z=centro.z+lado;
}

elipsoide::elipsoide()
{
	raio.x=0;
	raio.y=0;
	raio.z=0;
	red=1;
	green=1;
	blue=1;
	opacity=1;
	pointer=NULL;
}

elipsoide::~elipsoide(){if(pointer!=NULL)delete[] pointer;}

elipsoide::elipsoide(const Voxel_coordenadas &center, Voxel_coordenadas &raios, imagem &I)
{
	centro=center;
	red=1;
	green=1;
	blue=1;
	opacity=1;
	raio=raios;
	pointer=&I;
	desenhar();
}

void elipsoide::desenhar()
{
        cout<<"Entrei no metodo desenhar..."<<endl;
	int i,j,k;
	double x,y,z;
	for(i=(centro.x-raio.x)+1;i<centro.x+raio.x;i++)
{
		for(j=(centro.y-raio.y)+1;j<centro.y+raio.y;j++)
{
			for(k=(centro.z-raio.z)+1;k<centro.z+raio.z;k++)
{
	x=((centro.x-i)*1.0/raio.x);
	y=((centro.y-j)*1.0/raio.y);
	z=((centro.z-k)*1.0/raio.z);
	if(x*x + y*y + z*z<=1.0)
{
	pointer->inserir_voxel(i,j,k,red,green,blue,opacity);
}
}
}	
}
}

void elipsoide::set_max()
 {
         max=centro+raio;
         if(centro.x-raio.x<=0)
 {
         centro.x+=-(centro.x-raio.x)+1;
         set_max();
 }
         if(centro.y-raio.y<=0)
 {
         centro.y+=-(centro.y-raio.y)+1;
         set_max();
 }
         if(centro.z-raio.z<=0)
 {
         centro.z+=-(centro.z-raio.z)+1;
         set_max();
 }
}


cone::cone()
{
	altura=0;
	raio_base=0;
	pointer=NULL;
	centro.x=0;
	centro.y=0;
	centro.z=0;
	red=0;
	green=0;
	blue=0;
	opacity=0;
	max.x=0;
	max.y=0;
	max.z=0;
}

cone::~cone(){}

void cone::set_max()
{
	cout<<"Entrei no set_max()..."<<endl;
        max.x=centro.x+raio_base;
        max.y=centro.y+raio_base;
        max.z=centro.z+altura;

        if(centro.x-raio_base<=0)
{       centro.x+=-(centro.x-raio_base)+1;
        set_max();
}
        if(centro.y-raio_base<=0)
{       centro.y+=-(centro.y-raio_base)+1;
        set_max();
}
}

void cone::desenhar()
{
	int i;
	double z,y,teta;
	for(i=centro.x;i<centro.x+altura;i++)
{
		for(teta=1/(2*raio_base);teta<2*PI;teta+=1/(2*raio_base))
{
	y=(int)(centro.y+((centro.x+altura-i)/altura)*raio_base*cos(teta));
	z=(int)(centro.z+((centro.x+altura-i)/altura)*raio_base*sin(teta));
	pointer->inserir_voxel(i,y,z,red,green,blue,opacity);
}
}
}



void cone::configurar(imagem &I)
{
	pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
        cin>>nome;
	cout<<"Configurando o centro..."<<endl;
	cin>>this->centro;
	cout<<"Configurando a altura..."<<endl;
	cin>>altura;
	cout<<"Configurando o raio da base..."<<endl;
	cin>>raio_base;
	cout<<"Vermelho..."<<endl;
	do{cin>>this->red;}while(this->red<0 && this->red>1);
	cout<<"Verde..."<<endl;
	do{cin>>this->green;}while(this->green<0 && this->green>1);
	cout<<"Azul..."<<endl;
	do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
	cout<<"Opacidade..."<<endl;
	do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
	set_max();
}





void elipsoide::configurar(imagem &I)
{
	pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
        cin>>nome;
	cout<<"Configurando o centro..."<<endl;
	cin>>this->centro;
	cout<<"Configurando o raio..."<<endl;
	cin>>raio;
	cout<<"Vermelho..."<<endl;
	do{cin>>this->red;}while(this->red<0 && this->red>1);
	cout<<"Verde..."<<endl;
	do{cin>>this->green;}while(this->green<0 && this->green>1);
	cout<<"Azul..."<<endl;
	do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
	cout<<"Opacidade..."<<endl;
	do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
	set_max();
}


cilindro::cilindro()
{
	red=0;
	green=0;
	blue=0;
	opacity=0;
	raio.x=0;
	raio.y=0;
	raio.z=0;
	pointer=NULL;
	centro.x=0;
	centro.y=0;
	centro.z=0;
}

cilindro::~cilindro()
{
}

void cilindro::set_max()
{
	cout<<"Entrei no set_max()..."<<endl;
        max.x=centro.x+raio.x;
        max.y=centro.y+raio.y;
        max.z=centro.z+raio.z;

        if(centro.x-raio.x<=0)
{       centro.x+=-(centro.x-raio.x)+1;
        set_max();
}
        if(centro.y-raio.y<=0)
{       centro.y+=-(centro.y-raio.y)+1;
        set_max();
}
        if(centro.z-raio.z<=0)
{       centro.z+=-(centro.z-raio.z)+1;
        set_max();
}

}

void cilindro::configurar(imagem &I)
{
	pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
        cin>>nome;
        cout<<"Configurando o centro..."<<endl;
        cin>>this->centro;
        cout<<"Configurando o raio..."<<endl;
        cin>>raio;
        cout<<"Vermelho..."<<endl;
        do{cin>>this->red;}while(this->red<0 && this->red>1);
        cout<<"Verde..."<<endl;
        do{cin>>this->green;}while(this->green<0 && this->green>1);
        cout<<"Azul..."<<endl;
        do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
        cout<<"Opacidade..."<<endl;
        do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
	set_max();
}
	
void cilindro::desenhar()
{
	int i,j,k;
	
	for(i=centro.x-raio.x+1;i<centro.x+raio.x;i++)
{
		for(j=centro.y-raio.y+1;j<centro.y+raio.y;j++)
{
			for(k=centro.z-raio.z;k<centro.z+raio.z;k++)
{
	if(pow((1.0*(i-centro.x)/raio.x), 2.0) + pow((1.0*(j-centro.y)/raio.y),2.0)<=1)
{
	pointer->inserir_voxel(i,j,k,red,green,blue,opacity);
}
}
}
}
}


rosca::rosca()
{
	red=0;
        green=0;
        blue=0;
        opacity=0;
	RAIO=0;
	raio=0;
	orientacao=0;
        pointer=NULL;
        centro.x=0;
        centro.y=0;
        centro.z=0;
}

rosca::~rosca()
{
}

void rosca::configurar(imagem &I)
{
	pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
        cin>>nome;
        cout<<"Configurando o centro..."<<endl;
        cin>>this->centro;
        cout<<"Configurando o raio maior..."<<endl;
        cin>>RAIO;
	cout<<"Configurando o raio menor..."<<endl;
	cin>>raio;
        cout<<"Configurando a orientacao..."<<endl;
	cin>>orientacao;
	cout<<"Vermelho..."<<endl;
        do{cin>>this->red;}while(this->red<0 && this->red>1);
        cout<<"Verde..."<<endl;
        do{cin>>this->green;}while(this->green<0 && this->green>1);
        cout<<"Azul..."<<endl;
        do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
        cout<<"Opacidade..."<<endl;
        do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
	set_max();
}

void rosca::set_max()
{
	cout<<"Entrei no set_max()..."<<endl;
	max.x=centro.x+raio+RAIO;
	max.y=centro.y+RAIO+raio;
	max.z=centro.z+raio;

	if(centro.x-RAIO-raio<=0)
{	centro.x+=-(centro.x-RAIO-raio)+1;
	set_max();
}	
	if(centro.y-RAIO-raio<=0)
{	centro.y+=-(centro.y-RAIO-raio)+1;
	set_max();
}	
	if(centro.z-raio<=0)
{	centro.z+=-(centro.z-raio)+1;
	set_max();
}
	
		
}

void rosca::desenhar()
{
	double teta=0, phi=0;
	
	//x=(R+rcos(phi))cos(teta)
	//y=(R+rcos(phi))sen(teta)
	//z=(rsen(phi))

	if(orientacao==1)
{
	for(teta=0+(1/(2*RAIO));teta<2*PI;teta+=1/(2*RAIO))
{
		for(phi=0+(1/(2*raio));phi<2*PI;phi+=1/(2*raio))
{
	pointer->inserir_voxel(int(centro.x+raio*sin(phi)),int(centro.y+((RAIO+raio*cos(phi)))*cos(teta)),int(centro.z+(((RAIO+raio*cos(phi)))*sin(teta))), red, green, blue, opacity);
}
}
}
	if(orientacao==0)
{	
	for(teta=0+(1/(2*RAIO));teta<2*PI;teta+=1/(2*RAIO))
{
        	for(phi=0+(1/(2*raio));phi<2*PI;phi+=1/(2*raio))
{
	pointer->inserir_voxel(int(centro.x+((RAIO+raio*cos(phi)))*sin(teta)),int(centro.y+raio*sin(phi)),int(centro.z+(((RAIO+raio*cos(phi)))*cos(teta))), red, green, blue, opacity);	

//int(centro.y+raio*sin(phi))
}
}
}

}

arena::arena()
{
	red=0;
        green=0;
        blue=0;
        opacity=0;
        RAIO=0;
        raio=0;
        pointer=NULL;
        centro.x=0;
        centro.y=0;
        centro.z=0;
}

arena::~arena(){}

void arena::desenhar()
{
	double teta,z;
	for(teta=0+(1/(2*RAIO));teta<=2*PI;teta+=1/(2*RAIO))
{
	cout<<"Teta: "<<teta<<" Teta: "<<teta<<endl;	
		for(z=-raio;z<=raio;z++)
{
	cout<<"O valor de z e: "<<z<<endl;
	pointer->inserir_voxel(int(centro.x+((RAIO+z*cos(PI/4)))*cos(teta)), int(centro.y+(((RAIO+z*cos(PI/4)))*sin(teta))), int(centro.z+z), red, green, blue, opacity);

}

}

}

void arena::set_max()
{
        cout<<"Entrei no set_max()..."<<endl;
        max.x=centro.x+raio+RAIO;
        max.y=centro.y+RAIO+raio;
        max.z=centro.z+raio;

        if(centro.x-RAIO-raio<=0)
{       centro.x+=-(centro.x-RAIO-raio)+1;
        set_max();
}
        if(centro.y-RAIO-raio<=0)
{       centro.y+=-(centro.y-RAIO-raio)+1;
        set_max();
}
        if(centro.z-raio<=0)
{       centro.z+=-(centro.z-raio)+1;
        set_max();
}


}


void arena::configurar(imagem &I)
{
        pointer=&I;
	cout<<"Informe o nome da figura..."<<endl;
        cin>>nome;
        cout<<"Configurando o centro..."<<endl;
        cin>>this->centro;
        cout<<"Configurando o raio maior..."<<endl;
        cin>>RAIO;
        cout<<"Configurando o raio menor..."<<endl;
        cin>>raio;
        cout<<"Vermelho..."<<endl;
        do{cin>>this->red;}while(this->red<0 && this->red>1);
        cout<<"Verde..."<<endl;
        do{cin>>this->green;}while(this->green<0 && this->green>1);
        cout<<"Azul..."<<endl;
        do{cin>>this->blue;}while(this->blue<0 && this->blue>1);
        cout<<"Opacidade..."<<endl;
        do{cin>>this->opacity;}while(this->opacity<0 && this->opacity>1);
        set_max();
}
