#include "../Entidades/Alumno.h"



class SequentialFile{

private:

    string file_name;
    string auxiliar_data;
    long num_records = -1;
    long aux_num_records = -1;

public:

    SequentialFile(string file_name,string auxiliar_data){
        this->file_name = file_name;
        this->auxiliar_data = auxiliar_data;
        this->num_records = get_num_records(file_name);
        this->aux_num_records = get_num_records(auxiliar_data);
    } 

    // identificar cantidad de registros 
    int number_records_file(fstream& archivo){        
        if(archivo.is_open()){
            archivo.seekg(0,ios::end);
            int numrecords=((int)archivo.tellg()-sizeof(int)-sizeof(char))/sizeof(Alumno);
            archivo.seekg(0,ios::end);
            if(numrecords<0){return 0;}

            this->num_records = num_records;
            return numrecords;
        }
        return 0;
    }



    int binary_search(fstream& archivo,int l,int r,Alumno a1){
        if (r >= l) {
            int mid = (l + (r - l) / 2);
    
            //cout<<"Actual: ["<<l<<","<<r<<"]"<<endl;
            Alumno b1=Alumno();    
            archivo.seekg(mid * sizeof(Alumno) + sizeof(long) + sizeof(char), ios::beg);
            archivo.read((char*)& b1, sizeof(Alumno));
            //b1.showData();
            if (b1 == a1)
                return mid;

            if (b1>a1)
                return binary_search(archivo,l,mid-1,a1);
            
            if(mid>=number_records_file(archivo)){
                return mid;
            }


            return binary_search(archivo,mid+1,r,a1);

        }
        else{
           return l; 
        }

        return -2;
    }

    int find_by_binary(Alumno a1){
        fstream archivo(this->file_name,ios::binary | ios::in);
        return binary_search(archivo,0,number_records_file(archivo),a1);
        //cout<<"LA POSICION A INSERTAR ES"<<binary_search(archivo,0,number_records_file(archivo),a1)<<endl;
    }

    
    // SEARCH:
    
