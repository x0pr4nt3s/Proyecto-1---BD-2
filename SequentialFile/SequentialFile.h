#include "../Entidades/Alumno.h"



class SequentialFile{

private:

    string file_name;
    long num_records = -1;

public:

    SequentialFile(string file_name){
        this->file_name = file_name;
        get_num_records();
    } 

    void writeRecord(Alumno record){

        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";


        long next_val;
        char data_type;

        if(this->num_records==0){
            next_val = 1;
            data_type = 'd';
            file.write((char*)(&next_val), sizeof(next_val));
            file.write((char*)(&data_type), sizeof(data_type));
            file.seekp(sizeof(next_val)+sizeof(data_type),ios::beg);
            file.write((char*) &record, sizeof(Alumno));

            //guardar en formato binario
        }else{
            char codigo_temp[20];
            char codigo_temp2[20];
            char nombre_temp [11];
            char apellidos_temp [20];
            long temp_next_val;
            char temp_data_type[1];

            char carrera_temp [15];

            //cout<<"SIZE OF DE LA COSA "<<sizeof(record.tipo_archivo)<<endl;
            file.seekg(sizeof(temp_next_val)+sizeof(data_type),ios::beg);
            cout<<"ESTE ES EL VALOR DE NUM RECORDS"<<num_records<<endl;
            //file.seekg(sizeof(temp_next_val)+sizeof(temp_data_type)+sizeof(record.codigo)+sizeof(record.nombre)+sizeof(record.apellidos),ios::beg);
            Alumno nuevorecord = Alumno();
            /*
            file.read((char*)&codigo_temp,sizeof(codigo_temp));
            file.read((char*)&nombre_temp,sizeof(nombre_temp));
            file.read((char*)&apellidos_temp,sizeof(apellidos_temp));
            file.read((char*)&carrera_temp,sizeof(carrera_temp));
            file.read((char*)&temp_next_val,sizeof(temp_next_val));
            file.read((char*)&temp_data_type,sizeof(temp_data_type));
            file.read((char*)&codigo_temp2,sizeof(codigo_temp2));

            cout<<"codigo_temp: "<<codigo_temp<<endl;
            cout<<"nombre_temp: "<<nombre_temp<<endl;
            cout<<"apellidos_temp"<<apellidos_temp<<endl;
            cout<<"carrera_temp"<<carrera_temp<<endl;
            cout<<"temp_next_val"<<temp_next_val<<endl;
            cout<<"temp_data_type"<<temp_data_type<<endl;
            cout<<"codigo_temp2: "<<codigo_temp2<<endl;
*/
            file.read((char*)&nuevorecord, sizeof(nuevorecord));
            cout<<nuevorecord.nextval<<endl;
            //file.write(num_re`cords*sizeof(record))
            file.seekp(0,ios::end);

            file.write((char*)&record, sizeof(record));

        }

        //ofstream file(this->file_name, ios::app | ios::binary);
        this->num_records++;

        cout<<num_records<<endl;


        //file.write((char*) &record, sizeof(Alumno));//guardar en formato binario
        file.close();
    }  

    void get_num_records(){
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        file.seekg(0, ios::end);//ubicar cursos al final del archivo
        long size = file.tellg();//cantidad de bytes del archivo    
        size-=(sizeof(long)+sizeof(char));  
        if(size < 0 ){
            this->num_records = 0;
        }else{
            this->num_records =  size / sizeof(Alumno);

        }
        cout<<size<<endl;
  
        file.close();
    }


    vector<Alumno> scanAll(){
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        vector<Alumno> alumnos;
        Alumno record; 

        long header;

        char tipo_archivo;

        file.read((char*)&header, sizeof(header));
        file.read((char*)&tipo_archivo, sizeof(tipo_archivo));

        cout<<header<<" --- "<<tipo_archivo<<endl;


        while(!file.eof()){
            record = Alumno();               
            file.read((char*) &record, sizeof(record));
            if(file.tellg()==-1){
                break;
            }
            alumnos.push_back(record);    

        }
        
        file.close();

        return alumnos;
    } 


};