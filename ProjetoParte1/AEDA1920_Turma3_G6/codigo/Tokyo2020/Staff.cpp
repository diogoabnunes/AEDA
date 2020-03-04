#include "Staff.h"
using namespace std;

Staff::Staff(string n, Data nasc, int passp, string gen,
             Data cheg, Data part, string func, int cust) : Pessoa(n, nasc, passp, gen, cheg, part) {
    funcao = func;
    custo = cust;
}

string Staff::getFuncao() const {
    return funcao;
}
double Staff::getCusto() const {
    return custo;
}

void Staff::decompose(string s) {
    Pessoa::decompose(s);

    s = s.substr(s.find_first_of("-") +1);
    for (int i = 1; i <= 6; i++)
        s.erase(0, s.find_first_of("-") +1); // retira a substring de Pessoa

    funcao = trim(s);
    s.erase();

    if (funcao == "Treinador" || funcao == "Arbitro") custo += 500;
    else if (funcao == "Medico") custo += 800;
    else if (funcao == "Dirigente") custo += 750;
    else if (funcao == "Presidente") custo += 1000;
    else if (funcao == "Fisioterapeuta") custo += 700;
    else if (funcao == "Enfermeiro") custo += 600;
    else custo += 400;
}

void Staff::show() const {
    Pessoa::show();
    cout << "Funcao: " << getFuncao() << endl;
    cout << "Custo diario: " << getCusto() << endl;
}

string Staff::getTipo() const {
    return Pessoa::getTipo()+"Staff";
}

void Staff::setFuncao(string f) { funcao = f; }