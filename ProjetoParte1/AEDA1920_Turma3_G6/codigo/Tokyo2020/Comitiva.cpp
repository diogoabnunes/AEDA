#include "Comitiva.h"

Comitiva::Comitiva(string comit) {
    ifstream file;
    file.open( comit + ".txt");

    string line;
    if (file.is_open())
    {
        while (! file.eof())
        {
            getline(file, line);
            if (line[0] == 'A') {
                Pessoa *a = new Atleta;
                a->decompose(line);
                pessoas.push_back(a);
            }
            else if (line[0] == 'S') {
                Pessoa *b = new Staff;
                b->decompose(line);
                pessoas.push_back(b);
            }
        }
        file.close();
        line.erase();
        cout << "'portugal.txt' lido com sucesso!\n";
    }
    else cout << "'portugal.txt' nao encontrado...\n";
};

vector<Pessoa*> Comitiva::getComitiva() const {
    return pessoas;
}

double Comitiva::getCustoDiario() const {
    double custoTotal = 0;
    for (auto it = pessoas.begin(); it < pessoas.end(); it++)
    {
        custoTotal += (*it)->getCusto();
    }
    cout << "Custo diario total da comitiva: " << custoTotal << " euros" << endl;
    return custoTotal;
}

void Comitiva::showComitiva() const {

    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
    }
    cout << "####################" << endl;
}

void Comitiva::showPessoa(Pessoa *p) {
    (*p).show();
}

void Comitiva::addAtleta() {
    int d, m, a;
    int aux = 0;
    string aux_str;

    string nome, genero, modalidade;
    Data nascimento, chegada, partida;
    int passaporte, ranking;
    double peso, altura;
    vector<string> competicoes;

    clearInput();

    cout << "Nome: ";
    getline(cin, nome);
    if (nome == "") throw StringVazia();

    cout << "Nascimento: " << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    nascimento = Data(d, m, a);

    cout << "Passaporte: ";
    if (!(cin >> passaporte)) throw TipoInvalido();
    for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
        if (passaporte == (*it)->getPassaporte()) throw PassaporteJaExistente();
    }

    cout << "Genero: \n[1] Feminino\n[2] Masculino\n";
    if (!(cin >> aux)) throw TipoInvalido();
    if (aux != 1 && aux != 2) throw NumeroInvalido();
    else if (aux == 1) genero = "F";
    else if (aux == 2) genero = "M";

    cout << "Chegada a Toquio:" << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    chegada = Data(d, m, a);

    cout << "Partida de Toquio:" << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    partida = Data(d, m, a);

    if (!(chegada < partida)) throw DataChegadaPartida();

    clearInput();
    cout << "Modalidade: ";
    getline(cin, modalidade);
    if (modalidade == "") throw StringVazia();

    cout << "Peso: ";
    if (!(cin >> peso)) throw TipoInvalido();

    cout << "Altura: ";
    if (!(cin >> altura)) throw TipoInvalido();

    cout << "Ranking: ";
    if (!(cin >> ranking)) throw TipoInvalido();

    clearInput();
    cout << "Competicoes (se mais que uma, separe-as por virgula): ";
    getline(cin, aux_str);
    if (aux_str == "") throw StringVazia();

    competicoes = string_to_vector(aux_str);

    Pessoa *adding = new Atleta(nome, nascimento, passaporte, genero, chegada, partida,
                                modalidade, peso, altura, ranking, competicoes);

    int checking;
    bool checkinfo = false;
    adding->show();
    do {
        try {
            cout << "Confirma a informacao? \n[1] Sim (Adicionar)\n[2] Nao (Ignorar)\n";
            if (!(cin >> checking)) { clearInput(); throw TipoInvalido(); }
            if (checking != 1 && checking != 2) throw NumeroInvalido();
            checkinfo = true;
            break;
        }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
    } while (!checkinfo);

    if (checking == 1) { pessoas.push_back(adding); cout << "Atleta adicionado!" << endl; }
}

