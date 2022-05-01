#pragma once

#include "../Entidades/Alumno.h"
#include <fstream>
#include <sstream>

class ParserforEntity1{
public:
    string filename;
    ParserforEntity1(string filename){
    this->filename=filename;    
    }
    vector<Alumno> getDataFile(){
        ifstream file(filename,ios::in);
        if(!file.is_open()) throw "No se pudo abrir el archivo!\n";
        vector<Alumno> alumnos_vec;
        string datos="";
        string word="";

		while(getline(file, datos))
		{ 
            Alumno a1=Alumno();
			stringstream str(datos);
            int cont=0;
			while(getline(str, word, ',')){
                switch(cont){
                    case 0:
                        a1.set_codigo(word);
                        break;
                    case 1:
                        a1.set_nombre(word);
                        break;
                    case 2:
                        a1.set_apellidos(word);
                        break;
                    case 3:
                        a1.set_carrera(word);
                        break;

                }
                cont++;
            }
            alumnos_vec.push_back(a1);
		}
        return alumnos_vec;
    }
};




