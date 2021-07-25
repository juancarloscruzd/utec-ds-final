//
// Created by VICTOR HERRERA on 2021-07-07.
//
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <utility>
#include <cmath>
#include <random>

//#include <istream>

using namespace std;

//Clase Padre: Lista
template<typename E> class Lista{
private:
public:
    //Constructor
    Lista(){}
    //Destructor
    ~Lista(){}


    //Limpiar la lista: dejarla vacia la lista
    virtual void limpiar() = 0;
    //Insertar un elemento donde se encuentra el puntero "actual"
    virtual  void insertar(E elemento) = 0;
    //Agregar un elemento a la lista (al final)
    virtual void agregar(E elemento) = 0;
    //Libera de la memoria y retorna el elemento "actual"
    virtual E eliminar() = 0;
    //Mover "actual" al inicio de la lista
    virtual void moverAInicio() = 0;
    //Mover "actual" al final de la lista
    // primer espacio disponible
    virtual void moverAlFinal() = 0;
    //Mover "actual" a la posicion anterior (izquierda)
    virtual void anterior() = 0;
    //Mover "actual" a la posicion posterior (derecha)
    virtual void siguiente() = 0;
    //Retornar le numero de elementos de la lista
    virtual int longitud() = 0;
    //Retornar la posicion del elemento "actual"
    virtual int posicionActual() = 0;
    //"Actual" se mueve a la posicion "pos"
    virtual void moverAPosicion(int pos) = 0;
    //Retorna el valor que estaba en la posicion "actual"
    virtual E getValor() = 0;
    //Modificar el valor en la posicion "actual"
    virtual void setValor(E elemento) = 0;
};

