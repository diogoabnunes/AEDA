#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

// excecao ArestaRepetida
template <class N>
class ArestaRepetida
{
public:
    N info1, info2;
    ArestaRepetida(N inf1, N inf2) { info1=inf1; info2=inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &a)
{ out << "Aresta repetida: " << a.info1 << " , " << a.info2 ; return out; }

///////////////////////////////////////////////////////////////////////////////////////////

template <class N, class A>
Grafo<N,A>::Grafo() {}

template <class N, class A>
Grafo<N,A>::~Grafo() {
    //typename vector< No<N,A> *>::const_iterator it;
    for (auto it=nos.begin(); it!=nos.end(); it++)
        delete *it;
}

template <class N, class A>
int Grafo<N,A>::numNos() const {
    return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas() const {
    int narestas = 0;
    for (auto it = nos.begin(); it != nos.end(); it++)
        narestas += (*it)->arestas.size();
    return narestas;
}

template<class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirNo(const N &inf) {
    typename vector< No<N,A> *>::const_iterator it;
    // Verifica se o no ja existe e lanca excecao
    for (it = nos.begin(); it != nos.end(); it++) {
        if ((*it)->info == inf) throw NoRepetido<N>(inf);
    }
    No<N,A> *no1 = new No<N,A>(inf);
    nos.push_back(no1);
    return *this;
}

template<class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {

    // Percorrer o vetor de nos ate encontrar o No em que info = inicio
    typename vector< No<N,A> *>::iterator it;
    typename vector< Aresta<N,A> >::iterator ita;
    bool encontrouInicio = false;
    bool encontrouFim = false;

    No<N,A> *noInicio_apt=NULL;
    No<N,A> *noFim_apt=NULL;

    for (it = nos.begin(); it != nos.end(); it++)
    {
        // procura no vetor de nos o no em que info == inicio
        if ( (*it)->info == inicio )
        {
            // verificar se o vetor de arestas ja tem uma aresta para destino = fim
            encontrouInicio = true;
            noInicio_apt=*it;
            for (ita = (*it)->arestas.begin();  ita != (*it)->arestas.end(); ita++)
            {
                // lanca a excecao se for repetida
                if ( ita->destino->info == fim) throw ArestaRepetida<N> (inicio, fim);
            }
            if (encontrouFim==true) break;
        }
        else if ( (*it)->info == fim ) {
            encontrouFim=true;
            noFim_apt=*it;
            if (encontrouInicio==true) break;
        }
    }

    // se nao encontrar um dos nos, lanca excecao tipo NoInexistente
    if (!encontrouInicio) throw NoInexistente<N>(inicio);
    if (!encontrouFim) throw NoInexistente<N>(fim);

    // cria uma nova Aresta
    Aresta<N,A> aresta1(noFim_apt, val);
    // insere o objecto no vector de arestas do no
    noInicio_apt->arestas.push_back(aresta1);

    return *this;
}

