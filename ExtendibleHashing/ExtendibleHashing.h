#include "HashingNode.h"
#include <vector>
#include <functional>
#include <bitset>
#include "Bucket.h"
#include "../GlobalVariables/GlobalVariables.h"

class ExtendibleHashing{


    vector<HashNode> *Nodos;
    int profundidad = 1;
    long cantidad_buckets;
    string file_name;


public:

    ExtendibleHashing(){
        Nodos=nullptr;
        cantidad_buckets=0;
    }

    ExtendibleHashing(string filename){
        Nodos=nullptr;
        this->file_name=filename;
        cantidad_buckets=0;
    }

    void insert(Alumno registro){

        long pos = get_int(get_binary_hash(registro.getKey()),this->profundidad);

        if(Nodos==nullptr){
            Nodos = new vector<HashNode>(2);
            (*Nodos)[0].set(1,1,"0");
            (*Nodos)[1].set(2,1,"1");
            int pos_buck = (*Nodos)[pos].get_current_bucket();

            Bucket buck1;
            Bucket buck2;
            if(pos_buck%2==0){
                buck2.setRecord(registro);
            }
            else{
                buck1.setRecord(registro);
            }
            fstream file(this->file_name,ios::in | ios::out  | ios::binary);
            if(!file.is_open()) throw "No se pudo abrir el archivo";
            file.seekp(sizeof(Bucket)*(0),ios::beg);
            file.write((char*)&buck1,sizeof(buck1));
            file.seekp(sizeof(Bucket)*(1),ios::beg);
            file.write((char*)&buck2,sizeof(buck2));
            file.close();
            cantidad_buckets+=2;
            return;
        }
        
        int pos_buck = (*Nodos)[pos].get_current_bucket();
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        Bucket temp;
        file.seekp(sizeof(temp)*(pos_buck-1),ios::beg);
        file.read((char*)&temp, sizeof(temp));

        if(temp.isFull() && this->profundidad==(*Nodos)[pos].get_profundidad_nodo() && this->profundidad<MAXDEPTH){
            
            file.close();
            crecimiento_hash(pos,temp);
            insert(registro);
            return;
        }

        else if(temp.isFull() && this->profundidad>(*Nodos)[pos].get_profundidad_nodo() && this->profundidad<=MAXDEPTH){
            
            file.close();
            acomodar_hash(pos,temp);
            insert(registro);
            return;

        }
        else if(temp.isFull()){

            sequential_insert(pos,temp,registro);
            return;
        }

        temp.setRecord(registro);
        file.seekp(sizeof(Bucket)*(pos_buck-1),ios::beg);
        file.write((char*)&temp,sizeof(temp));
        file.close();

    }

    void sequential_insert(int pos_node, Bucket buck_temp, Alumno registro){
        //cout<<"ENTRO ACAAAAAAAAAAAAAAAA"<<endl;
        Bucket newBuck;
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        int buck_position=(*Nodos)[pos_node].get_current_bucket();
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        while(buck_temp.get_contador()==BUQUETSIZE){
            if(buck_temp.get_nextBucket()==-1){
                this->cantidad_buckets++;
                buck_temp.set_nextBucket(cantidad_buckets);
                
                newBuck.setRecord(registro);
                file.seekp(sizeof(Bucket)*(buck_position-1),ios::beg);
                file.write((char*)&buck_temp,sizeof(buck_temp));
                file.seekp(sizeof(Bucket)*(cantidad_buckets-1),ios::beg);
                file.write((char*)&newBuck,sizeof(newBuck));
                file.close();
                return;
            }
            else{
                buck_position=buck_temp.get_nextBucket();
                file.seekp(sizeof(Bucket)*(buck_temp.get_nextBucket()-1),ios::beg);
                file.read((char*)&buck_temp, sizeof(buck_temp));
               
            }
        }
        buck_temp.setRecord(registro);
        file.seekp(sizeof(Bucket)*(buck_position-1),ios::beg);
        file.write((char*)&buck_temp,sizeof(buck_temp));
        file.close();
        return;

    }

