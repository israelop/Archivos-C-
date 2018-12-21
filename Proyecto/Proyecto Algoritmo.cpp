#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>

using namespace std;

struct usuario{
	char user[20];
	char pass[20];
};

struct Nodo{
	int cont;
	char user[20];
	char pass[20];
	Nodo *siguiente;
};

struct Paciente{
	int cod;
	char nombre[20];
	char apellido[20];
	int tel;
	int num_TerS;
	int num_TerR;
	int num_TerP;
	int dia;
	int mes;
	int ano;
};

void menu();
void crear_usuario();
void usuario();
bool verificar_user(char [],char []);
void crear_arvPaciente(char []);
void eliminar_user();
void mostrar_users();
void insertar_lista(Nodo *&,int,char [],char []);
void mostrar(Nodo *);
void eliminar_lista(Nodo *&);
void elimina_usuario(char []);
void inicio(char []);
void ingreso_paciente(char []);
void direccion(char []);
int codigo_unico();
int cuantos_digitos(int);
void actualizar_paciente(char []);
void modificar_paciente(struct Paciente &);
void reporte(char []);
void eliminar_paciente(char []);
struct Nodo *lista = NULL;

int main(){
	menu();
	return 0;
}

void menu(){
	int opcion;
	do{
		system("cls");
		cout<<"\tBIENVENIDO"<<endl;
		cout<<"1. Iniciar secion\n2.Crear Usuario\n3.Eliminar Usuario\n0.Salir\nSeleccione: ";
		cin>>opcion;
		system("cls");
		switch(opcion){
			case 1:
				usuario();
				cout<<"\n";
				system("pause");
				break;
			case 2: 
				crear_usuario();
				cout<<"\n";
				system("pause");	
				break;
			case 3:
				eliminar_user();
				break;
		}
	}while(opcion != 0);
}

void crear_usuario(){
	ofstream archivo;
	
	archivo.open("usuarios.txt",ios::app | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}
	struct usuario nuevo;
	fflush(stdin);
	cout<<"Usuario: "; cin.getline(nuevo.user,20,'\n');
	cout<<"Contraseña: "; cin.getline(nuevo.pass,20,'\n');
	
	if(verificar_user(nuevo.user,nuevo.pass)){
		cout<<"\nEl usuario ya exite"<<endl;
	}else{
		archivo.write((char *)&nuevo,sizeof(struct usuario));
		crear_arvPaciente(nuevo.user);
		cout<<"\n\nSe creo CORRECTAMENTE"<<endl;
	}
	archivo.close();
}

