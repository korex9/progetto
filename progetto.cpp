#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Spesa
{
    string descrizione;
    float prezzo;
};


void richiestaProdotto();

int main(){

    return 0;
}

void richiestaProdotto(){
    Spesa spesa;
    string nomeFile = "spese.txt";
    ofstream file(nomeFile);

    if (!file) {
        cerr << "Errore nell'apertura del file." << endl;
        return;
    }

    cout << "Inserisci la descrizione della spesa: ";
    cin >> spesa.descrizione;

    cout << "Inserisci il prezzo della spesa: ";
    cin >> spesa.prezzo;

    file << spesa.descrizione << " " << spesa.prezzo << endl;

    file.close();
}