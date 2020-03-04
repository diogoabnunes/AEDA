#ifndef TOKYO2020_COMITIVA_H
#define TOKYO2020_COMITIVA_H

#include <vector>
#include <iostream>
#include <string>
#include "Pessoa.h"
#include "Atleta.h"
#include "Staff.h"
#include <fstream>
#include <algorithm>
#include "Data.h"
#include "Exception.h"

class Comitiva {
private:
    vector<Pessoa*> pessoas;
public:
    ///@brief Esta função coloca no vetor "pessoas" todas as pessoas presentes no ficheiro "portugal.txt".
    ///@param comit String com o nome do ficheiro a ser lido.
    ///@return Um objeto da classe Comitiva.
    Comitiva(string comit);
    ///@brief Retorna um vetor com toda a comitiva portuguesa (vetor "pessoas").
    ///@return Vector de apontador para Pessoa com as Pessoas da Comitiva.
    vector<Pessoa*> getComitiva() const;
    ///@brief Imprime nome, passaporte e tipo (Atleta ou Staff) de cada pessoa da comitiva portuguesa.
    void showComitiva() const;


    ///@brief Esta função adiciona uma Pessoa ao vetor "pessoas".
    void addPessoa();
    ///@brief Esta função adiciona um Atleta à Comitiva.
    void addAtleta();
    ///@brief Esta função adiciona um Staff à Comitiva.
    void addStaff();
    ///@brief Esta função edita as informações de uma Pessoa.
    void editPessoa();

    ///@brief Esta função elimina uma Pessoa do vetor "pessoas".
    void elimPessoa();

    ///@brief Retorna o custo diário de toda a comitiva portuguesa.
    ///@return Double com o custo diário de toda a comitiva portuguesa
    double getCustoDiario() const;
    ///@brief Imprime toda a informação detalhada de um vetor passado como argumento.
    void showPessoa(Pessoa *p);
    ///@brief Procura no vetor "pessoas" uma pessoa pelo numero de passaporte.
    void findPessoa();

    // Funcoes de pesquisa
    ///@brief Mostra todos os elementos com um nome específico.
    void searchByNome();
    ///@brief Mostra todos os elementos com uma data de nascimento específica.
    void searchByNascimento();
    ///@brief Mostra todos os elementos com um número de passaporte específico.
    void searchByPassaporte();
    ///@brief Mostra todos os elementos de um dado género.
    void searchByGenero();
    ///@brief Mostra todos os elementos com uma data de chegada a Tóquio específica.
    void searchByChegada();
    ///@brief Mostra todos os elementos com uma data de partida de Tóquio específica.
    void searchByPartida();
    ///@brief Mostra todos os elementos com uma modalidade específica de um vetor de atletas passado como argumento.
    void searchByModalidade( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos com um peso específico de um vetor de atletas passado como argumento.
    void searchByPeso( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos com uma altura específica de um vetor de atletas passado como argumento.
    void searchByAltura( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos com um ranking específico de um vetor de atletas passado como argumento.
    void searchByRanking( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos com uma competição específica de um vetor de atletas passado como argumento.
    void searchByCompeticoes( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos com uma função específica de um vetor de membros de staff passado como argumento.
    void searchByFuncao(vector<Pessoa*> v);
    ///@brief Menu para procura por Atletas
    void searchByAtletas();
    ///@brief Menu para procura por membros do Staff
    void searchByStaff();

    // Funcoes de ordenacao
    ///@brief Mostra todos os elementos ordenados pelo nome.
    void orderByNome();
    ///@brief Mostra todos os elementos ordenados pelo nascimento.
    void orderByNascimento();
    ///@brief Mostra todos os elementos ordenados por passaporte.
    void orderByPassaporte();
    ///@brief Mostra todos os elementos ordenados por data de chegada a Tóquio.
    void orderByChegada();
    ///@brief Mostra todos os elementos ordenados por data de partida de Tóquio.
    void orderByPartida();
    ///@brief Mostra todos os elementos ordenados por modalidade
    void orderByModalidade( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos ordenados por peso de um vetor de atletas passado como argumento.
    void orderByPeso( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos ordenados por altura de um vetor de atletas passado como argumento.
    void orderByAltura( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos ordenados por ranking de um vetor de atletas passado como argumento.
    void orderByRanking( vector<Pessoa*> v);
    ///@brief Mostra todos os elementos ordenados por função de um vetor de membros de staff passado como argumento.
    void orderByFuncao(vector<Pessoa*> v);
    ///@brief Menu para ordenação dos Atletas
    void orderByAtletas();
    ///@brief Menu para ordenação dos membros do Staff
    void orderByStaff();

    // Opcoes do menu principal
    ///@brief Esta função mostra as opções para interagir com a Comitiva (adicionar, editar, eliminar, ...).
    void aboutComitiva();
    ///@brief Apenas chama a função de pesquisa que o utilizador escolher.
    void searchBy();
    ///@brief Apenas chama a função de ordenação que o utilizador escolher.
    void orderBy();

    // Atualiza o ficheiro portugal.txt
    ///@brief Esta função atualiza o ficheiro de pessoas (portugal.txt) no fim do programa.
    ///@param comit Nome da comitiva a ter o ficheiro atualizado.
    void refreshComitiva(string comit);
};

#endif //TOKYO2020_COMITIVA_H