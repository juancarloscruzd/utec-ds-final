//
// Created by VICTOR HERRERA on 2021-07-14.
//
#include <algorithm>
#include <iostream>
#include <cmath>
#include <chrono>
#include <utility>

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
        if( this->actual < this->tamMax  )
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior() {
        //Sentinela
        if( this->actual > 0 )
            this->actual--;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    //Retornar le numero de elementos de la lista
    int longitud() {
        return this->tamLista;
    }

    int maxLongitud() {
        return this->tamMax;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual() {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos) {
        //Sentinela
        if(pos>=0)
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

    void setValorEnPosicion(int index, E valor) {
        this->arreglo[index] = valor;
    }
    E getValorEnPosicion(int index){
        return this->arreglo[index];
    }

};
//////////////////////////////////////////////

//Clase Abstracta: Set
template<typename Key> class Set{
public:
    //Constructor
    Set(){}

    //Base destructor
    ~Set(){}

    //Permite reinicializar la estructura de datos
    virtual void limpiar() = 0;

    //La inserción del valor k
    virtual void insertar(Key k) = 0;

    //Dada una clave, el registro correspondiente debe ser removido
    virtual void remover(Key k) = 0;

    //Retorna y remueve un registro arbitrario del set
    virtual Key removerCualquiera() = 0;

    //Retorna una posición del registro que se asocie con k
    virtual int encontrar(Key k) = 0;

    //Retornar el número de registros o claves existentes en el set
    virtual int longitud() = 0;
};

//SetBasico
template<typename Key>
class SetBasico : public Set<Key>{
private:
    ListaArreglo<Key*> *lista;
public:
    SetBasico(int tamanho = 100)  {
        this->lista = new ListaArreglo<Key*>(tamanho);
    }

    ~SetBasico(){
        delete lista;
    }

    void limpiar(){
        this->lista->limpiar();
    }
    //Retornar el número de registros o claves existentes en el set
    int longitud(){
        return this->lista->longitud();
    }

    //Retorna una posición del registro que se asocie con k
    int encontrar(Key k){
        int indice;
        Key *temp;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor() == &k){
                temp = this->lista->getValor();
                indice = this->lista->posicionActual();
            }
        }
        return indice;
    }
    bool encontrarbool(Key k){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor() == &k){
                return true;
            }
        }
        return false;
    }

    //La inserción del valor k
    void insertar(Key k){
        Key *temp = &k;
        //if(!this->encontrarbool(*temp)){
        this->lista->agregar(temp);
        //}
    }

    //Retorna y remueve un registro arbitrario del set
    void print(){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            cout<<*(this->lista->getValor())<<endl;
        }
    }

    //Dada una clave, el registro correspondiente debe ser removido
    void remover(Key k){
        Key *temp = &k;
        Key *x;
        if(this->encontrarbool(*temp)){
            this->lista->moverAPosicion(this->encontrar(k));
            x=this->lista->eliminar();
        }
    }
    //Retorna y remueve un registro arbitrario del set
    Key removerCualquiera(){
        this->lista->moverAlFinal();
        this->lista->anterior();
        return *(this->lista->eliminar());
    }
};
/////////////////////////////////////////

//clase abstracta cola
template<typename E> class Cola {
private:
    void operator = (const Cola&) {}  //Proteccion asignada
    Cola(const Cola&) {}  //Constructor Proteccion copia
public:
    Cola(){}  //por defecto
    virtual ~Cola() {}  //Base destructor

    //Reinicializar la cola. El usuario es responsable
    //por reclamar el espacio utilizado por el elemento
    //de la cola
    virtual void clear() = 0;

    //colocar un elemento en la parte de atras de la cola
    //it: el elemento siendo encolado
    virtual void encolar( E) = 0;

    //Remover y retornar elementos al frente de la cola
    //Retornar: El elemento en el frente de la cola.
    virtual E desencolar() = 0;

    //Retornar: Una copia de el elemento frontal
    virtual E valorFrontal() = 0;

    //Retornar: El numero de elementos in la cola .
    virtual int longitud() = 0;
};

