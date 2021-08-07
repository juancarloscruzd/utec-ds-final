#include <iostream>
#include <chrono>
#include <cmath>
#include <random>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <clocale>

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
        // En caso no exista se crea un elemento
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

    void insertarVal(Key k, E e){
        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(e,this->tamLongHash);

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
            this->arraySeparate->getValIndexpoint(i, &listBusc);
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
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().key()==k){
                temp = listTemp->getValor().valor();
                return temp;
                break;
            }
        }

        delete listTemp;
        return temp;
    }

    // Encontrar con string
    E encontrarS(E e){
        string temp = "";

        // Posicion con valor hash
        int hashVal = HashObj->valToHash3(e,this->tamLongHash);
        ListaArreglo<KVPar<Key, E>> *listTemp;
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);
        for (listTemp->moverAInicio(); listTemp->posicionActual() < listTemp->longitud(); listTemp->siguiente()){
            if (listTemp->getValor().valor()==e){
                temp = listTemp->getValor().key();
                return temp;
                break;
            }
        }
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
            this->arraySeparate->getValIndexpoint(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                cout << "Key: " << listBusc->getValor().key() << " Valor: " << listBusc->getValor().valor() << endl;
            }
        }
    }

    // Pasar elementos a una lista
    void expLista(ListaArreglo<string> **Lista){

        ListaArreglo<string> *listaNew = new ListaArreglo<string>(this->numElementos + this->colisiones);
        ListaArreglo<KVPar<Key,E>> *listExp;

        for (int i=0; i<this->tamLongHash; i++){
            this->arraySeparate->getValIndexpoint(i, &listExp);
            for (listExp->moverAInicio(); listExp->posicionActual() < listExp->longitud(); listExp->siguiente()){
                listaNew->agregar(listExp->getValor().key());
            }
        }
        *Lista = listaNew;
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
        this->arraySeparate->getValIndexpoint(hashVal, &listTemp);

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
            this->arraySeparate->getValIndexpoint(i, &listBusc);
            for (listBusc->moverAInicio(); listBusc->posicionActual() < listBusc->longitud(); listBusc->siguiente()){
                cout << "Key: " << listBusc->getValor().key() << " Valor: " << listBusc->getValor().valor() << endl;
            }
        }
        delete[] listBusc;
    }
};
*/

//-------------------------------------------------------------
// Distancia entre arreglos
template <typename E>
double distance(E *array1, E *array2, int p, int size){
    double temp = 1e-20;
    for(int i=0; i<size; i++ ){
        temp += pow(abs(array1[i] - array2[i]), p);
    };
    if (temp >= 1){
        temp = pow(temp, (double)1/p);
    }
    return temp;
};