//Clase Hija: ListaArreglo
template<typename E> class ListaArreglo : public Lista<E>{
private:
    //Arreglo de elementos
    E* arreglo;
    //Tamanho fijo
    int tamMax;
    //Tamanho de la lista
    int tamLista;
    //Indice "actual"
    int actual;
public:
    //Constructor
    ListaArreglo(int tamMax=100){
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Destructor
    ~ListaArreglo(){
        delete[] this->arreglo;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio() {
        this->actual = 0;
    }

    //Mover "actual" al final de la lista:
    // primer espacio disponible
    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente() {
        //Sentinela
        if( this->actual < this->tamLista  )
            this->actual++;
    }

    // Mover siguiente mod
    void mySiguiente() {
        this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior() {
        //Sentinela
        if( this->actual > 0 )
            this->actual--;
    }

    void agregarPoint(E *elemento) {
        this->arreglo[this->tamLista++] = *elemento;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    //Retornar le numero de elementos de la lista
    int longitud() {
        return this->tamLista;
    }
    //Retornar tamaño completo de la lista
    int longitudtotal(){
        return this->tamMax;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual() {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos) {
        //Sentinela
        if(pos>=0 && pos<this->tamLista)
            this->actual = pos;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor() {
        return this->arreglo[this->actual];
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento) {
        this->arreglo[this->actual] = elemento;
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }


    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento) {
        for (int i = this->tamLista; i >this->actual; i--)
            this->arreglo[i] = this->arreglo[i-1];
        this->arreglo[this->actual] = elemento;
        this->tamLista++;
    }

    //Eliminar y retornar el elemento "actual"
    E eliminar() {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i) {
            this->arreglo[i] = this->arreglo[i+1];
        }
        this->tamLista--;
        return eliminado;
    }
    //
    void setValorEnPosicion(int index, E valor) {
        this->arreglo[index] = valor;
    }
    E getValorEnPosicion(int index){
        return this->arreglo[index];
    }
    // get valor por indice
    void getValIndexpoint(int pos, E** dir){
        //cout << pos;
        //this->arreglo[pos].print();
        //return this->arreglo[pos];
        *dir = &this->arreglo[pos];
    }

    // get valor por indice
    void getValIndexpoint2(E** dir){
        *dir = &this->arreglo[this->actual];
    }

    // get valor por indice
    void getValIndexpoint3(int i, E** dir){
        *dir = &this->arreglo[i];
    }

    // Imprimir vector
    void imprimir(){
        for (int i = 0; i< this->tamLista; i++){
            cout << i << endl;
            //cout << this->arreglo[i] << endl;
        }
    }

    // Insertar en dict
    void insertPos(int pos, E *elemento){
        //elemento->print();
        this->arreglo[pos] = *elemento;
    }
};

template<typename Key, typename E> class KVPar{
private:
    Key k;
    E e;
public:
    //Constructor
    KVPar(){}
    KVPar(Key kval, E eval){this->k = kval; this->e = eval;}
    KVPar(KVPar &o){ this->k = o.k; this->e = o.e; }

    Key key(){
        return this->k;
    }
    E valor(){
        return this->e;
    }
    void setKey(Key ink){
        this->k = ink;
    }
    E setVal(){
        this->e++;
        return this->e;
    }
    friend ostream& operator<< (ostream& o, KVPar const& kv_par)
    {
        return o <<'<'<<kv_par.k<<":"<<kv_par.e<<'>';
    }
};

template<typename Key, typename E> class Diccionario{
private:
public:
    Diccionario(){} //Constructor
    ~Diccionario(){} //Destructor

    //Reinicializacion de un diccionario
    virtual void limpiar() = 0;

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    virtual void insertar(Key K, E e) = 0;

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    virtual E remover(Key K) = 0;


    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    virtual E removerCualquiera() = 0;

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    virtual E encontrar(Key K) = 0;

    //Retornar el número de registros dentro del diccionario
    virtual int longitud() = 0;

    //Retornar el primer elemento KVPar del arreglo.
    //virtual KVPar<Key,E> begin() = 0;

};

// -------------------------------------------------------------- //
// Diccionario basado en listas
template<typename Key, typename E> class DiccionarioArreglo : public Diccionario<Key,E>{
private:
    ListaArreglo<KVPar<Key, E>> *lista;
public:
    //Constructor
    DiccionarioArreglo(int tamDict = 100){
        this->lista = new ListaArreglo<KVPar<Key, E>>(tamDict);
    }

    //Destructor
    ~DiccionarioArreglo(){
        delete lista;
    }

    //Reinicializacion de un diccionario
    void limpiar(){
        this->lista->limpiar();
    }

    //Insertar un registro
    //k: la clave para el registro
    //e: el registro
    void insertar(Key k, E e){
        this->lista->agregar(*new KVPar<Key,E>(k,e));
    }

    void insertarUnic(Key k){
        // Se coteja que elemento no exista
        int temp=0;
        KVPar<Key,E> *pointer;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor().key() == k){
                // En caso exista se aumenta un valor
                this->lista->getValIndexpoint2(&pointer);
                temp = pointer->setVal();
            }
        }
        // En caso no exista se crea un elemeno
        if (temp==0){
            this->lista->agregarPoint(new KVPar<Key,int>(k,++temp));
        }
    }



    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    E remover(Key K){
        E temp;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor().key() == K){
                temp = this->lista->getValor().valor();
                this->lista->eliminar();
            }
        }
        return temp;
    }

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera(){
        if(this->lista->longitud()>0) {
            this->lista->moverAlFinal();
            E temp = this->lista->getValor().valor();
            this->lista->eliminar();
            return temp;
        }else{
            return NULL;
        }
    }

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key K){
        E temp;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor().key() == K){
                temp = this->lista->getValor().valor();
            }
        }
        return temp;
    }
    //Retornar true/false
    bool encontrarbool(Key K){
        E temp;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor().key() == K){
                return true;
            }
        }
        return false;
    }

    //Devolver la cantidad de elementos del Dictionario.
    int longitud(){
        return this->lista->longitud();
    }

    //Imprimir todos los valores del diccionario.
    void imprimirValores(){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            cout<<this->lista->getValor().valor()<<endl;
        }
    }
    //Print los KVPar contenidos en el diccionario.
    void print(){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            cout<<this->lista->getValor()<<endl;
        }
    }

    //Retornar el primer elemento KVPar del arreglo. AUN NO FUNCIONA.
    KVPar<int,string> begin(){
        this->lista->moverAInicio();
        return this->lista->getValor();
    }

    //Retornar valor en posicion
    E getValorEnPosicion(int i){
        return this->lista->getValorEnPosicion(i).valor();
    }

    //Retornar Key en posicion
    Key getKeyEnPosicion(int i){
        return this->lista->getValorEnPosicion(i).key();
    }

};

