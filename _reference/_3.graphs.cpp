//
// Created by VICTOR HERRERA on 2021-07-14.
//
#include <iostream>
#include <utility>
#include <queue>
#include <set>

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

//Implementacion usando representacion de matriz de adyacencia
class GrafoMA : public Grafo{
private:
    int numeroVertices;
    int numeroAristas;
    int **matriz;
    int **matrizw;
    int *marca;

    ListaArreglo<bool> *visitado = new ListaArreglo<bool>;

    ListaArreglo<ListaArreglo<int>*> *ListaAdjacencias = new ListaArreglo<ListaArreglo<int>*>;
    //SetBasico<pair<int,int>> *Aristas = new SetBasico<pair<int,int>>;

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
        //Inicializar la matriz de adyacencia
        this->matriz = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matriz[i] = new int[this->numeroVertices];
        }
        //Debemos colocar a la matriz adyacencia con valores CERO
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matriz[i][j] = 0; //Peso CERO
            }
        }
        //Inicializar la matriz de pesos(w)
        this->matrizw = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matrizw[i] = new int[this->numeroVertices];
        }
        //Completar con un valor la matriz de pesos(w).Valor muy negativo.
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matrizw[i][j] = -1000; //Peso CERO
            }
        }
        //Colocando en false la matriz visitado
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

    //Agregar elementos en la lista de Adyacencias FAILED
    void AgregarArista(int i, int j){
        cout<<"ok"<<endl;

        if(ListaAdjacencias->getValorEnPosicion(i)->longitud()==0){
            ListaArreglo<int> *Adjacencias = new ListaArreglo<int>;
            Adjacencias->agregar(j);
            ListaAdjacencias->setValorEnPosicion(i, Adjacencias);
            //delete[] Adjacencias;
        }else{
            ListaArreglo<int> *Adjacencias = new ListaArreglo<int>;
            Adjacencias = ListaAdjacencias->getValorEnPosicion(i);
            Adjacencias->agregar(j);
            ListaAdjacencias->setValorEnPosicion(i, Adjacencias);
        }
        /*

        if(true) {
            ListaArreglo<int> *Adjacencias;
            Adjacencias = ListaAdjacencias->getValorEnPosicion(i);
            Adjacencias->agregar(j);
            ListaAdjacencias->setValorEnPosicion(i, Adjacencias);
            Adjacencias = ListaAdjacencias->getValorEnPosicion(j);
            Adjacencias->agregar(i);
            ListaAdjacencias->setValorEnPosicion(j, Adjacencias);
        }
         */
    }

    //Retornar el numero de vertices y aristas
    int get_N_Vertices(){
        return this->numeroVertices;
    }

    int get_N_Aristas(){
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

    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    void setArista(int i, int j, int w) {
        this->matriz[i][j] = 1;
        this->matrizw[i][j] = w;
    }

    //Eliminar arista
    void eliminarArista(int i, int j) {
        this->matriz[i][j] = 0;
        this->matrizw[i][j] = -1000;
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
    void funcion_adyacencia(int v,ListaArreglo<int> **vector){
        ListaArreglo<int> *result = new ListaArreglo<int>;
        //cout<<vector;
        for (int i = 0; i < this->numeroVertices; ++i) {
            result->agregar(matriz[v][i]);
        }
        *vector = result;
    }

    //Recorrer el grafo con el metodo Depth-first search
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

    //Recorrer el Grafo con el metodo Breadth-first search
    void RecorridoBFS(int v){
        // Esta lista se puede entender tambien como si fue Visitado el vértice.
        ListaArreglo<int> *distancia = new ListaArreglo<int>;
        for (int i = 0; i < this->numeroVertices; i++) {
            distancia->setValorEnPosicion(i,-1);
        }
        ACola<int> *q1 = new ACola<int>();
        q1->encolar(v);
        distancia->setValorEnPosicion(v,0);

        while(q1->longitud() != 0){
            int u = q1->desencolar();
            cout<<u<<" "; // Mostrar los vertices
            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[u][i]!=0){
                    if(distancia->getValorEnPosicion(i)== -1){ //El -1 puede actuar como un check de No-Visitado.
                        distancia->setValorEnPosicion(i,distancia->getValorEnPosicion(u) + 1);
                        q1->encolar(i);
                    }
                }
            }
        }
        cout << endl;
        //Para mostrar la distancia en aristas hasta todos los otros vertices.
        /*
        for (int i = 0; i < this->numeroVertices; i++) {
            cout << distancia->getValorEnPosicion(i) << ' ';
        }
        */
        cout << endl;
        delete distancia;
    }

    //Devuelve el numero de saltos (aristas) desde el vertice v1 hasta el vertice v2.
    int NumSaltos(int v1, int v2){
        ListaArreglo<int> *distancia = new ListaArreglo<int>;
        for (int i = 0; i < this->numeroVertices; i++) {
            distancia->setValorEnPosicion(i,-1);
        }
        queue<int> q;
        q.push(v1);
        distancia->setValorEnPosicion(v1,0);

        while(!q.empty()){
            int u = q.front();
            q.pop();
            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[u][i]!=0){
                    if(distancia->getValorEnPosicion(i)== -1){
                        distancia->setValorEnPosicion(i,distancia->getValorEnPosicion(u) + 1);
                        q.push(i);
                    }
                }
            }
        }
        return distancia->getValorEnPosicion(v2);
    }

    int Prim(){
        //Colocando en false la matriz visitado
        for (int i = 0; i < this->numeroVertices; i++) {
            this->visitado->setValorEnPosicion(i,false);
        }
        set<pair<int, int>> pq;
        pq.insert({0, 0}); //Primer costo y primer Vertice.

        int mst = 0;
        while (!pq.empty()) {
            auto [w, v] = *pq.begin();
            pq.erase(pq.begin());
            if (this->visitado->getValorEnPosicion(v))
                continue;
            mst += w;
            cout<<v<<" ";
            this->visitado->setValorEnPosicion(v,true);
            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[v][i]!=0){
                    int u = i;
                    int w = this->matrizw[v][i];
                    pq.insert({w,u});
                }
            }
        }
        cout<<endl;
        return mst;
    }

    void Dijkstra(int s, ListaArreglo<int> **x){
        set<pair<int, int>> pq;

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
        pq.insert({0, s});

        while (!pq.empty()) {
            auto[d, v] = *pq.begin();
            pq.erase(pq.begin());

            if (d != distancia->getValorEnPosicion(v))
                continue;

            for (int i = 0; i < this->numeroVertices; ++i) {
                if(matriz[v][i]!=0){
                    int u = i;
                    int w = this->matrizw[v][i];
                    //cout<<u<<" - "<<w<<endl;
                    if(distancia->getValorEnPosicion(v) + w < distancia->getValorEnPosicion(u)){
                        path->setValorEnPosicion(u,v);
                        distancia->setValorEnPosicion(u,distancia->getValorEnPosicion(v) + w);
                        pq.insert({distancia->getValorEnPosicion(u), u});
                    }
                }
            }
        }
        *x = distancia;
    }
};

