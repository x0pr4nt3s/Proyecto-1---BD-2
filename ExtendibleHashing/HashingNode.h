#include <string>

using namespace std;

class HashNode{
    int current_bucket;
    int profundidad_nodo=1;
    string value;
    
    
public:

    HashNode(){};
    HashNode(int current_bucket, int profundidad_nodo, string value){
        this->current_bucket=current_bucket;
        this->profundidad_nodo=profundidad_nodo;
        this->value=value;
    }

    void set(int current_bucket, int profundidad_nodo, string value){
        this->current_bucket=current_bucket;
        this->profundidad_nodo=profundidad_nodo;
        this->value=value;
    }

    int get_current_bucket() {return current_bucket;}
    int get_profundidad_nodo() {return profundidad_nodo;}
    string get_value() {return value;}
    void set_current_bucket(int current_bucket) {this->current_bucket=current_bucket;}
    void set_profundidad_nodo(int profundidad_nodo) {this->profundidad_nodo=profundidad_nodo;}
    void set_value(string value) {this->value = value;}

};