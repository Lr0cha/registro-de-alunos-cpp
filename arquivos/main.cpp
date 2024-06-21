#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <cctype> // Biblioteca p/ usar a função isalpha
#include "alunos.h" //incluindo a classe 

using namespace std;

/*struct aluno{ //molde p/ armazenar as info do aluno
    string nome;
    float n1,n2;
    struct aluno* prox; //ponteiro para guardar o endereço da prox struct criada para "encadear"
};*/

Alunos *cabeca=nullptr;//referencia primaria
Alunos *ult=nullptr; //ultimo da lista

void limpar_tela() {
    system("clear||cls");
}

//prototipos funções
int menu();
void criar_alunos(int);
void preencher_alunos(int&, float&, float&, string&);
void exibir_lista_alunos();
void perguntar_exibir();
void remover_da_lista();
string padronizar_nomes();

//funcao principal
int main()
{
    int num_aluno;//var p/ guardar qnts alunos deverao ser criados e encadeadas
    num_aluno=menu();
    limpar_tela();
    criar_alunos(num_aluno);
    perguntar_exibir();
    return 0;
}

int menu(){
    bool num_valido=false;
    int num_aluno;
    cout<<"\t Bem Vindo Professor!\n";
    cout<<"Quantos alunos tem está sala: ";
    do{
        if (!(cin >> num_aluno)) { // Se a entrada não é um número
            cout<<"Entrada inválida. Por favor, digite um número inteiro maior que 0:";
            cin.clear(); // Limpa o erro do cin
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); //descartar caracteres da entrada ate o \n.
        }
        else if(num_aluno<=0){
            cout<<"Digite um número inteiro maior que 0:";
        }
        else{
            num_valido=true;
        }
    }while(!num_valido);
    return num_aluno; //retorna a var pro main
}

void criar_alunos(int num_alunos){
    int cont = 1;
    float n1 = 0.0,n2=0.0;
    string nome = "";
    for (int i = 0; i < num_alunos; ++i) {
        preencher_alunos(cont,n1,n2,nome);
        cont++;
        Alunos* ptr_aluno = new Alunos(nome,n1,n2);//criar ponteiro para uma instancia do obj
        if (cabeca == nullptr) {
            cabeca = ptr_aluno; // Se for o primeiro aluno, cabeça aponta para ele
        } else {
            ult->definir_proximo(ptr_aluno); // Se não for o primeiro, o último obj inserido aponta para ele
        }
        ult = ptr_aluno; // Atualiza o último para o novo aluno criado
    }
}

bool validar_nome(const string& nome) { //recebe o nome da funcao preencher_alunos
    for(char c : nome) { //verifica cada letra colocada na string
        if (!isalpha(c) && c != ' ') { // Se qualquer caractere não for uma letra e separador, retorna falso
            return false;
        }
    }
    return true; // Se tds os carac forem letras ou ' '
}

string padronizar_nomes(string nome){
    nome[0] = (char) toupper( (int) nome[0] );//converte o primeiro caractere para maiúsculo
    for(size_t i = 0; i < nome.size() - 1; ++i) { 
        if(nome[i] == ' '){
            nome[i+1] = (char) toupper( (int ) nome[i+1]);//caractere atual for '', converte proximo maiúsculo
        }
    }
    return nome;
}