template <typename E> class ACola : public Cola<E> {
private:
    int tamMax;  //Tamaño maximo de la cola
    int frente;     //Indice del elemento frontal
    int elemFin;    //Indice del elemento final
    E *listaArreglo;  //Arreglo conteniendo los elementos de la cola

public:

    /*
     * Constructor
     */
    ACola(int l=100){
        this->tamMax = l;
        this->frente=1;
        this->elemFin=0;
        this->listaArreglo = new E[this->tamMax+1];
    }

    /*
     * Destructor
     */
    ~ACola(){
        //limpiar();
    }

    void encolar(E val){
        //Al ENCOLAR, el puntero "elemFin" se calcula como "elemFin = (elemFin+1) % TamMax"
        //TamMax = TamUsuario + 1
        //this->listaArreglo[(elemFin+1)%(tamañoMax+1)] = val;
        this->listaArreglo[elemFin+1] = val;
        this->elemFin++;
    }

    E desencolar(){
        //Al DESENCOLAR, el puntero "frente" se calcula como "frente = (frente + longitud()) % TamMax"
        //TamMax = TamUsuario + 1
        E val = this->listaArreglo[frente];
        //this->frente = (this->frente + longitud()) % (tamañoMax+1);
        this->frente++;
        return val;
    }

    E valorFrontal(){
        return this->listaArreglo[frente];
    }

    int longitud(){
        if(this->elemFin==this->tamMax){
            return tamMax;
        }else {
            return (this->tamMax - this->frente + this->elemFin + 1) % (this->tamMax);
        }
    }

    void clear(){
        this->frente=1;
        this->elemFin=0;
        //this->listaArreglo[this->frente]=NULL;
    }


};
/////////////////////////////////////////

//Clase HeapSet
template<typename E>
class ArbolBinario{
private:
public:
    ArbolBinario(){}
    ~ArbolBinario(){}
    //virtual void insertar(E e) = 0;
    //virtual E encontrar(E e) = 0;
    //Retorna el numero de registros en el arbol binario
    //virtual int longitud()=0;
};

template<typename E>
class ArbolBinarioArreglo : ArbolBinario<E>{
private:
    ListaArreglo<E> *arreglo;
    int tamMax; //el tamanho maximo fijo del arreglo
    int tamLista;//elementos que realmente estan dentro del arbol binario
    int MaxIndex;//Indice maximo que contine datos
public:
    ArbolBinarioArreglo(int tamMax = 20){
        this->tamMax = tamMax;
        this->arreglo = new ListaArreglo<E>(tamMax);
        this->init();
    }
    void init(){
        this->tamLista = 0;
        this->MaxIndex = 0;
        this->arreglo->limpiar();
        this->arreglo->moverAInicio();

        for(this->arreglo->moverAInicio(); this->arreglo->posicionActual() < this->arreglo->maxLongitud(); this->arreglo->siguiente()){
            this->arreglo->setValor(NULL);
        }
    }

    //Insertar en orden, al final del arreglo
    void insertarnext(E valor){
        this->arreglo->agregar(valor);
        tamLista++;
        if(MaxIndex < tamLista){
            MaxIndex = tamLista-1;
        }
    }


    void print() {
        for(this->arreglo->moverAInicio();this->arreglo->posicionActual() <= this->MaxIndex; this->arreglo->siguiente()){
            cout<<this->arreglo->getValor() <<endl;
        }
    }

    int numelements(){
        return this->tamLista;
    }

    int maxindex(){
        return this->MaxIndex;
    }

    //Metodo Max Heapify
    void MaxHF(int i){
        if(i>-1) {
            int l = 2 * i + 1, r = 2 * (i + 1), largest;
            if (l < this->tamLista && this->arreglo->getValorEnPosicion(l) > this->arreglo->getValorEnPosicion(i)) {
                largest = l;
            } else {
                largest = i;
            }
            if (r < this->tamLista && this->arreglo->getValorEnPosicion(r) > this->arreglo->getValorEnPosicion(largest)) {
                largest = r;
            }
            if (largest != i) {
                E temp = this->arreglo->getValorEnPosicion(largest);
                this->arreglo->setValorEnPosicion(largest, this->arreglo->getValorEnPosicion(i));
                this->arreglo->setValorEnPosicion(i, temp);
                MaxHF(largest);
            }
        }
    }
    //Metodo Min Heapify
    void MinHF(int i){
        if(i>-1) {
            int l = 2 * i + 1, r = 2 * (i + 1), minimum;
            if (l < this->tamLista && this->arreglo->getValorEnPosicion(l) < this->arreglo->getValorEnPosicion(i)) {
                minimum = l;
            } else {
                minimum = i;
            }
            if (r < this->tamLista && this->arreglo->getValorEnPosicion(r) < this->arreglo->getValorEnPosicion(minimum)) {
                minimum = r;
            }
            if (minimum != i) {
                E temp = this->arreglo->getValorEnPosicion(minimum);
                this->arreglo->setValorEnPosicion(minimum, this->arreglo->getValorEnPosicion(i));
                this->arreglo->setValorEnPosicion(i, temp);
                MinHF(minimum);
            }
        }
    }

    //Metodo Building Max Heapify
    void BMaxH(){
        for (int i = floor(((float)MaxIndex)/2);i>=0;i--){
            MaxHF(i);
        }
    }

    //Metodo Building Min Heapify
    void BMinH(){
        for (int i = floor(((float)MaxIndex)/2);i>=0;i--){
            MinHF(i);
        }
    }

