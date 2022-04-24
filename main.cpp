#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();
    /*
    for(int i=0;i<a1.size();i++){
        a1.at(i).showData();
    }*/

    auto b=a1.at(1)<a1.at(2);
    b.showData();

    SequentialFile seq = SequentialFile("./files/data_guardar.txt");

    seq.writeRecord(a1.at(1));


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