//  ---------------- Diccionario Hash ------------------------------- //
// Hashing
class Hashes {
public:
    Hashes(){};
    ~Hashes(){};
    // **************************************************** //
    int valToHash1(string str, int sizeArray) {
        int val = 0;
        char cmp1 = '-';
        char cmp2 = '_';

        for (char c : str) {
            if (isdigit(c) == 0) {
                if (c==cmp1){
                    val = val + 60;
                }else if (c==cmp2){
                    val = val + 61;
                }
                else{
                    val = val + (c-64);
                }
            }else{
                val = val + (int)c + 26;
            }
        }
        return val % sizeArray;
    }

    // **************************************************** //
    int valToHash2(string str, int sizeArray) {
        int val = 0;
        char cmp1 = '-';
        char cmp2 = '_';
        int count = 2;

        for (char c : str) {
            if (isdigit(c) == 0) {
                if (c==cmp1){
                    val = val + 60*count;
                }else if (c==cmp2){
                    val = val + 61*count;
                }
                else{
                    val = val + (c-64)*count;
                }
            }else{
                val = val + ((int)c + 26)*count;
            }
            // Se aumenta el contador
            count++;
        }
        return val % sizeArray;
    }
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    int valToHash3(string k, int MOD){
        int suma=0;
        for(char c : k){
            suma = suma + c;
        }
        return suma % (MOD);
    }

};

// ---------------------------------------------------------- //
// Diccionario con hash
template<typename Key, typename E> class DiccionarioHash : public Diccionario<Key,E>{
private:
    int tamHash = 0;
    int tamLongHash;
    int numElementos =0;
    int colisiones=0;
    Hashes *HashObj = new Hashes();
    ListaArreglo<ListaArreglo<KVPar<Key, E>>> *arraySeparate;

public:
    //Constructor
    DiccionarioHash(int tamLongHash = 100){
        this->tamLongHash = tamLongHash;
        this->arraySeparate = new ListaArreglo<ListaArreglo<KVPar<Key, E>>>(tamLongHash);
    }

    //Destructor
    ~DiccionarioHash(){
        delete arraySeparate;
    }

    //Reinicializacion de un diccionario
    void limpiar(){
        this->arraySeparate->limpiar();
    }

    //Insertar un registro
    //k: la clave para el registro
    //e: el registro
    void insertar(Key k, E e){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        // El insertar se hace en posicion con valor hash
        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        int check = listTemp->longitud();
        if (check == 0){
            this->numElementos++;  // Elementos del vector grande utilizado
            KVPar<Key,E> KVTemp(k,e);
            listTemp->agregar(KVTemp);
            this->arraySeparate->insertPos(hashVal, listTemp);
        }else{
            // Colisiones
            this->colisiones++;
            // Se agrega el dato
            KVPar<Key,E> KVTemp2(k,e);
            listTemp->agregar(KVTemp2);
            this->arraySeparate->insertPos(hashVal, listTemp);
        }
    }

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    //E remover(Key k){
    E remover(Key k){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);
        E temp = NULL;
        ListaArreglo<KVPar<Key,E>> *listBusc;
        this->arraySeparate->getValIndexpoint(hashVal, &listBusc);

        // Solo se elimina si tiene algun elemento
        if (listBusc->longitud() >=1){
            for(listBusc->moverAInicio();listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()) {
                if (listBusc->getValor().key() == k) {
                    temp = listBusc->getValor().valor();
                    listBusc->eliminar();
                    return temp;
                    break;
                }
            }
        }else{
            return temp;
        }
    }

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera(){
        E temp =NULL;
        ListaArreglo<KVPar<Key,E>> *listBusc;
        for (int i=0; i<this->tamLongHash; i++){
            this->arraySeparate->getValIndexpoint3(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                temp = listBusc->getValor().valor();
                listBusc->eliminar();
                return temp;
                break;
            }
        }
        delete[] listBusc;
        return temp;
    }

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key k){
        E temp = NULL;

        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint3(hashVal, &listTemp);

        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().key()==k){
                temp = listTemp->getValor().valor();
                return temp;
                break;
            }
        }

        delete[] listTemp;
        return temp;
    }
    //Retornar true/false
    bool encontrarbool(Key k){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().key()==k){
                return true;
                break;
            }
        }

        delete[] listTemp;
        return false;

    }

    //Devolver la cantidad de elementos del Dictionario.
    int longitud(){
        return this->numElementos + this->colisiones;
    }

    //Imprimir todos los valores del diccionario.
    void imprimirValores(){
        ListaArreglo<KVPar<Key,E>> *listBusc;
        for (int i=0; i<this->tamLongHash; i++){
            this->arraySeparate->getValIndexpoint3(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                cout << "Key: " << listBusc->getValor().key() << " Valor: " << listBusc->getValor().valor() << endl;
            }
        }
        delete[] listBusc;
    }
};

