#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>


using namespace std;

class Alumno{
private: 
    char codigo [20];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
    long nextval ;
    char tipo_archivo;
    


public:
    Alumno(){}
    Alumno(string codigo,string nombre,string apellidos,string carrera){
        (codigo.size() > 5)?codigo=codigo.substr(0,5):strcpy(this->codigo,codigo.c_str());
        (nombre.size() > 11)?nombre=nombre.substr(0,11):strcpy(this->nombre,nombre.c_str());
        (apellidos.size() > 20)?apellidos=apellidos.substr(0,20):strcpy(this->apellidos,apellidos.c_str());
        (carrera.size() > 15)?carrera=carrera.substr(0,15):strcpy(this->carrera,carrera.c_str());
        this->nextval=0;
    }

    void showData(){
        cout<<"Codigo: "<<this->codigo<<" - "<<"Nombre: "<<this->nombre<<" - "<<"Apellidos: ";
        cout<<this->apellidos<<" - "<<"Carrera: "<<this->carrera<<endl;
    }
    //setters
    void set_nextval(long nextval){ this->nextval=nextval; }
    
    void set_codigo(string codigo){ 
        if(codigo.size() >= 5){ codigo=codigo.substr(0,5);};
        strcpy(this->codigo,codigo.c_str());
    }
    
    void set_nombre(string nombre){ 
        if(nombre.size() >= 11){ nombre=nombre.substr(0,11);};
        strcpy(this->nombre,nombre.c_str());
    }

    void set_apellidos(string apellidos){ 
        if(apellidos.size() >= 20){ apellidos=apellidos.substr(0,20);};
        strcpy(this->apellidos,apellidos.c_str());
    }

    void set_carrera(string carrera){ 
        if(carrera.size() >= 15){ carrera=carrera.substr(0,15);};
        strcpy(this->carrera,carrera.c_str());
    }

    //getters
    int set_nextval(){ return this->nextval; }    

};








