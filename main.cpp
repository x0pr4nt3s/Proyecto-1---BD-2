#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();

    for(int i=0;i<a1.size();i++){
        a1.at(i).showData();
    }



    SequentialFile seq = SequentialFile("./files/data_guardar.txt");

    seq.writeRecord(a1.at(2));

    cout<<"GAAAAAAAAAAAA"<<endl;

    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size()-1;i++){
        v2.at(i).showData();
    }



    return 0;
}
