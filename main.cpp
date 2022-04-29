#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"


void insercion_inicial(ParserforEntity1 &p1,SequentialFile& seq){
    auto a1=p1.getDataFile();
    for(int i=0;i<a1.size();i++){
        seq.writeRecord(a1.at(i));
    }
    Alumno a2=Alumno("CZT5","javier","prueba1 prueba2","carreraa");
    Alumno a4=Alumno("FZT5","javier","prueba1 prueba3","carreraa");
    Alumno a5=Alumno("ZZT5","javier","prueba1 prueba3","carreraa");
    Alumno a6=Alumno("CZT6","jier","pruea1 peba3","careraa");
    Alumno a7=Alumno("CAT6","jier","pruea1 pesa3","careraa");
    //seq.add(a2);
    /*
    seq.writeRecord(a4);
    seq.writeRecord(a5);
    seq.writeRecord(a6);
    seq.writeRecord(a7);
    */
}

void test_Insercion(SequentialFile& seq){
    // Insertando Datos
    auto ve2=seq.scanAll();   
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         DATA                             +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    for(int i=0;i<ve2.size();i++){
        ve2.at(i).showData();
    }
    // Mostrando Archivo Auxiliar:
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         AUXILIAR                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    auto v3 = seq.scanAllAuxiliar();
    for(int i=0;i<v3.size();i++){
        v3.at(i).showData();
    }
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                        INSERCION                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    Alumno a2=Alumno("EGYZ","javier","prueba1 prueba2","carreraa");
    seq.add(a2);
}

void Test_Busqueda_Individual(SequentialFile& seq){    // TERMINADO AL 100%
    // Mostrando Archivo Data:
    auto ve2=seq.scanAll();   
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         DATA                             +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    for(int i=0;i<ve2.size();i++){
        ve2.at(i).showData();
    }
    // Mostrando Archivo Auxiliar:
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         AUXILIAR                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    auto v3 = seq.scanAllAuxiliar();
    for(int i=0;i<v3.size();i++){
        v3.at(i).showData();
    }
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         BUSQUEDA                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    // BUSQUEDA POR KEY
    auto x=seq.search("CPT6");
    cout<<"Objeto:"<<endl;
    if(x.size()>0){
        for(int i=0;i<x.size();i++){
            x.at(i).showData();
        }
    }
    else{
        cout<<"El objeto con esa key no existe"<<endl;
    }

}

void Test_Busqueda_por_Rango(){

}

void Test_Eliminacion(SequentialFile& seq){

    cout<<"          DATOS ANTES DE ELIMINARLOS:      "<<endl<<endl;
    auto ve2=seq.scanAll();   
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         DATA                             +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    for(int i=0;i<ve2.size();i++){
        ve2.at(i).showData();
    }
    // Mostrando Archivo Auxiliar:
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         AUXILIAR                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    auto v3 = seq.scanAllAuxiliar();
    for(int i=0;i<v3.size();i++){
        v3.at(i).showData();
    }

    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         ELIMINAR                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    seq.remove("ABB7");

}


int main(){
    ParserforEntity1 p1("./files/datos1.csv");
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt");
    
    //insercion_inicial(p1,seq);
    //test_Insercion(seq);
    //Test_Busqueda_Individual(seq);
    //Test_Eliminacion(seq);
    test_Insercion(seq);

    return 0;
}