void crear_arvPaciente(char user[]){
	char direccion[60];
	strcpy(direccion,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
	strcat(direccion,user);
	strcat(direccion,".txt");
	
	ofstream archivoPa;
	
	archivoPa.open(direccion, ios::out | ios::binary);
	
	if(archivoPa.fail()){
		exit(-1);
	}
	archivoPa.close();
}

void usuario(){
	struct usuario intento;
	fflush(stdin);
	cout<<"Usuario: "; cin.getline(intento.user,20,'\n');
	cout<<"Contraseña: "; cin.getline(intento.pass,20,'\n');
	
	if(verificar_user(intento.user,intento.pass)){
		system("cls");
		cout<<"si esta"<<endl;
		inicio(intento.user);
	}else{
		cout<<"contraseña incorrecta"<<endl;	
	}
}

bool verificar_user(char user[],char pass[]) {
	bool verificar;
	
	ifstream archivo;
	
	archivo.open("usuarios.txt", ios::in | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}
	struct usuario ingreso;
	
	while(!archivo.eof()){
		archivo.read((char *)&ingreso,sizeof(struct usuario));
		if((strcmp(ingreso.user,user)==0) && (strcmp(ingreso.pass,pass)==0)){
			verificar = true;
			break;
		}else{
			verificar = false;
		}
	}
	archivo.close();
	
	return verificar;
}

void eliminar_user(){
	int user_delete;
	char contra[20];
	cout<<"\nLista de Usuarios"<<endl;
	mostrar_users();
	cout<<"\nCual desea eliminar?  ";
	cin>>user_delete;
	
	//	Mostrando Lista
	mostrar(lista);
	
	Nodo *aux = lista;
	while(aux != NULL){
		if(aux->cont == user_delete){
			fflush(stdin);
			cout<<"Usuario: "<<aux->user<<endl;
			cout<<"Contraseña: ";
			cin.getline(contra,20,'\n');
			if(strcmp(aux->pass,contra) == 0){
				cout<<"se eliminara xD"<<endl;
				elimina_usuario(aux->user);
			}else{
				cout<<"\nVuelve a intentarlo"<<endl;
			}
		}
		aux = aux->siguiente;
	}

	while(lista != NULL){
		eliminar_lista(lista);
	}
	getch();
}
void elimina_usuario(char user[]){
	struct usuario lectura;
	ifstream archivo;
	
	archivo.open("usuarios.txt", ios::in | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}else{
		ofstream temp;
		
		temp.open("temp.txt", ios::app | ios::binary);
		if(temp.fail()){
			exit(-1);
		}else{
			while(!archivo.eof()){
				archivo.read((char *)&lectura,sizeof(struct usuario));
				if(!archivo.eof()){
					if(strcmp(lectura.user,user) == 0){
					
					}else{
						temp.write((char *)&lectura,sizeof(struct usuario));
					}
				}
			}	
		}
		archivo.close();
		temp.close();
		char direccion[60];
		strcpy(direccion,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
		strcat(direccion,user);
		strcat(direccion,".txt");
		remove(direccion);
		remove("usuarios.txt");
		rename("temp.txt","usuarios.txt");
	}
}

void eliminar_lista(Nodo *&lista){
	Nodo *aux = lista;
	lista = aux->siguiente;
	delete aux;
}

void insertar_lista(Nodo *&lista,int cont,char user[],char pass[]){
	Nodo *nuevo = new Nodo();
	Nodo *aux;
	nuevo->cont = cont;
	strcpy(nuevo->user,user);
	strcpy(nuevo->pass,pass);
	nuevo->siguiente = NULL;
	
	if(lista == NULL){
		lista = nuevo;
	}else{
		aux = lista;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}
}
//Mostrar Lista
void mostrar(Nodo *lista){
	Nodo *aux = new Nodo();
	aux = lista;
	while(aux != NULL){
		cout<<aux->cont<<". "<<aux->user<<endl;
		aux = aux->siguiente;
	}
}

void mostrar_users(){
	int cont = 1;
	ifstream archivo;
	archivo.open("usuarios.txt", ios::in | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}
	
	struct usuario mostrar;
	while(!archivo.eof()){
		archivo.read((char *)&mostrar,sizeof(struct usuario));
		if(!archivo.eof()){
			cout<<"\n\t"<<cont<<". "<<mostrar.user<<endl;
			insertar_lista(lista,cont,mostrar.user,mostrar.pass);
			cont++;	
		}
	}
	archivo.close();
}

void inicio(char user[]){
	int opcion;
	do{
		cout<<"--INICIO--"<<endl;
		cout<<"1. Ingreso de pacientes"<<endl;
		cout<<"2. Actualizar paciente"<<endl;
		cout<<"3. Reporte en pantalla por paciente"<<endl;
		cout<<"4. Eliminar paciente"<<endl;
		cout<<"0. Salir"<<endl;
		cin>>opcion;
		system("cls");
		switch(opcion){
			case 1:
				ingreso_paciente(user);
				break;
			case 2: 
				actualizar_paciente(user);
				break;
			case 3:
				reporte(user);
				cout<<"\n";
				system("pause");
				break;
			case 4:
				eliminar_paciente(user);
			case 0: break;
		}
		system("cls");
	}while(opcion != 0);
}

void ingreso_paciente(char user[]){
	struct Paciente nuevo;
	int op_fecha;
	char dir[60];
	
	strcpy(dir,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
	strcat(dir,user);
	strcat(dir,".txt");
	
	ofstream archivo;
	
	archivo.open(dir,ios::app | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}else{
		nuevo.cod = codigo_unico();
		cout<<"\t INGRESO DE PACIENTES"<<endl;
		fflush(stdin);
		cout<<"Codigo: "<<nuevo.cod<<endl;
		cout<<"Nombre: "; cin.getline(nuevo.nombre,20,'\n');
		cout<<"Apellido:  "; cin.getline(nuevo.apellido,20,'\n');
		do{
			cout<<"Telefono: "; cin>>nuevo.tel;
		}while(cuantos_digitos(nuevo.tel) != 8);
		do{
			cout<<"Terapias Sugeridas: "; cin>>nuevo.num_TerS;
		}while(cuantos_digitos(nuevo.num_TerS) != 1);
		cout<<"Fecha"<<endl;
		do{
			cout<<"\tDia: ";
			cin>>nuevo.dia;
		}while(nuevo.dia > 31);
		do{
			cout<<"\tMes: ";
			cin>>nuevo.mes;
		}while(nuevo.mes > 12);
		do{
			cout<<"\tAño: ";
			cin>>nuevo.ano;
		}while(nuevo.ano < 1900);
		
		nuevo.num_TerR = 0;
		nuevo.num_TerP = 0;
		
		archivo.write((char *)&nuevo,sizeof(struct Paciente));
	}
	archivo.close();
}

int cuantos_digitos(int tel){
	int cont = 0, b = tel/10;
	while( b > 0){
		b = b/10;
		cont++;
	}
	return cont+1;
}

int codigo_unico(){
	int codigo;
	
	ifstream leer_cod;
	leer_cod.open("codigos.txt",ios::in);
	
	if(leer_cod.fail()){
		exit(-1);
	}else{
		leer_cod>>codigo;
		leer_cod.close();
	}

	codigo++;
	
	ofstream escribir;
	escribir.open("codigos.txt",ios::out);
	if(escribir.fail()){
		exit(-1);
	}else{
		escribir<<codigo;
		escribir.close();
	}
	
	return codigo;
}

void actualizar_paciente(char user[]){
	int codigo;
	char dir[60];
	struct Paciente nuevo;
	
	strcpy(dir,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
	strcat(dir,user);
	strcat(dir,".txt");
	
	cout<<"ACTUALIZAR PACIENTE"<<endl;
	cout<<"\nDigite el codigo: ";
	cin>>codigo;
	
	ifstream leer;
	leer.open(dir,ios::in | ios::binary);
	
	if(leer.fail()){
		exit(-1);
	}else{
		ofstream temp;
		temp.open("C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\temp.txt", ios::app | ios::binary);
		
		if(temp.fail()){
			exit(-1);
		}else{
			while(!leer.eof()){
				leer.read((char *)&nuevo,sizeof(struct Paciente));
				if(nuevo.cod == codigo){
					modificar_paciente(nuevo);
					temp.write((char *)&nuevo,sizeof(struct Paciente));		
				}else{
					temp.write((char *)&nuevo,sizeof(struct Paciente));
				}
			}
		}
		temp.close();
	}
	leer.close();
	remove(dir);
	rename("C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\temp.txt",dir);
}

void modificar_paciente(struct Paciente &nuevo){
	int opcion;
	do{
		cout<<" PACIENTE "<<endl;
		cout<<"Codigo: "<<nuevo.cod<<endl;
		cout<<"Nombre: "<<nuevo.nombre<<" "<<nuevo.apellido<<endl;
		cout<<"Telefono: "<<nuevo.tel<<endl;
		cout<<"Terapias Sugeridas: "<<nuevo.num_TerS<<endl;
		cout<<"Terapias Recibidas: "<<nuevo.num_TerR<<endl;
		cout<<"Terapias Pendientes: "<<nuevo.num_TerP<<endl;
		cout<<"\n ->MENU<- "<<endl;
		cout<<"\n1. Nombre"<<endl;
		cout<<"2. Terapias Sugeridas"<<endl;
		cout<<"3. Terapias Recibidas"<<endl;
		cout<<"4. Terapias Pendientes"<<endl;
		cout<<"5. Fecha"<<endl;
		cout<<"0. Salir"<<endl;
		cout<<"Seleccione: ";
		cin>>opcion;
		system("cls");
		switch(opcion){
			case 1:
					cout<<"MODIFICANDO NOMBRE"<<endl;
					cout<<"\nDigite nombre: "; cin>>nuevo.nombre;
					cout<<"Digite apellido: "; cin>>nuevo.apellido;
				break;
			case 2: 
					cout<<"MODIFICANDO TERAPIAS SUGERIDAS"<<endl;
					do{
						cout<<"Digite terapias sugeridas: ";
						cin>>nuevo.num_TerS;
					}while(cuantos_digitos(nuevo.num_TerS) != 1);
					
				break;
			case 3: 
					cout<<"MODIFIANDO TERAPIAS RECIBIDAS"<<endl;
					do{
						cout<<"Digite terapias recibidas: ";
						cin>>nuevo.num_TerR;
					}while((cuantos_digitos(nuevo.num_TerR != 1)) && (nuevo.num_TerR > nuevo.num_TerS));
					nuevo.num_TerP = nuevo.num_TerS - nuevo.num_TerR;
				break;
			case 4: 
					cout<<"MODIFICANDO TERAPIAS PENDIENTES"<<endl;
					do{
						cout<<"Digite terapias pendientes:  "; 
						cin>>nuevo.num_TerP;
					}while((cuantos_digitos(nuevo.num_TerP) != 1) && (nuevo.num_TerP > nuevo.num_TerS));
					nuevo.num_TerR = nuevo.num_TerS - nuevo.num_TerP;
				break;
			case 5: 
				cout<<"MODIFICANDO FECHA "<<endl;
				do{
					cout<<"Dia: ";
					cin>>nuevo.dia;	
				}while(nuevo.dia > 31);
				do{
					cout<<"Mes: ";
					cin>>nuevo.mes;
				}while(nuevo.mes > 12);
				do{
					cout<<"Año: ";
					cin>>nuevo.ano;
				}while(nuevo.ano < 1900);
				break;
			case 0: 
					opcion = 0; 			
				break;
		}
		system("cls");
	}while(opcion != 0);
}

void reporte(char user[]){
	int codigo;
	char dir[60];
	struct Paciente nuevo;
	
	strcpy(dir,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
	strcat(dir,user);
	strcat(dir,".txt");
	
	cout<<"Ingrese el codigo: ";
	cin>>codigo;
	
	ifstream archivo;
	
	archivo.open(dir, ios::in | ios::binary);
	
	if(archivo.fail()){
		exit(-1);
	}else{
		while(!archivo.eof()){
			archivo.read((char *)&nuevo,sizeof(struct Paciente));
			if(nuevo.cod == codigo){
				cout<<"Codigo: "<<nuevo.cod<<endl;
				cout<<"Nombre: "<<nuevo.nombre<<" "<<nuevo.apellido<<endl;
				cout<<"Telefono: "<<nuevo.tel<<endl;
				cout<<"Terapias Sugeridas: "<<nuevo.num_TerS<<endl;
				cout<<"Terapias Recibidas: "<<nuevo.num_TerR<<endl;
				cout<<"Terapias Pendientes: "<<nuevo.num_TerP<<endl;
				break;
			}
		}
		archivo.close();
	}
}

void eliminar_paciente(char user[]){
	int codigo;
	char dir[60],opcion;
	struct Paciente nuevo;
	strcpy(dir,"C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\");
	strcat(dir,user);
	strcat(dir,".txt");
	cout<<"Ingrese codigo: ";
	cin>>codigo;
	ifstream leer;
	leer.open(dir,ios::in | ios::binary);
	if(leer.fail()){
		exit(-1);
	}else{
		ofstream temp;
		temp.open("C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\temp.txt",ios::app | ios::binary);
		if(temp.fail()){
			exit(-1);
		}else{
			while(!leer.eof()){
				leer.read((char *)&nuevo,sizeof(struct Paciente));
				if(nuevo.cod == codigo){
					cout<<"Codigo: "<<nuevo.cod<<endl;
					cout<<"Nombre: "<<nuevo.nombre<<" "<<nuevo.apellido<<endl;
					cout<<"Telefono: "<<nuevo.tel<<endl;
					cout<<"Terapias Sugeridas: "<<nuevo.num_TerS<<endl;
					cout<<"Terapias Recibidas: "<<nuevo.num_TerR<<endl;
					cout<<"Terapias Pendientes: "<<nuevo.num_TerP<<endl;
					cout<<"\nEsta seguro de eliminar al paciente? (S/N)";
					cin>>opcion;
					if((opcion == 'S') || (opcion == 's')){
						cout<<"El paciente a sido eliminado CORRECTAMENTE"<<endl;
					}else{
						temp.write((char *)&nuevo,sizeof(struct Paciente));
						cout<<"Vuelva a intentarlo en otro momento"<<endl;
					}
				}else{
					temp.write((char *)&nuevo,sizeof(struct Paciente));
				}
			}
			temp.close();
		}
	}
	leer.close();
	remove(dir);
	rename("C:\\Users\\Israel\\Desktop\\Proyecto Algoritmo\\Pacientes\\temp.txt",dir);
}
