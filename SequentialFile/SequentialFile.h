#include "../Entidades/Alumno.h"



class SequentialFile{

private:

    string file_name;
    string auxiliar_data;
    string construccion_file;
    long num_records = -1;
    long aux_num_records = -1;
    long max_tam_aux = 50;
public:

    SequentialFile(string file_name,string auxiliar_data,string construccion_file,int tam){
        this->file_name = file_name;
        this->auxiliar_data = auxiliar_data;
        this->num_records = get_num_records();
        this->aux_num_records = get_num_records_aux();
        this->construccion_file = construccion_file;
        this->max_tam_aux= tam;
    } 

    // identificar cantidad de registros 
    int number_records_file(fstream& archivo){        
        if(archivo.is_open()){
            archivo.seekg(0,ios::end);
            int numrecords=((int)archivo.tellg()-sizeof(int)-sizeof(char))/sizeof(Alumno);
            archivo.seekg(0,ios::end);
            if(numrecords<0){return 0;}

            this->num_records = num_records;
            return numrecords;
        }
        return 0;
    }

    int get_num_records(){
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        file.seekg(0, ios::end);//ubicar cursos al final del archivo
        long size = file.tellg();//cantidad de bytes del archivo    
        size-=(sizeof(long)+sizeof(char));  
        file.close();

        if(size < 0 ){
            return 0;
        }else{
            return  size / sizeof(Alumno);

        }
    }

