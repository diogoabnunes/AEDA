#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	tabHInt::const_iterator it = numeros.find(num);
    return (it != numeros.end());
}

void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    numeros.clear();
    unsigned int nVal = 0, i = 0;
    while (nVal < n)
    {
        pair<tabHInt::iterator,bool> res = numeros.insert(valores[i]);
        if (res.second) nVal++;
        i++;
    }
}

unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned certos = 0;
    for (tabHInt::const_iterator it = sorteio.begin(); it != sorteio.end(); it++)
        if (contem(*it)) certos++;
    return certos;
}

unsigned Aposta::somaNumeros() const {
    unsigned soma = 0;
    for (tabHInt::const_iterator it = numeros.begin(); it != numeros.end(); it++)
        soma += *it;
    return soma;
}

unsigned Aposta::tamanho() const {
    return numeros.size();
}