// ------------------------------------------------------- /
// Diccionario con arboles
/*
template<typename Key, typename E> class DiccionarioTree : public Diccionario<Key,E>{
private:
    int tamHash = 0;
    int tamLongHash;
    int numElementos =0;
    int colisiones=0;
    Hashes *HashObj = new Hashes();
    ListaArreglo<ListaArreglo<KVPar<Key, E>>> *arraySeparate;

public:
    //Constructor
    DiccionarioHash(int tamLongHash = 100){
        this->tamLongHash = tamLongHash;
        this->arraySeparate = new ListaArreglo<ListaArreglo<KVPar<Key, E>>>(tamLongHash);
    }

    //Destructor
    ~DiccionarioHash(){
        delete arraySeparate;
    }

    //Reinicializacion de un diccionario
    void limpiar(){
        this->arraySeparate->limpiar();
    }

    //Insertar un registro
    //k: la clave para el registro
    //e: el registro
    void insertar(Key k, E e){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        // El insertar se hace en posicion con valor hash
        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        int check = listTemp->longitud();
        if (check == 0){
            this->numElementos++;  // Elementos del vector grande utilizado
            KVPar<Key,E> KVTemp(k,e);
            listTemp->agregar(KVTemp);
            this->arraySeparate->insertPos(hashVal, listTemp);
        }else{
            // Colisiones
            this->colisiones++;
            // Se agrega el dato
            KVPar<Key,E> KVTemp2(k,e);
            listTemp->agregar(KVTemp2);
            this->arraySeparate->insertPos(hashVal, listTemp);
        }
    }

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    //E remover(Key k){
    E remover(Key k){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);
        E temp = NULL;
        ListaArreglo<KVPar<Key,E>> *listBusc;
        this->arraySeparate->getValIndexpoint(hashVal, &listBusc);

        // Solo se elimina si tiene algun elemento
        if (listBusc->longitud() >=1){
            for(listBusc->moverAInicio();listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()) {
                if (listBusc->getValor().key() == k) {
                    temp = listBusc->getValor().valor();
                    listBusc->eliminar();
                    return temp;
                    break;
                }
            }
        }else{
            return temp;
        }
    }

    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera(){
        E temp =NULL;
        ListaArreglo<KVPar<Key,E>> *listBusc;
        for (int i=0; i<this->tamLongHash; i++){
            this->arraySeparate->getValIndexpoint3(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                temp = listBusc->getValor().valor();
                listBusc->eliminar();
                return temp;
                break;
            }
        }
        delete[] listBusc;
        return temp;
    }

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key k){
        E temp = NULL;

        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint3(hashVal, &listTemp);

        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().key()==k){
                temp = listTemp->getValor().valor();
                return temp;
                break;
            }
        }

        delete[] listTemp;
        return temp;
    }
    //Retornar true/false
    bool encontrarbool(Key k){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(k,this->tamLongHash);

        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().key()==k){
                return true;
                break;
            }
        }

        delete[] listTemp;
        return false;

    }

    //Devolver la cantidad de elementos del Dictionario.
    int longitud(){
        return this->numElementos + this->colisiones;
    }

    //Imprimir todos los valores del diccionario.
    void imprimirValores(){
        ListaArreglo<KVPar<Key,E>> *listBusc;
        for (int i=0; i<this->tamLongHash; i++){
            this->arraySeparate->getValIndexpoint3(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                cout << "Key: " << listBusc->getValor().key() << " Valor: " << listBusc->getValor().valor() << endl;
            }
        }
        delete[] listBusc;
    }
};
*/






