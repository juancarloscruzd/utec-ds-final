//
// Created by VICTOR HERRERA on 2021-06-09.
//
#include <iostream>
#include <cmath>
using namespace std;

//Clase Padre: Lista
template<typename E> class Lista {
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
    //Devuelve la Mediana de los datos contenidos en la Lista
    E mediana() {
        //Ordenar los datos ascendentes sin llamar al metodo de la clase.
        int j,temp1;
        for(int i=1;i<this->tamLista;i++){
            temp1=this->arreglo[i];
            j=i-1;
            while(j>=0 && this->arreglo[j]<temp1){
                this->arreglo[j+1] = this->arreglo[j];
                j -= 1;
            }
            this->arreglo[j+1] = temp1;
        }
        //Elegir el valor medio (dependencia par o impar)
        if(this->tamLista%2!=0){
            return this->arreglo[this->tamLista/2];
        }else{
            return (E)(this->arreglo[this->tamLista/2-1]+this->arreglo[this->tamLista/2])/2;
        }
    }
    //Ordena la lista de forma ascendente
    void OrdenarAsc() {
        int j,temp1;

        for(int i=1;i<this->tamLista;i++){
            temp1=this->arreglo[i];
            j=i-1;
            while(j>=0 && this->arreglo[j]>temp1){
                this->arreglo[j+1] = this->arreglo[j];
                j -= 1;
            }
            this->arreglo[j+1] = temp1;
        }
    }

    //
    void triorder(int i, int j){
        int med;
        int array[j-i+1];
        for(int ih = i; ih <=j; ih++){
            array[ih] = this->arreglo[ih];
        }
        cout<<i<<endl;
        cout<<j<<endl;
        if((j-i+1)%2 != 0){
            med = array[(j-i)/2];
        }else{
            med = (array[(j-i)/2]+array[(j-i)/2+1])/2;
        }
        cout<<med<<endl;
        //triorder();
    }
    void reorder(int tamanho){
        int i=0; int j = tamanho -1;
        this->triorder(i,j);
    }
};


template<typename E>
class ArbolBinario{
private:
public:
    ArbolBinario(){}
    ~ArbolBinario(){}
    virtual void insertar(E e) = 0;
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
        this->tamLista = 0;
        this->MaxIndex = 0;
        this->arreglo->moverAInicio();