    int get_num_records_aux(){
        ifstream file(this->auxiliar_data, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        file.seekg(0, ios::end);//ubicar cursos al final del archivo
        long size = file.tellg();//cantidad de bytes del archivo    
        file.close();

        if(size < 0 ){
            return 0;
        }else{
            return  size / sizeof(Alumno);
        }     
    }



    int binary_search(fstream& archivo,int l,int r,Alumno a1){
        if (r >= l) {
            int mid = (l + (r - l) / 2);
    
            //cout<<"Actual: ["<<l<<","<<r<<"]"<<endl;
            Alumno b1=Alumno();    
            archivo.seekg(mid * sizeof(Alumno) + sizeof(long) + sizeof(char), ios::beg);
            archivo.read((char*)& b1, sizeof(Alumno));
            //b1.showData();
            if (b1 == a1)
                return mid;

            if (b1>a1)
                return binary_search(archivo,l,mid-1,a1);
            
            if(mid>=number_records_file(archivo)){
                return mid;
            }


            return binary_search(archivo,mid+1,r,a1);

        }
        else{
           return l; 
        }

        return -2;
    }

    int find_by_binary(Alumno a1){
        fstream archivo(this->file_name,ios::binary | ios::in);
        return binary_search(archivo,0,this->num_records,a1);
        //cout<<"LA POSICION A INSERTAR ES"<<binary_search(archivo,0,number_records_file(archivo),a1)<<endl;
    }

    
    // SEARCH:
    
    int bsearch(fstream& archivo,int l,int r,string a1){
        if (r >= l) {
            int mid = (l + (r - l) / 2);
            //cout<<"Actual: ["<<l<<","<<r<<"]"<<endl;
            Alumno b1=Alumno();    
            archivo.seekg(mid * sizeof(Alumno) + sizeof(long) + sizeof(char), ios::beg);
            archivo.read((char*)& b1, sizeof(Alumno));

            string keyb1=b1.get_codigo();
            if (keyb1 == a1 && b1.get_nextvalue()!=-2)
                return mid;

            if (keyb1>a1)
                return bsearch(archivo,l,mid-1,a1);
            
            if(mid>=number_records_file(archivo)){
                return mid;
            }

            return bsearch(archivo,mid+1,r,a1);
            
        }
        else{
           return l*(-1); 
        }

        return -1;
    }
   
    
    vector<Alumno> search(string key){
        vector<Alumno> output;
        fstream archivo(this->file_name,ios::binary | ios::in);
        fstream aux_file(this->auxiliar_data, ios::in | ios::binary);

        Alumno al1=Alumno();
        
        int posicion_obj=bsearch(archivo,0,this->num_records,key);
        //cout<<posicion_obj<<endl;
        if(posicion_obj < 0){
            int lectura=posicion_obj*-1; // Convierte la posicion que obtuvo en negativo a positivo
            lectura--; // Le resta uno pq comienza desde el 0 y no del 1
            archivo.seekg(sizeof(Alumno)*(lectura)+sizeof(long)+sizeof(char),ios::beg);
            archivo.read((char*)&al1, sizeof(Alumno));
            output.push_back(al1);
            while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                long new_pos=al1.get_nextvalue()-1;
                aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                aux_file.read((char*)&al1, sizeof(Alumno));
                if(al1.get_codigo()<key && al1.get_nextvalue()!=-2){
                    //al1.showData();
                    output.push_back(al1);
                }
                if(al1.get_codigo()==key && al1.get_nextvalue()!=-2){
                    //cout<<"AHHH"<<endl;
                    output.push_back(al1);
                    return output;
                }
            }
            output.clear();
            return output;                    
        }
        else if(posicion_obj==0){
            archivo.seekg(sizeof(Alumno)*(posicion_obj)+sizeof(long)+sizeof(char),ios::beg);
            archivo.read((char*)&al1, sizeof(Alumno));
            if(al1.get_codigo()==key && al1.get_nextvalue()!=-2){
                long header_next;
                char header_char;
                archivo.seekg(0,ios::beg);
                archivo.read((char*)&header_next, sizeof(long));
                archivo.seekg(sizeof(long),ios::beg);
                archivo.read((char*)&header_char, sizeof(char));
                if(header_char!='d'){
                    Alumno nuevo=Alumno();
                    // Leer linealmente AUXILIAR PARA ENCONTRAR AHI EL ELEMENTO EN 0
                    aux_file.seekg(sizeof(Alumno)*(header_next-1),ios::beg);
                    aux_file.read((char*)&nuevo, sizeof(Alumno));
                    output.push_back(nuevo);
                    //nuevo.showData();
                    if(nuevo.get_codigo()==key){
                        return output;
                    }
                    else{ // EN CASO EL PRIMER ELEMENTO EN AUX QUE APUNTE HEADER NO SEA LA KEY SEGUIR LINEALMENTE LOS PUNTEROS.
                    while(nuevo.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                        long new_pos=nuevo.get_nextvalue()-1;
                        aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                        aux_file.read((char*)&nuevo, sizeof(Alumno));
                        //nuevo.showData();
                        if(nuevo.get_codigo()<key){
                            output.push_back(nuevo);
                        }
                        if(nuevo.get_codigo()==key){
                            output.push_back(nuevo);
                            return output;
                        }
                    }
                    output.push_back(al1);
                    return output;
                    }
                }
                //output.push_back(al1);
                return output;
            }
            else if(al1.get_codigo()!=key){ 
                // leemos el header de datafile a ver donde apunta:
                long header_next;
                char header_char;

                archivo.seekg(0,ios::beg);
                archivo.read((char*)&header_next, sizeof(long));
                archivo.seekg(sizeof(long),ios::beg);
                archivo.read((char*)&header_char, sizeof(char));

                if(header_char!='d'){
                    // Leer linealmente AUXILIAR PARA ENCONTRAR AHI EL ELEMENTO EN 0
                    aux_file.seekg(sizeof(Alumno)*(header_next-1),ios::beg);
                    aux_file.read((char*)&al1, sizeof(Alumno));
                    output.push_back(al1);

                    if(al1.get_codigo()==key){
                        return output;
                    }
                    else{ // EN CASO EL PRIMER ELEMENTO EN AUX QUE APUNTE HEADER NO SEA LA KEY SEGUIR LINEALMENTE LOS PUNTEROS.
                    while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                        long new_pos=al1.get_nextvalue()-1;
                        aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                        aux_file.read((char*)&al1, sizeof(Alumno));
                        if(al1.get_codigo()<key){
                            output.push_back(al1);
                        }
                        if(al1.get_codigo()==key){
                            output.push_back(al1);
                            return output;
                        }
                    }
                    output.clear();
                    return output;
                    }
                }
                else{
                    output.clear();
                    return output;
                }

                return output;
            }
        }
        else{

        al1=Alumno();
        archivo.seekg(sizeof(Alumno)*(posicion_obj)+sizeof(long)+sizeof(char),ios::beg);
        archivo.read((char*)&al1, sizeof(Alumno));
        if( al1.get_codigo()==key){            
            archivo.seekg(sizeof(Alumno)*(posicion_obj-1)+sizeof(long)+sizeof(char),ios::beg);
            archivo.read((char*)&al1, sizeof(Alumno));
            output.push_back(al1);
            while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                long new_pos=al1.get_nextvalue()-1;
                aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                aux_file.read((char*)&al1, sizeof(Alumno));
                if(al1.get_codigo()<key){
                    //al1.showData();
                    output.push_back(al1);
                }
                if(al1.get_codigo()==key){
                    //cout<<"AHHH"<<endl;
                    output.push_back(al1);
                    return output;
                }
            }            


            archivo.seekg(sizeof(Alumno)*(posicion_obj)+sizeof(long)+sizeof(char),ios::beg);
            archivo.read((char*)&al1, sizeof(Alumno));
            output.push_back(al1);
            return output;
        }
        else{
            return output;                    
        }
        }
        archivo.close();
        aux_file.close();
        return output;
    }

    vector<Alumno> rangeSearch(string key1,string key2){
        vector<Alumno> vec_return;
        auto vec_key1=search(key1);
        fstream archivo(this->file_name,ios::binary | ios::in);
        fstream aux_file(this->auxiliar_data, ios::in | ios::binary);
        long temp_pos;
        Alumno temp_key1_obj=Alumno();
        if(vec_key1.empty()){
            long pos_key1=bsearch(archivo,0,this->num_records,key1);
            if(pos_key1!=0){
                
                cout<<"Posicion : "<<pos_key1<<endl;
                archivo.seekg((sizeof(Alumno)*((pos_key1*-1)-1))+sizeof(long)+sizeof(char),ios::beg);
                archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                //temp_key1_obj.showData();
                
                long temp_next=temp_key1_obj.get_nextvalue()-1;
                char temp_char_next=temp_key1_obj.get_tipo_archivo();

                if(temp_char_next=='d'){
                    archivo.seekg((sizeof(Alumno)*(temp_next))+sizeof(long)+sizeof(char),ios::beg);
                    archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                }
                else{
                    aux_file.seekg((sizeof(Alumno)*(temp_next)),ios::beg);
                    aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));                    
                }

                if(temp_key1_obj.get_codigo()>=key1 && temp_key1_obj.get_codigo()<key2){
                    //temp_key1_obj.showData();
                    vec_key1.push_back(temp_key1_obj);
                }

                while(temp_key1_obj.get_codigo()<key2){
                    temp_next=temp_key1_obj.get_nextvalue()-1;
                    temp_char_next=temp_key1_obj.get_tipo_archivo();
                    if(temp_char_next=='d'){
                    archivo.seekg((sizeof(Alumno)*(temp_next))+sizeof(long)+sizeof(char),ios::beg);
                    archivo.read((char*)&temp_key1_obj,sizeof(Alumno));                        
                    }
                    else{
                    aux_file.seekg((sizeof(Alumno)*(temp_next)),ios::beg);
                    aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));                    
                    }

                    if(temp_key1_obj.get_codigo()>=key1 && temp_key1_obj.get_codigo()!=key2){
                        vec_return.push_back(temp_key1_obj);
                        //temp_key1_obj.showData();
                    }

                }

                if(temp_key1_obj.get_codigo()==key2){
                    //temp_key1_obj.showData();
                    vec_return.push_back(temp_key1_obj);
                }

                return vec_return;
            }
            else{
                //cout<<"Posicion"<<pos_key1<<endl;
                archivo.seekg((sizeof(Alumno)*((pos_key1*-1)))+sizeof(long)+sizeof(char),ios::beg);
                archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                // LEER HEADER : SI APUNTA A DATA SIGNIFICA QUE ES EL UNICO ELEMENTO EN EL RANGO
                // SI APUNTA A AUX SIGNIFICA QUE HAY MAS Y HAY QUE COMPARAR LINEALMENTE
                long header_lectura;
                char header_lectura_char;
                archivo.seekg(0,ios::beg);
                archivo.read((char*)&header_lectura,sizeof(long));
                archivo.seekg(sizeof(long),ios::beg);
                archivo.read((char*)&header_lectura_char,sizeof(char));

                if(header_lectura_char=='d'){
                    if(temp_key1_obj.get_codigo()<=key2 && temp_key1_obj.get_codigo()>=key1){
                        //temp_key1_obj.showData();
                        vec_return.push_back(temp_key1_obj);

                        while(temp_key1_obj.get_codigo()< key2){
                            header_lectura_char=temp_key1_obj.get_tipo_archivo();
                            header_lectura=temp_key1_obj.get_nextvalue();

                            if(header_lectura_char=='d'){
                                archivo.seekg((sizeof(Alumno)*(header_lectura-1))+sizeof(long)+sizeof(char),ios::beg);
                                archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                            }
                            else{
                                aux_file.seekg((sizeof(Alumno)*(header_lectura-1)),ios::beg);
                                aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));
                            }

                            if(temp_key1_obj.get_codigo() >=key1 && temp_key1_obj.get_codigo()<=key2){
                                //temp_key1_obj.showData();
                                vec_return.push_back(temp_key1_obj);
                            }      
                        }
 
                    }
 
                    return vec_return;
 
                }
                else{
                    aux_file.seekg((sizeof(Alumno)*((header_lectura)-1)),ios::beg);
                    aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));

                    while(temp_key1_obj.get_codigo()< key2){
                        header_lectura_char=temp_key1_obj.get_tipo_archivo();
                        header_lectura=temp_key1_obj.get_nextvalue();

                        if(header_lectura_char=='d'){
                            archivo.seekg((sizeof(Alumno)*(header_lectura-1))+sizeof(long)+sizeof(char),ios::beg);
                            archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                        }
                        else{
                            aux_file.seekg((sizeof(Alumno)*(header_lectura-1)),ios::beg);
                            aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));
                        }

                        if(temp_key1_obj.get_codigo() >=key1){
                            //temp_key1_obj.showData();
                            vec_return.push_back(temp_key1_obj);
                        }      
                    }

                    if(temp_key1_obj.get_codigo()== key2){
                        //temp_key1_obj.showData();
                        vec_return.push_back(temp_key1_obj);
                    }
                    return vec_return;
                }
            }
        }
        else{            
            long pos_key1;
            char file_key1;
            if(vec_key1.size()>1){
                pos_key1=vec_key1.at(vec_key1.size()-2).get_nextvalue();
                file_key1=vec_key1.at(vec_key1.size()-2).get_tipo_archivo();                
                //cout<<pos_key1<<endl;

                if(file_key1=='d'){
                    archivo.seekg((sizeof(Alumno)*(pos_key1-1))+sizeof(long)+sizeof(char),ios::beg);
                    archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                }
                else{
                    aux_file.seekg((sizeof(Alumno)*(pos_key1-1)),ios::beg);
                    aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));
                }

                while(temp_key1_obj.get_codigo()<=key2 && temp_key1_obj.get_nextvalue()!=-1){
                    vec_return.push_back(temp_key1_obj);
                    temp_pos=temp_key1_obj.get_nextvalue();
                    temp_key1_obj.showData();

                    if(temp_key1_obj.get_tipo_archivo()=='d'){
                        archivo.seekg((sizeof(Alumno)*(temp_pos-1))+sizeof(long)+sizeof(char),ios::beg);
                        archivo.read((char*)&temp_key1_obj,sizeof(Alumno));
                    }
                    else{
                        aux_file.seekg((sizeof(Alumno)*(temp_pos-1)),ios::beg);
                        aux_file.read((char*)&temp_key1_obj,sizeof(Alumno));                            
                    }
                }

                if(temp_key1_obj.get_nextvalue()==-1){
                    temp_key1_obj.showData();
                    vec_return.push_back(temp_key1_obj);
                }
            
            }
            else{
                cout<<"igual a 1"<<endl;
            }
            
            return vec_return;
        }
    }


    void Reconstruccion(){

        cout<<"-------------------------------------------------"<<endl;
        fstream archivo(this->file_name,ios::binary | ios::in);
        fstream aux_file(this->auxiliar_data, ios::in | ios::binary);
        // ----------------------------------------
        // Sobreescribe todo y LIMPIA EL ARCHIVO
        ofstream file(this->construccion_file);
        char a='F';
        file.write((char*)&a, sizeof(char));  
        file.close();
        // Preparando la correcta escritura
        fstream file_const(this->construccion_file,ios::binary | ios::in | ios::out);
        
        // Lectura lineal de los punteros empezando por header
        long header_value;
        char header_char_value;

        long contador=2;

        
        archivo.seekg(0,ios::beg);
        archivo.read((char*)(&header_value), sizeof(long));
        archivo.seekg(sizeof(long),ios::beg);
        archivo.read((char*)(&header_char_value), sizeof(char));
        long value_next=header_value;
        char value_next_char=header_char_value;
        Alumno al1=Alumno();
        // CONSTRUYENDO EL ARCHIVO TEMPORAL PARA ORDENAR
        while(value_next!=-1){
            if(value_next_char=='d'){
                archivo.seekg(((sizeof(Alumno)*(value_next-1))+sizeof(long)+sizeof(char)),ios::beg);
                archivo.read((char*)&al1, sizeof(Alumno));     
            }
            else{
                aux_file.seekg((sizeof(Alumno)*(value_next-1)),ios::beg);
                aux_file.read((char*)&al1, sizeof(Alumno));
            }
            value_next=al1.get_nextvalue();
            value_next_char=al1.get_tipo_archivo();
            al1.set_nextval(contador);
            al1.set_tipo_archivo('d');
            //al1.showData();

            // ESCRITURA 
            file_const.seekp((sizeof(Alumno)*(contador-2)),ios::beg);
            file_const.write((char*)&al1, sizeof(Alumno));    
            //al1.showData();
            contador++;
        }
        al1.set_nextval(-1);
        al1.set_tipo_archivo('d');
        //al1.showData();
        file_const.seekp((sizeof(Alumno)*(contador-3)),ios::beg);
        file_const.write((char*)&al1, sizeof(Alumno));    




        //SOBRESCRIBIENDO FILE DATA:
        archivo.close();
        
        ofstream archivoborrar(this->file_name);
        char b='F';
        archivoborrar.write((char*)&a, sizeof(char));  
        archivoborrar.close();
        
        fstream archivodata(this->file_name,ios::binary | ios::in | ios::out);
        long cont_lineal=0;
        //SOBRESCRIBIENDO HEADER:
        
        long header_next=1;
        long header_c='d';
        archivodata.seekp(0,ios::beg);
        archivodata.write((char*)(&header_next), sizeof(long));
        archivodata.seekp(sizeof(long),ios::beg);
        archivodata.write((char*)(&header_c), sizeof(char));

        //LEYENDO COPIA O CONSTRUCT FILE
        Alumno copia=Alumno();
        file_const.seekg(cont_lineal*sizeof(Alumno),ios::beg);
        file_const.read((char*)(&copia), sizeof(Alumno));
        copia.showData(); 

        archivodata.seekp((sizeof(Alumno)*cont_lineal)+sizeof(long)+sizeof(char),ios::beg);
        archivodata.write((char*)(&copia), sizeof(Alumno));
        value_next=copia.get_nextvalue();
        //cout<<"ACA SE VE LA COPIA"<<endl;
        while(value_next!=-1){
        //cout<<"Escribiendo"<<endl;
        cont_lineal++;
        file_const.seekg(cont_lineal*sizeof(Alumno),ios::beg);
        file_const.read((char*)(&copia), sizeof(Alumno));
        value_next=copia.get_nextvalue();        
        archivodata.seekp((sizeof(Alumno)*cont_lineal)+sizeof(long)+sizeof(char),ios::beg);
        archivodata.write((char*)(&copia), sizeof(Alumno));
        }
        // SOBRESCRIBIENDO AUX DATA:
        aux_file.close();
        ofstream fileaux(this->auxiliar_data);
        char c='F';
        fileaux.write((char*)&a, sizeof(char));  
    }




    void remove(string key){
        auto vec_obj=search(key);
        fstream archivo(this->file_name,ios::binary | ios::in | ios::out);
        fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);
        
        Alumno a1=Alumno();
        //cout<<vec_obj.size()<<endl;
        //cout<<"SIZE: "<<vec_obj.size()<<" "<<vec_obj.at(vec_obj.size()-1).get_nextvalue()<<" "<<bsearch(archivo,0,this->num_records,key)<<endl;
        if(vec_obj.size()>0 && vec_obj.at(vec_obj.size()-1).get_nextvalue()!=-2 ){
            for(int i=0;i<vec_obj.size();i++){
                vec_obj.at(i).showData();
            }
            // EMPIEZA EL ALGORITMO PARA ELIMINAR

            if(vec_obj.size()==1){
                //cout<<"CASO 3: SOLO CUENTO CON UN ELEMENTO, Y EL HEADER"<<endl;                
                long next_val_temp;
                char typefile_temp;
                long next_val_vec=vec_obj.at(vec_obj.size()-1).get_nextvalue();
                char typefile_vec=vec_obj.at(vec_obj.size()-1).get_tipo_archivo();
                // Leer el HEADER

                archivo.seekg(0,ios::beg);
                archivo.read((char*)(&next_val_temp), sizeof(long));
                archivo.seekg(sizeof(long),ios::beg);
                archivo.read((char*)(&typefile_temp), sizeof(char));

                //cout<<next_val_temp<<" "<<typefile_temp<<" : "<<next_val_vec<<" "<<typefile_vec<<endl;
                
                // SETEAR VALORES DEL ELIMINADO A -2
                vec_obj.at(vec_obj.size()-1).set_nextval(-2);
                //vec_obj.at(vec_obj.size()-1).showData();                
                //


                // SOBRESCRIBIENDO EL HEADER
                archivo.seekp(0,ios::beg);
                archivo.write((char*)(& next_val_vec), sizeof(long));
                archivo.seekp(sizeof(long),ios::beg);
                archivo.write((char*)(&typefile_vec), sizeof(char));
                
                // SOBRESCRIBIENDO EL VALOR ELMINADO A -2 
                if(typefile_temp=='d'){
                    archivo.seekp(((sizeof(Alumno)*(next_val_temp-1))+sizeof(long)+sizeof(char)),ios::beg);
                    archivo.write((char*)(&vec_obj.at(vec_obj.size()-1)), sizeof(Alumno));     
                }
                else{
                    aux_file.seekp((sizeof(Alumno)*(next_val_temp-1)),ios::beg);
                    aux_file.write((char*)(&vec_obj.at(vec_obj.size()-1)), sizeof(Alumno));
                }


                //archivo.

            }
            else if(vec_obj.size()!=1 && bsearch(archivo,0,this->num_records,key)==0){
                //cout<<"CASO 2: TIENE DOS O MAS ELEMENTOS EN EL VECTOR QUE APUNTAN AL ELIMINADO PERO ANTES DE ESE VECTOR ESTA EL HEADER."<<endl;
                long next_val_temp;
                char typefile_temp;
                // Leer el HEADER

                archivo.seekg(0,ios::beg);
                archivo.read((char*)(&next_val_temp), sizeof(long));

                
                //cout<<next_val_temp<<endl;

                long posicion_eliminado=vec_obj.at(vec_obj.size()-2).get_nextvalue();              
                //cout<<posicion_eliminado<<endl;
                vec_obj.at(vec_obj.size()-2).set_nextval(vec_obj.at(vec_obj.size()-1).get_nextvalue());
                vec_obj.at(vec_obj.size()-2).set_tipo_archivo(vec_obj.at(vec_obj.size()-1).get_tipo_archivo());
                //cout<<"--------------------"<<endl;
                //vec_obj.at(vec_obj.size()-2).showData();

                // Sobreescribir puntero anterior que apunte al siguiente de el eliminado

                // Sobreescribir puntero del eliminado
                vec_obj.at(vec_obj.size()-1).set_nextval(-2);
                vec_obj.at(vec_obj.size()-1).showData();
                
                aux_file.seekp((sizeof(Alumno)*(next_val_temp-1)),ios::beg);
                aux_file.write((char*)(&vec_obj.at(vec_obj.size()-2)), sizeof(Alumno));

                archivo.seekp(((sizeof(Alumno)*(posicion_eliminado-1))+sizeof(long)+sizeof(char)),ios::beg);
                archivo.write((char*)(&vec_obj.at(vec_obj.size()-1)), sizeof(Alumno));
    
                archivo.close();
                aux_file.close();
            }
            else{
                //cout<<"CASO 1: SOLO TIENE DOS ELEMENTOS EN EL VECTOR DE REGISTROS"<<endl;
                //vector<Alumno> vec_old;
                auto vec_old=search(vec_obj.at(vec_obj.size()-2).get_codigo());
                //cout<<vec_old.size();
                // cout<<"FAAAA"<<endl;
                cout<<"------------------"<<endl;
                // POSICION DEL ANTERIOR AL ELIMINADO
                vec_old.at(vec_old.size()-2).showData();
                
                long posicion_old=vec_old.at(vec_old.size()-2).get_nextvalue();
                char tipefile= vec_old.at(vec_old.size()-2).get_tipo_archivo();
                // POSICION DEL ELIMINADO
                long posicion_eliminado=vec_obj.at(vec_obj.size()-2).get_nextvalue();
                char tipefile_eliminado=vec_obj.at(vec_obj.size()-2).get_tipo_archivo();

                //cout<<posicion_old<<" "<<tipefile<<" : "<<posicion_eliminado<<" "<<tipefile_eliminado<<endl;

                // SETEANDO VALORES DEL ANTERIOR AL ELIMINADO
                vec_obj.at(vec_obj.size()-2).set_nextval(vec_obj.at(vec_obj.size()-1).get_nextvalue());
                vec_obj.at(vec_obj.size()-2).set_tipo_archivo(vec_obj.at(vec_obj.size()-1).get_tipo_archivo());

                //vec_obj.at(vec_obj.size()-2).showData();

                // SETEANDO LOS VALORES DEL ELIMINADO
                vec_obj.at(vec_obj.size()-1).set_nextval(-2);
                vec_obj.at(vec_obj.size()-1).set_tipo_archivo('d');

                //vec_obj.at(vec_obj.size()-1).showData();

                
                if(tipefile=='d'){
                    archivo.seekp(((sizeof(Alumno)*(posicion_old-1))+sizeof(long)+sizeof(char)),ios::beg);
                    archivo.write((char*)(&vec_obj.at(vec_obj.size()-2)), sizeof(Alumno));            
                }
                else{
                    aux_file.seekp((sizeof(Alumno)*(posicion_old-1)),ios::beg);
                    aux_file.write((char*)(&vec_obj.at(vec_obj.size()-2)), sizeof(Alumno));
                }

                if(tipefile_eliminado=='d'){
                    archivo.seekp(((sizeof(Alumno)*(posicion_eliminado-1))+sizeof(long)+sizeof(char)),ios::beg);
                    archivo.write((char*)(&vec_obj.at(vec_obj.size()-1)), sizeof(Alumno));            
                }
                else{
                    aux_file.seekp((sizeof(Alumno)*(posicion_eliminado-1)),ios::beg);
                    aux_file.write((char*)(&vec_obj.at(vec_obj.size()-1)), sizeof(Alumno));
                }

            }        
        }
        else{
            //cout<<"El OBJETO CON ESE CODIGO NO EXISTE"<<endl;
        }
    }


    void add(Alumno record){
        this->aux_num_records=get_num_records_aux();
        this->num_records=get_num_records();
        fstream archivo(this->file_name,ios::binary | ios::in | ios::out);
        fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);
        long nextval;
        char data_type;
        if(this->num_records==0){ // Si el archivo de data esta vacio
            nextval = 1;
            data_type = 'd';
            archivo.write((char*)(&nextval), sizeof(nextval));
            archivo.write((char*)(&data_type), sizeof(data_type));
            archivo.seekp(sizeof(nextval)+sizeof(data_type),ios::beg);
            archivo.write((char*) &record, sizeof(Alumno));
            this->num_records++;

            //guardar en formato binario
        }
        else{ // En caso si hayan valores dentro
            
            Alumno al1=Alumno();
            long posicion_obj=bsearch(archivo,0,number_records_file(archivo),record.get_codigo());
            //cout<<"Posicion: "<<posicion_obj<<endl;

            if(posicion_obj < 0){
                long new_pos=posicion_obj*-1;
                new_pos--;
                // Leyendo el objeto en DATA FILE:
                archivo.seekg(sizeof(Alumno)*(new_pos)+sizeof(long)+sizeof(char),ios::beg);
                archivo.read((char*)&al1, sizeof(Alumno));
                if(al1.get_tipo_archivo()=='d'){ 

                    // Seteandp e intercambiando valores de los punteros para insertar el valor nuevo
                    record.set_nextval(al1.get_nextvalue());
                    record.set_tipo_archivo(al1.get_tipo_archivo());
                    //cout<<"Estamos aqui"<<endl;
                    //record.showData();
                    al1.set_nextval(this->aux_num_records+1);
                    al1.set_tipo_archivo('a');
                    //al1.showData();

                    // SETEANDO DATA DE ALGUN BORRADO

                    Alumno temp_del=Alumno();
                    archivo.seekg((sizeof(Alumno)*(new_pos+1))+sizeof(long)+sizeof(char),ios::beg);
                    archivo.read((char*)&temp_del, sizeof(Alumno));        
                    //temp_del.showData();

                    if(temp_del.get_nextvalue()==-2){
                        //cout<<"CASO 11: EL OBJETO MENOR AL MIO SE ENCUENTRA EN DATA, ESCRIBO UN REGISTRO ENCIMA DEL -2 EN DATA "<<endl;
                        // RESETEANDO EL ELEMENTO ANTERIOR
                        al1.set_nextval(new_pos+2);
                        al1.set_tipo_archivo('d');
                        //al1.showData();

                        archivo.seekp(sizeof(Alumno)*(new_pos)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&al1, sizeof(Alumno));

                        archivo.seekp(sizeof(Alumno)*(new_pos+1)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&record, sizeof(Alumno));


                    }
                    else{
                        //cout<<"CASO 7: EL OBJETO MENOR AL MIO SE ENCUENTRA EN DATA, ESCRIBO UN REGISTRO MAS EN AUX "<<endl;
                        //cout<<"------------------"<<endl;
                        archivo.seekp(sizeof(Alumno)*(new_pos)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&al1, sizeof(Alumno));

                        aux_file.seekp(sizeof(Alumno)*(this->aux_num_records),ios::beg);
                        aux_file.write((char*)&record, sizeof(Alumno));
                    }

                    

                    //
                    archivo.close();
                    aux_file.close();        
                    this->aux_num_records=this->aux_num_records+1;
                    //cout<<"SIZE :"<<aux_num_records<<endl;
                    if(this->aux_num_records==max_tam_aux-1){
                        this->Reconstruccion();    
                    }

                }
                else{
                    vector<Alumno> vec_temp;
                    vec_temp.push_back(al1);
                    while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                        long new_pos=al1.get_nextvalue()-1;
                        aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                        aux_file.read((char*)&al1, sizeof(Alumno));
                        if(al1.get_codigo()<record.get_codigo()){
                            vec_temp.push_back(al1);
                        }
                        else if(al1.get_codigo()>record.get_codigo()){
                                break;
                        }
                        else if(al1.get_codigo()==record.get_codigo()){
                            //cout<<"YA EXISTE UN REGISTRO CON ESE CODIGO"<<endl;
                            archivo.close();
                            aux_file.close();
                            break;
                        }
                    } 

                    if(archivo.is_open()){
                        //cout<<"CASO 6: EN CASO QUE EL QUE ES MAYOR A MI ESTE EN AUX Y LUEGO APUNTE A DATA"<<endl;
                        //cout<<"------------------"<<endl;
                        record.set_nextval(vec_temp.at(vec_temp.size()-1).get_nextvalue());
                        record.set_tipo_archivo(vec_temp.at(vec_temp.size()-1).get_tipo_archivo());
                        //record.showData();
                        vec_temp.at(vec_temp.size()-1).set_nextval(this->aux_num_records+1);
                        vec_temp.at(vec_temp.size()-1).set_tipo_archivo('a');
                        //vec_temp.at(vec_temp.size()-1).showData();         
                        //  SOLO FALTA PONER EL ESCRIBIR:
                        
                        
                        if(vec_temp.size()==1){
                            long temp_value=posicion_obj*-1;

                            Alumno temp_del=Alumno();
                            archivo.seekg((sizeof(Alumno)*temp_value)+sizeof(long)+sizeof(char),ios::beg);
                            archivo.read((char*)&temp_del, sizeof(Alumno));
                            

                            if(temp_del.get_nextvalue()==-2){
                                //cout<<"CASO 9: DESPUES DEL ELEMENTO QUE APUNTA A AUX HAY UN -2 "<<endl;                        

                                // RESETEANDO LOS VALORES
                                //record.showData();
                                vec_temp.at(vec_temp.size()-1).set_nextval(temp_value+1);
                                vec_temp.at(vec_temp.size()-1).set_tipo_archivo('d');
                                
                                //vec_temp.at(vec_temp.size()-1).showData();
                                //record.showData(); 
                                
                                //cout<<temp_value<<" "<<temp_value+1<<endl;
                                //cout<<temp_value<<endl;
                                
                                archivo.seekp((sizeof(Alumno)*temp_value-1)+sizeof(long)+sizeof(char),ios::beg);
                                archivo.write((char*)&(vec_temp.at(vec_temp.size()-1)), sizeof(Alumno));
                                
                                archivo.seekp((sizeof(Alumno)*temp_value)+sizeof(long)+sizeof(char),ios::beg);
                                archivo.write((char*)&record, sizeof(Alumno));                                
                            }
                            else{
                                temp_value=temp_value-1;
                                //cout<<"CASO 10: DESPUES DEL ELEMENTO QUE APUNTA A AUX HAY UN ELEMENTO MAYOR A NUESTRO REGISTRO"<<endl;                        

                                archivo.seekp(sizeof(Alumno)*(temp_value)+sizeof(long)+sizeof(char),ios::beg);
                                archivo.write((char*)&vec_temp.at(vec_temp.size()-1), sizeof(Alumno));

                                aux_file.seekp(sizeof(Alumno)*(this->aux_num_records),ios::beg);
                                aux_file.write((char*)&record, sizeof(Alumno));
                                
                                archivo.close();
                                aux_file.close();        
                                this->aux_num_records=this->aux_num_records+1;
                                //cout<<"SIZE :"<<aux_num_records<<endl;
                                if(this->aux_num_records==max_tam_aux-1){
                                    this->Reconstruccion();    
                                }

                            }

                        }
                        else{
                            
                            long temp_value=vec_temp.at(vec_temp.size()-2).get_nextvalue();
                            temp_value=temp_value-1;                            
                            
                            // VALIDACION SI HAY UN -2 POR AHI
                            long posicion_deleted=posicion_obj*-1;
                            //cout<<posicion_deleted;
                            Alumno temp_del=Alumno();
                            archivo.seekg((sizeof(Alumno)*posicion_deleted)+sizeof(long)+sizeof(char),ios::beg);
                            archivo.read((char*)&temp_del, sizeof(Alumno));

                            if(temp_del.get_nextvalue()==-2){
                                //cout<<"CASO 8: UN ELMENTO DESPUES DEL QUE ESTABA EN DATA TIENE -2."<<endl;                            
                                // RESETEANDO LOS VALORES
                                //record.showData();
                                vec_temp.at(vec_temp.size()-1).set_nextval(posicion_deleted+1);
                                vec_temp.at(vec_temp.size()-1).set_tipo_archivo('d');
                                //vec_temp.at(vec_temp.size()-1).showData(); 
                                //cout<<posicion_deleted<<" "<<temp_value<<endl;
                                archivo.seekp((sizeof(Alumno)*posicion_deleted)+sizeof(long)+sizeof(char),ios::beg);
                                archivo.write((char*)&record, sizeof(Alumno));
                                
                                aux_file.seekp(sizeof(Alumno)*(temp_value),ios::beg);
                                aux_file.write((char*)&vec_temp.at(vec_temp.size()-1), sizeof(Alumno));

                                archivo.close();
                                aux_file.close();        
                                this->aux_num_records=this->aux_num_records+1;
                                cout<<"SIZE :"<<aux_num_records<<endl;
                                if(this->aux_num_records==max_tam_aux-1){
                                    this->Reconstruccion();    
                                }

                            }
                            else{
                                aux_file.seekp(sizeof(Alumno)*(temp_value),ios::beg);
                                aux_file.write((char*)&vec_temp.at(vec_temp.size()-1), sizeof(Alumno));

                                aux_file.seekp(sizeof(Alumno)*(this->aux_num_records),ios::beg);
                                aux_file.write((char*)&record, sizeof(Alumno));

                                archivo.close();
                                aux_file.close();        
                                this->aux_num_records=this->aux_num_records+1;
                                cout<<"SIZE :"<<aux_num_records<<endl;
                                if(this->aux_num_records==max_tam_aux-1){
                                    this->Reconstruccion();    
                                }


                            }
                        }
                        /*
                        this->aux_num_records=this->aux_num_records+1;
                        cout<<"SIZE :"<<aux_num_records<<endl;
                        if(this->aux_num_records==max_tam_aux-1){
                            this->Reconstruccion();    
                        }*/
                    }
                }

            }
            else if(posicion_obj==0){
                long header_next;
                char header_char;

                archivo.seekg(0,ios::beg);
                archivo.read((char*)&header_next, sizeof(long));
                archivo.seekg(sizeof(long),ios::beg);
                archivo.read((char*)&header_char, sizeof(char));

                if(header_char!='d'){
                    vector<Alumno> output;
                    // Leer linealmente AUXILIAR PARA ENCONTRAR AHI EL ELEMENTO EN 0
                    aux_file.seekg(sizeof(Alumno)*(header_next-1),ios::beg);
                    aux_file.read((char*)&al1, sizeof(Alumno));
                    //al1.showData();
                    output.push_back(al1);
                    if(al1.get_codigo()>record.get_codigo()){
                        //this->aux_num_records=aux_num_records+1;
                        //cout<<"CASO 2: EL OBJETO ES MENOR QUE 1D Y EL HEADER APUNTA A AUX ,PERO ES MENOR QUE LO QUE APUNTA EL HEADER EN AUX"<<endl;
                        long temp_next=this->aux_num_records;
                        temp_next=temp_next+1;
                        char temp_char_h='a';
                        record.set_nextval(header_next);
                        record.set_tipo_archivo(header_char);

                        // ESCRITURA HECHA:
                                           
                        aux_file.seekp(sizeof(Alumno)*(temp_next-1),ios::beg);
                        aux_file.write((char*) &record, sizeof(Alumno));   
                        
                        archivo.seekp(0,ios::beg);
                        archivo.write((char*) &temp_next, sizeof(long));
                        archivo.seekp(sizeof(long),ios::beg);
                        archivo.write((char*) &temp_char_h, sizeof(char));
                        
                        archivo.close();
                        aux_file.close();
                        this->aux_num_records=this->aux_num_records+1;
                        if(this->aux_num_records==max_tam_aux-1){
                            // Reconstruccion    
                        }
                    
                    }
                    else{ // EN CASO EL PRIMER ELEMENTO EN AUX QUE APUNTE HEADER NO SEA LA KEY SEGUIR LINEALMENTE LOS PUNTEROS.
                        while(al1.get_tipo_archivo()!='d'){ // Validacion de seguimiento lineal de puntero en AUX
                            long new_pos=al1.get_nextvalue()-1;
                            aux_file.seekg(sizeof(Alumno)*(new_pos),ios::beg);
                            aux_file.read((char*)&al1, sizeof(Alumno));
                            if(al1.get_codigo()<record.get_codigo()){
                                output.push_back(al1);
                            }
                            if(al1.get_codigo()>record.get_codigo()){
                                break;
                            }
                            if(al1.get_codigo()==record.get_codigo()){
                                archivo.close();
                                aux_file.close();
                                //cout<<"YA EXISTE UN REGISTRO CON ESE CODIGO"<<endl;
                                break;
                            }
                        }

                        if(output.size()==1 && archivo.is_open()){
                            //cout<<"CASO 3: EL RECORRIDO DE LOS PUNTEROS DESDE LA POSICION 0 TIENE 1 ELEMENTO"<<endl;
                            for(int i=0;i<output.size();i++){
                                output.at(i).showData();
                            }
                            // Guardar posicion del que escribire:
                            long header_val;

                            record.set_nextval(output.at(output.size()-1).get_nextvalue());
                            record.set_tipo_archivo(output.at(output.size()-1).get_tipo_archivo());
                            long total_aux_records=this->aux_num_records+1;
                            output.at(output.size()-1).set_nextval(total_aux_records);
                            output.at(output.size()-1).set_tipo_archivo('a');
                            //output.at(output.size()-1).showData();
                            //record.showData();
                            archivo.seekg(0,ios::beg);
                            archivo.read((char*)&header_val, sizeof(long));

                                                        
                            aux_file.seekp(sizeof(Alumno)*(header_val-1),ios::beg);
                            aux_file.write((char*)&output.at(output.size()-1),sizeof(Alumno));

                            aux_file.seekp(sizeof(Alumno)*(this->aux_num_records),ios::beg);
                            aux_file.write((char*)&record,sizeof(Alumno));
                            
                            archivo.close();
                            aux_file.close();
                            this->aux_num_records=this->aux_num_records+1;
                            if(this->aux_num_records==max_tam_aux-1){
                                // Reconstruccion    
                            }
                        }
                        else if(output.size()>1 && archivo.is_open()){
                            //cout<<"CASO 4: EL RECORRIDO DE LOS PUNTEROS DESDE LA POSICION 0 TIENE MAS DE 1 ELEMENTO"<<endl;
                            long header_val;
                            char header_char;
                            // SETEANDO POSICION DONDE ESCRIBIR
                            header_val=output.at(output.size()-2).get_nextvalue();
                            header_char=output.at(output.size()-2).get_tipo_archivo();
                            // APUNTANDO A MI CON EL PUNTERO DEL ELEMENTO ANTERIOR
                            long total_aux_records=this->aux_num_records+1;
                            record.set_nextval(output.at(output.size()-1).get_nextvalue());
                            record.set_tipo_archivo(output.at(output.size()-1).get_tipo_archivo());
                            output.at(output.size()-1).set_nextval(total_aux_records);
                            output.at(output.size()-1).set_tipo_archivo('a');
                            //output.at(output.size()-1).showData();
                            
                            aux_file.seekp(sizeof(Alumno)*(header_val-1),ios::beg);
                            aux_file.write((char*)&output.at(output.size()-1),sizeof(Alumno));

                            aux_file.seekp(sizeof(Alumno)*(this->aux_num_records),ios::beg);
                            aux_file.write((char*)&record,sizeof(Alumno));
                            
                            archivo.close();
                            aux_file.close();
                            this->aux_num_records=this->aux_num_records+1;
                            if(this->aux_num_records==max_tam_aux-1){
                                // Reconstruccion    
                            }   
                        }

                    }


                }
                else{
                    
                    // En este caso tienes que cambiar el valor del header y que apunte a mi objeto
                    
                    //cout<<"CASO 1: OBJETO ES MENOR QUE 1D POR LO CUAL SE INSERTA EN AUX Y CAMBIA EL HEADER"<<endl;

                    record.set_nextval(header_next);
                    record.set_tipo_archivo(header_char);
                    record.showData();
                    this->aux_num_records=aux_num_records+1;
                    long temp_next=this->aux_num_records;
                    char temp_char_h='a';
                    
                    // ESCRITURA PUESTA EN COMENTARIO
                    //cout<<temp_next<<endl;
                    
                    aux_file.seekp(sizeof(Alumno)*(temp_next-1),ios::beg);
                    aux_file.write((char*) &record, sizeof(Alumno));
                    cout<<temp_next<<endl;
                    archivo.seekp(0,ios::beg);
                    archivo.write((char*) &temp_next, sizeof(long));
                    archivo.seekp(sizeof(long),ios::beg);
                    archivo.write((char*) &temp_char_h, sizeof(char));
                    
                    archivo.close();
                    aux_file.close();
                    this->aux_num_records=this->aux_num_records+1;
                    if(this->aux_num_records==max_tam_aux-1){
                    // Reconstruccion    
                    }
                }



                
            }
            else{
                
                if(posicion_obj==this->num_records){
                    //cout<<"CASO 5: INSERTAR EN LA ULTIMA POSICION"<<endl;
                    Alumno nuevo=Alumno();

                    archivo.close();
                    fstream archivo(this->file_name,ios::binary | ios::in | ios::out);
                    archivo.seekg(sizeof(Alumno)*(this->num_records-1)+sizeof(long)+sizeof(char),ios::beg);
                    archivo.read((char*)&nuevo, sizeof(Alumno));
                    //nuevo.showData();
                    //record.showData();

                    if(nuevo.get_codigo()!=record.get_codigo() && nuevo.get_nextvalue()!=-2){
                        record.set_nextval(-1);
                        record.set_tipo_archivo('d');
                        nuevo.set_nextval(this->num_records+1);
                        nuevo.set_tipo_archivo('d');
                        //record.showData();
                        //nuevo.showData();

                        // ESCRITURA
                        
                        archivo.seekp(sizeof(Alumno)*(this->num_records-1)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&nuevo, sizeof(Alumno));

                        archivo.seekp(sizeof(Alumno)*(this->num_records)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&record, sizeof(Alumno));
                            
                        archivo.close();
                        aux_file.close();

                    }
                    else if(nuevo.get_codigo()!=record.get_codigo() && nuevo.get_nextvalue()==-2){
                        record.set_nextval(-1);
                        record.set_tipo_archivo('d');
                        archivo.seekg(sizeof(Alumno)*(this->num_records-2)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.read((char*)&nuevo, sizeof(Alumno));

                        nuevo.set_nextval(this->num_records);
                        nuevo.set_tipo_archivo('d');

                        //record.showData();
                        //nuevo.showData();                        

                        //cout<<this->num_records-1<<" "<<this->num_records-2;
                    
                        archivo.seekp(sizeof(Alumno)*(this->num_records-2)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&nuevo, sizeof(Alumno));

                        archivo.seekp(sizeof(Alumno)*(this->num_records-1)+sizeof(long)+sizeof(char),ios::beg);
                        archivo.write((char*)&record, sizeof(Alumno));

                    }
                    else{
                        //cout<<"YA EXISTE UN REGISTRO CON ESE CODIGO"<<endl; 
                        archivo.close();
                        aux_file.close();
                    }
                }
                else{
                    //cout<<"YA EXISTE UN REGISTRO CON ESE CODIGO"<<endl;                     
                    archivo.close();
                    aux_file.close();
                
                }

            }


        }
    }


    // PRUEBA

    void writeRecord(Alumno record){

        fstream file(this->file_name,ios::in | ios::out  | ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";


        long nextval;
        char data_type;

        if(this->num_records==0){
            nextval = 1;
            data_type = 'd';
            file.write((char*)(&nextval), sizeof(nextval));
            file.write((char*)(&data_type), sizeof(data_type));
            file.seekp(sizeof(nextval)+sizeof(data_type),ios::beg);
            file.write((char*) &record, sizeof(Alumno));
            this->num_records++;

            //guardar en formato binario
        }else{
   
            //cout<<"DEBO INSERTARLO EN: "<<find_by_binary(record)<<endl;;
            int posicion = find_by_binary(record);
            Alumno oldRecord = Alumno();

            //cout<<"SIZE OF DE LA COSA "<<sizeof(record.tipo_archivo)<<endl;
            file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
            file.read((char*)&oldRecord, sizeof(oldRecord));
            if(oldRecord.nextval==-1 ){ //si no hay nada delante o debajo de el inserto y tambien no hay auxiliar
                int new_pos = posicion+1;
                if(new_pos>this->num_records){
                    oldRecord.nextval=new_pos;
                }

                file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
                file.write((char*)&oldRecord, sizeof(oldRecord));
                file.seekg(sizeof(Alumno)*(posicion)+sizeof(nextval)+sizeof(data_type),ios::beg);
                file.write((char*)&record, sizeof(record));
                this->num_records++;

            }else{
                fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);

                if(oldRecord.tipo_archivo=='d'){
                    record.nextval=oldRecord.nextval;
                    aux_file.seekg(sizeof(Alumno)*(aux_num_records++));
                    aux_file.write((char*)&record,sizeof(record));
                    oldRecord.nextval=aux_num_records;
                    oldRecord.tipo_archivo='a';
                    file.seekg(sizeof(Alumno)*(posicion-1)+sizeof(nextval)+sizeof(data_type),ios::beg);
                    file.write((char*)&oldRecord, sizeof(oldRecord));

                }
                //fstream aux_file(this->auxiliar_data, ios::in | ios::out | ios::binary);
                else{
                    Alumno record_temp = Alumno();
                    long temp_next = oldRecord.nextval;
                    aux_file.seekg((oldRecord.nextval-1)*sizeof(Alumno));
                    aux_file.read((char*)&oldRecord, sizeof(oldRecord));
                    while(oldRecord.tipo_archivo!='d'){
                        if(oldRecord < record){
                            break;
                        }
                        temp_next = oldRecord.nextval;
                        aux_file.seekg(sizeof((oldRecord.nextval-1)*sizeof(Alumno)));
                    }
                    //cout<<"ENTRO"<<endl;
                    cout<<oldRecord.codigo<<endl;

                    record.nextval=oldRecord.nextval;
                    record.tipo_archivo=oldRecord.tipo_archivo;
                    oldRecord.nextval=++aux_num_records;
                    oldRecord.tipo_archivo='a';
                    aux_file.seekg((temp_next-1)*sizeof(Alumno));

                    aux_file.write((char*)&oldRecord,sizeof(oldRecord));
                    aux_file.seekg(sizeof(Alumno)*(aux_num_records-1));
                    aux_file.write((char*)&record,sizeof(record));
 
                    
                }
                aux_file.close();

            }


        }

        file.close();
    }  


    string get_filename(){
        return this->file_name;
    }



    vector<Alumno> scanAll(){
        ifstream file(this->file_name, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        vector<Alumno> alumnos;
        Alumno record; 

        long header;

        char tipo_archivo;

        file.read((char*)&header, sizeof(header));
        file.read((char*)&tipo_archivo, sizeof(tipo_archivo)); 

        //cout<<header<<" "<<tipo_archivo<<endl;


        while(!file.eof()){
            record = Alumno();               
            file.read((char*) &record, sizeof(record));
            if(file.tellg()==-1){
                break;
            }
            alumnos.push_back(record);    
        }
        
        file.close();

        return alumnos;
    } 


    vector<Alumno> scanAllAuxiliar(){
        ifstream file(this->auxiliar_data, ios::binary);
        if(!file.is_open()) throw "No se pudo abrir el archivo";
        
        vector<Alumno> alumnos;
        Alumno record; 

        while(!file.eof()){
            record = Alumno();               
            file.read((char*) &record, sizeof(record));
            if(file.tellg()==-1){
                break;
            }
            alumnos.push_back(record);    
        }
        
        file.close();

        return alumnos;
    } 

};