int main(){
    // Palabras para simulacion
    int numWords = 500;
    int sizeWords = 5;
    string letras[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    string words[numWords];  // Vector de palabras creadas
    int randGen[numWords];   // Vector de valores creados
    int paso = 5;
    std::chrono::duration<double, std::milli> exper1[numWords/paso]; // Vector para guardar resultados de experimento Hash
    std::chrono::duration<double, std::milli> exper2[numWords/paso]; // Vector para guardar resultados de experimento Hash
    int randNum;
    int contador=0;
    string genWord;

    // Se ingresan las 500 palabras en cada diccionario
    DiccionarioHash<string, int> *dictHash = new DiccionarioHash<string, int>(500);
    DiccionarioArreglo<string, int> *dictLista = new DiccionarioArreglo<string, int>(500);

    for(int i=0;i<numWords;i++){
        genWord="";
        for (int j=0; j<sizeWords; j++){
            // Se generan 5 numero aleatorios
            randNum = rand()%(25) + 1;
            genWord += letras[randNum];
        }
        words[i] = genWord;
        randGen[i] = randNum;
        dictHash->insertar(genWord,randNum); // Se guarda el ultimo numero aleatorio generado
        dictLista->insertar(genWord,randNum);
    }

    // Se hace consultas de 5 a 500
    for(int i=4; i<numWords; i+=paso){
        // Tiempo del diccionario hash
        auto t_start1 = std::chrono::high_resolution_clock::now();
        for(int j=0; j<=i; j++){
            // Buscar de diccionario hash y revisar correctitud con el valor guardado
            if (dictHash->encontrar(words[j]) != randGen[j]){
                cout << "Valor incorrecto" << endl;
            }
        }
        auto t_end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tiempo1 = t_end1-t_start1;

        // Tiempo del diccionario lista
        auto t_start2 = std::chrono::high_resolution_clock::now();
        for(int j=0; j<=i; j++){
            // Buscar de diccionario lista y revisar correctitud con el valor guardado
            if (dictLista->encontrar(words[j]) != randGen[j]){
                cout << "Valor incorrecto" << endl;
            }
        }
        // Buscar de diccionario lista
        auto t_end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tiempo2 = t_end2-t_start2;

        // Se guarda el resultado del experimento
        exper1[contador] = tiempo1;
        exper2[contador] = tiempo2;
        contador++;
    }

    // Se muestra los resultados del experimento
    int count1 = 0;
    for(int i=4; i<numWords; i+=paso){
        cout << "Experimento con (n=" << i+1 << ") Tiempo con diccionario Hash: " << exper1[count1].count() << " Tiempo con diccionario Lista: " << exper2[count1].count() <<  endl;
        count1++;
    }

    return 0;
}


