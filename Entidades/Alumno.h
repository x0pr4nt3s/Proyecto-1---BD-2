#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>


using namespace std;

class Alumno{
public: 
    char codigo [20];
    char nombre [11];
    char apellidos [20];
    char carrera [15];
    long nextval;
    char tipo_archivo;
    


public:
    Alumno(){
        this->nextval=-1;
        this->tipo_archivo='d';
    }
    Alumno(string codigo,string nombre,string apellidos,string carrera){
        (codigo.size() > 5)?codigo=codigo.substr(0,5):strcpy(this->codigo,codigo.c_str());
        (nombre.size() > 11)?nombre=nombre.substr(0,11):strcpy(this->nombre,nombre.c_str());
        (apellidos.size() > 20)?apellidos=apellidos.substr(0,20):strcpy(this->apellidos,apellidos.c_str());
        (carrera.size() > 15)?carrera=carrera.substr(0,15):strcpy(this->carrera,carrera.c_str());
        this->nextval=-1;
        this->tipo_archivo='d';
    }

    void showData(){
        cout<<"Codigo: "<<this->codigo<<" - "<<"Nombre: "<<this->nombre<<" - "<<"Apellidos: ";
        cout<<this->apellidos<<" - "<<"Carrera: "<<this->carrera<<" - " << "NEXT_VAL: "<<this->nextval<<" - "<<" TIPO ARCHIVO: "<<this->tipo_archivo<<endl;
    }

    void ext_showData(){
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


    string getKey(){
        string s(codigo);
        return s;
    }
    /*
    void set_nextval(string nextval){ 
        if(nextval.size() >= 15){ nextval=nextval.substr(0,15);};
        strcpy(this->nextval,nextval.c_str());
    }*/



    Alumno& operator=(const Alumno& a1){
        this->set_codigo(a1.codigo);
        this->set_nombre(a1.nombre);
        this->set_apellidos(a1.apellidos);
        this->set_carrera(a1.carrera);
        this->set_nombre(a1.nombre);

        return *this;
    }


    //getters

    int set_nextval(){ return this->nextval; }    
    /*
    Alumno operator<(const Alumno& a1){
        Alumno a3;
        string alumno1=this->codigo;
        string alumno2=a1.codigo;
        //cout<<alumno1<<" "<<alumno2<<endl;
        for(int i=0;i<alumno1.size();i++){
            if((int)alumno1[i] < (int)alumno2[i]){
                a3=*this;
                return a3;
            }
            else if((int)alumno1[i] == (int)alumno2[i]){ continue;}
            else{
                a3=a1;
                return a3;
            }
        }
        //int k=(int)a;
        //int l=(int)this;
        a3=*this;
        return a3;
    }*/

    friend bool operator<(const Alumno& a0,const Alumno& a1){
        string alumno1=a0.codigo;
        string alumno2=a1.codigo;
        //cout<<alumno1<<" "<<alumno2<<endl;
        for(int i=0;i<alumno1.size();i++){
            if((int)alumno1[i] > (int)alumno2[i]){
                return false; 
            }
            else if((int)alumno1[i] < (int)alumno2[i]){
                return true;
            }
        }
        return true;
    }


    friend bool operator>(const Alumno& a0,const Alumno& a1){
        string alumno1=a0.codigo;
        string alumno2=a1.codigo;
        //cout<<alumno1<<" "<<alumno2<<endl;
        for(int i=0;i<alumno1.size();i++){
            if((int)alumno1[i] < (int)alumno2[i]){
                return false; 
            }
            else if((int)alumno1[i] > (int)alumno2[i]){
                return true;
            }
        }
        return true;
    }


    friend bool operator==(const Alumno& a0,const Alumno& a1){
        string alumno1=a0.codigo;
        string alumno2=a1.codigo;
        //cout<<alumno1<<" "<<alumno2<<endl;
        for(int i=0;i<alumno1.size();i++){
            if((int)alumno1[i] != (int)alumno2[i]){
                return false; 
            }
        }
        return true;
    }


};





