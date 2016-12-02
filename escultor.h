#ifndef escultor_h
#define escultor_h
#include "voxel.h"
#include <string>
#include <list>
#include <algorithm>
using  namespace std;

/*
	Todas as figuras serão compostas de voxels. O voxel é um elemento de volume, semelhante a um pixel, porém no espaço. As classes cubo, esfera, elipsoide, dentre outros, serão todas compostas de diversos voxels.

*/

class imagem;
typedef imagem* ptr_imagem;

class forma
{
protected:
	Voxel_coordenadas centro;
	float red, green, blue, opacity;
	ptr_imagem pointer;
	Voxel_coordenadas max;
	string nome;	
public:
	inline forma();
	virtual ~forma()=0;
	virtual void desenhar()=0;
	virtual void configurar(imagem &I)=0;
	virtual void set_max()=0;
	bool test_nome();
	void nome_figura();
	void test_max();
};

typedef forma* ptr_forma;

/*--------Bloco de código da classe imagem. A classe imagem contém as figuras------*/

class imagem{
private:
	list<ptr_forma> formas;
	Voxel ***grid; //matriz de voxel que armazenará a figura
	int dim_x,dim_y,dim_z; //metade do tamanho de um lado do cubo (voxel)
public:
	imagem();
	imagem(const int x, const int y, const int z);
	~imagem();
	void PUSH_BACK(ptr_forma &F);
	void inserir_voxel(const int x, const int y, const int z, const float red, const float green, const float blue, const float opacity);
	void gerar_OFF();
	bool otimizar(const int &x, const int &y, const int &z);
	void alocar();
	void desalocar();
	void excluir_forma();
	void formatar();
	void check_max();
	void nomes();
	int get_dim_x();
	int get_dim_y();
	int get_dim_z();
	void set_dim_x(const float &x);
	void set_dim_y(const float &y);
	void set_dim_z(const float &z);
};

class caixa: virtual public forma
{
protected:
	float lado;
public:
	caixa();
	~caixa(); 
	caixa(const int &x, const int &y, const int &z, const float &side, imagem &I);
	void desenhar();
	void configurar(imagem &I);
	void set_max();
};

class cone: virtual public forma
{
private:
	float altura;
	float raio_base;

public:
	cone();
	~cone();
	void desenhar();
	void configurar(imagem &I);
	void set_max();
};

class elipsoide: virtual public forma
{
private:
	Voxel_coordenadas raio;
public:
	elipsoide();
	~elipsoide();
	elipsoide(const Voxel_coordenadas &center, Voxel_coordenadas &raios, imagem &I);
	void configurar(imagem &I);
	void desenhar();
	void set_max();	
};


class cilindro: virtual public forma
{
private:
	Voxel_coordenadas raio;
public:
	cilindro();
	~cilindro();
	void desenhar();
	void configurar(imagem &I);
	void set_max();
};


class rosca: virtual public forma
{
protected:
	float RAIO;
	float raio;
	int orientacao;
public:
	rosca();
	~rosca();
	void desenhar();
	void configurar(imagem &I);
	void set_max();
};

class arena: virtual public forma
{
protected:
	float RAIO,raio;
public:
	arena();
	~arena();
	void desenhar();
        void configurar(imagem &I);
        void set_max();
};

#endif	
