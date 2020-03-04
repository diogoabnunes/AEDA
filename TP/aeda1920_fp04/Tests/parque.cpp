#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

bool InfoCartao::operator == (const InfoCartao &ic1) const
{
    if (nome==ic1.nome) return true;
    return false;
}

bool InfoCartao::operator < (const InfoCartao &ic1) const
{
    if (frequencia > ic1.frequencia)
        return true;
    else if (frequencia < ic1.frequencia)
        return false;
    else
        return (nome<ic1.nome);
}

bool compNome(const InfoCartao &c1, const InfoCartao &c2)
{
    return c1.nome < c2.nome;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a implementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    InfoCartao info;
    info.nome = nome;
    return sequentialSearch(clientes, info);
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if (pos == -1) throw ClienteNaoExistente(nome);
    return clientes[pos].frequencia;
}

// a alterar/atualizar ? Sim (frequencia = 0)
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ? Não
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ? Sim (frequencia++)
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

// a alterar/atualizar ? Não
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort(clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    sort(clientes.begin(), clientes.end(), compNome);
}


// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;
    for (unsigned int i=0; i<clientes.size(); i++)
    {
        if (clientes[i].frequencia < n1)
            break;
        if (clientes[i].frequencia <= n2)
            nomes.push_back(clientes[i].nome);
    }
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    for (int i = 0; i != pe.clientes.size(); i++)
    {
        os << "Nome: " << pe.clientes[i].nome;
        if (pe.clientes[i].presente == true) os << " (esta presente)" ;
        os << " ; frequencia = " << pe.clientes[i].frequencia << endl;
    }
    return os;
}


// a implementar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    if (p >= clientes.size()) throw PosicaoNaoExistente(p);
    return clientes[p];
}