template<typename D> class CorpusVectorizado{
private:
    DiccionarioArreglo<D, int> *diccionario;
    DiccionarioHash<D, string> *CorpusHash;
    ListaArreglo<string> *Licorpus;
    DiccionarioArreglo<D, string> *FinalWords;
    Hashes *HashObj = new Hashes();
    int TamanhoHash = 0;

public:
    //Constructor
    CorpusVectorizado(int Tam=100){
        this->CorpusHash = new DiccionarioHash<D, string>(Tam);
        this->diccionario = new DiccionarioArreglo<D, int>(Tam);
        this->Licorpus = new ListaArreglo<string>(Tam);
        this->FinalWords = new DiccionarioArreglo<D, string>(Tam);
        this->TamanhoHash = Tam;
    }

    //Destructor
    ~CorpusVectorizado(){
        delete CorpusHash;
    }

    // Cargar datos de entrenamiento y se construye diccionario
    void dataTrain(ListaArreglo<D> *Li, ListaArreglo<D> *Stops){
        int conteo;
        for(Li->moverAInicio();Li->posicionActual() < Li->longitud(); Li->siguiente()){
            this->Licorpus->agregar(Li->getValor());
            stringstream flujo(Li->getValor());
            string linetext;
            while(getline(flujo,linetext,' ')){
                conteo = 0;
                for(Stops->moverAInicio(); Stops->posicionActual()<Stops->longitud(); Stops->siguiente()){
                    if (linetext == Stops->getValor()){
                        conteo++;
                        break;
                    }
                }

                // Solo se agrega si no es stopword y tiene al menos dos silabas
                if ((conteo == 0) & (linetext.length() > 2)) {
                    this->diccionario->insertarUnic(linetext);
                }
            }
        }
    }

    //Vectorizacion del Corpus.
    void Vectorizacion(){
        int conteo;
        int array1[this->diccionario->longitud()];
        for(this->Licorpus->moverAInicio();this->Licorpus->posicionActual() < this->Licorpus->longitud(); this->Licorpus->siguiente()){
            conteo = 0;
            stringstream flujo(this->Licorpus->getValor());
            string linetext;

            for(int x=0;x< this->diccionario->longitud();x++){
                array1[x] = 0;
            }

            while(getline(flujo,linetext,' ')){
                for(int x=0;x< this->diccionario->longitud();x++){
                    if (this->diccionario->getKeyEnPosicion(x) == linetext){
                        array1[x] = 1;
                        conteo++;
                    }
                }
            }

            // Solo se inserta si el vector no son todos ceros
            if (conteo>0){
                string vecBin = "";
                for(int x=0;x< this->diccionario->longitud();x++){
                    vecBin += to_string(array1[x]);
                }
                //Diccionario hash para buscar palabras
                this->CorpusHash->insertarVal(vecBin,this->Licorpus->getValor());

                // Diccionario simple para recorrer todos los elementos
                this->FinalWords->insertar(vecBin, this->Licorpus->getValor());
            }
        }
    }

    // Devolver oraciones de entrenamiento con su distancia
    void predict(string newWord, int pVal, DiccionarioArreglo<D,double> **dicReturn){
        // Arreglos para guardar oraciones q se van a comparar
        int array1[this->diccionario->longitud()];
        int array2[this->diccionario->longitud()];
        DiccionarioArreglo<D, double> *dictResul =  new DiccionarioArreglo<D, double>(this->diccionario->longitud());   // Resultado se guarda en un diccionario

        // ---------------------------------------------------- //
        // Palabra nueva se convierte a su valor binario
        stringstream flujo(newWord);
        string linetext;

        for(int ix=0; ix<this->diccionario->longitud(); ix++){
            array1[ix]=0;
        }

        while(getline(flujo,linetext,' ')){
            for(int x=0;x< this->diccionario->longitud();x++){
                if (this->diccionario->getKeyEnPosicion(x) == linetext){
                    array1[x] = 1;
                }
            }
        }

        // ---------------------------------------------------- //
        // Se compara este array con cada una de las oraciones iniciales
        for(this->Licorpus->moverAInicio();this->Licorpus->posicionActual() < this->Licorpus->longitud(); this->Licorpus->siguiente()){
            // Conversion a su valor binario
            string x = this->CorpusHash->encontrarS(this->Licorpus->getValor());

            int centi1 = 0;
            for (auto xx : x){
                array2[centi1++] = (int)xx-48;
            }

            // Se calcula la distancia
            double temp = 1e-20;

            // Al menos deben tener alguna palabra igual
            int count1 = 0;

            for(int jx=0; jx<this->diccionario->longitud(); jx++){
                // Al menos deben tener una palabra en comun
                if (array1[jx] == 1 & array2[jx] == 1){
                    count1++;
                }
                temp += pow(abs(array1[jx] - array2[jx]), pVal);
            }

            // Si no tienen ninguna palabra igual se les coloca una distancia de 1000
            if (count1==0){
                temp = 10000;
            }else{
                if (temp >= 1 ){
                    temp = pow(temp, (double)1/pVal);
                }
            }

            // Diccionario con oracion original y su diferencia con la palabra consultada
            dictResul->insertar(this->Licorpus->getValor(), temp);
        }

        // Se retorna el diccionario
        *dicReturn = dictResul;
    }

    // Extraer diccionario de palabras
    void getDictWords(DiccionarioArreglo<D,int> **Dir){
        *Dir = this->diccionario;
    }

    // Extraer el diccionario con vector binario y oraciones
    void getDict(DiccionarioArreglo<D,string> **Dir){
        //*Dir = this->diccionario;
        *Dir = this->FinalWords;
    }

    // Extraer Corpus
    void getCorpus(DiccionarioHash<D, string> **Dir){
        *Dir = this->CorpusHash;
    }

    // Numero de pabras en el diccionario
    int numWords(){
        return this->diccionario->longitud();
    }

};

