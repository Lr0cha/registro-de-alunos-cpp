#ifndef ALUNOS_H
#define ALUNOS_H

#include <string>
using namespace std;

class Alunos {
private:
    string nome;
    float n1, n2;
    Alunos* prox; //ponteiro para o próximo objeto Alunos
public:
    //construtores
    Alunos(); // Construtor inicial
    Alunos(string nome, float n1, float n2); // Construtor com parâmetros
    //getters
    Alunos* obter_proximo() const;
    string obter_nome() const;
    float obter_n1() const;
    float obter_n2() const;
    float media() const;
    //setters
    void definir_proximo(Alunos* proximo);
};

#endif // ALUNOS_H