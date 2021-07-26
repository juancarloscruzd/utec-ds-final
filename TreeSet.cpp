//
// Created by VICTOR HERRERA on 2021-06-29.
//
#include <iostream>

using namespace std;

template <class T>
class BinarySearchTree {
private:
    class Node {
    public:
        T key;
        int size = 1;
        Node *left, *right;

        Node(T key):
                key(key), left(nullptr), right(nullptr) {}

        Node(T key, Node *l, Node *r):
                key(key), left(l), right(r) {}
    };

    Node* root = nullptr;
    int counter = 0;

    void print_in_o(Node *node) {
        if (node == nullptr)
            return;
        print_in_o(node->left);
        cout << node->key << endl;
        print_in_o(node->right);
    }

    T kth_element(Node *node, int k) {
        int lftSz = node->left ? node->left->size : 0;

        if (lftSz >= k)
            return kth_element(node->left, k);

        if (lftSz == k - 1)
            return node->key;

        return kth_element(node->right, k - lftSz - 1);
    }

    Node* insert(Node *node, T x) {
        if (node == nullptr) {
            return new Node(x);
        }
        node->size++;

        if (x < node->key) {
            node->left = insert(node->left, x);
        }
        else if (x > node->key) {
            node->right = insert(node->right, x);
        }

        return node;
    }

    bool search(Node *node, T x) {
        if (node == nullptr) {
            return false;
        }

        if (x < node->key) {
            return search(node->left, x);
        }
        else if (x > node->key) {
            return	search(node->right, x);
        }

        return true;
    }

    T successor(Node *node) {
        if (node->left)
            return successor(node->left);
        return node->key;
    }

    void erase(Node *&node, T x) {
        node->size--;

        if (x < node->key) {
            return erase(node->left, x);
        }
        else if (x > node->key) {
            return erase(node->right, x);
        }

        if (node->left && node->right) {
            T succ = successor(node->right);
            node->key = succ;
            return erase(node->right, succ);
        }
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
            return;
        }

        Node* toDel = node;
        node = node->left ? node->left : node->right;
        delete toDel;
    }

public:
    BinarySearchTree() = default;

    ~BinarySearchTree(){}

    void print_in_o() {
        if (root) {
            print_in_o(root);
        }
        cout << endl;
    }

    T kth_element(int k) {
        return kth_element(root, k);
    }

    void insert(T x) {
        if (!search(root, x))
            root = insert(root, x);
    }

    bool search(T x) {
        return search(root, x);
    }

    void erase(T x) {
        if (search(root, x))
            erase(root, x);
    }

    void limpiar(){
        delete root;
    }
    int longitug(){
        return this->root->size;
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
class TreeSet : public Set<Key> {
private:
    BinarySearchTree<Key> *ArbolBST = new BinarySearchTree<Key>;
public:
    TreeSet() {
        //this->lista = new ListaArreglo<Key>(tamanho);
    }

    ~TreeSet() {
        delete ArbolBST;
    }

    // Complejidad O(1)
    void limpiar() {
        this->ArbolBST->limpiar();
    }
    void print(){
        this->ArbolBST->print_in_o();
    }

    //La inserción del valor k. // Complejidad O(lgn)
    void insertar(Key k){
        this->ArbolBST->insert(k);
    }
    int longitud(){
        return this->ArbolBST->longitug();
    }
    //Dada una clave, el registro correspondiente debe ser removido // Complejidad O(lgn)
    void remover(Key k){
        this->ArbolBST->erase(k);
    }
    //Retorna y remueve un registro arbitrario del set. En este caso el último valor. // Complejidad O(lgn)
    Key removerCualquiera(){
        Key temp = this->ArbolBST->kth_element(ArbolBST->longitug());
        this->ArbolBST->erase(temp);
        return temp;
    }
    //Reportar Key en ubicación. OK // Complejidad O(lgn)
    Key k_valor(int l){
        return this->ArbolBST->kth_element(l);
    }

    //Retorna una posición del registro que se asocie con k. // Complejidad O(lgn)
    int encontrar(Key k){
        for (int i=1;i<=this->ArbolBST->longitug();i++){
            if(this->ArbolBST->kth_element(i) == k){
                return i;
            }
        }
        return NULL;
    }
};

int main() {

    TreeSet<int> *NuevoSet = new TreeSet<int>;

    NuevoSet->insertar(10);
    NuevoSet->insertar(10);
    NuevoSet->insertar(10);
    NuevoSet->insertar(12);
    NuevoSet->insertar(15);
    NuevoSet->insertar(18);
    NuevoSet->insertar(18);
    NuevoSet->insertar(19);
    NuevoSet->insertar(5);
    NuevoSet->insertar(8);

    cout<<"Print del Set: "<<endl;
    NuevoSet->print();
    cout<<"Removemos el valor 15"<<endl;
    NuevoSet->remover(15);
    NuevoSet->print();
    cout<<"Buscamos el valor 12: "<<NuevoSet->encontrar(12)<<endl;
    cout<<endl;
    cout<<"Removemos los 3 ultimos elementos:"<<endl;
    cout<<NuevoSet->removerCualquiera()<<endl;
    cout<<NuevoSet->removerCualquiera()<<endl;
    cout<<NuevoSet->removerCualquiera()<<endl;

    cout<<"Nueva longitud del Set: "<<NuevoSet->longitud()<<endl;
    cout<<"Nuevo print del Set: "<<endl;
    NuevoSet->print();

    return 0;
}
