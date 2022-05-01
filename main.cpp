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
    auto af1=p1.getDataFile();
    for(int i=0;i<af1.size();i++){
        seq.add(af1.at(i));
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

double insert_prueba(string nombre_archivo,int num){
    ParserforEntity1 p1(nombre_archivo);
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",40);

    auto a1=p1.getDataFile();

    if(num==1){  // SEQUENTIAL FILE
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
        return diff.count();    
    }
    else{ // EXTENDIBLE HASHING

    /*
    ExtendibleHashing extend("./files/ext_data_guardar.txt");
    for(long i=0;i<a1.size();i++){
        extend.insert(a1.at(i));

    } 
    extend.SearchRecord("1ZLG").codigo;
    */

    }
    //cout<<"Insertando 100 datos..."<<endl;

    //std::cout << "Tiempo : "<< diff.count() << " s\n"; 
    return 0.00;
}

SequentialFile insert_uno(string nombre_archivo){ // INSERCION RAPIDA SEQUENTIAL FILE
    ParserforEntity1 p1(nombre_archivo);
    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",40);
    auto a1=p1.getDataFile();
    for(int i=0;i<a1.size();i++){
        seq.add(a1.at(i));
    }

    return seq;
}





void test_Insercion(int num){
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"|                 SEQUENTIAL FILE INSERCION                |"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    double promedio=0;    
    reset_files();
    promedio=promedio+insert_prueba("./files/data-100.txt",num);
    cout<<"| Prueba de 100 inserciones : "<<promedio<<" s                |"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    promedio=0;
    reset_files();
    promedio=promedio+insert_prueba("./files/data-1k.txt",num);
    cout<<"| Prueba de 1K inserciones : "<<promedio<<" s                 | "<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    promedio=0;
    reset_files();
    promedio=insert_prueba("./files/data-10k.txt",num);
    cout<<"| Prueba de 10K inserciones : "<<promedio<<" s                | "<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    promedio=0;
    reset_files();
    promedio=promedio+insert_prueba("./files/data-100k.txt",num);
    cout<<"| Prueba de 100K inserciones : "<<promedio<<" s               |"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;

    // 100 -> 0.012534436 s
    // 1 k -> 0.056939166 s
    // 10 k -> 0.682435693 s
    // 100 k -> 8.005181312 s
    // 1 M -> 90 s
}

double search_prueba(SequentialFile& seq){
    volatile int sink;
    std::cout << std::fixed << std::setprecision(9) << std::left;
    // record start time
    auto start = std::chrono::system_clock::now();
    auto x=seq.search("002H");
    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    //std::cout << "Tiempo : "<< diff.count() << " s\n"; 
    return diff.count();
}


void Test_Busqueda_Individual(int num){    // TERMINADO AL 100%
    // Mostrando Archivo Data:
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"|                 SEQUENTIAL FILE BUSQUEDA                 |"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl;
    double promedio=0;    

    if(num==1){// SEQUENTIAL FILE 
        reset_files();
        auto x=insert_uno("./files/data-100.txt");
        promedio=search_prueba(x);
        cout<<"| Tiempo de busquedas en 100 datos : "<<promedio<<" s         |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        reset_files();
        x=insert_uno("./files/data-1k.txt");
        promedio=search_prueba(x);
        cout<<"| Tiempo de busquedas en 1K datos : "<<promedio<<" s          |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        reset_files();
        x=insert_uno("./files/data-10k.txt");
        promedio=search_prueba(x);
        cout<<"| Tiempo de busquedas en 10K datos : "<<promedio<<" s         |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        reset_files();
        x=insert_uno("./files/data-100k.txt");
        promedio=search_prueba(x);
        cout<<"| Tiempo de busquedas en 100K datos : "<<promedio<<" s        |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        reset_files();
    }

}

void Test_Busqueda_por_Rango(SequentialFile& seq){


    cout<<"----------------------------------------------------------+"<<endl;

    auto F=seq.rangeSearch("AAA6","CZY5");


}



double delete_prueba(SequentialFile& seq){
    volatile int sink;
    std::cout << std::fixed << std::setprecision(9) << std::left;
    // record start time
    auto elements=seq.scanAll();
    auto start = std::chrono::system_clock::now();
    for(int i=0;i<elements.size()-1;i++){
        seq.remove(elements.at(i).get_codigo());
    }
    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    //std::cout << "Tiempo : "<< diff.count() << " s\n";
    /*elements=seq.scanAll();
    for(int i=0;i<elements.size()-1;i++){
        elements.at(i).showData();
    }*/

    return diff.count();
}


void Test_Eliminacion(int num){
    cout<<"+----------------------------------------------------------+"<<endl;
    cout<<"|                SEQUENTIAL FILE ELIMINACION               |"<<endl;
    cout<<"+----------------------------------------------------------+"<<endl; 
    double promedio=0;
    if(num==1){// SEQUENTIAL FILE 
        // BORRANDO 100 DATOS
        reset_files();
        auto x=insert_uno("./files/data-100.txt");
        promedio=delete_prueba(x);
        cout<<"| Tiempo de Eliminacion de 100 datos : "<<promedio<<" s       |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl; 

        reset_files();
        x=insert_uno("./files/data-1k.txt");
        promedio=delete_prueba(x);
        cout<<"| Tiempo de Eliminacion de 1k datos : "<<promedio<<" s        |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl; 

        reset_files();
        x=insert_uno("./files/data-10k.txt");
        promedio=delete_prueba(x);
        cout<<"| Tiempo de Eliminacion de 10k datos : "<<promedio<<" s       |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl; 

        reset_files();
        x=insert_uno("./files/data-100k.txt");
        promedio=delete_prueba(x);
        cout<<"| Tiempo de Eliminacion de 100k datos : "<<promedio<<" s      |"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl; 

    }

}

void Test_Reconstruccion(SequentialFile& seq){

    auto v3 = seq.scanAllAuxiliar();
    for(int i=0;i<v3.size();i++){
        v3.at(i).showData();
    } 
    seq.Reconstruccion();
}


// 

void Test_Ext_Eliminacion_Individual(int numero){

    reset_files();


    if(numero==1){

        ParserforEntity1 p2("./files/datos1.csv");
        auto a1=p2.getDataFile();
        SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",5);

        for(long i=0;i<a1.size();i++){
            seq.add(a1.at(i));
        }

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                 SEQUENTIAL FILE                                                   +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        auto ve2=seq.scanAll();   
        fstream file_temp(seq.get_filename(),ios::binary | ios::in);   
        long header_value;
        char header_char_value;        
        file_temp.seekg(0,ios::beg);
        file_temp.read((char*)(&header_value), sizeof(long));
        file_temp.seekg(sizeof(long),ios::beg);
        file_temp.read((char*)(&header_char_value), sizeof(char));
        file_temp.close();


        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp.close();
        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        auto v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        cout<<"1. Eliminando elemento JJY6..."<<endl;
        seq.remove("JJY6");
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"2. Eliminando elemento ZFF6..."<<endl;
        seq.remove("ZFF6");
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"3. Eliminando elemento ABB7..."<<endl;
        seq.remove("ABB7");
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;




        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                   RESULTADOS                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        ve2=seq.scanAll();   
        fstream file_temp1(seq.get_filename(),ios::binary | ios::in);   
        file_temp1.seekg(0,ios::beg);
        file_temp1.read((char*)(&header_value), sizeof(long));
        file_temp1.seekg(sizeof(long),ios::beg);
        file_temp1.read((char*)(&header_char_value), sizeof(char));

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp1.close();        
        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;





    }
    else if(numero==2){

        ParserforEntity1 p2("./files/data-40.txt");
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
        extend.deleteRecord("000D");

        cout<<"\n\n                     DATO ELIMINADO      "<<endl<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"+                         DATA                             +"<<endl;
        cout<<"+                         000D                             +"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;

        extend.showAllRecords();   

        extend.deleteRecord("000Y");

        cout<<"\n\n                     DATO ELIMINADO      "<<endl<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"+                         DATA                             +"<<endl;
        cout<<"+                         000Y                             +"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;

        extend.showAllRecords();  
    } 

}

void Test_Ext_Busqueda_Individual(int numero){

    reset_files();
    

    if(numero==1){
        ParserforEntity1 p2("./files/datos1.csv");
        auto a1=p2.getDataFile();
        SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",5);

        for(long i=0;i<a1.size();i++){
            seq.add(a1.at(i));
        }

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                 SEQUENTIAL FILE                                                   +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        auto ve2=seq.scanAll();   
        fstream file_temp(seq.get_filename(),ios::binary | ios::in);   
        long header_value;
        char header_char_value;        
        file_temp.seekg(0,ios::beg);
        file_temp.read((char*)(&header_value), sizeof(long));
        file_temp.seekg(sizeof(long),ios::beg);
        file_temp.read((char*)(&header_char_value), sizeof(char));
        file_temp.close();


        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp.close();

        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        auto v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        cout<<"1. Buscando elemento CRY6..."<<endl;
        auto x=seq.search("CRY6");
        if(x.size()==1){
            x.at(x.size()-1).showData();
        }
        else if(x.size()>1){
            for(int i=0;i<x.size();i++){
                x.at(i).showData();
            }
        }
        else{
            cout<<"El objeto no existe"<<endl;
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"2. Buscando elemento JJY6..."<<endl;
        x=seq.search("JJY6");
        if(x.size()==1){
            x.at(x.size()-1).showData();
        }
        else if(x.size()>1){
            for(int i=0;i<x.size();i++){
                x.at(i).showData();
            }
        }
        else{
            cout<<"El objeto no existe"<<endl;
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"3. Buscando elemento ZFF6..."<<endl;
        x=seq.search("ZFF6");
        if(x.size()==1){
            x.at(x.size()-1).showData();
        }
        else if(x.size()>1){
            for(int i=0;i<x.size();i++){
                x.at(i).showData();
            }
        }
        else{
            cout<<"El objeto no existe"<<endl;
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"4. Buscando elemento ABB7..."<<endl;
        x=seq.search("ABB7");
        if(x.size()==1){
            x.at(x.size()-1).showData();
        }
        else if(x.size()>1){
            for(int i=0;i<x.size();i++){
                x.at(i).showData();
            }
        }
        else{
            cout<<"El objeto no existe"<<endl;
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;



    }
    else if(numero==2){
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

        cout<<"                     DATOS BUSCADO      "<<endl<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"+                         DATA                             +"<<endl;
        cout<<"+                         002G                             +"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;

        extend.SearchRecord("002G").showData();

        cout<<"\n\n\n";

        cout<<"                     DATOS BUSCADO      "<<endl<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"+                         DATA                             +"<<endl;
        cout<<"+                         002J                             +"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;

        extend.SearchRecord("002J").showData();
        cout<<"\n*******************************************************************\n";


    cout<<"\n\n\n";

        cout<<"                     DATOS BUSCADO      "<<endl<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;
        cout<<"+                         DATA                             +"<<endl;
        cout<<"+                         ZZZZ                             +"<<endl;
        cout<<"+----------------------------------------------------------+"<<endl;

        extend.SearchRecord("ZZZZ").showData();
        cout<<"\n*******************************************************************\n";
    }


    //seq.remove("DRY6");

}


void Test_Ext_Insercion_Individual(int numero){
    reset_files();


    if(numero==1){

        ParserforEntity1 p2("./files/datos1.csv");
        auto a1=p2.getDataFile();
        SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt","./files/data_reconstruccion.txt",4);

        for(long i=0;i<a1.size();i++){
            seq.add(a1.at(i));
        }

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                 SEQUENTIAL FILE                                                   +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        auto ve2=seq.scanAll();
        fstream file_temp(seq.get_filename(),ios::binary | ios::in);   
        long header_value;
        char header_char_value;        
        file_temp.seekg(0,ios::beg);
        file_temp.read((char*)(&header_value), sizeof(long));
        file_temp.seekg(sizeof(long),ios::beg);
        file_temp.read((char*)(&header_char_value), sizeof(char));
        file_temp.close();
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp.close();
        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        auto v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        
        cout<<"1. Insertando elemento CZT5..."<<endl;
        Alumno a2=Alumno("CZT5","javier","prueba1 prueba2","carreraa");
        seq.add(a2);

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"2. Insertando elemento AAA5..."<<endl;
        a2=Alumno("AAA5","javier","prueba1 prueba2","carreraa");
        seq.add(a2);
    

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"3. Insertando elemento ZHT5..."<<endl;
        a2=Alumno("ZHT5","javier","prueba1 prueba2","carreraa");
        seq.add(a2);

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                   RESULTADOS                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        ve2=seq.scanAll();   
        fstream file_temp1(seq.get_filename(),ios::binary | ios::in);   
        file_temp1.seekg(0,ios::beg);
        file_temp1.read((char*)(&header_value), sizeof(long));
        file_temp1.seekg(sizeof(long),ios::beg);
        file_temp1.read((char*)(&header_char_value), sizeof(char));

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp1.close();        
        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;



        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"4. Insertando elemento AAA9..."<<endl;
        a2=Alumno("AAA9","javier","prueba1 prueba2","carreraa");
        seq.add(a2);
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                   RESULTADOS                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        ve2=seq.scanAll();   
        fstream file_temp2(seq.get_filename(),ios::binary | ios::in);   
        file_temp2.seekg(0,ios::beg);
        file_temp2.read((char*)(&header_value), sizeof(long));
        file_temp2.seekg(sizeof(long),ios::beg);
        file_temp2.read((char*)(&header_char_value), sizeof(char));

        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                    DATA FILE                                                      +"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"HEADER: "<<header_value<<" "<<header_char_value<<endl;
        file_temp2.close();        
        for(int i=0;i<ve2.size();i++){
            ve2.at(i).showData();
        }

        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"+                                                  AUXILIAR FILE                                                   +"<<endl;
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        v3 = seq.scanAllAuxiliar();
        for(int i=0;i<v3.size();i++){
            v3.at(i).showData();
        }
        cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;
    }
    else if(numero==2){

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
    }
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

        if(num==3){
            break;
        }
        
        if(n==1){
            //Test_Busqueda_Individual(num);   
            Test_Ext_Busqueda_Individual(num);
            // Poner todas las pruebas de busqueda Especifica
            bucle_ver();
            system("clear");
        }
        else if(n==2){
            //test_Insercion(num);      
            Test_Ext_Insercion_Individual(num);      
            bucle_ver();
            system("clear");

        }
        else if(n==3){
            // INSERCION DE 100 ELEMENTOS
            //Test_Eliminacion(num);
            Test_Ext_Eliminacion_Individual(num);

            bucle_ver();
            system("clear");

        }

    }
    


}

void Menu(){
    system("clear");
    while(true){
    cout<<"+--------------------------------------+"<<endl;
    cout<<"| Escoja una de estas opciones:        |"<<endl;
    cout<<"| 1. Busqueda Especifica.              |"<<endl;
    cout<<"| 2. Insercion.                        |"<<endl;
    cout<<"| 3. Eliminacion.                      |"<<endl;
    cout<<"| 4. Salir de la interfaz.             |"<<endl;
    cout<<"+--------------------------------------+"<<endl;

    int n;
    cout<<"Digite un numero: ";
    cin>>n;
    system("clear");

    if(n==1 || n==2 || n==3){
        estructuras(n);
    }
    else if(n==4){
        break;
    }   


    }


}



int main(){

    //test_Insercion(1);
    //Test_Busqueda_Individual(1);
    //test_Insercion(1);
    //Test_Eliminacion(1);
    Menu();
    return 0;
}