void Comitiva::addStaff() {
    int d, m, a;
    int aux = 0, func, custo;
    string aux_str;

    string nome, genero, funcao;
    Data nascimento, chegada, partida;
    int passaporte;

    clearInput();

    cout << "Nome: ";
    getline(cin, nome);
    if (nome == "") throw StringVazia();

    cout << "Nascimento: " << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    nascimento = Data(d, m, a);

    cout << "Passaporte: ";
    if (!(cin >> passaporte)) throw TipoInvalido();
    for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
        if (passaporte == (*it)->getPassaporte()) throw PassaporteJaExistente();
    }

    cout << "Genero: \n[1] Feminino\n[2] Masculino\n";
    if (!(cin >> aux)) throw TipoInvalido();
    if (aux != 1 && aux != 2) throw NumeroInvalido();
    else if (aux == 1) genero = "F";
    else if (aux == 2) genero = "M";

    cout << "Chegada a Toquio:" << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    chegada = Data(d, m, a);

    cout << "Partida de Toquio:" << endl;
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    partida = Data(d, m, a);

    if (!(chegada < partida)) throw DataChegadaPartida();

    clearInput();
    cout << "Funcao: \n[1] Treinador\n[2] Arbitro\n[3] Medico\n"
            "[4] Dirigente\n[5] Enfermeiro\n[6] Presidente\n[7] Outro\n";
    if (!(cin >> func)) throw TipoInvalido();
    if (func != 1 && func != 2 && func != 3 && func != 4 && func != 5 && func != 6 && func != 7) throw NumeroInvalido();

    if (func == 1) { funcao = "Treinador"; custo = 500; }
    else if (func == 2) { funcao = "Arbitro"; custo = 500; }
    else if (func == 3) { funcao = "Medico"; custo = 800; }
    else if (func == 4) { funcao = "Dirigente"; custo = 750; }
    else if (func == 5) { funcao = "Enfermeiro"; custo = 600; }
    else if (func == 6) { funcao = "Presidente"; custo = 1000; }
    else { funcao = "Outro"; custo = 400; }

    Pessoa *adding = new Staff(nome, nascimento, passaporte, genero, chegada, partida, funcao, custo);

    clearInput();
    int checking;
    bool checkinfo = false;
    adding->show();
    do {
        try {
            cout << "Confirma a informacao? \n[1] Sim (Adicionar)\n[2] Nao (Ignorar)\n";
            if (!(cin >> checking)) { clearInput(); throw TipoInvalido(); }
            if (checking != 1 && checking != 2) throw NumeroInvalido();
            checkinfo = true;
            break;
        }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
    } while (!checkinfo);

    if (checking == 1) { pessoas.push_back(adding); cout << "Staff adicionado!" << endl; }
}

