#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

Cliente::Cliente() {
    numPresentes = rand() % 5 + 1;
}

int Cliente::getNumPresentes() const {
    return numPresentes;
}

Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual = 0;
    prox_chegada = rand() % 20 + 1;
    prox_saida = 0;
    clientes_atendidos = 0;
}

void Balcao:: proximoEvento()
{
    chegada();
    saida();
}

void Balcao::chegada()
{
    Cliente *c = new Cliente;
    clientes.push(*c);
    prox_chegada = rand() % 20 + 1;
    prox_saida += tempo_atual + (*c).getNumPresentes()*tempo_embrulho;
    cout << "Tempo atual: " << tempo_atual <<
    "\nNovo cliente tem " << (*c).getNumPresentes() << " presentes." <<
    "\nProxima Chegada: " << prox_chegada << "\nProxima Saida: " << prox_saida << endl;
    cout << "##########" << endl;
}

void Balcao::saida()
{
    Cliente *exit = new Cliente;
    *exit = getProxCliente();
    prox_saida -= (*exit).getNumPresentes()*tempo_embrulho;
    clientes.pop();
    cout << "Tempo atual: " << tempo_atual <<
         "\nNovo cliente tem " << (*exit).getNumPresentes() << " presentes." <<
         "\nProxima Chegada: " << prox_chegada << "\nProxima Saida: " << prox_saida << endl;
    cout << "##########" << endl;
    clientes_atendidos+=1;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

ostream & operator << (ostream & out, const Balcao & b1)
{
    out << "Numero de clientes atendidos: " << b1.clientes_atendidos <<
    "\nNumero de clientes em espera: " << b1.clientes_atendidos << endl;
    return out;
}

int Balcao::getTempoEmbrulho() const { return tempo_embrulho; }

int Balcao::getProxSaida() const { return prox_saida; }

int Balcao::getClientesAtendidos() const { return clientes_atendidos; }

Cliente & Balcao::getProxCliente() {
    Cliente *c = new Cliente();
    if (clientes.empty())
        throw FilaVazia();
    *c = clientes.front();
    return *c;
}

      
