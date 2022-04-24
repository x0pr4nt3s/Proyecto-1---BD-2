#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();
    SequentialFile seq = SequentialFile("./files/data_guardar.txt");

    for(int i=0;i<a1.size();i++){
        seq.writeRecord(a1.at(i));
    }
    
/*
    auto b=a1.at(1)<a1.at(2);
    b.showData();

    */



    /*
    seq.writeRecord(a1.at(0));
    */
    cout<<"------------"<<endl;

    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    }
    
    //seq.find_by_binary();



    return 0;
}