void Comitiva::addPessoa() {
    int tipo = 0;
    do {
        try {
            while (true) {
                cout << "Adicionar:\n[1] Atleta\n[2] Staff\n[0] Voltar\n";
                try {
                    if (!(cin >> tipo)) {
                        clearInput();
                        throw TipoInvalido();
                    }
                    break;
                }
                catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
            }
            switch (tipo) {
                case 1: addAtleta(); break;
                case 2: addStaff(); break;
                case 0: break;
                default: throw NumeroInvalido();
            }
        }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (StringVazia &msg) { cout << msg.getMSG() << endl; }
        catch (DiaInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (MesInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (AnoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (DataInvalida &msg) { cout << msg.getMSG() << endl; }
        catch (DataChegadaPartida &msg) { cout << msg.getMSG() << endl; }
        catch (PassaporteJaExistente &msg) { cout << msg.getMSG() << endl; }

    } while(tipo != 1 && tipo != 2 && tipo != 0);
}

void Comitiva::editPessoa() {
    Pessoa *p;
    unsigned int option = 0;
    int editing;
    bool found = false;

    clearInput();
    do {
        try {
            cout << "Passaporte da pessoa a editar (0 para sair): ";
            if (!(cin >> editing)) throw TipoInvalido();
            if (editing == 0) break;

            for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
                if ((*it)->getPassaporte() == editing) {
                    p = *it;
                    found = true;
                    cout << "Pessoa encontrada!" << endl;
                }
            }

            if (found) {
                do {
                    cout << "O que deseja editar?" << endl;
                    cout << "[1] Nome" << endl;
                    cout << "[2] Nascimento" << endl;
                    cout << "[3] Passaporte" << endl;
                    cout << "[4] Genero" << endl;
                    cout << "[5] Chegada a Toquio" << endl;
                    cout << "[6] Partida de Toquio" << endl;
                    cout << "[7] Modalidade, Peso, Altura, Ranking ou Competicoes (Atleta)" << endl;
                    cout << "[8] Funcao (Staff)" << endl;
                    cout << "[0] Voltar" << endl;
                    if (!(cin >> option)) throw TipoInvalido();
                    if (option >= 9) throw NumeroInvalido();

                    switch (option) {
                        case 1: {
                            clearInput();
                            string novoNome;
                            cout << "Novo nome: ";
                            getline(cin, novoNome);
                            if (novoNome == "") throw StringVazia();
                            p->setNome(novoNome);
                            cout << "Nome alterado com sucesso!\n";
                            break;
                        }
                        case 2: {
                            int d, m, a;
                            cout << "Nascimento: " << endl;
                            cout << "Dia: ";
                            if (!(cin >> d)) throw TipoInvalido();
                            if (d < 0 || d > 31) throw DiaInvalido();
                            cout << "Mes: ";
                            if (!(cin >> m)) throw TipoInvalido();
                            if (m < 0 || m > 12) throw MesInvalido();
                            cout << "Ano: ";
                            if (!(cin >> a)) throw TipoInvalido();
                            if (a < 1900 || a > 2099) throw AnoInvalido();
                            if (!Data::validData(d, m, a)) throw DataInvalida();
                            if (!Data::validDia(d, m, a)) throw DiaInvalido();
                            Data novaData(d, m, a);
                            p->setNascimento(novaData);
                            cout << "Data de nascimento alterada com sucesso!\n";
                            break;
                        }
                        case 3: {
                            int newp;
                            cout << "Novo passaporte: ";
                            if (!(cin >> newp)) throw TipoInvalido();
                            for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
                                if (newp == (*it)->getPassaporte()) throw PassaporteJaExistente();
                            }
                            p->setPassaporte(newp);
                            cout << "Passaporte alterado com sucesso!\n";
                            break;
                        }
                        case 4: {
                            int gen;
                            cout << "[1] Feminino\n[2] Masculino";
                            if (!(cin >> gen)) throw TipoInvalido();
                            if (gen == 0 || gen > 2) throw NumeroInvalido();
                            if (gen == 1) p->setGenero("F");
                            else if (gen == 2) p->setGenero("M");
                            cout << "Genero alterado com sucesso!\n";
                            break;
                        }
                        case 5: {
                            int d, m, a;
                            cout << "Nova data de chegada a Toquio: " << endl;
                            cout << "Dia: ";
                            if (!(cin >> d)) throw TipoInvalido();
                            if (d < 0 || d > 31) throw DiaInvalido();
                            cout << "Mes: ";
                            if (!(cin >> m)) throw TipoInvalido();
                            if (m < 0 || m > 12) throw MesInvalido();
                            cout << "Ano: ";
                            if (!(cin >> a)) throw TipoInvalido();
                            if (a < 1900 || a > 2099) throw AnoInvalido();
                            if (!Data::validData(d, m, a)) throw DataInvalida();
                            if (!Data::validDia(d, m, a)) throw DiaInvalido();
                            Data novaData(d, m, a);
                            if (!(novaData < p->getPartida())) throw DataChegadaPartida();
                            p->setChegada(novaData);
                            cout << "Data de chegada a Toquio alterada com sucesso!\n";
                            break;
                        }
                        case 6: {
                            int d, m, a;
                            cout << "Nova data de partida de Toquio: " << endl;
                            cout << "Dia: ";
                            if (!(cin >> d)) throw TipoInvalido();
                            if (d < 0 || d > 31) throw DiaInvalido();
                            cout << "Mes: ";
                            if (!(cin >> m)) throw TipoInvalido();
                            if (m < 0 || m > 12) throw MesInvalido();
                            cout << "Ano: ";
                            if (!(cin >> a)) throw TipoInvalido();
                            if (a < 1900 || a > 2099) throw AnoInvalido();
                            if (!Data::validData(d, m, a)) throw DataInvalida();
                            if (!Data::validDia(d, m, a)) throw DiaInvalido();
                            Data novaData(d, m, a);
                            if (!(p->getChegada() < novaData)) throw DataChegadaPartida();
                            p->setPartida(novaData);
                            cout << "Data de partida de Toquio alterada com sucesso!\n";
                            break;
                        }
                        case 7: {
                            cout << "[1] Modalidade\n[2] Peso\n[3] Altura\n[4] Ranking\n"
                                    "[5] Competicoes\n[0] Voltar ao menu anterior\n";
                            int option_atl;
                            if (!(cin >> option_atl)) throw TipoInvalido();
                            if (option_atl > 5) throw NumeroInvalido();
                            clearInput();

                            switch (option_atl) {
                                case 1: {
                                    string novaM;
                                    cout << "Nova modalidade: ";
                                    getline(cin, novaM);
                                    if (novaM == "") throw StringVazia();
                                    p->setModalidade(novaM);
                                    cout << "Modalidade alterada com sucesso!\n";
                                    break;
                                }
                                case 2: {
                                    double pes;
                                    cout << "Novo peso: ";
                                    if (!(cin >> pes)) throw TipoInvalido();
                                    p->setPeso(pes);
                                    cout << "Peso alterado com sucesso!\n";
                                    break;
                                }
                                case 3: {
                                    double alt;
                                    cout << "Nova altura: ";
                                    if (!(cin >> alt)) throw TipoInvalido();
                                    p->setAltura(alt);
                                    cout << "Altura alterada com sucesso!\n";
                                    break;
                                }
                                case 4: {
                                    int rank;
                                    cout << "Novo ranking: ";
                                    if (!(cin >> rank)) throw TipoInvalido();
                                    p->setRanking(rank);
                                    cout << "Ranking alterado com sucesso!\n";
                                    break;
                                }
                                case 5: {
                                    string str;
                                    cout << "Competicoes (se mais que uma, separe-as por virgula): ";
                                    getline(cin, str);
                                    if (str == "") throw StringVazia();
                                    vector<string> comp = string_to_vector(str);
                                    p->setCompeticoes(comp);
                                    cout << "Competicoes alteradas com sucesso!\n";
                                    break;
                                }
                                case 0:
                                    break;
                            }
                            break;
                        }
                        case 8: {
                            int func;
                            cout << "Nova funcao: \n[1] Treinador\n[2] Arbitro\n[3] Medico\n"
                                    "[4] Dirigente\n[5] Enfermeiro\n[6] Presidente\n[7] Outro\n";
                            if (!(cin >> func)) throw TipoInvalido();
                            if (func == 0 || func > 7) throw NumeroInvalido();
                            if (func == 1) p->setFuncao("Treinador");
                            else if (func == 2) p->setFuncao("Arbitro");
                            else if (func == 3) p->setFuncao("Medico");
                            else if (func == 4) p->setFuncao("Dirigente");
                            else if (func == 5) p->setFuncao("Enfermeiro");
                            else if (func == 6) p->setFuncao("Presidente");
                            else p->setFuncao("Outro");
                            cout << "Funcao alterada com sucesso!\n";
                            break;
                        }
                        case 0:
                            break;
                    }
                } while (option > 0);
            }
            else throw PassaporteInexistente();
        }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (PassaporteInexistente &msg) { cout << msg.getMSG() << endl; }
        catch (StringVazia &msg) { cout << msg.getMSG() << endl; }
        catch (DataChegadaPartida &msg) { cout << msg.getMSG() << endl; }
        catch (DataInvalida &msg) {cout << msg.getMSG() << endl; }
        catch (DiaInvalido &msg ) { cout << msg.getMSG() << endl; }
        catch (MesInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (AnoInvalido &msg) { cout << msg.getMSG() << endl; }

    } while(editing != 0);
}

void Comitiva::elimPessoa() {
    vector<Pessoa*>::iterator it = pessoas.begin();
    bool found = false;
    int eliminating = 1;

    do {
        try {
            clearInput();
            cout << "Passaporte da pessoa a eliminar (0 para sair): ";
            if (!(cin >> eliminating)) throw TipoInvalido();
            if (eliminating == 0) break;

            while (it != pessoas.end()) {
                if ((*it)->getPassaporte() == eliminating) {
                    found = true;
                    int opt_elim = 0;
                    (*it)->show();
                    clearInput();
                    cout << "Pessoa encontrada: de certeza que pretende eliminar?\n[1] Sim\n[2] Nao\n" << endl;
                    if (!(cin >> opt_elim)) throw TipoInvalido();
                    if (opt_elim == 1) { pessoas.erase(it); eliminating = 0; break; }
                    else if (opt_elim == 2) { eliminating = 0; break; }
                    else throw NumeroInvalido();
                }
                else it++;
            }
            if (!found) throw PassaporteInexistente();
        }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (PassaporteInexistente &msg) { cout << msg.getMSG() << endl; }
    } while (eliminating != 0);
}

void Comitiva::findPessoa() {
    int passp;
    bool found = false;

    try {
        cout << "Numero do passaporte da pessoa a procurar: ";
        if (!(cin >> passp)) throw TipoInvalido();

        for (auto it = pessoas.begin(); it != pessoas.end(); it++)
        {
            if ((*it)->getPassaporte() == passp)
            {
                found = true;
                Pessoa *p = (*it);
                showPessoa(p);
                cout << "####################" << endl;
            }
        }
        if (!found) throw PassaporteInexistente();
    }
    catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
    catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
    catch (PassaporteInexistente &msg) { cout << msg.getMSG() << endl; }

}

void Comitiva::searchByModalidade(vector<Pessoa *> v) {
    vector <Pessoa*> res;
    string mod;
    clearInput();
    cout << "Modalidade: "; getline(cin, mod);

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->getModalidade() == mod)
        {
            res.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
}

void Comitiva::searchByPeso(vector<Pessoa *> v) {
    vector <Pessoa*> res;
    int peso;
    clearInput();
    cout << "Peso: "; cin >> peso;

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->getPeso() == peso)
        {
            res.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
}

void Comitiva::searchByAltura(vector<Pessoa *> v) {
    vector <Pessoa*> res;
    int alt;
    clearInput();
    cout << "Altura: "; cin >> alt;

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->getAltura() == alt)
        {
            res.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
}

void Comitiva::searchByRanking(vector<Pessoa *> v) {
    vector <Pessoa*> res;
    int rank;
    clearInput();
    cout << "Ranking: "; cin >> rank;

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->getRanking() == rank)
        {
            res.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
}

void Comitiva::searchByCompeticoes(vector<Pessoa *> v) {
    vector <Pessoa*> res;
    string comp;
    clearInput();
    cout << "Competicao: ";
    getline(cin, comp);

    for (auto it = v.begin(); it != v.end(); it++)
    {
        string competicoes = (*it)->showCompeticoes();
        vector<string> vec_competicoes = string_to_vector(competicoes);

        for (auto it2 = vec_competicoes.begin(); it2 != vec_competicoes.end(); it2++)
        {
            if ((*it2) == comp) {
                res.push_back((*it));
                cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
            }
        }
    }
}

void Comitiva::searchByAtletas() {
    vector<Pessoa *> v;
    for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
        if ((*it)->getTipo() == "Atleta") {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
    cout << endl << endl;

    int option = 0;
    cout << "Deseja procurar algum atleta por: \n[1] Modalidade\n[2] Peso\n[3] Altura\n[4] Ranking\n"
                                                "[5] Competicoes\n[0] Voltar ao menu anterior\n";
    if (!(cin >> option)) throw TipoInvalido();
    if (option > 5) throw NumeroInvalido();

    switch (option)
    {
        case 1: searchByModalidade(v); break;
        case 2: searchByPeso(v); break;
        case 3: searchByAltura(v); break;
        case 4: searchByRanking(v); break;
        case 5: searchByCompeticoes(v); break;
        case 0: break;
    }
}

void Comitiva::searchByFuncao(vector<Pessoa*> v) {
    vector<Pessoa*> res;
    string func;
    clearInput();
    cout << "Funcao: "; getline(cin, func);

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if ((*it)->getFuncao() == func)
        {
            res.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
}

void Comitiva::searchByStaff() {
    vector<Pessoa*> v;
    for (auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        if ((*it)->getTipo() == "Staff") {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
        }
    }
    cout << endl << endl;
    int option = 0;
    cout << "Deseja procurar algum staff por funcao? \n[1] Sim\n[0] Nao";
    if (!(cin >> option)) throw TipoInvalido();
    if (option == 1) searchByFuncao(v);

}

void Comitiva::searchByNome() {
    vector<Pessoa*> v;
    clearInput();
    string n; cout << "Nome a procurar: ";
    getline(cin, n);
    if (n == "") throw StringVazia();
    clearInput();
    vector<Pessoa*> aux = getComitiva();
    for(auto it = aux.begin(); it != aux.end(); it++)
    {
        if ((*it)->getNome() == n) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
        }
        cout << endl;
    }
    if (v.empty()) throw NomeInexistente();
}

void Comitiva::searchByNascimento() {
    vector <Pessoa*> v;
    int d, m, a;

    cout << "Data de nascimento a procurar: ";
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    Data data(d, m, a);

    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        Data datavec = (*it)->getNascimento();
        if (data == datavec) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Nascimento: ";
            (*it)->getNascimento().show();
            cout << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
        }
    }
    if (v.empty()) throw DataNascimentoNaoEncontrado();
}

void Comitiva::searchByPassaporte() {
    int p; cout << "Passaporte a procurar: ";
    if (!(cin >> p)) throw TipoInvalido();
    vector<Pessoa*> v;
    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        if ((*it)->getPassaporte() == p) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
        }
    }
    if (v.empty()) throw PassaporteInexistente();
}