//-------------------------------------------------------------
class importDatos {
private:
    int numUnic;
    string dirFile;
    string dirStops;
    DiccionarioHash<string,string> *DictHash;
    ListaArreglo<string> *StopList;

public:
    importDatos(string dirFile, string dirStops, int tam, int tamStop = 1000){
        this->dirFile = dirFile;
        this->dirStops = dirStops;
        this->DictHash = new DiccionarioHash<string,string>(tam);
        this->StopList = new ListaArreglo<string>(tamStop);
        this->numUnic=0;
    };
    ~importDatos(){};

    // **************************************************** //
    // Se importa las stopwords
    void importStopWords(ListaArreglo<string> **Lista) {
        ifstream file(this->dirStops);
        string linea;
        getline(file, linea);
        while (getline(file, linea)) {
            stringstream flujo(linea); //Convertimos la cadena a un stream.
            string ID, valor;
            getline(flujo, ID, ';');
            getline(flujo, valor);
            this->StopList->agregar(ID);
        }

        *Lista = this->StopList;
    }

    // Se carga informacion
    void import(DiccionarioHash<string,string> **Dict){
        //Extraer datos del dataset.

        ifstream file(this->dirFile);
        string linea;
        char delimiter = ';';
        getline(file,linea);
        int conteo;
        while(getline(file,linea)){
            stringstream flujo(linea); //Convertimos la cadena a un stream.
            string ID, valor;
            getline(flujo,ID,';');
            getline(flujo,valor);

            // Se estandariza la palabra
            string word = "";
            conteo = 0;
            for (auto cx: ID){

                // No se guardan nombres que comienzan con @
                if (cx == '@'){
                    conteo = 1;
                }
                else if ((cx == ' ') && (conteo == 1)){
                    conteo = 0;
                }
                else if (conteo==0){
                    if (cx == ' '){
                        cx = tolower(cx);
                        word += cx;
                    }
                    else if (isalpha(cx)){
                        cx = tolower(cx);
                        word += cx;
                    }
                }
            }

            // Solo se guarda si hay informacion
            int check1 = 0;
            for (auto str : word){
                if (str != ' '){
                    check1++;
                    break;
                }
            }

            if (check1>=1){
                // Solo se inserta en caso no sea un stopword
                this->DictHash->insertar(word,"");
            }
        }
        file.close();
        *Dict = this->DictHash;
    }

    int numWords(){
        return this->numUnic;
    }

};