int main() {

    GrafoMA *grafo = new GrafoMA(6);
    ListaArreglo<int> *fadyacencia = new ListaArreglo<int>;
    ListaArreglo<int> *t = new ListaArreglo<int>;

    grafo->setArista(0,1, 11);
    grafo->setArista(0,3, 12);
    grafo->setArista(1,0, 11);
    grafo->setArista(1,4, 12);
    grafo->setArista(1,2, 10);
    grafo->setArista(1,3, 6);
    grafo->setArista(2,1, 10);
    grafo->setArista(2,3, 14);
    grafo->setArista(3,0, 12);
    grafo->setArista(3,1, 6);
    grafo->setArista(3,2, 14);
    grafo->setArista(3,5, 7);
    grafo->setArista(4,1, 12);
    grafo->setArista(5,3, 7);

    //grafo->RecorridoDFS(1);
    //cout<<endl;
    //grafo->RecorridoBFS(1);
    //cout<<grafo->Prim()<<endl;

    grafo->Dijkstra(5,&t);
    for(int j=0;j<t->longitud();j++) {
        cout << t->getValorEnPosicion(j) << " ";
    }
    
    //grafo->funcion_adyacencia(3,&fadyacencia);

    //for(int j=0;j<fadyacencia->longitud();j++) {
    //    cout << fadyacencia->getValorEnPosicion(j) << " ";
    //}

    delete grafo;

    return 0;
}

