#include <iostream>
#include <fstream> // per leggere e scrivere i file
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// QUESTO PROGRAMMA DEVE CREARE UNA STRUTTURA DATI DI UTENTI, SALVATO IN UN FILE, OGNI UTENTE HA UN NOME, UNA PASSWORD, UN CONTO BANCARIO
// l'UTENTE DEVE ESSERE IN GRADO DI ACCEDERE AL PROPRIO CONTO BANCARIO, VEDERE IL CONTENUTO CON DATI AGGIUNTIVI, MODIFICARLO
// CON FUNZIONI PRELEVA() E VERSA()
// SI POTRA' CREARE UN NUOVO UTENTE E ACCEDERE, I DATI SARANNO IN UNA STRUTTURA USER
fstream _utenti ("utenti.txt");
/*
int numero_linee(){
    int conta = 0;
    string line;
    while(getline(_utenti, line)){
        conta++;
    }
    return conta;
}
*/
struct user {
    string nome;
    string password;
    double conto_bancario;
};
void splitstring(string dati[3],string stringa){
    int indice = 0;
    for(int i = 0; i < stringa.length(); ++i){
        if(stringa[i] == ' ') {
            indice++;
            i++;
        }
        dati[indice] += stringa[i];
    }
}
int numerolinee() {
    fstream _utenti("utenti.txt");
    int conta = 0;
    string line;
    while(getline(_utenti, line)){
        conta++;
    }
    return conta;
}
void nuovo_utente(){
    fstream _utenti("utenti.txt", ios::app); 
    
    user utente;
    cout << "Inserisci il nome utente: -->";
    cin >> utente.nome; // CONTROLLARE DOPO GESTIONE DEGLI SPAZI
    cout << "\nInserisci la password: --> ";
    cin >> utente.password;
    cout << "\nInserisci il conto bancario iniziale: --> ";
    cin >> utente.conto_bancario;
    if(utente.nome != "  9.27868e-315" or utente.password != "  9.27868e-315" or utente.conto_bancario != 9.27868e-315) {
        if(_utenti.is_open()) {
            _utenti << utente.nome << " " << utente.password << " " << utente.conto_bancario << " " << "\n";

        }
    }
}

bool logged(string utente_lg[3]){
    fstream _utenti("utenti.txt"); 
    vector<string> list;
    int numero_linee = numerolinee();
    string line;
    string nome, utente[numero_linee+1][3], passwd;
    cout << "Inserisci il nome utente: -->";
    cin >> nome; // CONTROLLARE DOPO GESTIONE DEGLI SPAZI
    cout << "Inserisci la password: -->";
    cin >> passwd;
    int b = 0;

    while(getline(_utenti, line)){
        b++;
        //cout << line;
        list.push_back(line);
    }

    b = 0;
    for(int r = 0; r < numero_linee; r++){
        //cout << list[r] << endl;
        splitstring(utente[r], list[r]);
    }

    bool userfound = false;
    for(int r = 0; r < numero_linee; ++r){
        bool flag = true ? utente[r][0][0] == *"\0" : false;
        if(flag) utente[r][0].erase(0, 1);
        //cout << utente[r][1] << " " << passwd << " " << utente[r][1].c_str() << endl;
        if(utente[r][0] == nome){
            userfound = true;
            if(strcmp(utente[r][1].c_str(), passwd.c_str()) != -1) {
                cout << "Hai loggato come: " << nome << endl;
                utente_lg[0] = nome;
                utente_lg[1] = passwd;
                utente_lg[2] = utente[r][2];
                return true;
            } else {
                cout << "Password errata" <<endl;
            }
        }
    } 
    if(!userfound){
        cout << "Utente non trovato." << endl;
    }
    return false;
}



void modifica_conto(string nome, double nuovo_valore){
    
    fstream _utenti;
    _utenti.open("utenti.txt", fstream::in | fstream::out);
    vector<string> list;
    string line;
    int numero_linee = numerolinee();
    string utente[numero_linee+1][3];
    while(getline(_utenti, line)){
        list.push_back(line);
    }
    for(int r = 0; r < numero_linee; r++){
        //cout << list[r] << endl;
        splitstring(utente[r], list[r]);
    }
    for(int r = 0; r < numero_linee; r++){
        //cout << "Debug: Before update - " << utente[r][0][0] << " " << utente[r][2] << endl;
        string to_compare = "";
        if(r > 0) {
            for(int i = 1; i < utente[r][0].length(); ++i){
                to_compare += utente[r][0][i];
            }
        } else {
            to_compare = utente[r][0];
        }
        if(to_compare == nome) {
            //cout << "Debug: After update - " << utente[r][0] << " " << utente[r][2] << endl;
                utente[r][2] = to_string(nuovo_valore);
                break;
        }   
        
    }
    _utenti.close();
    _utenti.open("utenti.txt", fstream::out);
    for(int r = 0; r < numero_linee; r++){
        for(int c = 0; c < 3; c++) {
            bool flag = true ? utente[r][0][0] == *"\0" : false;
            if(flag) utente[r][0].erase(0, 1);
            
            //cout << "Debug: lenght utenterc " << utente[r][0] << ": "<< utente[r][0].length() << endl;
            _utenti << utente[r][c] << " ";
        }
        _utenti << endl;
    }
    
    
}

void preleva(user& utente) {
    double soldi_da_prelevare;
    cout << "Quanti soldi vuoi prelevare?\n-->";
    cin >> soldi_da_prelevare;
    if(soldi_da_prelevare > utente.conto_bancario) {
        cout << "Mi dispiace, non hai abbastanza soldi nel conto." << endl;
    } else {
        utente.conto_bancario -= soldi_da_prelevare;
        modifica_conto(utente.nome, utente.conto_bancario);
    }
}
void versa(user& utente) {
    double soldi_da_versare;
    cout << "Quanti soldi vuoi versare?\n-->";
    cin >> soldi_da_versare;
    if(soldi_da_versare <= 0) {
        cout << "Puoi versare solo un numero positivo di soldi." << endl;
    } else {
        utente.conto_bancario += soldi_da_versare;
        modifica_conto(utente.nome, utente.conto_bancario);
    }
}
int main(){
    int scelta;
    string utente_loggato[3];
    user utente;
    bool has_logged = false;
    bool running = true;
    while(running){
        while(!has_logged){
            if(_utenti.is_open()) {
                cout << "Seleziona una operazione:\n[1] NUOVO UTENTE\n[2] LOGIN\n[3] ESCI\n-->";
                cin >> scelta;
                if(scelta == 1) {
                    nuovo_utente();
                } else if(scelta == 2) {
                    string line;
                    if(logged(utente_loggato)) {
                        utente.nome = utente_loggato[0];
                        utente.password = utente_loggato[1];
                        utente.conto_bancario = stoi(utente_loggato[2]);
                        has_logged = true;
                    }

                } else{
                    running = false;
                    has_logged = true;
                }
            }
        }
        while((has_logged) && (running)){
            cout << "Ciao " << utente.nome << "\nSoldi nel conto: " << utente.conto_bancario <<"$\nChe operazione vuoi eseguire?\n[1] PRELEVA\n[2] VERSA\n[3] ESCI\n--> ";
            cin >> scelta;
            if(scelta == 1) {
                preleva(utente);
            } else if(scelta == 2){
                versa(utente);
            } else{
                has_logged = false;
            }
        }
    }
    _utenti.close();
    return 0;
}