    //Metodo para ordenar Creciente/Ascendente.
    void HeapSortAsc(){
        this->BMaxH();
        for(int i=MaxIndex;i>0;i--){
            E temp=this->arreglo->getValorEnPosicion(i);
            this->arreglo->setValorEnPosicion(i, this->arreglo->getValorEnPosicion(0));
            this->arreglo->setValorEnPosicion(0,temp);
            this->tamLista--;
            this->MaxHF(0);
        }
        this->tamLista = this->MaxIndex + 1;
    }

    //Metodo para retornar el TOP del Heap (depende de si es Max Heap o Min Heap)
    E HeapTop(){
        return this->arreglo->getValorEnPosicion(0);
    }

    //Metodo para reemplzar un valor MAYOR q el existente. (MAX HEAP)
    void HeapIncreaseKey(int index,E value){
        if(value > this->arreglo->getValorEnPosicion(index)){
            this->arreglo->setValorEnPosicion(index,value);
            while(index >0 && this->arreglo->getValorEnPosicion(floor(((float)index-1)/2)) < this->arreglo->getValorEnPosicion(index)){
                E temp = this->arreglo->getValorEnPosicion(floor(((float)index-1)/2));
                this->arreglo->setValorEnPosicion(floor(((float)index-1)/2),this->arreglo->getValorEnPosicion(index));
                this->arreglo->setValorEnPosicion(index,temp);
                index = floor(((float)index-1)/2);
            }
        }
    }
    //Metodo para reemplzar un valor MENOR q el existente. (MIN HEAP)
    void HeapDecreaseKey(int index,E value){
        if(value < this->arreglo->getValorEnPosicion(index)){
            this->arreglo->setValorEnPosicion(index,value);
            while(index >0 && this->arreglo->getValorEnPosicion(floor(((float)index-1)/2)) > this->arreglo->getValorEnPosicion(index)){
                E temp = this->arreglo->getValorEnPosicion(floor(((float)index-1)/2));
                this->arreglo->setValorEnPosicion(floor(((float)index-1)/2),this->arreglo->getValorEnPosicion(index));
                this->arreglo->setValorEnPosicion(index,temp);
                index = floor(((float)index-1)/2);
            }
        }
    }

    //Inserta un elemento al Heap y Mantiene la estructura MAX HEAP.
    void MaxHeapInsert(E valor){
        this->insertarnext(valor);
        this->BMaxH();
    }
    //Inserta un elemento al Heap y Mantiene la estructura MIN HEAP.
    void MinHeapInsert(E valor){
        this->insertarnext(valor);
        this->BMinH();
    }

    //Extrae el valor TOP del MAX Heap, indice=0, borrandolo del arreglo.
    E MaxHeapExtractTop(){
        if(this->tamLista>1){
            E temp = this->arreglo->getValorEnPosicion(0);
            this->arreglo->setValorEnPosicion(0,this->arreglo->getValorEnPosicion(this->MaxIndex));
            this->arreglo->moverAlFinal();
            this->arreglo->eliminar();
            this->tamLista--;
            this->MaxIndex--;
            this->MaxHF(0);
            return temp;
        }else if(this->tamLista == 1){
            E temp = this->arreglo->getValorEnPosicion(0);
            this->init();
            return temp;
        }else{
            this->init();
            return -1;
        }
    }

    //Extrae el valor TOP del MIN Heap, indice=0, borrandolo del arreglo.
    E MinHeapExtractTop(){
        if(this->tamLista>1){
            E temp = this->arreglo->getValorEnPosicion(0);
            this->arreglo->setValorEnPosicion(0,this->arreglo->getValorEnPosicion(this->MaxIndex));
            this->arreglo->moverAlFinal();
            this->arreglo->eliminar();
            this->tamLista--;
            this->MaxIndex--;
            this->MinHF(0);
            return temp;
        }else if(this->tamLista == 1){
            E temp = this->arreglo->getValorEnPosicion(0);
            this->init();
            return temp;
        }else{
            this->init();
            return -1;
        }
    }


