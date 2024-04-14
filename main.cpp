#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <cctype> // Biblioteca p/ usar a função isalpha

using namespace std;

struct aluno{ //molde p/ armazenar as info do aluno
    string nome;
    float n1,n2;
    struct aluno* prox; //ponteiro para guardar o endereço da prox struct criada para "encadear"
};

struct aluno *cabeca=nullptr;//referencia primaria
struct aluno *ult=nullptr; //ultimo da lista

void limpar_tela() {
    system("clear||cls");
}

//prototipos funções
int menu();
void criar_struct_alunos(int);
void preencher_alunos(int);
void exibir_lista_alunos();
void perguntar_exibir();
void remover_da_lista();
string padronizar_nomes();

//funcao principal
int main()
{
    int num_aluno;//var p/ guardar qnts structs deverao ser criadas e encadeadas
    num_aluno=menu();
    limpar_tela();
    criar_struct_alunos(num_aluno);
    preencher_alunos(num_aluno);
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
    return num_aluno; //returna a var pro main
}

void criar_struct_alunos(int num_alunos){
    struct aluno *novo=nullptr;//cria um ponteiro que aponta pra struct (local da funcao)
    for(int i=0;i<num_alunos;i++){ //rodar a qnt de alunos que deverao ser alocados
        novo=(struct aluno*)malloc(sizeof(struct aluno));/*pega o tamanho da struct e armazena na MP e guarda 
        o end. da primeira celula no ponteiro*/
        if(cabeca==nullptr){ //se não tiver nenhum aluno marcado
            cabeca=novo;
        }
        else{
            ult->prox=novo;//vai receber o novo end. criado para não perder a referencia
        }
        ult=novo;//vai apontar pra ultima struct armazenada
    }
}

bool validar_nome(const string& nome) { //recebe o nome da funcao preencher_alunos
    for(char c : nome) { //verifica cada letra colocada
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


void preencher_alunos(int cont){
    int cont1=1;//pra usar na comparacao
    bool num_valido=false;
    float n1,n2;
    string nome;
    struct aluno *aux=nullptr;//pra não mexer diretamente com a cabeca faço uma copia
    aux=cabeca;//a var local recebe a cabeca
    while(cont1 <= cont){ //enquanto ainda não preencheu todos os alunos armazenados
       cout<<"Digite o nome do "<<cont1<<" ° aluno:";
       cin.ignore(); // Limpar o buffer do teclado antes de usar getline
       getline(cin, nome);
       // Se a entrada do usuário foi bem-sucedida e se o nome fornecido é válido
       if(cin.fail() || nome.empty() || !validar_nome(nome)) {
           cout << "Erro: Entrada inválida. Por favor, digite um nome válido.\n";
           cin.clear(); // Limpar o estado de erro
           cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora entrada inválida
           continue; // Ignora o resto e volta ao início no loop
       }
       nome = padronizar_nomes(nome); //funcao para colocar maiuscula na primeira letra do nome e sobrenome
       aux->nome=nome;
       
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
       aux->n1=n1; //guarda var na struct que o ponteiro aponta
       
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
       aux->n2=n2;
       aux=aux->prox;//aux aponta para a proxima struct encadeada
       cont1++;
    }
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
            exibir_lista_alunos();
            break;
            case 2:
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
    struct aluno *aux=cabeca; //copia da cabeca

    cout << "\t\t INFORMAÇÕES DOS ALUNOS REGISTRADOS:\n\n ";
    while(aux!=nullptr){ //enquanto ainda tiver um prox elemento
        cout << "NOME: " << aux->nome << "\n";
        cout << "NOTA 1: " << aux->n1 << "\n";
        cout << "NOTA 2: " << aux->n2 << "\n";
        cout << "MÉDIA: " << ((aux->n1 + aux->n2) / 2) << "\n"; // calcular média
        cout << "--------------------------------------------------\n";
        aux = aux->prox;
    }
    cout << "Pressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); // Limpar o buffer do teclado
    cin.get(); // Aguardar que o usuário pressione Enter
}

void remover_da_lista() {
    string nome;
    int cont=1;
    struct aluno *aux = cabeca;
    cout<<"=====================================================\n";
    cout<<"\t\tALUNOS REGISTRADOS NA SALA:\n";
    while(aux!=nullptr){
        cout<<"Aluno(a) "<<cont<<":"<<aux->nome<<"\n";
        aux=aux->prox;
        cont++;
    }
    cout<<"=====================================================\n";
    cout << "Digite o nome do aluno(a) que você deseja excluir: ";
    cin.ignore(); // Limpar o buffer do teclado antes de usar getline
    getline(cin, nome);
    //o primeiro char do nome recebe a versão maiúscula dele mesmo
    nome = padronizar_nomes(nome);
    struct aluno *ant = nullptr;
    aux = cabeca;

    while (aux != nullptr) {
        if (aux->nome == nome) {
            break; // Nome encontrado, sair do loop
        }
        ant = aux;
        aux = aux->prox;
    }

    if (aux == nullptr) { //se rodou tudo e não achou
        cout << "Aluno(a) não encontrado.\n";
        cout << "Pressione Enter para continuar...";
        cin.get(); // Aguardar que o usuário pressione Enter para continuar
        return; //volta onde foi chamado
    }

    // Ajustar ponteiros para remover o nó da lista
    if (ant == nullptr) { // Se for o primeiro da lista para remover
        cabeca = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    if (aux == ult) { // Se o nó a ser removido for o último da lista
        ult = ant; //recebe o end. do anterior
    }

    // Liberar memória alocada do nó removido
    free(aux);

    cout << "Aluno apagado com sucesso!\n";
    cout << "Pressione Enter para continuar...";
    cin.get(); // Aguardar que o usuário pressione Enter para continuar
}












