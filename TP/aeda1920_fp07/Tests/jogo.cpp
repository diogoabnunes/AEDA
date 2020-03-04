#include "jogo.h"
#include <sstream>

ostream &operator << (ostream &os, Circulo &c1)
{
    string estado = "";
    if (c1.estado) estado = "true";
    else estado = "false";
	os << c1.pontuacao << "-" << estado << "-" << c1.nVisitas << endl;
    return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados)
{
    Circulo c1(pontos[pos], estados[pos]);
    if (niv == 0) return BinaryTree<Circulo> (c1);

    BinaryTree<Circulo> filhoE = iniciaJogo(2*pos + 1, niv - 1, pontos, estados);
    BinaryTree<Circulo> filhoD = iniciaJogo(2*pos + 2, niv - 1, pontos, estados);
    return BinaryTree<Circulo> (c1, filhoE, filhoD);
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = iniciaJogo(0, niv, pontos, estados);
}

string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);
	stringstream ss;
	while (!it.isAtEnd())
    {
	    ss << it.retrieve();
	    it.advance();
    }
	return ss.str();
}

//a alterar
int Jogo::jogada()
{
	int pos = 1, pontos = -1;
	BTItrLevel<Circulo> it(jogo);

    if (it.isAtEnd()) return pontos;
    while (true)
    {
        int n;
        if (!it.retrieve().getEstado()) n = pos;
        else n = pos + 1;

        it.retrieve().mudaEstado();
        it.retrieve().incNVisitas();
        pontos = it.retrieve().getPontuacao();

        int i = 0;
        while (i < n && !it.isAtEnd())
        {
            it.advance();
            i++;
        }

        if (!it.isAtEnd()) pos += n;
        else break;
    }
    return pontos;
}

int Jogo::maisVisitado()
{
    int maisV = -1;
    BTItrLevel<Circulo> it(jogo);
    if (it.isAtEnd()) return maisV;
    it.advance();
    while (!it.isAtEnd())
    {
        if (it.retrieve().getNVisitas() > maisV)
            maisV = it.retrieve().getNVisitas();
        it.advance();
    }
	return maisV;
}

