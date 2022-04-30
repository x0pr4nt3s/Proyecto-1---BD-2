#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"
#include <stdlib.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <numeric>
#include <iomanip>

void insercion_inicial(ParserforEntity1 &p1,SequentialFile& seq){
    auto a1=p1.getDataFile();
    for(int i=0;i<a1.size();i++){
        seq.add(a1.at(i));
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



void reset_files(){
    system("rm ./files/data_guardar.txt ./files/auxiliar_data.txt ./files/data_reconstruccion.txt");
    system("touch ./files/data_guardar.txt ./files/auxiliar_data.txt ./files/data_reconstruccion.txt");
}

double insert_prueba(string nombre_archivo){
    ParserforEntity1 p1(nombre_archivo);
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",40);

    auto a1=p1.getDataFile();
    //cout<<"Insertando 100 datos..."<<endl;
    volatile int sink;
    std::cout << std::fixed << std::setprecision(9) << std::left;
    // record start time
    auto start = std::chrono::system_clock::now();
    for(int i=0;i<a1.size();i++){
        seq.add(a1.at(i));
    }
    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    //std::cout << "Tiempo : "<< diff.count() << " s\n"; 
    return diff.count();
}

void test_Insercion(){

    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                        INSERCION                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    double promedio=0;    
    for(int i=0;i<100;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-100.txt");
    }
    cout<<"Prueba de 100 inserciones : "<<promedio/100<<" s "<<endl;

    promedio=0;
    for(int i=0;i<100;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-1k.txt");
    }
    cout<<"Prueba de 1 K inserciones : "<<promedio/100<<" s "<<endl;

    promedio=0;
    for(int i=0;i<100;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-10k.txt");
    }
    cout<<"Prueba de 10 K inserciones : "<<promedio/100<<" s "<<endl;





    // 1000 -> 0.13 s

    // 10 k -> 0.95 s

    // 100 k -> 7.8 s

    // 1 M -> 90 s



}

void Test_Busqueda_Individual(SequentialFile& seq){    // TERMINADO AL 100%
    // Mostrando Archivo Data:

    // BUSQUEDA POR KEY
    auto x=seq.search("HHH7");
    cout<<"Objeto:"<<endl;
    if(x.size()>0){
        //for(int i=0;i<x.size();i++){
           //x.at(i).showData();
        //}
    }
    else{
        cout<<"El objeto con esa key no existe"<<endl;
    }

}

void Test_Busqueda_por_Rango(SequentialFile& seq){
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

    cout<<"----------------------------------------------------------+"<<endl;

    auto F=seq.rangeSearch("AAA6","CZY5");
    for(int i=0;i<F.size();i++){
        F.at(i).showData();
    }

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

    //seq.remove("DRY6");

}

void Test_Reconstruccion(SequentialFile& seq){
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
    seq.Reconstruccion();
}


void bucle_ver(){
    int cero;
    while(true){
        cout<<endl;
        cout<<"Ingrese 0 cuando desea dejar de ver el contenido:";
        cin>>cero;
        if(cero==0){
            break;
        }
    }
}

void estructuras(int n){
    while(true){
    cout<<"+--------------------------------------+"<<endl;
    cout<<"| Escoja una de estas opciones:        |"<<endl;
    cout<<"| 1. SEQUENTIAL FILE.                  |"<<endl;
    cout<<"| 2. EXTENDIBLE HASH.                  |"<<endl;
    cout<<"| 3. Volver al menu.                   |"<<endl;
    cout<<"+--------------------------------------+"<<endl;

    int num;
    cout<<"Digite un numero: ";
    cin>>num;
    system("clear");
    
    if(num==1){
        if(n==1){
            
            // 

            // Poner todas las pruebas de busqueda Especifica
            bucle_ver();
        }
        else if(n==2){

            bucle_ver();
        }
        else if(n==3){
            // INSERCION DE 100 ELEMENTOS
            test_Insercion();
            bucle_ver();
        }
        else if(n==4){

            bucle_ver();
        }

        
        break;
    }
    else if(num==2){

        if(n==1){
            // Poner todas las pruebas de busqueda Especifica

            bucle_ver();
        }
        else if(n==2){
            cout<<"La estructura de datos no cuenta con esta funcionalidad"<<endl;
        }
        else if(n==3){


            bucle_ver();
        }
        else if(n==4){


            bucle_ver();
        }
        break;    
    }
    else if(num==3){
        break;
    }
    }


}

void Menu(){
    system("clear");
    while(true){
    cout<<"+--------------------------------------+"<<endl;
    cout<<"| Escoja una de estas opciones:        |"<<endl;
    cout<<"| 1. Busqueda Especifica.              |"<<endl;
    cout<<"| 2. Busqueda por Rango.               |"<<endl;
    cout<<"| 3. Insercion.                        |"<<endl;
    cout<<"| 4. Eliminacion.                      |"<<endl;
    cout<<"| 5. Salir de la interfaz.             |"<<endl;
    cout<<"+--------------------------------------+"<<endl;

    int n;
    cout<<"Digite un numero: ";
    cin>>n;
    system("clear");

    if(n==1 || n==2 || n==3 || n==4){
        estructuras(n);
    }
    else if(n==5){
        break;
    }   


    }


}



int main(){
    //ParserforEntity1 p1("./files/datos1.csv");
    //SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",5);
    //insercion_inicial(p1,seq);
    //test_Insercion(seq);
    //Test_Busqueda_Individual(seq);
    //Test_Eliminacion(seq);
    //test_Insercion(seq);
    //Test_Reconstruccion(seq);
    //Test_Busqueda_por_Rango(seq);
    //Menu();
    test_Insercion();
    return 0;
}
