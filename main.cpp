#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();
    /*
    for(int i=0;i<a1.size();i++){
        a1.at(i).showData();
    }*/




    SequentialFile seq = SequentialFile("./files/data_guardar.txt");
    //seq.writeRecord(a1.at(1));    
    auto v2 = seq.scanAll();
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    } 
    cout<<"-------------------"<<endl;
    cout<<"-------------------"<<endl;
    Alumno a2=Alumno("AA56","javier","prueba1 prueba2","carreraa");
    //seq.find_by_binary(a2);
    if(v2.at(0)==a1.at(2)){
        //cout<<"GAA"<<endl;
    }
    //b.showData();

    /*

    seq.writeRecord(a1.at(1));
*/

    /*
    seq.writeRecord(a1.at(0));
    
    cout<<"------------"<<endl;

    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    }*/
    
    //seq.find_by_binary();



    return 0;
}