void preencher_alunos(int& cont, float& n1, float& n2, string& nome){
    bool num_valido=false;
    do{
        cout<<"Digite o nome do "<<cont<<" ° aluno:";
        cin.ignore(); // Limpar o buffer do teclado antes de usar getline
        getline(cin, nome);
        // Se a entrada do usuário foi bem-sucedida e se o nome fornecido é válido
        if(cin.fail() || nome.empty() || !validar_nome(nome)) {
            cout << "Erro: Entrada inválida. Por favor, digite um nome válido.\n";
            cin.clear(); // Limpar o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entrada inválida
            continue; // Ignora o resto e volta ao início no loop
        }
    }while(num_valido);
    nome = padronizar_nomes(nome); //funcao para colocar maiuscula na primeira letra do nome e sobrenome
    cout<<"\nDigite a primeira nota[0 a 10]: do aluno "<<nome<<":";
    do{
        if (!(cin >> n1)) { // Verifica se a entrada não é um número
        cout<<"Entrada inválida. Por favor, digite um número válido (0 a 10): \n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    else if(n1 < 0 || n1 > 10){
        cout<<"Digite um número inteiro válido (0 a 10): \n";
        continue;
    }
    else{
        num_valido=true;
    }
    }while(!num_valido);//entro no !verdade sai do loop
    num_valido = false;
    cout<<"\nDigite a segunda nota[0 a 10] do aluno "<<nome<<":";
    do{
        if (!(cin >> n2)) { // Verifica se a entrada não é um número
        cout<<"Entrada inválida. Por favor, digite um número válido (0 a 10): \n";
        cin.clear(); // Limpa o estado de erro
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    else if(n2 < 0 || n2 > 10){
        cout<<"Digite um número inteiro válido (0 a 10): \n";
        continue;
    }
    else{
        num_valido=true;
    }
    }while(!num_valido);//tratamento de erro
    cout<<"--------------------------------------------------------------------\n\n";
}

bool lista_vazia(){
    if (cabeca == nullptr){
        cout<<"-----------------------------------\n";
        cout<<"Lista de alunos vazia!\n";
        cout<<"-----------------------------------\n";
        cout << "Pressione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); // Limpar o buffer do teclado
        cin.get(); // Aguardar que o usuário pressione Enter
        return true;
    }
    return false;
}
void perguntar_exibir(){
    int op;
    cout<<"\t\tDADOS DEVIDAMENTE PREENCHIDOS: \n\n";
    cout<<"--------------------------------------------------------------------\n\n";
    cin.get();
    do{
        limpar_tela();
        cout<<"POR FAVOR, DIGITE UM NÚMERO DE (1 a 3):\n";
        cout<<"1- Exibir a lista de alunos da sala:\n";
        cout<<"2- Apagar algum registro de aluno:\n";
        cout<<"3- Sair do programa:\n";
        if (!(cin >> op)) { 
            cout<<"Entrada inválida. Por favor, digite um número referente as opções acima:";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        switch(op){
            case 1:
            if(lista_vazia()){
                continue;
            }
            exibir_lista_alunos();
            break;
            case 2:
            if(lista_vazia()){
                continue;
            }
            remover_da_lista();
            break;
            case 3:
            cout<<"Saindo do programa....";
            exit(0);//funcao para fechar o programa
            break;
            default:
            cout<<"O número digitado não foi válido\n";
        }   
    }while(op!=3);
}

void exibir_lista_alunos(){
    Alunos *aux=cabeca; //copia o end do primeiro da lista 

    cout << "\t\t INFORMAÇÕES DOS ALUNOS REGISTRADOS:\n\n ";
    while(aux!=nullptr){ //enquanto ainda tiver um prox elemento
        cout << "NOME: " << aux->obter_nome() << "\n";
        cout << "NOTA 1: " << aux->obter_n1() << "\n";
        cout << "NOTA 2: " << aux->obter_n2() << "\n";
        cout << "MÉDIA: " << aux->media() << "\n"; // calcular média
        cout << "--------------------------------------------------\n";
        aux = aux->obter_proximo(); //passa para o proximo aluno na MP
    }
    cout << "Pressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // Limpar o buffer do teclado
    cin.get(); // Aguardar que o usuário pressione Enter
}

void remover_da_lista() {
    string nome;
    int cont=1;
    Alunos *aux = cabeca;
    cout<<"=====================================================\n";
    cout<<"\t\tALUNOS REGISTRADOS NA SALA:\n";
    while(aux!=nullptr){
        cout<<"Aluno(a) "<<cont<<":"<<aux->obter_nome()<<"\n";
        aux=aux->obter_proximo();//proximo aluno
        cont++;
    }
    cout<<"=====================================================\n";
    cout << "Digite o nome do aluno(a) que você deseja excluir: ";
    cin.ignore(); // Limpar o buffer do teclado antes de usar getline
    getline(cin, nome);
    //o primeiro char do nome recebe a versão maiúscula dele mesmo
    nome = padronizar_nomes(nome);
    Alunos *ant = nullptr; //guardar aluno que antecede o obj "excluido"
    aux = cabeca;//volta pro inicio da lista de alunos

    while (aux != nullptr) {
        if (aux->obter_nome() == nome) {
            break; // Nome encontrado, sair do loop
        }
        ant = aux;
        aux = aux->obter_proximo();
    }

    if (aux == nullptr) { //se rodou tudo e não achou o nome
        cout << "Aluno(a) não encontrado.\n";
        cout << "Pressione Enter para continuar...";
        cin.get(); // Aguardar que o usuário pressione Enter para continuar
        return; //volta onde foi chamado
    }

    // Ajustar ponteiros para remover o nó da lista
    if (ant == nullptr) { // Se for o primeiro da lista para remover
        cabeca = aux->obter_proximo();
    } else {
    //o anterior recebe o proximo obj para não perder referencia
        ant->definir_proximo(aux->obter_proximo()); 
    }
    if (aux == ult) { // Se o nó a ser removido for o último da lista
        ult = ant; //recebe o end. do anterior
    }
    delete aux; // Liberando a memória alocada do obj

    cout << "Aluno apagado com sucesso!\n";
    cout << "Pressione Enter para continuar...";
    cin.get(); // Aguardar que o usuário pressione Enter para continuar
}












