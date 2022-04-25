#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt");




    //seq.writeRecord(a1.at(2));    
    //auto v2 = seq.scanAll();
    for(int i=0;i<a1.size();i++){
        seq.writeRecord(a1.at(i));
    } 






    cout<<"-------------------"<<endl;
    cout<<"-------------------"<<endl;
    Alumno a2=Alumno("CZT5","javier","prueba1 prueba2","carreraa");
    Alumno a4=Alumno("FZT5","javier","prueba1 prueba3","carreraa");
    Alumno a5=Alumno("ZZT5","javier","prueba1 prueba3","carreraa");
    Alumno a6=Alumno("CZT6","jier","pruea1 peba3","careraa");
    Alumno a7=Alumno("CAT6","jier","pruea1 pesa3","careraa");

    cout<<"INSERTAR EN "<<seq.find_by_binary(a2)<<endl;

    seq.writeRecord(a2);
    seq.writeRecord(a4);

    seq.writeRecord(a5);

    seq.writeRecord(a6);
    
    seq.writeRecord(a7);


    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    }

    cout<<"AUXILIAAAAAR"<<endl;


    auto v3 = seq.scanAllAuxiliar();

    for(int i=0;i<v3.size();i++){
        v3.at(i).showData();
    }

    /*if(v2.at(0)==a1.at(0)){
        cout<<"GAA"<<endl;
    }*/
    //b.showData();

    /*


    /*
    seq.writeRecord(a1.at(0));
   
    cout<<"------------"<<endl;

    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    }
     */
    //seq.find_by_binary();



    return 0;
}
