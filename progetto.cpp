#include <iostream>
#include <fstream>

using namespace std;

struct Spesa
{
    string categoria;
    double prezzo;
    bool entrata;
    bool uscita;
};


void richiestaProdotto(string oldFile);
void salvaFile(string nomeFile, string oldFile);

int main(){
    string oldFile = "speseOld.txt";
    richiestaProdotto(oldFile);

    return 0;
}

void richiestaProdotto(string oldFile){
    Spesa spesa;
    string nomeFile = "spese.txt";
    ofstream file(nomeFile);
    char s;

    if (!file) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    cout << "Inserisci la categoria della spesa: ";
    getline(cin, spesa.categoria);

    cout << "Inserisci il prezzo della spesa: ";
    cin >> spesa.prezzo;

    do{
        cout << "Inserisci 'U' se la spesa e' un'uscita oppure 'E' se è un'entrata: ";
        cin >> s;
        if (s!='U' && s!='E')
            cout << "Inserimento errato...riprova!"<<endl;
    }while (s!='U' && s!='E');

    if(s=='U'){
        spesa.uscita=true;
        spesa.entrata=false;
    }
    else{
        spesa.uscita=false;
        spesa.entrata=true;
    }

    if(spesa.uscita)
        file <<"Categoria: "<<spesa.categoria << "; prezzo: " << spesa.prezzo << "; uscita." << endl;
    else if(spesa.entrata)
        file <<"Categoria: "<<spesa.categoria << "; prezzo: " << spesa.prezzo << "; entrata." << endl;

    salvaFile(nomeFile, oldFile);

    file.close();
}

void salvaFile(string nomeFile, string oldFile) {
    ifstream file(nomeFile);
    ofstream oldFileStream(oldFile);
    string line, oldLine;

    if (!file || !oldFileStream) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    while (getline(file, oldLine)) {
        getline(file, line);
        oldFileStream << oldLine << endl << line << endl;
    }

    file.close();
    oldFileStream.close();

    cout << "File salvato correttamente in " << oldFile << endl;
}