#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
    return this->palavra < ps1.palavra;
}

bool PalavraSignificado::operator==(const PalavraSignificado &ps1) const {
    return this->palavra == ps1.palavra;
}

void Dicionario::lerDicionario(ifstream &fich)
{
    string pal, sig;
    while (!fich.eof())
    {
        getline(fich, pal);
        getline(fich, sig);
        PalavraSignificado p(pal, sig);
        palavras.insert(p);
    }
}

string Dicionario::consulta(string palavra) const
{
    PalavraSignificado p(palavra, "");
    PalavraSignificado px = palavras.find(p);
    PalavraSignificado notFound("","");
    if (px == notFound)
    {
        BSTItrIn<PalavraSignificado> it(palavras);

        string palA = "", sigA = "";
        while (!it.isAtEnd() && it.retrieve()<p)
        {
            palA =it.retrieve().getPalavra();
            sigA = it.retrieve().getSignificado();
            it.advance();
        }

        string palD = "", sigD = "";
        if (!it.isAtEnd())
        {
            palD = it.retrieve().getPalavra();
            sigD = it.retrieve().getSignificado();
        }
        throw PalavraNaoExiste(palA, sigA, palD, sigD);
    }
    else return px.getSignificado();
}

bool Dicionario::corrige(string palavra, string significado)
{
    PalavraSignificado p(palavra, "");
    PalavraSignificado px = palavras.find(p);
    PalavraSignificado notFound("","");
    if (px == notFound)
    {
        p.setSignificado(significado);
        palavras.insert(p);
        return false;
    }
    else
    {
        palavras.remove(p);
        p.setSignificado(significado);
        palavras.insert(p);
        return true;
    }
}

void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while (!it.isAtEnd())
    {
        cout << it.retrieve().getPalavra() << endl << it.retrieve().getSignificado() << endl;
        it.advance();
    }
}

