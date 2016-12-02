#include <iostream>
#include "voxel.h"
#include "escultor.h"
using namespace std;


int main()
{
	int opcao;
	Voxel_coordenadas center, raios;
	imagem figura;
do{
	cout<<"Dimensao x: "<<figura.get_dim_x()<<endl;
	cout<<"Dimensao y: "<<figura.get_dim_y()<<endl;
	cout<<"Dimensao z: "<<figura.get_dim_z()<<endl;
	
	cout<<"MENUS:"<<endl;
	cout<<"1 - Inserir elipsoide"<<endl;
	cout<<"2 - Inserir Cilindro"<<endl;
	cout<<"3 - Inserir Rosca"<<endl;
	cout<<"4 - Inserir Arena"<<endl;
	cout<<"5 - Inserir Caixa"<<endl;
	cout<<"6 - Inserir Cone"<<endl;
	cout<<"7 - Alocar matriz"<<endl;
	cout<<"8 - Gerar Figura"<<endl;
	cout<<"9 - Gerar .OFF"<<endl;
	cout<<"10 - Lista de figuras"<<endl;
	cout<<"11 - Excluir Figura"<<endl;
	cout<<"12 - Sair"<<endl;
do{
	cin>>opcao;
}while(opcao<1 && opcao >12);

	switch(opcao)
{
	case 1:
	ptr_forma E; 
	E=new elipsoide;
	E->configurar(figura);
	figura.PUSH_BACK(E);
	break;
	
	case 2:
	ptr_forma C;
	C=new cilindro;
	C->configurar(figura);
	figura.PUSH_BACK(C);
	break;
	
	case 3:
	ptr_forma R;
	R=new rosca;
	R->configurar(figura);
	figura.PUSH_BACK(R);
	break;
 	
	case 4:
        ptr_forma RM;
        RM= new arena;
        RM->configurar(figura);
        figura.PUSH_BACK(RM);
        break;
	
	case 5:
        ptr_forma CX;
        CX= new caixa;
        CX->configurar(figura);
        figura.PUSH_BACK(CX);
        break;


	case 6:
	ptr_forma marquinhos;
	marquinhos=new cone;
	marquinhos->configurar(figura);
	figura.PUSH_BACK(marquinhos);
	break;
	
	case 7:
	figura.check_max();
	figura.desalocar();
	figura.alocar();
	break;

	case 8:
	figura.formatar();
	break;

	case 9:
	figura.gerar_OFF();
	break;

	case 10:
	figura.nomes();
	break;
	
	case 11:
	figura.excluir_forma();
	break;

}
}while(opcao!=12);	
	return 0;
}