    void crecimiento_hash(int pos_node, Bucket buck_temp){
        this->profundidad++;

        vector<HashNode> *tmp;
        tmp = new vector<HashNode>(pow(2,this->profundidad));
        for(int i=0;i<Nodos->size();i++){
            (*tmp)[2*i].set_value((*Nodos)[i].get_value()+"0");
            (*tmp)[2*i + 1].set_value((*Nodos)[i].get_value()+"1");
            if(i==pos_node){
                (*tmp)[2*i].set_current_bucket((*Nodos)[i].get_current_bucket());
                this->cantidad_buckets+=1;
                (*tmp)[2*i + 1].set_current_bucket(this->cantidad_buckets);
                (*tmp)[2*i].set_profundidad_nodo((*Nodos)[i].get_profundidad_nodo()+1);
                (*tmp)[2*i + 1].set_profundidad_nodo((*Nodos)[i].get_profundidad_nodo()+1);
                Bucket buck1;
                Bucket buck2;
                for(int j=0; j<MAXDEPTH;j++){
                    int tamp_pos=get_int(get_binary_hash(buck_temp.get_lista_Records()[j].getKey()),this->profundidad);
                    if(tamp_pos % 2 == 0){
                        buck1.setRecord(buck_temp.get_lista_Records()[j]);
                    }
                    else{
                        buck2.setRecord(buck_temp.get_lista_Records()[j]);
                    }
                }
                fstream file(this->file_name,ios::in | ios::out  | ios::binary);
                if(!file.is_open()) throw "No se pudo abrir el archivo";
                file.seekp(sizeof(Bucket)*((*tmp)[2*i].get_current_bucket()-1),ios::beg);
                file.write((char*)&buck1,sizeof(buck1));
                file.seekp(sizeof(Bucket)*(this->cantidad_buckets-1),ios::beg);
                file.write((char*)&buck2,sizeof(buck2));
                file.close();

            }
            else{
                (*tmp)[2*i].set_current_bucket((*Nodos)[i].get_current_bucket());
                (*tmp)[2*i + 1].set_current_bucket((*Nodos)[i].get_current_bucket());
                (*tmp)[2*i].set_profundidad_nodo((*Nodos)[i].get_profundidad_nodo());
                (*tmp)[2*i + 1].set_profundidad_nodo((*Nodos)[i].get_profundidad_nodo());
            }
        }
        this->Nodos = tmp;
    }

    void acomodar_hash(int pos_node, Bucket buck_temp){

        Bucket buck1;
        Bucket buck2; 
        int profundidad_nodo_dividido = (*Nodos)[pos_node].get_profundidad_nodo()+1;
        string value_nodo = (*Nodos)[pos_node].get_value().substr(0,profundidad_nodo_dividido-1);
                    //cout<<"ESTA ES LA KEY "<< get_int(get_binary_hash(buck_temp.get_lista_Records()[0].getKey()),profundidad_nodo_dividido)<<endl;

        for (int i=0 ; i <MAXDEPTH; i++){
            int tamp_pos=get_int(get_binary_hash(buck_temp.get_lista_Records()[i].getKey()),profundidad_nodo_dividido);
            if(tamp_pos%2==0){
                buck1.setRecord(buck_temp.get_lista_Records()[i]);
            }
            else{
                buck2.setRecord(buck_temp.get_lista_Records()[i]);
            }
        }     
        string value_cero = value_nodo+"0";
        string value_uno = value_nodo+"1";
        this->cantidad_buckets++;
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        file.seekp(sizeof(Bucket)*((*Nodos)[pos_node].get_current_bucket()-1),ios::beg);
        file.write((char*)&buck1,sizeof(buck1));
        file.seekp(sizeof(Bucket)*(this->cantidad_buckets-1),ios::beg);
        file.write((char*)&buck2,sizeof(buck2));
        file.close();
        
        for(int i=0; i<(*Nodos).size();i++){
            if((*Nodos)[i].get_value().substr(0,profundidad_nodo_dividido) == value_cero){
                (*Nodos)[i].set_current_bucket((*Nodos)[pos_node].get_current_bucket());
                (*Nodos)[i].set_profundidad_nodo(profundidad_nodo_dividido);

            }
            else if((*Nodos)[i].get_value().substr(0,profundidad_nodo_dividido) == value_uno){
                (*Nodos)[i].set_current_bucket(this->cantidad_buckets);
                (*Nodos)[i].set_profundidad_nodo(profundidad_nodo_dividido);

            }
        }  

    }

    Alumno SearchRecord(string key){
        //cout<<"\n********BUSQUEDAAAAA*********\n";
        long pos = get_int(get_binary_hash(key),this->profundidad);
        int pos_buck = (*Nodos)[pos].get_current_bucket();
        Bucket temp;
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        file.seekp(sizeof(temp)*(pos_buck-1),ios::beg);
        file.read((char*)&temp, sizeof(temp));
        int temp_buck;
        while(true){
            for(int i=0; i<temp.get_contador(); i++){
                if(temp.get_lista_Records()[i].getKey()==key){
                    //temp.printRecords();
                    file.close();
                    
                    cout<<"\n**********************ENCONTRADO***********************************\n"<<endl;
                    cout<<"NODO "<<setw(10)<<""<<pos+1<<endl<<endl;

                    cout<<"BUCKET "<<setw(10)<<""<<temp_buck<<endl<<endl;

                    return temp.get_lista_Records()[i];
                }
            }
            if(temp.get_nextBucket()!=-1){
                temp_buck=temp.get_nextBucket();
                file.seekp(sizeof(temp)*(temp.get_nextBucket()-1),ios::beg);
                file.read((char*)&temp, sizeof(temp));
                continue;
            }
            if(temp.get_nextBucket()==-1) throw "Data no encontrada";

        }

    }

