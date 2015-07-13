#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
struct Agenda{
	char Nombre[50];
	char Correo[50];
	char Direccion[50];
	char Numero[9];
	Agenda *sgte;
};
struct Cola{
	struct Agenda *delante;
	struct Agenda *atras;
};

void Inicializa(Cola &);
void Ingreso(Cola &,int);
void Muestra(Cola);
void Buscar(int,Cola &,char []);
void Actualizar(Cola &q, char []);
void Visualizar(Cola); 
int main() {
	Cola q;
	Inicializa(q);
	int op;
	int n;
	do{
		system("cls");
		cout<<"..:: MENU DE OPCIONES ::.."<<endl;
		cout<<"1. REGISTRO DE PERSONAS (COLAS)"<<endl;
		cout<<"2. MUESTRA DE PERSONAS REGISTRADAS"<<endl;
		cout<<"3. BUSCAR Y MOSTRAR PERSONAS"<<endl;
		cout<<"4. ACTUALIZAR PERSONA"<<endl;
		cout<<"5. VISUALIZAR REGISTROS"<<endl;
		cout<<"Opcion: ";
		cin>>op;
		switch(op){
		case 1:
			cout<<endl;
			cout<<endl;
			cout<<"CANTIDAD DE REGISTROS: ";
			cin>>n;
			Ingreso(q,n);
			cout<<endl;
			system("pause");
			break;
		case 2:
			Muestra(q);
			cout<<endl;
			system("pause");
			break;
		case 3:
			char pal[50];
			cout<<endl;
			cout<<endl;
			cout<<"NOMBRE DE LA PERSONA A BUSCAR: ";
			cin>>pal;
			Buscar(n,q,pal);
			system("pause");
			break;
		case 4:
			char Dato[50];
			cout<<endl;
			cout<<endl;
			cout<<"NOMBRE DE LA PERSONA PARA ACTUALIZAR: ";
			cin>>Dato;
			Actualizar(q,Dato);
			cout<<endl;
			system("pause");
			break;
		case 5:
			cout<<endl;
			cout<<endl;
			cout<<"PERSONAS EN LA AGENDA: ";
			cout<<endl;
			Visualizar(q);
			system("pause");
			break;
		}
	}while(op!=6);
	
}
void Inicializa(struct Cola &q){
	q.delante=NULL;
	q.atras=NULL;
}
void Ingreso(Cola &q,int n){
	Agenda *p;
	FILE *Fichero;
	Fichero=fopen("E:\\Final\\Directorio.txt","wt");
	char Nomb[50];
	int i;
	for(i=0;i<n;i++){
		p=new Agenda;
		cout<<"NOMBRE CONTACTO ("<<i+1<<"): ";
		cin.ignore();
		cin.getline(p->Nombre,50);
		cout<<"CORREO CONTACTO ("<<i+1<<"): ";
		cin.getline(p->Correo,50);
		cout<<"TELEFONO CONTACTO ("<<i+1<<"): ";
		cin>>p->Numero;
		cout<<"INGRESA DESCRIPCION ("<<i+1<<"): ";
		cin.ignore();
		cin.getline(p->Direccion,50);
		
		p->sgte=NULL;
		
		if(q.delante==NULL){
			q.delante=p;
			strcpy(Nomb,p->Nombre);
			strcat(Nomb,".txt");
			Fichero=fopen(Nomb,"wb");
			fwrite(p,sizeof(struct Cola),1,Fichero);
		}else
			q.atras->sgte=p;
		q.atras=p;
	}fclose(Fichero);
}
void Muestra(Cola q){
	Agenda *p;
	p=q.delante;
	while(p!=NULL){
		cout<<endl;
		cout<<endl;
		cout<<"PERSONAS REGISTRADAS ACTUALMENTE :"<<endl;
		cout<<"NOMBRE CONTACTO: "<<p->Nombre<<endl;
		cout<<"CORREO CONTACTO: "<<p->Correo<<endl;
		cout<<"TELEFONO CONTACTO: "<<p->Numero<<endl;
		cout<<"INGRESA DESCRIPCION: "<<p->Direccion<<endl;
		p=p->sgte;
	}
}
void Buscar(int n, Cola &q,char pal[]){
	int i;
	Agenda *p;
	p=q.delante;
	FILE *Fichero;
	int band=0;
	for(i=0;i<n;i++){
		if(strcmp(p->Nombre,pal)==0){
			cout<<"Nombre: "<<p->Nombre<<endl;
			cout<<"Correo: "<<p->Correo<<endl;
			cout<<"Numero: "<<p->Numero<<endl;
			cout<<"Direccion: "<<p->Direccion<<endl;
			Fichero=fopen(pal,"wb");
			fwrite(p,sizeof(struct Cola),1,Fichero);
			strcpy(pal,p->Nombre);
			fclose(Fichero);
			band++;
			break;
		}
		p=p->sgte;
	}
	if(band==0)
		cout<<"ESTA PERSONA NO ESTA EN LIBERTA DE CONTACTOS";
}
void Actualizar(Cola &q, char Dato[]){
	
	Agenda *p;
	p=q.delante;

	while(p!=NULL){
		if (strcmp(p->Nombre, Dato)==0) {
			cin.ignore();
			cout<<"Nombre: ";
			cin.ignore();
			cin.getline(p->Nombre,50);
			cout<<endl;
			cout<<"Correo electronico: ";
			cin.getline(p->Correo,50);
			cout<<endl;
			cout<<"Numero: ";
			cin>>p->Numero;
			cout<<endl;
			cout<<"Ingresa Direccion: ";
			cin.ignore();
			cin.getline(p->Direccion,50);
			cout<<endl;
		}
		p=p->sgte;
	}
	
}
void Visualizar(Cola q){
	char Nomb[50];
	Agenda *p;
	FILE *Fichero;
	Fichero=fopen("E:\\Final\\Directorio.txt","r");
	p=q.delante;
	fread(p,sizeof(struct Agenda),1,Fichero);
	while(p!=NULL){
		Fichero=fopen(Nomb,"wb");
		cout<<endl;
		cout<<p->Nombre<<endl;
		p=p->sgte;
		fread(p,sizeof(struct Agenda),1,Fichero);
	}fclose(Fichero);
}
