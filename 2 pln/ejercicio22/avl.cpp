//Nodo Arbol
template <typename E>
class Nodo
{
private:
    E e;
    Nodo *izq;
    Nodo *der;
    Nodo *pad;

public:
    int altura = 0;

    Nodo() {
        this->izq = this->der = NULL;
    }

    Nodo(E eval, Nodo *ival = NULL, Nodo *dval = NULL) {
        this->e = eval;
        this->izq = ival;
        this->der = dval;
        this->pad = NULL;
    }

    ~Nodo() {}

    E valor() {
        return e;
    };

    bool esHoja() {
        return this->izq == NULL && this->der == NULL;
    };

    void setPadre(Nodo *pval) {
        this->pad = pval;
    };

    void setValor(E eval)
    {
        this->e = eval;
    };

    Nodo *izquierda() {
        return this->izq;
    };

    void setIzquierda(Nodo *ival) {
        this->izq = ival;
    };

    Nodo *derecha() {
        return this->der;
    };

    void setDerecha(Nodo *dval) {
        this->der = dval;
    };

    Nodo *padre() {
        return this->pad;
    };    
};

template <typename E>
class AVL {
private:
    Nodo<KVPar<int, E> *> *raiz;
    int tam;

public:
    AVL() {
        this->raiz = NULL;
        this->tam = 0;
    }

    ~AVL() {
        delete raiz;
    }

    void actualizarAlturaNodo(Nodo<KVPar<int, E> *> *nodo) {
        if (nodo->izquierda() != NULL && nodo->derecha() != NULL)
            nodo->altura = 1 + max(nodo->izquierda()->altura, nodo->derecha()->altura);
        else if (nodo->izquierda() != NULL)
            nodo->altura = 1 + nodo->izquierda()->altura;
        else if (nodo->derecha() != NULL)
            nodo->altura = 1 + nodo->derecha()->altura;
        else
            nodo->altura = 0;
    }

    Nodo<KVPar<int, E> *>* actualizarAlturaArbol(Nodo<KVPar<int, E> *> *nodo) {
        Nodo<KVPar<int, E> *> *temp = nodo->padre();
        while (temp != NULL)
        {
            this->actualizarAlturaNodo(temp);
            temp = temp->padre();
        }
        return temp;
    }

    int calculardeltaAltura(Nodo<KVPar<int, E> *> *nodo) {
        if (nodo == NULL)
            return 0;
        else if (nodo->esHoja())
            return 0;
        else if (nodo->izquierda() == NULL)
            return (-1 - (nodo->derecha()->altura));
        else if (nodo->derecha() == NULL)
            return (nodo->izquierda()->altura + 1);
        else
            return (nodo->izquierda()->altura - nodo->derecha()->altura);
    }

    Nodo<KVPar<int, E> *> * rotarDerecha(Nodo<KVPar<int, E> *> *nodo) {
        Nodo<KVPar<int, E> *> *temp = nodo->izquierda();
        Nodo<KVPar<int, E> *> *pivot = temp->derecha();

        temp->setDerecha(nodo);
        nodo->setIzquierda(pivot);

        if (pivot != NULL)
            pivot->setPadre(nodo);
        nodo->setPadre(temp);

        this->actualizarAlturaNodo(nodo);
        this->actualizarAlturaNodo(temp);

        return temp;
    }

    Nodo<KVPar<int, E> *> * rotarIzquierda(Nodo<KVPar<int, E> *> *nodo) {
        Nodo<KVPar<int, E> *> *temp =  nodo->derecha();
        Nodo<KVPar<int, E> *> *pivot = temp->izquierda();

        temp->setIzquierda(nodo);
        nodo->setDerecha(pivot);
        if (pivot != NULL)
            pivot->setPadre(nodo);
        nodo->setPadre(temp);

        this->actualizarAlturaNodo(nodo);
        this->actualizarAlturaNodo(temp);

        return temp;
    }

    void balancearArbol(Nodo<KVPar<int, E> *> *nodo) {
        Nodo<KVPar<int, E> *> *temp, *tmp1, *tmp2, *tmp3, *tmp4;
        int deltaAltura;

        temp = nodo->padre();

        tmp1 = nodo->padre();
        tmp2 = nodo;
        tmp3 = NULL;

        while (tmp1 != NULL)
        {

            deltaAltura = this->calculardeltaAltura(tmp1);

            if ((deltaAltura > 1) || (deltaAltura < (-1)))
            {
                tmp4 = tmp1->padre();
                if (tmp1->izquierda() == tmp2 && tmp2->izquierda() == tmp3)
                    temp = this->rotarDerecha(tmp1);
                else if (tmp1->izquierda() == tmp2 && tmp2->derecha() == tmp3)
                {
                    temp = this->rotarIzquierda(tmp2);
                    temp->setPadre(tmp1);
                    tmp1->setIzquierda(temp);

                    temp = rotarDerecha(tmp1);
                } else if (tmp1->derecha() == tmp2 && tmp2->derecha() == tmp3)
                    temp = this->rotarIzquierda(tmp1);
                else {
                    temp = rotarDerecha(tmp2);
                    temp->setPadre(tmp1);
                    tmp1->setDerecha(temp);

                    temp = this->rotarIzquierda(tmp1);
                }
                if (tmp4 != NULL) {
                    temp->setPadre(tmp4);
                    if(tmp4->derecha() == tmp1)
                        tmp4->setDerecha(temp);
                    else
                        tmp4->setIzquierda(temp);
                } else {
                    this->raiz = temp;
                    temp->setPadre(NULL);
                }
                temp = this->actualizarAlturaArbol(temp);
            }
            tmp3 = tmp2;
            tmp2 = tmp1;
            tmp1 = tmp1->padre();
        }
    }

    void agregar(E e) {
        int key = this->tam;
        Nodo<KVPar<int, E> *> *nodo = new Nodo<KVPar<int, E> *>(new KVPar<int, E>(key, e));

        Nodo<KVPar<int, E> *> *temp = this->raiz;
        this->tam++;

        while (1) {
            if (temp == NULL) {
                this->raiz = nodo;
                return;
            }

            if (key > temp->valor()->key()) {
                if (temp->derecha() == NULL)
                {
                    nodo->setPadre(temp);
                    temp->setDerecha(nodo);
                    break;
                }
                else {
                    temp = temp->derecha();
                }
            }
            else if (key < temp->valor()->key()) {
                if (temp->izquierda() == NULL)
                {
                    nodo->setPadre(temp);
                    temp->setIzquierda(nodo);
                    break;
                }
                else
                {
                    temp = temp->izquierda();
                }
            }
            else
            {
                // Si el nodo entrante tiene el mismo valor
                // no hacemos nada
                this->tam--;
                return;
            }
        }

        // actualizar la altura del arbol
        this->actualizarAlturaArbol(nodo);

        // balancear el arbol
        this->balancearArbol(nodo);
    }

    int numNodos() {
        return this->tam;
    }
};