void Comitiva::searchByGenero() {
    vector<Pessoa*> v;
    string n;
    cout << "[M] Masculino\n [F] Feminino:\n";
    cin >> n;
    clearInput();
    if (n != "M" && n != "F") throw TipoInvalido();

    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        if ((*it)->getGenero() == n) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
        }
    }
    if (v.empty()) throw GeneroNaoEncontrado();
}

void Comitiva::searchByChegada() {
    vector <Pessoa*> v;
    int d, m, a;
    cout << "Data de chegada a Toquio a procurar: ";
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    Data data(d, m, a);

    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        Data datavec = (*it)->getChegada();
        if (data == datavec) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Chegada a Tóquio: "; (*it)->getChegada().show(); cout << endl;
        }
    }
    if (v.empty()) throw ChegadaInexistente();
}

void Comitiva::searchByPartida() {
    vector <Pessoa*> v;
    int d, m, a;
    cout << "Data de partida de Toquio a procurar: ";
    cout << "Dia: ";
    if (!(cin >> d)) throw TipoInvalido();
    if (d < 0 || d > 31) throw DiaInvalido();
    cout << "Mes: ";
    if (!(cin >> m)) throw TipoInvalido();
    if (m < 0 || m > 12) throw MesInvalido();
    cout << "Ano: ";
    if (!(cin >> a)) throw TipoInvalido();
    if (a < 1900 || a > 2099) throw AnoInvalido();
    if (!Data::validData(d, m, a)) throw DataInvalida();
    if (!Data::validDia(d, m, a)) throw DiaInvalido();
    Data data(d, m, a);

    for(auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        Data datavec = (*it)->getPartida();
        if (data == datavec) {
            v.push_back((*it));
            cout << (*it)->getNome() << " - Partida de Tóquio: "; (*it)->getPartida().show(); cout << endl;
        }
    }
    if (v.empty()) throw PartidaInexistente();
}

