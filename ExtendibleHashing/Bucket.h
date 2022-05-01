#include "../Entidades/Alumno.h"
#include "../GlobalVariables/GlobalVariables.h" 


class Bucket{
    int contador=0;
    Alumno lista_Records[BUQUETSIZE];
    int nextBucket;

public:

    int get_contador(){return contador;}
    int get_nextBucket(){return nextBucket;}
    Alumno* get_lista_Records(){return lista_Records;}
    void set_contador(int contador){this->contador=contador;}
    Bucket(){
        this->contador = 0;
        this->nextBucket = -1;
    }



    bool isFull(){
        if(this->contador==BUQUETSIZE) return true;
        return false;
    }

    int setRecord(Alumno record){
        if(contador==BUQUETSIZE) return -1;
        lista_Records[contador++] = record;
        return 1;
    }
    void set_nextBucket(int nextBucket){ this->nextBucket=nextBucket;    }
    void printRecords(){
        if(contador==0) return;
        for(int i=0;i<contador;i++){
            //cout<<lista_Records[i].codigo<<" - ";
            lista_Records[i].ext_showData();
        }
        //cout<<endl;
    }

    void printRecords_buckets(int tam){
        if(contador==0) return;
        for(int i=0;i<contador;i++){
            //cout<<lista_Records[i].codigo<<" - ";
            lista_Records[i].ext_showData(tam);
        }
        //cout<<endl;
    }

};