int main(){
    /* --------------------------------------------------------------------------------------- */
    // Se carga informacion
    int sizeBd = 3000;
    importDatos *Datos = new importDatos("..\\Comentarios.csv", "..\\stopwords.csv", sizeBd);

    /* --------------------------------------------------------------------------------------- */
    // Parte 3
    // Diccionario para guardar los datos importados
    DiccionarioHash<string,string> *myDict1 = new DiccionarioHash<string,string>(sizeBd);
    ListaArreglo<string> *myStops = new ListaArreglo<string>(sizeBd);
    Datos->importStopWords(&myStops);
    Datos->import(&myDict1);

    // Se extrea la lista que compone el corpus
    ListaArreglo<string> *Licorpus = new ListaArreglo<string>();
    myDict1->expLista(&Licorpus);

    // Se carga la lista de palabras de entrenamiento y las StopsWords
    CorpusVectorizado<string> *CorpusVec = new CorpusVectorizado<string>(8000);
    CorpusVec->dataTrain(Licorpus, myStops);

    // Entrenar modelo
    CorpusVec->Vectorizacion();

    // Se extra el diccionario con clave: vector binario y valor: texto
    DiccionarioArreglo<string, string> *diccionarioWords = new DiccionarioArreglo<string, string>;
    CorpusVec->getDict(&diccionarioWords);

    /* --------------------------------------------------------------------------------------- */
    // Primero se introduce los datos de consulta
    int introDato=1;
    string consult;    // Palabra que se va a consultar
    int radio;          // radio de consulta
    string keyStr;
    int conteo;

    // Diccionario con informacion del Corpus previamente entrenado
    DiccionarioHash<string, string> *diccionario = new DiccionarioHash<string, string>;
    DiccionarioArreglo<string, double> *dicResult = new DiccionarioArreglo<string, double>(8000);
    CorpusVec->getCorpus(&diccionario);

    // Diccionario con informacion de palabras consideradas para la construccion vectorial (BAGOFWORDS)
    DiccionarioArreglo<string, int> *dicWords = new DiccionarioArreglo<string, int>(8000);
    CorpusVec->getDictWords(&dicWords);

    while (introDato==1){
        // Se hace la pregunta si quiere ingresar dato 0=No, 1=Si
        cout << "\n --------------------------------------------- " << endl;
        cout << "Desea ingresar dato: 0=No, 1=Si: ";
        cin>>introDato;

        while(!(introDato == 0 | introDato == 1)){
            // Introducir dato valido
            cout << "\nIngreso dato no valido: " << endl;
            cout << "Ingresar dato: 0=No, 1=Si: ";
            cin>>introDato;
        }

        if (introDato==1){
            cout << "\nIntroducir el texto de consulta: ";
            cin.ignore();
            getline(cin, consult);
            cout << "\nIntroducir radio (maxima diferencia) r>0: ";
            cin>>radio;

            while(radio < 0 ){
                // Introducir dato valido
                cout << "\nIntroducir un radio valido (r>0): ";
                cin>>radio;
            }

            cin.ignore();

            // La palabra se convierte a minuscula antes de consultar
            string strLower = "";
            string temp;
            setlocale(LC_ALL, "en_US.utf8");
            for (auto cc: consult){
                temp = tolower(cc);
                if ((int)temp[0] == -96){
                    temp = "a";
                } else if((int)temp[0] == -95){
                    temp = "i";
                } else if((int)temp[0] == -94){
                    temp = "o";
                } else if((int)temp[0] == -93){
                    temp = "u";
                } else if(((int)temp[0] == -126) | ((int)temp[0] == -112)) {
                    temp = "e";
                }
                strLower += temp;
            }

            // palabra homogenizada
            consult = strLower;

            // Antes de buscar, se verifica que alguna palabra exista en el diccionario
            conteo = 0;
            string subs;
            istringstream iss(consult);
             while(iss) {
                 iss >> subs;
                 for (int i = 0; i < dicWords->longitud() & conteo == 0; i++) {
                     keyStr = dicWords->getKeyEnPosicion(i);
                     if (keyStr == subs) {
                         conteo++;
                     }
                 }
             }

            if (conteo > 0){
                // Se busca la palabra
                CorpusVec->predict(consult, 1, &dicResult);

                // Se muestra las palabras mas parecidas segun el radio introducido
                cout << "\n\n" << endl;
                for  (int i=0; i<dicResult->longitud(); i++){
                    if (dicResult->getValorEnPosicion(i)<=radio){
                        cout << dicResult->getKeyEnPosicion(i);
                        cout << " // "<< dicResult->getValorEnPosicion(i) << endl;
                    }
                }
            }
        }
    }

    return 0;
}