bool compareNome(const Pessoa *p1, const Pessoa *p2) { return ((*p1).getNome() < (*p2).getNome()); }
void Comitiva::orderByNome() {
    vector<Pessoa*> v = pessoas;
    sort(v.begin(), v.end(), compareNome);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
    }
}

bool compareNascimento(const Pessoa *p1, const Pessoa *p2) {
    if ((*p1).getNascimento().getAno() == (*p2).getNascimento().getAno())
        if ((*p1).getNascimento().getMes() == (*p2).getNascimento().getMes())
            return ((*p1).getNascimento().getDia() <= (*p2).getNascimento().getDia());
        else
            return ((*p1).getNascimento().getMes() < (*p2).getNascimento().getMes());
    else
        return ((*p1).getNascimento().getAno() < (*p2).getNascimento().getAno());
}
void Comitiva::orderByNascimento() {
    vector<Pessoa*> v = pessoas;
    sort(v.begin(), v.end(), compareNascimento);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Nascimento: ";
        (*it)->getNascimento().show(); cout << " (" << (*it)->getTipo() << ")" << endl;
    }
}

bool comparePassaporte(const Pessoa *p1, const Pessoa *p2) { return (*p1).getPassaporte() < (*p2).getPassaporte(); }
void Comitiva::orderByPassaporte() {
    vector<Pessoa*> v = pessoas;
    sort(v.begin(), v.end(), comparePassaporte);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " (" << (*it)->getTipo() << ")" << endl;
    }
}

