#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
    return veiculos.size();
}

int Frota::menorAno() const {
    if (veiculos.size() == 0) return 0;
    int menorA = 99999;
    for (int i = 0; i < veiculos.size(); i++)
    {
        if (veiculos[i]->getAno() < menorA) menorA = veiculos[i]->getAno();
    }
    return menorA;
}

ostream &operator<<(ostream &o, const Frota &f) {
    for (auto it = f.veiculos.begin(); it != f.veiculos.end(); it++)
    {
        (*it)->info();
    }
    return o;
}

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo*> vAno;
    for (auto it = veiculos.begin(); it != veiculos.end(); it++)
    {
        if ((*it)->getAno() == anoM) vAno.push_back((*it));
    }
    return vAno;
}

float Frota::totalImposto() const {
    float total = 0;
    for (auto it = veiculos.begin(); it != veiculos.end(); it ++)
    {
        total += (*it)->calcImposto();
    }
    return total;
}
