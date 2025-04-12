#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Spesa
{
    string categoria;
    float prezzo;
    bool entrata;
    bool uscita;
};


void richiestaProdotto();

int main(){

    return 0;
}

void richiestaProdotto(Spesa spesa){
    string nomeFile = "spese.txt";
    ofstream file(nomeFile);

    if (!file) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    cout << "Inserisci la descrizione della spesa: ";
    cin >> spesa.categoria;

    cout << "Inserisci il prezzo della spesa: ";
    cin >> spesa.prezzo;

    file << spesa.categoria << " " << spesa.prezzo << endl;

    file.close();
}