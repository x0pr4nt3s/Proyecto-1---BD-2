#include "./Parser/ParserEntities.h"
#include "./SequentialFile/SequentialFile.h"
#include "./ExtendibleHashing/ExtendibleHashing.h"

int main(){

    ParserforEntity1 p1("./files/data-100k.txt");
    auto a1=p1.getDataFile();
    ExtendibleHashing extend("./files/ext_data_guardar.txt");

    for(long i=0;i<a1.size();i++){
        extend.insert(a1.at(i));

    } 
    extend.SearchRecord("1ZLG").codigo;

    volatile int sink;
    std::cout << std::fixed << std::setprecision(9) << std::left;
    // record start time
    auto start = std::chrono::system_clock::now();




    extend.deleteRecord("001J");

    // record end time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to fill and iterate a vector of " << std::setw(9)<< " ints : " << diff.count() << " s\n";
    cout<<extend.SearchRecord("001J").codigo<<endl;



/*
    Alumno a2=Alumno("CZT8","jier","pruea1 peba3","careraa");
    Alumno a3=Alumno("EZ84","jier","pruea1 pesa3","careraa");
    Alumno a4=Alumno("EZF5","jier","pruea1 pesa3","careraa");
    Alumno a5=Alumno("GGF3","jier","pruea1 pesa3","careraa");
    Alumno a6=Alumno("ZYY3","jier","pruea1 pesa3","careraa");
    Alumno a7=Alumno("FZT5","javier","prueba1 prueba3","carreraa");
    Alumno a8=Alumno("ZZT5","javier","prueba1 prueba3","carreraa");
    Alumno a9=Alumno("CZT6","jier","pruea1 peba3","careraa");
    Alumno a10=Alumno("CAT8","jier","pruea1 pesa3","careraa");



    Alumno a11=Alumno("DDT8","jier","pruea1 pesa3","careraa");


    Alumno a12=Alumno("ZZT8","jier","pruea1 pesa3","careraa");
    Alumno a13=Alumno("AB19","jier","pruea1 pesa3","careraa");

    Alumno a14=Alumno("AB96","jier","pruea1 pesa3","careraa");
    Alumno a15=Alumno("A888","jier","pruea1 pesa3","careraa");
    Alumno a16=Alumno("fff8","jier","pruea1 pesa3","careraa");
    Alumno a17=Alumno("fhhh","jier","pruea1 pesa3","careraa");
    Alumno a18=Alumno("zzzz","jier","pruea1 pesa3","careraa");
    Alumno a19=Alumno("bbbb","jier","pruea1 pesa3","careraa");
    Alumno a20=Alumno("CZT7","javier","prueba1 prueba2","carreraa");
    Alumno a21=Alumno("yyy7","javier","prueba1 prueba2","carreraa");

    Alumno a22=Alumno("8yy7","javier","prueba1 prueba2","carreraa");
    Alumno a23=Alumno("Fyy7","javier","prueba1 prueba2","carreraa");
    Alumno a24=Alumno("yZZ7","javier","prueba1 prueba2","carreraa");
    Alumno a25=Alumno("XXy7","javier","prueba1 prueba2","carreraa");
    Alumno a26=Alumno("y297","javier","prueba1 prueba2","carreraa");


    extend.insert(a2);
    extend.insert(a3);
    extend.insert(a4);
    extend.insert(a5);
    extend.insert(a6);
    extend.insert(a7);
    extend.insert(a8);

    extend.showAllRecords();

    cout<<"***********DELETEEEEEEEEEEEE************"<<endl;

    extend.deleteRecord("EZ84");

    extend.deleteRecord("EZF5");

    extend.deleteRecord("CZT8");

    extend.deleteRecord("EZ84");

    cout<<"***********DELETEEEEEEEEEEEE************"<<endl;

       
    extend.insert(a9);
    extend.insert(a10);
    extend.insert(a11);
    extend.insert(a12);

    extend.insert(a13);
    extend.insert(a14);
    extend.insert(a15);
    extend.insert(a16);
    extend.insert(a17);
    extend.insert(a18);
    extend.insert(a19);
    extend.insert(a20);
    extend.insert(a21);
    extend.insert(a22);
    extend.insert(a23);
    extend.insert(a24);
    extend.insert(a25);
    extend.insert(a26);
*/

/*
            


        */
    //extend.showAllRecords();
/*
    cout<<extend.SearchRecord("1ZLF").codigo<<endl;






    SequentialFile seq = SequentialFile("./files/data_guardar.txt","./files/auxiliar_data.txt");




    //seq.writeRecord(a1.at(2));    
    //auto v2 = seq.scanAll();







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
    }
    //b.showData();

    


    
    seq.writeRecord(a1.at(0));
   
    cout<<"------------"<<endl;

    auto v2 = seq.scanAll();

    
    for(int i=0;i<v2.size();i++){
        v2.at(i).showData();
    }
     
    //seq.find_by_binary();

*/

    return 0;
}
