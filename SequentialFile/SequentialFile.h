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

    // identificar cantidad de registros 
    int number_records_file(fstream& archivo){        
        if(archivo.is_open()){
            archivo.seekg(0,ios::end);
            int numrecords=((int)archivo.tellg()-sizeof(int)-sizeof(char))/sizeof(Alumno);
            archivo.seekg(0,ios::end);
            return numrecords;
        }
        return 0;
    }

    int binary_search(fstream& archivo,int l,int r,Alumno a1){
        if (r >= l) {
            int mid = (l + (r - l) / 2);
    
            // If the element is present at the middle
            // itself
            cout<<r<<endl;
            cout<<"mid:"<<mid<<endl;
            Alumno b1=Alumno();    
            archivo.seekg(mid * sizeof(Alumno) + sizeof(long) + sizeof(char), ios::beg);
            archivo.read((char*)& b1, sizeof(Alumno));
            b1.showData();
            if (b1 == a1)
                return mid;

            if (b1>a1)
                //cout<<"mayor"<<endl;
                return binary_search(archivo,l,mid-1,a1);
            
            if(mid>=number_records_file(archivo)){
                return mid;
            }

            return binary_search(archivo,mid+1,r,a1);
            
            /*
            // If element is smaller than mid, then
            // it can only be present in left subarray
            if (arr[mid] > x)
                return binarySearch(arr, l, mid - 1, x);
    
            // Else the element can only be present
            // in right subarray
            return binarySearch(arr, mid + 1, r, x);
            */
        }
        else{
           return l; 
        }


        return -1;
    }

    void find_by_binary(Alumno a1){
        fstream archivo(this->file_name,ios::binary | ios::in);

        cout<<"Posicion: "<<binary_search(archivo,0,number_records_file(archivo),a1)<<endl;
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
            //cout<<"ESTE ES EL VALOR DE NUM RECORDS"<<num_records<<endl;
            //file.seekg(sizeof(temp_next_val)+sizeof(temp_data_type)+sizeof(record.codigo)+sizeof(record.nombre)+sizeof(record.apellidos),ios::beg);
            Alumno oldRecord = Alumno();
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
            file.read((char*)&oldRecord, sizeof(oldRecord));

            while((oldRecord<record).codigo == oldRecord.codigo){
                
            }

            if((oldRecord<record).codigo != oldRecord.codigo){
                file.seekp(0,ios::end);
                file.write((char*)&record, sizeof(record));

            }else{
                cout<<"INSERTAR EL NUEVO"<<endl;
            }

            //file.write(num_re`cords*sizeof(record))
            
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