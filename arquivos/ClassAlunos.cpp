#include "alunos.h"

// Construtor sem parâmetros
Alunos::Alunos()
    : nome(""), n1(0.0f), n2(0.0f), prox(nullptr) {}
    
// Construtor com parâmetros
Alunos::Alunos(const std::string nome, float n1, float n2)
    : nome(nome), n1(n1), n2(n2), prox(nullptr) {}
    
Alunos* Alunos::obter_proximo() const {
    return prox;
}
string Alunos::obter_nome() const{
    return nome;
}
float Alunos::obter_n1() const{
    return n1;
}
float Alunos::obter_n2() const{
    return n2;
}
float Alunos::media() const{
    float media = 0.0;
    media = (this->n1 + this-> n2)/2.0; //acessar os atributos (n1,n2) do obj atual
    return media;
}

// Método para definir o próximo aluno
void Alunos::definir_proximo(Alunos* proximo) {
    prox = proximo;
}