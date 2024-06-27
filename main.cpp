#include <iostream>
using namespace std;

struct noGerado {
	int senha;
	noGerado *prox;
};

struct noAtendido {
    int senha;
    noAtendido *prox;
};

struct senhasGeradas {
	noGerado *ini;
	noGerado *fim;
};

struct senhasAtendidas {
    noAtendido *ini;
    noAtendido *fim;
};

// _____________________________________________________

senhasGeradas* initGer() {
	senhasGeradas *sGer = new senhasGeradas;
	sGer->ini = NULL;
	sGer->fim = NULL;
	return sGer;
}

int isEmptyGer(senhasGeradas *sGer) {
	return (sGer->ini == NULL);
}

void enfSenhaGer(senhasGeradas *sGer, float s) {
	noGerado *no = new noGerado;
	no->senha = s;
	no->prox = NULL;
	if (isEmptyGer(sGer)) {
		sGer->ini = no;
	}
	else {
		sGer->fim->prox = no;
	}
	sGer->fim = no;
}

int desSenhaGer(senhasGeradas *sGer) {
	int res;
	if (isEmptyGer(sGer)) {
		res = -1;
	}
	else {
		noGerado *no = sGer->ini;
		res = no->senha;
		sGer->ini = no->prox;
		if (sGer->ini == NULL) {
			sGer->fim = NULL;
		}
	    free(no);	
	}
	return res;
}

// _____________________________________________________

senhasAtendidas* initAten() {
	senhasAtendidas *sAten = new senhasAtendidas;
	sAten->ini = NULL;
	sAten->fim = NULL;
	return sAten;
}

int isEmptyAten(senhasAtendidas *sAten) {
	return (sAten->ini == NULL);
}

void enfSenhaAten(senhasAtendidas *sAten, int s) {
	noAtendido *no = new noAtendido;
	no->senha = s;
	no->prox = NULL;
	if (isEmptyAten(sAten)) {
		sAten->ini = no;
	}
	else {
		sAten->fim->prox = no;
	}
	sAten->fim = no;
}


// _____________________________________________________

int count(senhasGeradas *sGer) {
	int qtde = 0;
	noGerado *no;
	no = sGer->ini;
	while (no != NULL) {
		qtde++;
		no = no->prox;
	}
	return qtde;
}

int senhaVez(senhasGeradas *sGer) {
    int senha = 0;
	noGerado *no;
	no = sGer->ini;
	if (no != NULL) {
		senha = no->senha;
	}
	
	return senha;
}


void freeAtendimento(senhasAtendidas *sAten) {
	noAtendido *no = sAten->ini;
	while (no != NULL) {
		noAtendido *temp = no->prox;
		free(no);
		no = temp;
	}
	free(sAten);
}

int gerSenha(){
    srand(time(0));
    
    return rand();
}

void opcoes(senhasGeradas *sGer, senhasAtendidas *sAten){
    cout << "--------------------------------------";
    cout << endl << count(sGer) << " pessoas estao aguardando atendimento" << endl;
    cout << "--------------------------------------";
    
    int opcao;
    int senha = gerSenha();
    
    cout << "\nEscolha uma opcao:\n"    << endl
         << "0. Sair"                   << endl
         << "1. Gerar senha"            << endl
         << "2. Realizar atendimento\n" << endl;
         
    cin >> opcao;
    
    switch(opcao){
        case 0:
            cout << "Sair" << endl;
            if(count(sGer) == 0){
                cout << "Atendimentos encerrados" << endl;
                freeAtendimento(sAten);
            }else{
                cout << "Ainda existem pessoas a serem atendidas" << endl;
                opcoes(sGer, sAten);
            }
            break;
        case 1:
            cout << "Gerar senha"  << endl;
            cout << "Senha " << senha << " gerada" << endl;
            enfSenhaGer(sGer, senha);
            opcoes(sGer, sAten);
            break;
        case 2:
            cout << "Realizar atendimento" << endl;
            cout << "Senha da vez: " << senhaVez(sGer) << endl;
            enfSenhaAten(sAten, senhaVez(sGer));
            desSenhaGer(sGer);
            opcoes(sGer, sAten);
            break;
        default:
            cout << "!!! POR FAVOR, SELECIONE UMA OPCAO DE 0 A 2 !!!" << endl;
            opcoes(sGer, sAten);
    }
}

int main(int argc, char** argv)
{
    senhasGeradas *geradaInt;
    senhasAtendidas *atendidaInt;
    
    geradaInt = initGer();
    atendidaInt = initAten();
    
    opcoes(geradaInt, atendidaInt);
	
	return 0;
}