    void deleteRecord(string key){
        //cout<<"\n********DELETE*********\n";
        long pos = get_int(get_binary_hash(key),this->profundidad);
        //cout<<"KEY"<<endl;
        int pos_buck = (*Nodos)[pos].get_current_bucket();
        cout<<"EL VALOR "<<key<<" ELIMINADO DEL NODO "<<pos+1<<endl<<endl;;
        Bucket temp,nuevo;
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        file.seekp(sizeof(temp)*(pos_buck-1),ios::beg);
        file.read((char*)&temp, sizeof(temp));

        int pos_delete;

            
        for(int i=0; i<temp.get_contador(); i++){
            if(temp.get_lista_Records()[i].getKey()!=key){
                nuevo.setRecord(temp.get_lista_Records()[i]);
            }
        }

        string value_temp = (*Nodos)[pos].get_value();
        string val0 = value_temp.substr(0,(*Nodos)[pos].get_profundidad_nodo()-1)+"0";
        string val1 = value_temp.substr(0,(*Nodos)[pos].get_profundidad_nodo()-1)+"1";
        long pos_val0 = get_int(val0);
        long pos_val1 = get_int(val1);


        int pos_buck0 = (*Nodos)[pos_val0].get_current_bucket();
        int pos_buck1 = (*Nodos)[pos_val1].get_current_bucket();

        Bucket b0,b1;

        file.seekp(sizeof(b0)*(pos_buck0-1),ios::beg);
        file.read((char*)&b0, sizeof(b0));
        file.seekp(sizeof(b1)*(pos_buck1-1),ios::beg);
        file.read((char*)&b1, sizeof(b1));
        if(b0.get_contador()+b1.get_contador()-1<=MAXDEPTH){
            Bucket temp;
            for(int i=0;i<b0.get_contador();i++){
                temp.setRecord(b0.get_lista_Records()[i]);
            }
            for(int i=0;i<b1.get_contador();i++){
                temp.setRecord(b1.get_lista_Records()[i]);
            }
            file.seekp(sizeof(b0)*(pos_buck0-1),ios::beg);
            file.write((char*)&temp, sizeof(temp)); 
            string new_temp = value_temp.substr(0,(*Nodos)[pos].get_profundidad_nodo()-1);

            for(int i=0;i<(*Nodos).size();i++){
                if((*Nodos)[i].get_value().substr(0,(*Nodos)[pos].get_profundidad_nodo()-1)==new_temp){
                    (*Nodos)[i].set_value(new_temp);
                    (*Nodos)[i].set_profundidad_nodo((*Nodos)[pos].get_profundidad_nodo()-1);
                    (*Nodos)[i].set_current_bucket(pos_buck0);
                }
            }
        }
        else{

            file.seekp(sizeof(nuevo)*(pos_buck-1),ios::beg);
            file.write((char*)&nuevo, sizeof(nuevo)); 


        }
        file.close();




    }

    void showAllRecords(){
        Bucket temp;
        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        for(int i=0; i<(*Nodos).size();i++){
            int pos_buck = (*Nodos)[i].get_current_bucket();
            file.seekp(sizeof(temp)*(pos_buck-1),ios::beg);
            file.read((char*)&temp, sizeof(temp));
            cout<<"******************************** NODO POS "<<i+1<<" ***************************************************"<<endl<<endl;
            cout<<"BUCKET "<<setw(10)<<""<<pos_buck<<endl<<endl;
            /*
            cout<<"******* NODO VALUE "<<(*Nodos)[i].get_value()<<endl;
            cout<<"******* NODO PROFUNDIDAD "<<(*Nodos)[i].get_profundidad_nodo()<<endl;
            cout<<"******* CONTADOR DE ALUMNSO EN BUCKET "<<temp.get_contador()<<endl;
            cout<<"******* SIGUIENTE BUCKET "<<temp.get_nextBucket()<<endl;
            */
            temp.printRecords();


            int tam = 4;
            while(temp.get_nextBucket()!=-1){
                cout<<"\n"<<setw(tam)<<""<<"ADICIONAL BUCKET "<<endl;
                cout<<setw(tam)<<""<<"BUCKET POSICION "<<setw(10)<<""<<temp.get_nextBucket()<<endl<<endl;

                file.seekp(sizeof(temp)*(temp.get_nextBucket()-1),ios::beg);
                file.read((char*)&temp, sizeof(temp));
        
                temp.printRecords_buckets(tam);
                tam+=4;
                cout<<"\n\n";
            }
            cout<<"***********************************************************************************************\n\n"<<endl;


        }


 
    }


    string get_binary_hash(string key){

        hash<string> mystdhash;
        string binary="";
        string temp=to_string(mystdhash(key));
        for(char const &c: temp){
            binary+=bitset<8>(c).to_string();
        }
        //cout<<binary<<endl;
        return binary;
    }

    long get_int(string binary, int profundidad){
        string full_binary = binary.substr(binary.length()-MAXDEPTH,MAXDEPTH);
        //cout<<full_binary<<endl;
        string full_value = full_binary.substr(0,profundidad);
        //cout<<full_binary.substr(0,profundidad)<<endl;
        bitset<8> bits(full_value);

        return bits.to_ulong();
    }

    long get_int(string binary){
        //string full_binary = binary.substr(binary.length()-MAXDEPTH,MAXDEPTH);
        //cout<<full_binary<<endl;
        //tring full_value = full_binary.substr(0,profundidad);
        //cout<<full_binary.substr(0,profundidad)<<endl;
        bitset<8> bits(binary);

    return bits.to_ulong();
    }

};