bool compareChegada(const Pessoa *p1, const Pessoa *p2) {
    if ((*p1).getChegada().getAno() == (*p2).getChegada().getAno())
        if ((*p1).getChegada().getMes() == (*p2).getChegada().getMes())
            return ((*p1).getChegada().getDia() <= (*p2).getChegada().getDia());
        else
            return ((*p1).getChegada().getMes() < (*p2).getChegada().getMes());
    else
        return ((*p1).getChegada().getAno() < (*p2).getChegada().getAno());
}
void Comitiva::orderByChegada() {
    vector<Pessoa*> v = pessoas;
    sort(v.begin(), v.end(), compareChegada);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Chegada a Toquio: ";
        (*it)->getChegada().show(); cout << " (" << (*it)->getTipo() << ")" << endl;
    }
}

bool comparePartida(const Pessoa *p1, const Pessoa *p2) {
    if ((*p1).getPartida().getAno() == (*p2).getPartida().getAno())
        if ((*p1).getPartida().getMes() == (*p2).getPartida().getMes())
            return ((*p1).getPartida().getDia() <= (*p2).getPartida().getDia());
        else
            return ((*p1).getPartida().getMes() < (*p2).getPartida().getMes());
    else
        return ((*p1).getPartida().getAno() < (*p2).getPartida().getAno());
}
void Comitiva::orderByPartida() {
    vector<Pessoa*> v = pessoas;
    sort(v.begin(), v.end(), comparePartida);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Partida de Toquio: ";
        (*it)->getPartida().show(); cout << " (" << (*it)->getTipo() << ")" << endl;
    }
}

bool compareModalidade(Pessoa *p1, Pessoa *p2)
{
    if ((*p1).getModalidade() == (*p2).getModalidade())
        return (*p1).getNome() < (*p2).getNome();
    return (*p1).getModalidade() < (*p2).getModalidade();
}
void Comitiva::orderByModalidade(vector<Pessoa *> v) {
    sort(v.begin(), v.end(), compareModalidade);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Modalidade: ";
        cout << (*it)->getModalidade() << endl;
    }
}