    int bsearch(fstream& archivo,int l,int r,string a1){
        if (r >= l) {
            int mid = (l + (r - l) / 2);
            cout<<"Actual: ["<<l<<","<<r<<"]"<<endl;
            Alumno b1=Alumno();    
            archivo.seekg(mid * sizeof(Alumno) + sizeof(long) + sizeof(char), ios::beg);
            archivo.read((char*)& b1, sizeof(Alumno));

            string keyb1=b1.get_codigo();
            if (keyb1 == a1 && b1.get_nextvalue()!=-2)
                return mid;

            if (keyb1>a1)
                return bsearch(archivo,l,mid-1,a1);
            
            if(mid>=number_records_file(archivo)){
                return mid;
            }
            return bsearch(archivo,mid+1,r,a1);
            
        }
        else{
           return l*(-1); 
        }

        return -1;
    }
   
    
    Alumno search(string key){
        //long nextval;
        //char data_type;
        fstream archivo(this->file_name,ios::binary | ios::in);
        fstream aux_file(this->auxiliar_data, ios::in | ios::binary);

        Alumno al1=Alumno();
        //int postion=bsearch(archivo,0,number_records_file(archivo),key)
        int posicion_obj=bsearch(archivo,0,number_records_file(archivo),key);
        if(posicion_obj < 0){
            int lectura=posicion_obj*-1;
            lectura--;
            cout<<lectura<<endl;
            archivo.seekg(sizeof(Alumno)*(lectura)+sizeof(long)+sizeof(char),ios::beg);
            archivo.read((char*)&al1, sizeof(Alumno));
            // Valida de que si es 0 el codigo que recibe que pregunte si es igual o no al objeto que buscamos 
            // si es lo devolvemos y si no lo es vamos a buscar al archivo Auxiliar.
            if(posicion_obj==0 && al1.get_codigo()==key){ 
                return al1;
            }            
            while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                al1.showData();
                long new_pos=al1.get_nextvalue()-1;
                //cout<<new_pos<<endl;
                //cout<<"Posicion:"<<new_pos<<endl;
                aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                aux_file.read((char*)&al1, sizeof(Alumno));
                /*if(al1.get_codigo()>key){ // Si el objeto que buscamos es menor nos quedamos ahi y devolvemos
                    //cout<<"Key es mayor"<<endl;
                    al1.showData();
                    return al1;
                }*/
                if(al1.get_codigo()==key){
                    //cout<<"AHHH"<<endl;
                    al1.showData();
                    return al1;
                }
            }
            Alumno al2=Alumno();// Retornar usuario vacio
            return al2;                    
        }
        else{
        al1=Alumno();
        archivo.seekg(sizeof(Alumno)*(posicion_obj)+sizeof(long)+sizeof(char),ios::beg);
        archivo.read((char*)&al1, sizeof(Alumno));
        cout<<al1.get_codigo()<<endl;
        if( al1.get_codigo()==key){
            cout<<"Se encontro el objeto"<<endl;
        }else cout<<"No se encontro el Objeto"<<endl;

        //const char* s=al1.get_codigo();
        /*std::string str(s);
        */
        }
        archivo.close();
        aux_file.close();
        return al1;
    }






    void writeRecord(Alumno record){

        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";


        long nextval;
        char data_type;

        if(this->num_records==0){
            nextval = 1;
            data_type = 'd';
            file.write((char*)(&nextval), sizeof(nextval));
            file.write((char*)(&data_type), sizeof(data_type));
            file.seekp(sizeof(nextval)+sizeof(data_type),ios::beg);
            file.write((char*) &record, sizeof(Alumno));
            this->num_records++;

            //guardar en formato binario
        }else{
   
            //cout<<"DEBO INSERTARLO EN: "<<find_by_binary(record)<<endl;;
            int posicion = find_by_binary(record);
            Alumno oldRecord = Alumno();

            //cout<<"SIZE OF DE LA COSA "<<sizeof(record.tipo_archivo)<<endl;
            file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
            file.read((char*)&oldRecord, sizeof(oldRecord));
            if(oldRecord.nextval==-1 ){ //si no hay nada delante o debajo de el inserto y tambien no hay auxiliar
                int new_pos = posicion+1;
                if(new_pos>this->num_records){
                    oldRecord.nextval=new_pos;
                }

                file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
                file.write((char*)&oldRecord, sizeof(oldRecord));
                file.seekg(sizeof(Alumno)*(posicion)+sizeof(nextval)+sizeof(data_type),ios::beg);
                file.write((char*)&record, sizeof(record));
                this->num_records++;

            }else{
                fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);

                if(oldRecord.tipo_archivo=='d'){
                    record.nextval=oldRecord.nextval;
                    aux_file.seekg(sizeof(Alumno)*(aux_num_records++));
                    aux_file.write((char*)&record,sizeof(record));
                    oldRecord.nextval=aux_num_records;
                    oldRecord.tipo_archivo='a';
                    file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
                    file.write((char*)&oldRecord, sizeof(oldRecord));

                }
                //fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);
                else{
                    Alumno record_temp = Alumno();
                    long temp_next = oldRecord.nextval;
                    aux_file.seekg((oldRecord.nextval-1)*sizeof(Alumno));
                    aux_file.read((char*)&oldRecord, sizeof(oldRecord));
                    while(oldRecord.tipo_archivo!='d'){
                        if(oldRecord < record){
                            break;
                        }
                        temp_next = oldRecord.nextval;
                        aux_file.seekg(sizeof((oldRecord.nextval-1)*sizeof(Alumno)));
                    }
                                            cout<<"ENTRO"<<endl;
                    cout<<oldRecord.codigo<<endl;

                    record.nextval=oldRecord.nextval;
                    record.tipo_archivo=oldRecord.tipo_archivo;
                    oldRecord.nextval=++aux_num_records;
                    oldRecord.tipo_archivo='a';
                    aux_file.seekg((temp_next-1)*sizeof(Alumno));

                    aux_file.write((char*)&oldRecord,sizeof(oldRecord));
                    aux_file.seekg(sizeof(Alumno)*(aux_num_records-1));
                    aux_file.write((char*)&record,sizeof(record));
 
                    
                }
                aux_file.close();

            }


            //cout<<"ESTE ES EL VALOR DE NUM RECORDS"<<num_records<<endl;
            //file.seekg(sizeof(temp_next_val)+sizeof(temp_data_type)+sizeof(record.codigo)+sizeof(record.nombre)+sizeof(record.apellidos),ios::beg);
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



            if((oldRecord<record).codigo != oldRecord.codigo){
                file.seekp(0,ios::end);
                file.write((char*)&record, sizeof(record));

            }else{
                cout<<"INSERTAR EL NUEVO"<<endl;
            }
*/

            //file.write(num_re`cords*sizeof(record))

            //file.read((char*)&oldRecord, sizeof(oldRecord));
            //file.seekp(0,ios::end);


        }

        //ofstream file(this->file_name, ios::app | ios::binary);

        //cout<<num_records<<endl;


        //file.write((char*) &record, sizeof(Alumno));//guardar en formato binario
        file.close();
    }  


    string get_filename(){
        return this->file_name;
    }

    int get_num_records(string archivo){
        ifstream file(archivo, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        file.seekg(0, ios::end);//ubicar cursos al final del archivo
        long size = file.tellg();//cantidad de bytes del archivo    
        size-=(sizeof(long)+sizeof(char));  
        file.close();

        if(size < 0 ){
            return 0;
        }else{
            return  size / sizeof(Alumno);

        }

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

        cout<<header<<" "<<tipo_archivo<<endl;


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


    vector<Alumno> scanAllAuxiliar(){
        ifstream file(this->auxiliar_data, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        vector<Alumno> alumnos;
        Alumno record; 

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