    //Devuelve el hijo izquierdo
    E hijo_izq(int index){
        if(this->MaxIndex >= 2*index+1){
            return this->arreglo->getValorEnPosicion(2*index+1);
        }
    }
    //Devuelve el hijo derecho
    E hijo_der(int index){
        if(this->MaxIndex >= 2 * (index + 1)) {
            return this->arreglo->getValorEnPosicion(2 * (index + 1));
        }
    }
    //Devuelve el padre de un indice.
    E padre(int index){
        if((floor(((float) index - 1) / 2))>=0) {
            return this->arreglo->getValorEnPosicion(floor(((float) index - 1) / 2));
        }
    }
    //Devuelve la altura del Heap (Piso(lg n))
    int altura(){
        return floor(log(this->tamLista)/(log(2)));
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

template<typename Key, typename E> class DiccionarioArreglo : public Diccionario<Key,E>{
private:
    ListaArreglo<KVPar<Key, E>> *lista = new ListaArreglo<KVPar<Key, E>>;
public:
    //Constructor
    DiccionarioArreglo(){}

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
    KVPar<Key,E> begin(){
        this->lista->moverAInicio();
        return this->lista->getValor();
    }
    //Retornar valor en posicion
    E getValorenPosicion(int i){
        this->lista->getValorEnPosicion(i).valor();
    }

    //Retornar Key en posicion
    Key getKeyEnPosicion(int i){
        this->lista->getValorEnPosicion(i).key();
    }

};

//Clase Set basada en Heap.
template <typename S,typename T> class HeapSet: public ArbolBinarioArreglo<S>{
private:
    ArbolBinarioArreglo<S> *HeapData;
    DiccionarioArreglo<S,T> *DictData;

public:
    //Constructor
    HeapSet(){
        HeapData = new ArbolBinarioArreglo<S>;
        DictData = new DiccionarioArreglo<S,T>;
    }
    //Destructor
    ~HeapSet(){
    }

    void insertar(S a,T b){
        this->HeapData->MinHeapInsert(a);
        this->DictData->insertar(a,b);
    }

    pair<S,T> ExtraerTop(){
        pair<S, T> par;
        if(this->HeapData->numelements()!=0) {
            par.first = this->HeapData->MinHeapExtractTop();
            par.second = this->DictData->encontrar(par.first);
        }else{
            par.first=-1;
            par.second=-1;
        }
        return par;
    }
    int longitud(){
        return HeapData->numelements();
    }
    void print(){
        this->HeapData->print();
    }

};
////////////////////////////////////////////////
//Implementacion de clases Disjoint Set Union.
class DSU {
public:
    int n;

    ListaArreglo<int> *padre;
    ListaArreglo<int> *rank;

     DSU(int n){
        this->n = n;
        this->padre = new ListaArreglo<int>(n);
        this->rank = new ListaArreglo<int>(n);

        for(int i=0; i < n;i++){
            this->padre->agregar(i);
        }
        for(int i=0; i < n;i++){
            this->rank->agregar(0);
        }
    }

    ~DSU(){

    }

    int raiz(int x){
        while(this->padre->getValorEnPosicion(x) != x){
            this->padre->setValorEnPosicion(x,this->padre->getValorEnPosicion(this->padre->getValorEnPosicion(x)));
            x = this->padre->getValorEnPosicion(x);
        }
        return x;
    }
    bool join(int x, int y) {
        x = raiz(x);
        y = raiz(y);

        if (x == y)
            return false;

        if(this->rank->getValorEnPosicion(x) < this->rank->getValorEnPosicion(y)){
            swap(x, y);
        }

        this->padre->setValorEnPosicion(y,x);

        if(this->rank->getValorEnPosicion(x) == this->rank->getValorEnPosicion(y)){
            this->rank->setValorEnPosicion(x,this->rank->getValorEnPosicion(x) + 1);
        }
        return true;
    }
};

/////////////////////////////////////////////////
// Implementacion de GRAFO.
class Grafo{
private:
public:
    //Constructor
    Grafo(){}
    //Metodo de inicializacion
    virtual void init(int n) = 0;
    //Retornar el numero de vertices y aristas
    virtual int get_N_Vertices()=0;
    virtual int get_N_Aristas()=0;
    //Retornar el primer vecino
    virtual int primero(int v) = 0;
    //Retornar el siguiente vecino
    virtual int siguiente(int v, int w) = 0;
    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    virtual void setArista(int i, int j, int w) = 0;
    //Eliminar arista
    virtual void eliminarArista(int i, int j) = 0;
    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    virtual bool esArista(int i, int j) = 0;
    //Retornar el peso de una arista
    virtual int getPeso(int i, int j) = 0;
    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    virtual int getMarca(int v) = 0;
    virtual void setMarca(int v, int val) = 0;
};

//Implementacion de Grafo
class GrafoMA : public Grafo{
private:
    int numeroVertices;
    int numeroAristas;
    int **matriz;
    int **matrizw;
    int **matrizfw;
    int **matrizfwp;
    int *marca;

    //Clase Arista
    class Arista{
    public:
        int u,v,w;
        bool operator<(const Arista &e) const {
            return w < e.w;
        }
    };
    ListaArreglo<bool> *visitado = new ListaArreglo<bool>;
    ListaArreglo<Arista> *Aristas = new ListaArreglo<Arista>;

public:

    //Metodo de inicializacion: inicializar la matriz
    void init(int n) {
        int i,j;
        this->numeroVertices = n;
        this->numeroAristas = 0;
        this->marca = new int[n];
        //Inicializamos el arreglo de marca (visitados)
        for (i = 0; i < this->numeroVertices; i++) {
            this->marca[i] = 0; //NO VISITADO
        }
        //Inicializar la matriz de adyacencia y completarla con valores CERO
        this->matriz = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matriz[i] = new int[this->numeroVertices];
        }
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matriz[i][j] = 0; //Cero es igual a no adyacencia.
            }
        }
        //Inicializar la matriz de pesos(w) y colocar un valor muy negativo.
        this->matrizw = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matrizw[i] = new int[this->numeroVertices];
        }
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matrizw[i][j] = -1000000; //Valor muy negativo.
            }
        }
        //Inicializar la matriz para Floyd-Warshall y completarla con un valor muy ALTO.
        this->matrizfw = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matrizfw[i] = new int[this->numeroVertices];
        }
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                if(i!=j){
                    this->matrizfw[i][j] = 1000000; //valor muy alto.
                }else{
                    this->matrizfw[i][j] = 0;
                }
            }
        }
        //Inicializar la matriz PATH para Floyd-Warshall y completarla con -1.
        this->matrizfwp = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matrizfwp[i] = new int[this->numeroVertices];
        }
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matrizfwp[i][j] = -1; //-1 indica vertice no alcanzable.
            }
        }
        //Colocando en false el arreglo visitado
        for (i = 0; i < this->numeroVertices; i++) {
            this->visitado->setValorEnPosicion(i,false);
        }
    }

    GrafoMA(int numVert){
        this->init(numVert);
    }

    ~GrafoMA(){
        delete[] this->marca;
        delete[] this->matriz;
    }

    void SortAristasAsc(){
        Arista temp;
        int j=0;
        for(int i=1;i<Aristas->longitud();i++){
            temp = this->Aristas->getValorEnPosicion(i);
            //temp1 = lista[i];
            j=i-1;
            //while(j>=0 && lista[j]>temp1){
            while(j>=0 && this->Aristas->getValorEnPosicion(j).w>temp.w){
                this->Aristas->setValorEnPosicion(j+1,this->Aristas->getValorEnPosicion(j));
                //lista[j+1] = lista[j];
                j -= 1;
            }
            //lista[j+1] = temp1;
            this->Aristas->setValorEnPosicion(j+1,temp);
        }
    }

    //Retornar el numero de vertices y aristas
    int get_N_Vertices(){
        return this->numeroVertices;
    }
    int get_N_Aristas(){
        int A=0;
        for(int i=0;i<this->numeroVertices;i++){
            for(int j=0;j<this->numeroVertices;j++){
                A = A + this->matriz[i][j];
            }
        }
        this->numeroAristas=A/2;
        return this->numeroAristas;
    }

    //Retornar el primer vecino de v
    int primero(int v) {
        for (int i = 0; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Retornar el siguiente vecino
    int siguiente(int v, int w) {
        for (int i = w+1; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Ingresar o Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    void setArista(int i, int j, int w) {
        this->matriz[i][j] = 1;
        this->matriz[j][i] = 1;
        this->matrizw[i][j] = w;
        this->matrizw[j][i] = w;
        this->matrizfw[i][j] = w;
        this->matrizfw[j][i] = w;
        this->matrizfwp[i][j] = i;
        this->matrizfwp[j][i] = j;
        this->Aristas->agregar({i,j,w});
    }

    //Eliminar arista
    void eliminarArista(int i, int j) {
        this->matriz[i][j] = 0;
        this->matriz[j][i] = 0;
        this->matrizw[i][j] = -1000000;
        this->matrizw[j][i] = -1000000;
        this->matrizfw[i][j] = 1000000;
        this->matrizfw[j][i] = 1000000;
        this->matrizfwp[i][j] = -1;
        this->matrizfwp[j][i] = -1;
    }

    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    bool esArista(int i, int j) {
        return this->matriz[i][j] != 0;
    }

    //Retornar el peso de una arista
    int getPeso(int i, int j) {
        return this->matrizw[i][j];
    }

    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    int getMarca(int v) {
        return this->marca[v];
    }
    void setMarca(int v, int val) {
        this->marca[v] = val;
    }

    //La funcion adyacencia retorna una lista con el contenido de todas las aristas con el resto de Vertices.
    //Se ingresa el vértice "v".
    //Se devuelve una lista de los vertices con conexión directa con el vértice "v".
    void funcion_adyacencia(int v,ListaArreglo<int> **vector){
        ListaArreglo<int> *result = new ListaArreglo<int>;
        //cout<<vector;
        for (int i = 0; i < this->numeroVertices; ++i) {
            result->agregar(matriz[v][i]);
        }
        *vector = result;
    }

    //Recorre el grafo con el metodo Depth-first search
    //Desde el vertice "v"
    void RecorridoDFS(int v){
        cout<<v<<" ";
        //Previsit(G,v); //util para realizar alguna tarea antes de marcar como visitado al vertice.
        this->visitado->setValorEnPosicion(v,true);
        for (int i = 0; i < this->numeroVertices; ++i) {
            if(matriz[v][i]!=0){
                if(!this->visitado->getValorEnPosicion(i)){
                    this->RecorridoDFS(i);
                }
            }
        }
        //PostVisit(G,v); //util para realizar alguna tarea luego de la ejecucion del traverse.
    }

    //Recorre el Grafo con el metodo Breadth-first search Modificado
    //Se ingresa el source "s" y devuelve dos arreglos:
    //Uno con los COSTOS a cada uno de los demas vertices
    //Otro arreglo para poder identificar la RUTA.
    void RecorridoBFS(int s, ListaArreglo<int> **L,ListaArreglo<int> **P){
        // Esta lista se puede entender tambien como si fue Visitado el vértice.
        ListaArreglo<int> *distancia = new ListaArreglo<int>;
        for (int i = 0; i < this->numeroVertices; i++) {
            distancia->setValorEnPosicion(i,-1);
        }
        //Arreglo de padres para calcular el camino.
        ListaArreglo<int> *path = new ListaArreglo<int>(this->numeroVertices);
        for (int i = 0; i < this->numeroVertices; i++) {
            path->agregar(-1);
        }
        ACola<int> *q1 = new ACola<int>();
        q1->encolar(s);
        distancia->setValorEnPosicion(s,0);
        //path->setValorEnPosicion(s,s);

        while(q1->longitud() != 0){
            int u = q1->desencolar();
            //cout<<u<<" "; // Mostrar los vertices
            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[u][i]!=0){
                    if(distancia->getValorEnPosicion(i)== -1){ //El -1 puede actuar como un check de No-Visitado.
                        //distancia->setValorEnPosicion(i,distancia->getValorEnPosicion(u) + 1);
                        distancia->setValorEnPosicion(i,distancia->getValorEnPosicion(u) + this->matrizw[u][i]);
                        q1->encolar(i);
                        path->setValorEnPosicion(i,u);
                    }
                }
            }
        }
        *L = distancia;
        *P = path;
    }

    //Realiza el calculo de COSTO y RUTA para un par de vertices especificos.
    //vertice fuente: "V"
    //vertuce destino: "U"
    void PathCostBFS(int V, int U){
        ListaArreglo<int> *temp = new ListaArreglo<int>;
        ListaArreglo<int> *camfull = new ListaArreglo<int>;
        ListaArreglo<int> *cam = new ListaArreglo<int>;
        this->RecorridoBFS(V,&temp,&camfull);
        cout<<"Costo BFS Modificado: "<<temp->getValorEnPosicion(U)<<endl;
        int vertice = U;
        while(vertice != -1){
            cam->agregar(vertice);
            vertice = camfull->getValorEnPosicion(vertice);
        }
        cout<<"Ruta BFS Modificado: ";
        for(int i=cam->longitud()-1; i>=0;i--){
            cout<<cam->getValorEnPosicion(i)<<" ";
        }
    }

    //Genera un Minimum Spanning Tree mediante el algoritmo PRIM.
    int Prim(int n){
        //Colocando en false la matriz visitado
        for (int i = 0; i < this->numeroVertices; i++) {
            this->visitado->setValorEnPosicion(i,false);
        }
        HeapSet<int,int> *PQ = new HeapSet<int,int>;
        PQ->insertar(0,n);//Primer costo y primer Vertice.

        int mst = 0;
        while (PQ->longitud() > 0) {
            pair<int,int> r;
            r = PQ->ExtraerTop();
            int w = r.first;
            int v = r.second;
            int u;

            if (this->visitado->getValorEnPosicion(v))
                continue;
            mst += w;
            cout<<v<<" ";
            this->visitado->setValorEnPosicion(v,true);
            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[v][i]!=0){
                    u = i;
                    w = this->matrizw[v][i];
                    PQ->insertar(w,u);
                }
            }
            //cout<<u<<" ";
        }
        cout<<endl;
        return mst;
    }

    //Genera un Minimum Spanning Tree mediante el algoritmo KRUSKAL.
    int Kruskal() {

        this->SortAristasAsc();
        DSU dsu(this->numeroVertices);

        int mst = 0;
        int u,v,w;

        //cout<<this->Aristas->getValorEnPosicion(0).u<<" ";

        for(int i=0; i<this->Aristas->longitud();i++){
            u = this->Aristas->getValorEnPosicion(i).u;
            v = this->Aristas->getValorEnPosicion(i).v;
            w = this->Aristas->getValorEnPosicion(i).w;
            if (dsu.join(u, v)) {
                cout<<u<<"-"<<v<<" ";
                mst += w;
            }
        }
        cout<<endl;
        //for(int i=0; i<this->Aristas->longitud();i++){
        //    cout<<this->Aristas->getValorEnPosicion(i).w<<" : "<<this->Aristas->getValorEnPosicion(i).u<<"-"<<this->Aristas->getValorEnPosicion(i).v<<endl;
        //}
        return mst;
    }

    //Implementación del algoritmo DIJKSTRA
    //Se ingresa el source "s" y devuelve dos arreglos:
    //Uno con los COSTOS a cada uno de los demas vertices
    //Otro arreglo para poder identificar la RUTA.
    void Dijkstra(int s, ListaArreglo<int> **L,ListaArreglo<int> **P){

        //Arreglo para distancias mínimas de un Vertice hacia el resto.
        ListaArreglo<int> *distancia = new ListaArreglo<int>(this->numeroVertices);
        for (int i = 0; i < this->numeroVertices; i++) {
            distancia->agregar(1000000);
        }
        //Arreglo de padres para calcular el camino.
        ListaArreglo<int> *path = new ListaArreglo<int>(this->numeroVertices);
        for (int i = 0; i < this->numeroVertices; i++) {
            path->agregar(-1);
        }
        HeapSet<int,int> *PQ = new HeapSet<int,int>;

        distancia->setValorEnPosicion(s,0);
        PQ->insertar(0,s);// Insertar costo "0" y el Vertice de partida o inicio.

        while (PQ->longitud() > 0) {
            pair<int,int> r;
            r = PQ->ExtraerTop();
            int d = r.first;
            int v = r.second;

            if (d != distancia->getValorEnPosicion(v))
                continue;

            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[v][i]!=0){
                    int u = i;
                    int w = this->matrizw[v][i];
                    if(distancia->getValorEnPosicion(v) + w < distancia->getValorEnPosicion(u)){
                        path->setValorEnPosicion(u,v);
                        distancia->setValorEnPosicion(u,distancia->getValorEnPosicion(v) + w);
                        PQ->insertar(distancia->getValorEnPosicion(u),u);
                    }
                }
            }
        }
        *L = distancia;
        *P = path;
    }

    //Realiza el calculo de COSTO y RUTA para un par de vertices especificos.
    //vertice fuente: "V"
    //vertuce destino: "U"
    void PathCostDijkstra(int V,int U){
        ListaArreglo<int> *temp = new ListaArreglo<int>;
        ListaArreglo<int> *camfull = new ListaArreglo<int>;
        ListaArreglo<int> *cam = new ListaArreglo<int>;
        this->Dijkstra(V,&temp,&camfull);
        cout<<"Costo Dijkstra: "<<temp->getValorEnPosicion(U)<<endl;
        int vertice=U;
        while(vertice != -1){
            cam->agregar(vertice);
            vertice = camfull->getValorEnPosicion(vertice);
        }
        cout<<"Ruta Dijkstra: ";
        for(int i=cam->longitud()-1; i>=0;i--){
            cout<<cam->getValorEnPosicion(i)<<" ";
        }
    }

    //Implementación del algoritmo BELLMAN-FORD
    //Se ingresa el source "s" y devuelve dos arreglos:
    //Uno con los COSTOS a cada uno de los demas vertices
    //Otro arreglo para poder identificar la RUTA.
    void BellmanFord(int s, ListaArreglo<int> **L,ListaArreglo<int> **P){

        //Arreglo para distancias mínimas de un Vertice hacia el resto.
        ListaArreglo<int> *distancia = new ListaArreglo<int>(this->numeroVertices);
        for (int i = 0; i < this->numeroVertices; i++) {
            distancia->agregar(1000000);
        }
        //Arreglo de padres para calcular el camino.
        ListaArreglo<int> *path = new ListaArreglo<int>(this->numeroVertices);
        for (int i = 0; i < this->numeroVertices; i++) {
            path->agregar(-1);
        }

        distancia->setValorEnPosicion(s,0);
        int u,v,w;
        for(int m=1;m<this->numeroVertices-1;m++){
            u=s;
            for(int i=0; i<this->Aristas->longitud();i++){
                u = this->Aristas->getValorEnPosicion(i).u;
                v = this->Aristas->getValorEnPosicion(i).v;
                w = this->Aristas->getValorEnPosicion(i).w;
                if(distancia->getValorEnPosicion(u) + w < distancia->getValorEnPosicion(v)){
                    distancia->setValorEnPosicion(v,distancia->getValorEnPosicion(u) + w);
                    path->setValorEnPosicion(v,u);
                }
            }
        }
        *L = distancia;
        *P = path;
    }

    //Realiza el calculo de COSTO y RUTA para un par de vertices especificos.
    //vertice fuente: "V"
    //vertuce destino: "U"
    void PathCostBellmanFord(int V,int U){
        ListaArreglo<int> *temp = new ListaArreglo<int>;
        ListaArreglo<int> *camfull = new ListaArreglo<int>;
        ListaArreglo<int> *cam = new ListaArreglo<int>;
        this->BellmanFord(V,&temp,&camfull);
        cout<<"Costo Bellman-Ford: "<<temp->getValorEnPosicion(U)<<endl;
        int vertice=U;
        while(vertice != -1){
            cam->agregar(vertice);
            vertice = camfull->getValorEnPosicion(vertice);
        }
        cout<<"Ruta Bellman-Ford: ";
        for(int i=cam->longitud()-1; i>=0;i--){
            cout<<cam->getValorEnPosicion(i)<<" ";
        }
    }

    //Implementación del algoritmo FLOYD-WARSHALL
    //Este algoritmo calcula la ruta mas corta de todo par de vertices en el grafo.
    //APSP: All Pairs Shortest Path.
    //Genera internamente dos matrices: COSTOS y otra para identificar la RUTA.
    void FloydWarshall(){
        for(int k = 0;k<this->numeroVertices;k++){
            for(int i = 0;i<this->numeroVertices;i++){
                for(int j = 0;j<this->numeroVertices;j++){
                    if(i!=k && j!=k){
                        if(matrizfw[i][j] > matrizfw[i][k]+matrizfw[k][j]){
                            this->matrizfw[i][j] = matrizfw[i][k]+matrizfw[k][j];
                            this->matrizfwp[i][j] = this->matrizfwp[k][j];
                        }
                    }
                }
            }
        }
    }

    //Realiza el calculo de COSTO y RUTA para un par de vertices especificos.
    //vertice fuente: "V"
    //vertuce destino: "U"
    void PathCostFloydWarshall(int V,int U){
        ListaArreglo<int> *cam = new ListaArreglo<int>;
        this->FloydWarshall();

        cout<<"Costo Floyd-Warshall: "<<this->matrizfw[V][U]<<endl;
        int vertice=U;
        while(vertice != -1){
            cam->agregar(vertice);
            vertice = this->matrizfwp[V][vertice];
        }
        cout<<"Ruta Floyd-Warshall: ";
        for(int i=cam->longitud()-1; i>=0;i--){
            cout<<cam->getValorEnPosicion(i)<<" ";
        }
    }
};