bool comparePeso(Pessoa *p1, Pessoa *p2)
{
    if ((*p1).getPeso() == (*p2).getPeso())
        return (*p1).getNome() < (*p2).getNome();
    return (*p1).getPeso() < (*p2).getPeso();
}
void Comitiva::orderByPeso(vector<Pessoa *> v) {
    sort(v.begin(), v.end(), comparePeso);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Peso: ";
        cout << (*it)->getPeso() << endl;
    }
}

bool compareAltura(Pessoa *p1, Pessoa *p2)
{
    if ((*p1).getAltura() == (*p2).getAltura())
        return (*p1).getNome() < (*p2).getNome();
    return (*p1).getAltura() < (*p2).getAltura();
}
void Comitiva::orderByAltura(vector<Pessoa *> v) {
    sort(v.begin(), v.end(), compareAltura);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Altura: ";
        cout << (*it)->getAltura() << endl;
    }
}

bool compareRanking(Pessoa *p1, Pessoa *p2)
{
    if ((*p1).getRanking() == (*p2).getRanking())
        return (*p1).getNome() < (*p2).getNome();
    return (*p1).getRanking() < (*p2).getRanking();
}
void Comitiva::orderByRanking(vector<Pessoa *> v) {
    sort(v.begin(), v.end(), compareRanking);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Ranking: ";
        cout << (*it)->getRanking() << endl;
    }
}

bool compareFuncao(Pessoa *p1, Pessoa *p2)
{
    if ((*p1).getFuncao() == (*p2).getFuncao())
        return (*p1).getNome() < (*p2).getNome();
    return (*p1).getFuncao() < (*p2).getFuncao();
}
void Comitiva::orderByFuncao(vector<Pessoa *> v) {
    sort(v.begin(), v.end(), compareFuncao);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << " - Funcao: ";
        cout << (*it)->getFuncao() << endl;
    }
}

void Comitiva::orderByAtletas() {
    unsigned int option = 0;
    vector<Pessoa*> v;
    for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
        if ((*it)->getTipo() == "Atleta") {
            v.push_back((*it));
        }
    }
    sort(v.begin(), v.end(), compareNome);
    for (auto it = v.begin(); it != v.end(); it++)
    {
        cout << (*it)->getNome() << " - Passaporte: " << (*it)->getPassaporte() << endl;
    }

    try {
        cout << endl;
        cout << "Ordenar atletas por: \n[1] Modalidade \n[2] Peso \n[3] Altura \n[4] Ranking\n"
                "[0] Voltar ao menu anterior \n";

        if (!(cin >> option)) throw TipoInvalido();
        if (option > 4) throw NumeroInvalido();

        switch (option) {
            case 1: orderByModalidade(v); break;
            case 2: orderByPeso(v); break;
            case 3: orderByAltura(v); break;
            case 4: orderByRanking(v); break;
            case 0: break;
        }
    }
    catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
    catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
}

void Comitiva::orderByStaff() {
    vector<Pessoa*> v;
    for (auto it = pessoas.begin(); it != pessoas.end(); it++) {
        if ((*it)->getTipo() == "Staff") {
            v.push_back((*it));
        }
    }
    orderByFuncao(v);
}

