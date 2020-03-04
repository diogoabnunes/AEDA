/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

Jogo::Jogo()
{
}

Jogo::Jogo(list<Crianca>& lc2)
{
}

void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
    return criancas;
}

string Jogo::escreve() const
{
    string res;
    for (auto it = criancas.begin(); it != criancas.end(); it ++)
    {
        res += (*it).escreve() + "\n";
    }
    return res;
}

Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c = new Crianca;
    unsigned int count = numPalavras(frase), i = 0;
    list<Crianca> l = getCriancasJogo();
    while (l.size() != 1)
    {
        for (auto it = l.begin(); it != l.end(); it++) {
            if (l.size() == 1) break;
            i++;
            if (i == count) {
                l.erase(it);
                i = 0;
            }
        }
    }
    *c = l.front();
    return *c;
}

list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    for (list<Crianca>::const_iterator it = criancas.begin(); it != criancas.end(); it++)
    {
        if ((*it).getIdade() > id)
        {
            res.push_back(*it);
            criancas.erase(it);
            it--;
        }
    }
    return res;
}
/*Esta função remove do jogo as crianças de idade superior ao valor id especificado como parâmetro, e retorna
uma nova lista com as crianças que foram removidas.*/

void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas = l1;
}

bool Jogo::operator==(Jogo& j2)
{
    return criancas == j2.getCriancasJogo();
}

list<Crianca> Jogo::baralha() const
{
    list<Crianca> res, alterada = criancas;
    int num, counter;
    while (alterada.size() != 0)
    {
        num = rand() % alterada.size();
        for (auto it2 = alterada.begin(); it2 != alterada.end(); it2++)
        {
            if (counter == num)
            {
                res.push_back(*it2);
                alterada.erase(it2);
                break;
            }
            else counter++;
        }
        counter = 0;
    }
    return res;
}