int main() {

    cout<<"Ingrese el numero de VERTICES del Grafo, segido del numero de ARISTAS."<<endl;
    cout<<"Luego ingrese las aristas U V W. (Aristas de U a V con peso W)."<<endl;
    cout<<"En la ultima linea coloque S D. (S es el vertice fuente y D el vertice destino)."<<endl;
    cout<<"(p.d. se está considerando un grafo no dirigido)"<<endl;

    int c1,c2,i,j,val;
    int vertices;
    int aristas;
    cin>>vertices;
    cin>>aristas;
    GrafoMA *grafo = new GrafoMA(vertices);

    for(int ix = 0; ix<aristas; ix++) {
        cin >> i;
        cin >> j;
        cin >> val;
        grafo->setArista(i,j, val);
        grafo->setArista(j,i, val);
    }
    cin>>c1;
    cin>>c2;

    char opt2='Y';
    while (opt2 != 'N'){

        cout<<"Elegir Algoritmo:"<<endl;
        cout<<"(1) - Dijkstra."<<endl;
        cout<<"(2) - Bellman-Ford."<<endl;
        cout<<"(3) - Floyd-Warshall."<<endl;
        cout<<"(4) - BFS Modificado."<<endl;

        int opt;
        cin>>opt;

        switch(opt)
        {
            case 1:
                grafo->PathCostDijkstra(c1,c2);
                cout<<endl<<"Desea continuar? (Y=Cualquier tecla/N):"<<endl;
                cin>>opt2;
                break;
            case 2:
                grafo->PathCostBellmanFord(c1,c2);
                cout<<endl<<"Desea continuar? (Y=Cualquier tecla/N):"<<endl;
                cin>>opt2;
                break;
            case 3:
                grafo->PathCostFloydWarshall(c1,c2);
                cout<<endl<<"Desea continuar? (Y=Cualquier tecla/N):"<<endl;
                cin>>opt2;
                break;
            case 4:
                grafo->PathCostBFS(c1,c2);
                cout<<endl<<"Desea continuar? (Y=Cualquier tecla/N):"<<endl;
                cin>>opt2;
                break;
            default:
                cout<<"No ha ingresado una opcion valida. Desea continuar? (Y=Cualquier tecla/N):"<<endl;
                cin>>opt2;
        }
    }
    delete grafo;
    return 0;
}

