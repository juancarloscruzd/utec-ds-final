//
// Created by VICTOR HERRERA on 2021-06-23.
//

#include <iostream>
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
template<typename E> class ListaArreglo : public Lista<E> {
private:
    //Arreglo de elementos
    E *arreglo;
    //Tamanho fijo
    int tamMax;
    //Tamanho de la lista
    int tamLista;
    //Indice "actual"
    int actual;
public:
    //Constructor
    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Destructor
    ~ListaArreglo() {
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
        if (this->actual < this->tamMax)
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior() {
        //Sentinela
        if (this->actual > 0)
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
        if (pos >= 0)
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
        for (int i = this->tamLista; i > this->actual; i--)
            this->arreglo[i] = this->arreglo[i - 1];
        this->arreglo[this->actual] = elemento;
        this->tamLista++;
    }


    //Eliminar y retornar el elemento "actual"
    E eliminar() {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i) {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return eliminado;
    }

    void setValorEnPosicion(int index, E valor) {
        this->arreglo[index] = valor;
    }

    E getValorEnPosicion(int index) {
        return this->arreglo[index];
    }

    //Devuelve la Mediana de los datos contenidos en la Lista
    E mediana() {
        //Ordenar los datos ascendentes sin llamar al metodo de la clase.
        int j, temp1;
        for (int i = 1; i < this->tamLista; i++) {
            temp1 = this->arreglo[i];
            j = i - 1;
            while (j >= 0 && this->arreglo[j] < temp1) {
                this->arreglo[j + 1] = this->arreglo[j];
                j -= 1;
            }
            this->arreglo[j + 1] = temp1;
        }
        //Elegir el valor medio (dependencia par o impar)
        if (this->tamLista % 2 != 0) {
            return this->arreglo[this->tamLista / 2];
        } else {
            return (E) (this->arreglo[this->tamLista / 2 - 1] + this->arreglo[this->tamLista / 2]) / 2;
        }
    }

    //Ordena la lista de forma ascendente
    void OrdenarAsc() {
        int j, temp1;

        for (int i = 1; i < this->tamLista; i++) {
            temp1 = this->arreglo[i];
            j = i - 1;
            while (j >= 0 && this->arreglo[j] > temp1) {
                this->arreglo[j + 1] = this->arreglo[j];
                j -= 1;
            }
            this->arreglo[j + 1] = temp1;
        }
    }
};


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
    ListaArreglo<Key> *lista;
public:
    SetBasico(int tamanho = 100)  {
        this->lista = new ListaArreglo<Key>(tamanho);
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
        Key temp;
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor() == k){
                temp = this->lista->getValor();
                indice = this->lista->posicionActual();
            }
        }
        return indice;
    }
    bool encontrarbool(Key k){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            if(this->lista->getValor() == k){
                return true;
            }
        }
        return false;
    }

    //La inserción del valor k
    void insertar(Key k){
        if(!this->encontrarbool(k)){
            this->lista->agregar(k);
        }
    }

    //Retorna y remueve un registro arbitrario del set
    Key print(){
        for(this->lista->moverAInicio();this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente()){
            cout<<this->lista->getValor() <<endl;
        }
    }

    //Dada una clave, el registro correspondiente debe ser removido
    void remover(Key k){
        if(this->encontrarbool(k)){
            this->lista->moverAPosicion(this->encontrar(k));
            Key x=this->lista->eliminar();
        }
    }
    //Retorna y remueve un registro arbitrario del set
    Key removerCualquiera(){
        this->lista->moverAlFinal();
        this->lista->anterior();
        return this->lista->eliminar();
    }


};


int main(){
    int tamMax = 10;
    SetBasico<int> *conjunto = new SetBasico<int>(tamMax);
    conjunto->insertar(10);
    conjunto->insertar(10);
    conjunto->insertar(10);
    conjunto->insertar(12);
    conjunto->insertar(15);
    conjunto->insertar(18);
    conjunto->insertar(18);
    conjunto->print();
    cout<<endl<<"Removemos el valor 15"<<endl;
    conjunto->remover(15);
    conjunto->print();
    cout<<endl;

    cout<<conjunto->removerCualquiera()<<endl;
    cout<<conjunto->removerCualquiera()<<endl;
    cout<<conjunto->removerCualquiera()<<endl;



/*
    int i = 0, valor;
    while(i<=conjunto->longitud()){
        valor = conjunto->removerCualquiera();
        cout<<valor<<endl;
        i++;
    }
*/
    /*Reporta:
      18
      15
      12
      10
    */
    return 0;
}
