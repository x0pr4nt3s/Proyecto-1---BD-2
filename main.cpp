#include "./Parser/ParserEntities.h"

int main(){

    ParserforEntity1 p1("./files/datos1.csv");
    auto a1=p1.getDataFile();

    for(int i=0;i<a1.size();i++){
        a1.at(i).showData();
    }


    return 0;
}
