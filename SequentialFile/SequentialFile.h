#include "../Entidades/Alumno.h"



class SequentialFile{

private:

    string file_name;

public:

    SequentialFile(string file_name) : file_name(file_name){};

    void writeRecord(Alumno record){

        ofstream file(this->file_name, ios::app | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";


        long next_val;
        char data_type;

        if(file.tellp()==0){
            next_val = 1;
            data_type = 'd';
            file.write((char*)(&next_val), sizeof(next_val));
            file.write((char*)(&data_type), sizeof(data_type));
        }


        //ofstream file(this->file_name, ios::app | ios::binary);
        
        file.write((char*) &record, sizeof(Alumno));//guardar en formato binario
        file.close();
    }  



    vector<Alumno> scanAll(){
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        vector<Alumno> alumnos;
        Alumno record; 

        long header;

        char tipo_archivo;

        file.read((char*) & header, sizeof(header));
        //file.seekg(sizeof(header), ios::beg);
        file.read((char*)&tipo_archivo, sizeof(tipo_archivo));

        cout<<header<<" --- "<<tipo_archivo<<endl;


        while(!file.eof()){
            record = Alumno();               
            file.read((char*) &record, sizeof(Alumno));
            if(file.tellg()==-1){
                break;
            }
            alumnos.push_back(record);    

        }
        
        file.close();

        return alumnos;
    } 


};