        for(this->arreglo->moverAInicio(); this->arreglo->posicionActual() < this->arreglo->maxLongitud(); this->arreglo->siguiente()){
            this->arreglo->setValor(NULL);
        }
    }
    //Inserta elementos en el arbol binario la IZQ menores que el Padre y la DER mayores que el Padre
    void insertar(E valor) {
        int index = 0;
        this->arreglo->moverAInicio();
        E actual = this->arreglo->getValor();
        while (actual != NULL) {
            if (actual > valor) {
                index = 2 * index + 1;
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            } else {
                index = 2 * (index + 1);
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            }
        }

        if (actual == NULL) {
            this->arreglo->setValorEnPosicion(index, valor);
            tamLista++;
        }
        if(MaxIndex < index){
            MaxIndex = index;
        }
    }

    E encontrar(E valor){
        int index = 0;
        this->arreglo->moverAInicio();
        E actual = this->arreglo->getValor();
        while (actual != valor && index <= this->tamMax) {
            if (actual > valor) {
                index = 2 * index + 1;
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            } else {
                index = 2 * (index + 1);
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            }
        }

        if (index > this->tamMax) {
            return -1;
        }else{
            return valor;
        }
    }

    int encontrarIndice(E valor){
        int index = 0;
        this->arreglo->moverAInicio();
        E actual = this->arreglo->getValor();
        while (actual != valor && index <= this->tamMax) {
            if (actual > valor) {
                index = 2 * index + 1;
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            } else {
                index = 2 * (index + 1);
                this->arreglo->moverAPosicion(index);
                actual = this->arreglo->getValor();
            }
        }

        if (index > this->tamMax) {
            return -1;
        }else{
            return index;
        }
    }

    E hijoDer(int index){
        int id = 2 * (index + 1);
        this->arreglo->moverAPosicion(id);
        return this->arreglo->getValor();
    }
    E hijoIzq(int index){
        this->arreglo->moverAPosicion(2 * index + 1);
        return this->arreglo->getValor();
    }

    //Eliminar un elemento del arbol
    void eliminar(E valor){
        int indice  = this->encontrarIndice(valor);
        ListaArreglo<int> *L1 = new ListaArreglo<int>;
        ListaArreglo<int> *L2 = new ListaArreglo<int>;
        ListaArreglo<int> *L3 = new ListaArreglo<int>;

        int hizq = 2*indice+1;
        int hder = 2*(indice+1);
        if(hizq != 0){
            L1->agregar(hizq);
            L2->agregar(hizq);
        }if(hder != 0){
            L1->agregar(hder);
            L2->agregar(hder);
        }

        while(L2->longitud() >= 1){
            L2->moverAInicio();
            int val2 = L2->eliminar();

            hizq = 2*val2+1;
            hder = 2*(val2+1);
            if(hizq != 0 && hizq <= this->MaxIndex){
                L1->agregar(hizq);
                L2->agregar(hizq);
            }if(hder != 0 && hder <= this->MaxIndex){
                L1->agregar(hder);
                L2->agregar(hder);
            }
        }
        cout<<"------"<<endl;
        for(L1->moverAInicio(); L1->posicionActual() < L1->longitud(); L1->siguiente()){
            L3->agregar(this->arreglo->getValorEnPosicion(L1->getValor()));
            cout<<this->arreglo->getValorEnPosicion(L1->getValor())<<endl;
        }
        cout<<"------"<<endl;
        int med= L3->mediana();
        L3->OrdenarAsc();

        //L3->reorder(L3->longitud());

    }



    //Insertar en orden
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
    void MHF(int i){
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
                MHF(largest);
            }
        }
    }
    //Metodo Building Max Heapify
    void BMH(){
        for (int i = floor(((float)MaxIndex)/2);i>=0;i--){
            MHF(i);
        }
    }

    //Metodo para ordenar creciente.
    void HeapSort(){
        this->BMH();
        for(int i=MaxIndex;i>0;i--){
            E temp=this->arreglo->getValorEnPosicion(i);
            this->arreglo->setValorEnPosicion(i, this->arreglo->getValorEnPosicion(0));
            this->arreglo->setValorEnPosicion(0,temp);
            this->tamLista--;
            this->MHF(0);
        }
        this->tamLista = this->MaxIndex + 1;
    }
    //Metodo para retornar Maximo del Heap
    E MaxHeap(){
      return this->arreglo->getValorEnPosicion(0);
    }
    //Metodo para reemplzar un valor mayor q el existente.
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
};


int main() {
    ArbolBinarioArreglo<int> *arbol = new ArbolBinarioArreglo<int>;

    arbol->insertar(7);
    arbol->insertar(6);
    arbol->insertar(13);
    arbol->insertar(10);
    arbol->insertar(15);
    arbol->insertar(9);
    arbol->insertar(11);
    arbol->insertar(14);
    arbol->insertar(18);

/*
    arbol->insertarnext(2);
    arbol->insertarnext(6);
    arbol->insertarnext(9);
    arbol->insertarnext(20);
    arbol->insertarnext(13);
    arbol->insertarnext(24);
    arbol->insertarnext(33);
    arbol->insertarnext(42);
    arbol->insertarnext(46);

    arbol->print();
    cout<<"Numero de elementos = "<<arbol->numelements()<<endl;
    cout<<"Maximo indice con datos = "<<arbol->maxindex()<<endl;

    //arbol->MHF(0);
    arbol->BMH();
    arbol->print();
    cout<<"Numero de elementos = "<<arbol->numelements()<<endl;
    cout<<"Maximo indice con datos = "<<arbol->maxindex()<<endl;

    //arbol->HeapSort();
    //arbol->print();
    //cout<<"Numero de elementos = "<<arbol->numelements()<<endl;
    //cout<<"Maximo indice con datos = "<<arbol->maxindex()<<endl;
    cout<<arbol->MaxHeap()<<endl<<endl;

    arbol->HeapIncreaseKey(8,47);
    arbol->print();
*/

    arbol->print();
    cout<<"------"<<endl;
    arbol->eliminar(13);

    return 0;
}