// Opcoes do menu principal
void Comitiva::aboutComitiva() {

    int option1 = 0;

    do {
        try {
            while (true) {
                cout << endl;
                cout << "[1] Ver comitiva\n[2] Adicionar\n[3] Editar\n"
                        "[4] Eliminar\n[5] Consultar custo diario da comitiva\n"
                        "[6] Obter informacao detalhada sobre uma pessoa\n[0] Voltar\n";

                try {
                    if (!(cin >> option1)) {
                        clearInput();
                        throw TipoInvalido();
                    }
                    break;
                }
                catch (TipoInvalido &msg) {
                    cout << msg.getMSG() << endl;
                }
            }

            switch (option1) {
                case 1:
                    showComitiva();
                    break;
                case 2:
                    addPessoa();
                    break;
                case 3:
                    editPessoa();
                    break;
                case 4:
                    elimPessoa();
                    break;
                case 5:
                    getCustoDiario();
                    break;
                case 6:
                    findPessoa();
                    break;
                case 0:
                    break;
                default:
                    break;
            }
        }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }

    } while (option1 != 0);
}
void Comitiva::searchBy() {
    int option2 = 0;

    do {
        try {
            while (true) {
                cout << endl;
                cout << "Procurar por: \n[1] Atletas \n[2] Staff \n[3] Nome \n[4] Nascimento \n[5] Passaporte "
                        "\n[6] Genero \n[7] Data de chegada a Toquio \n[8] Data de partida de Toquio \n[0] Voltar ao menu anterior \n";

                try {
                    if (!(cin >> option2)) {
                        clearInput();
                        throw TipoInvalido();
                    }
                    break;
                }
                catch (TipoInvalido &msg) {
                    cout << msg.getMSG() << endl;
                }
            }

            switch (option2) {
                case 1:
                    searchByAtletas();
                    break;
                case 2:
                    searchByStaff();
                    break;
                case 3:
                    searchByNome();
                    break;
                case 4:
                    searchByNascimento();
                    break;
                case 5:
                    searchByPassaporte();
                    break;
                case 6:
                    searchByGenero();
                    break;
                case 7:
                    searchByChegada();
                    break;
                case 8:
                    searchByPartida();
                    break;
                case 0:
                    break;
                default:
                    throw NumeroInvalido();
            }
        }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (NomeInexistente &msg) { cout << msg.getMSG() << endl; }
        catch (DataNascimentoNaoEncontrado &msg) { cout << msg.getMSG() << endl; }
        catch (PassaporteInexistente &msg) { cout << msg.getMSG() << endl; }
        catch (GeneroNaoEncontrado &msg) { cout << msg.getMSG() << endl; }
        catch (ChegadaInexistente &msg) { cout << msg.getMSG() << endl; }
        catch (PartidaInexistente &msg) { cout << msg.getMSG() << endl; }
        catch (StringVazia &msg) { cout << msg.getMSG() << endl; }

    } while (option2 != 0);
}
void Comitiva::orderBy() {
    int option3 = 0;

    do {
        try {
            while (true) {
                cout << endl;
                cout << "Ordenar por: \n[1] Atletas \n[2] Staff \n[3] Nome \n[4] Nascimento \n[5] Passaporte"
                        " \n[6] Data de chegada a Toquio \n[7] Data de partida de Toquio \n"
                        "[0] Voltar ao menu anterior \n";

                try {
                    if (!(cin >> option3)) {
                        clearInput();
                        throw TipoInvalido();
                    }
                    break;
                }
                catch (TipoInvalido &msg) {
                    cout << msg.getMSG() << endl;
                }
            }
            switch (option3) {
                case 1:
                    orderByAtletas();
                    break;
                case 2:
                    orderByStaff();
                    break;
                case 3:
                    orderByNome();
                    break;
                case 4:
                    orderByNascimento();
                    break;
                case 5:
                    orderByPassaporte();
                    break;
                case 6:
                    orderByChegada();
                    break;
                case 7:
                    orderByPartida();
                    break;
                case 0:
                    break;
                default:
                    throw NumeroInvalido();
                }
        }
        catch (NumeroInvalido &msg) { cout << msg.getMSG() << endl; }
        catch (TipoInvalido &msg) { cout << msg.getMSG() << endl; }

    } while (option3 != 0);
}

// Atualiza o ficheiro portugal.txt
void Comitiva::refreshComitiva(string comit) {

    ofstream file;
    file.open( comit + ".txt");

    for (auto it = pessoas.begin(); it != pessoas.end(); it++)
    {
        if ((*it)->getTipo() == "Atleta") {
            file << (*it)->getTipo() << " - " << (*it)->getNome() << " - "
                 << (*it)->getNascimento().getDia() << "/" << (*it)->getNascimento().getMes() << "/"
                 << (*it)->getNascimento().getAno() << " - "
                 << (*it)->getPassaporte() << " - " << (*it)->getGenero() << " - "
                 << (*it)->getChegada().getDia() << "/" << (*it)->getChegada().getMes() << "/"
                 << (*it)->getChegada().getAno() << " - "
                 << (*it)->getPartida().getDia() << "/" << (*it)->getPartida().getMes() << "/"
                 << (*it)->getPartida().getAno() << " - " << (*it)->getModalidade() << " - "
                 << (*it)->getPeso() << " - " << (*it)->getAltura() << " - " << (*it)->getRanking() << " - ";
            string str = (*it)->showCompeticoes();
            file << str << endl;
        }
        else if ((*it)->getTipo() == "Staff") {
            file << (*it)->getTipo() << " - " << (*it)->getNome() << " - "
                 << (*it)->getNascimento().getDia() << "/" << (*it)->getNascimento().getMes() << "/"
                 << (*it)->getNascimento().getAno() << " - "
                 << (*it)->getPassaporte() << " - " << (*it)->getGenero() << " - "
                 << (*it)->getChegada().getDia() << "/" << (*it)->getChegada().getMes() << "/"
                 << (*it)->getChegada().getAno() << " - "
                 << (*it)->getPartida().getDia() << "/" << (*it)->getPartida().getMes() << "/"
                 << (*it)->getPartida().getAno() << " - " << (*it)->getFuncao() << endl;
        }
    }
    file.close();
    cout << "\n'portugal.txt' atualizado com sucesso!\n";
}
