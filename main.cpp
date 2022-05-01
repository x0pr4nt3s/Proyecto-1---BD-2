#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"
#include "./ExtendibleHashing/ExtendibleHashing.h"
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
    system("rm ./files/data_guardar.txt ./files/auxiliar_data.txt ./files/data_reconstruccion.txt ./files/ext_data_guardar.txt" );
    system("touch ./files/data_guardar.txt ./files/auxiliar_data.txt ./files/data_reconstruccion.txt ./files/ext_data_guardar.txt");
}

double insert_prueba(string nombre_archivo){
    //ParserforEntity1 p1(nombre_archivo);
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",40);

    //auto a1=p1.getDataFile();
    //cout<<"Insertando 100 datos..."<<endl;
    ParserforEntity1 p1("./files/data-100k.txt");
    auto a1=p1.getDataFile();

    ExtendibleHashing extend("./files/ext_data_guardar.txt");

    for(long i=0;i<a1.size();i++){
        extend.insert(a1.at(i));

    } 
    //extend.SearchRecord("1ZLG").codigo;

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

SequentialFile insert_uno(string nombre_archivo){
    ParserforEntity1 p1(nombre_archivo);
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",40);
    auto a1=p1.getDataFile();
    for(int i=0;i<a1.size();i++){
        seq.add(a1.at(i));
    }

    return seq;
}


void test_Insercion(){

    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                        INSERCION                         +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    double promedio=0;    
    for(int i=0;i<10;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-100.txt");
    }
    cout<<"Prueba de 100 inserciones : "<<promedio/10<<" s "<<endl;

    promedio=0;
    for(int i=0;i<10;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-1k.txt");
    }
    cout<<"Prueba de 1 K inserciones : "<<promedio/10<<" s "<<endl;

    promedio=0;
    for(int i=0;i<10;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-10k.txt");
    }
    cout<<"Prueba de 10 K inserciones : "<<promedio/10<<" s "<<endl;

    promedio=0;
    for(int i=0;i<10;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-100k.txt");
    }
    cout<<"Prueba de 100 K inserciones : "<<promedio/10<<" s "<<endl;

    promedio=0;
    for(int i=0;i<10;i++){
        reset_files();
        promedio=promedio+insert_prueba("./files/data-1M.txt");
    }
    cout<<"Prueba de 1 M inserciones : "<<promedio/10<<" s "<<endl;


    // 100 -> 0.012534436 s

    // 1 k -> 0.056939166 s

    // 10 k -> 0.682435693 s

    // 100 k -> 8.005181312 s

    // 1 M -> 90 s
}

double search_prueba(SequentialFile& seq){


    //cout<<"Insertando 100 datos..."<<endl;
    volatile int sink;
    std::cout << std::fixed << std::setprecision(9) << std::left;
    // record start time
    auto start = std::chrono::system_clock::now();
    auto x=seq.search("002H");
    /*if(x.size()>0){
        x.at(x.size()-1).showData();
    }*/
    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    //std::cout << "Tiempo : "<< diff.count() << " s\n"; 
    return diff.count();
}


void Test_Busqueda_Individual(){    // TERMINADO AL 100%
    // Mostrando Archivo Data:
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                        BUSQUEDA                          +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    double promedio=0;    
    reset_files();
    auto x=insert_uno("./files/data-100.txt");
    promedio=search_prueba(x);
    cout<<"Tiempo de busquedas en 100 datos : "<<promedio<<" s "<<endl;
    
    reset_files();
    x=insert_uno("./files/data-1k.txt");
    promedio=search_prueba(x);
    cout<<"Tiempo de busquedas en 1K datos : "<<promedio<<" s "<<endl;

    reset_files();
    x=insert_uno("./files/data-10k.txt");
    promedio=search_prueba(x);
    cout<<"Tiempo de busquedas en 10K datos : "<<promedio<<" s "<<endl;

    reset_files();
    x=insert_uno("./files/data-100k.txt");
    promedio=search_prueba(x);
    cout<<"Tiempo de busquedas en 100K datos : "<<promedio<<" s "<<endl;

    reset_files();
    x=insert_uno("./files/data-1M.txt");
    promedio=search_prueba(x);
    cout<<"Tiempo de busquedas en 1M datos : "<<promedio<<" s "<<endl;

    /*
    for(int i=0;i<1000;i++){
        reset_files();
        promedio=promedio+search_prueba("./files/data-1k.txt");
    }
    cout<<"Prueba de 1 k busquedas : "<<promedio/10<<" s "<<endl;
    */

}

void Test_Busqueda_por_Rango(SequentialFile& seq){


    cout<<"----------------------------------------------------------+"<<endl;

    auto F=seq.rangeSearch("AAA6","CZY5");


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


void Test_Ext_Eliminacion_Individual(){
/*
    ExtendibleHashing extend("./files/ext_data_guardar.txt");


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
*/
}

void Test_Ext_Busqueda_Individual(){
    ParserforEntity1 p1("/files/data-100.txt");

    //ExtendibleHashing ext();

/*
    cout<<"          DATOS INSERTADOS:      "<<endl<<endl;
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
*/
    //seq.remove("DRY6");

}


void Test_Ext_Insercion_Individual(){
    reset_files();

    ParserforEntity1 p2("./files/data-100.txt");
    auto a1=p2.getDataFile();

    ExtendibleHashing extend("./files/ext_data_guardar.txt");

    for(long i=0;i<a1.size();i++){
        extend.insert(a1.at(i));
    }
    cout<<"                     DATOS INSERTADOS      "<<endl<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"+                         DATA                             +"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    extend.showAllRecords();   

    // Mostrando Archivo Auxiliar:

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
            Test_Ext_Busqueda_Individual();
            bucle_ver();
        }
        else if(n==2){
            cout<<"La estructura de datos no cuenta con esta funcionalidad"<<endl;
        }
        else if(n==3){
            
            Test_Ext_Insercion_Individual();            
            bucle_ver();
        }
        else if(n==4){

            Test_Ext_Eliminacion_Individual();            

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
    //test_Insercion();
    //Test_Busqueda_Individual();
    
    Menu();
    return 0;
}
