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

void menu (int &s); //menù per le scelte
void fSwitch (int s, string oldFile, Spesa &spesa); //funzione con lo switch
void richiestaProdotto(string oldFile, Spesa &spesa);
void stampaEU (Spesa &spesa); //stampa totale entrata e uscite
void salvaFile(string nomeFile, string oldFile);

int main(){
    Spesa spesa;
    int scelta=0;
    string oldFile = "speseOld.txt";

    do{
        menu (scelta);
        fSwitch(scelta, oldFile, spesa);
    }while(scelta!=0);

    return 0;
}

void richiestaProdotto(string oldFile, Spesa &spesa){
    string nomeFile = "spese.txt";
    ofstream file(nomeFile);
    char s;

    if (!file) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    cin.ignore();
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

void menu (int &s){

    cout<<"-----GESTORE DI SPESE PERSONALI-----"<<endl;
    cout<<"1- Inserimento di un prodotto."<<endl;
    cout<<"2- Stampa delle entrate e delle uscite mensili."<<endl;
    cout<<"3- Stampa differenza tra entrate e uscite mensili."<<endl;
    cout<<"4- Stampa delle entrate e delle uscite mensili di una categoria."<<endl;
    cout<<"5- Stampa differenza tra entrate e uscite mensili di una categoria."<<endl;
    cout<<"6- Stampa della percentuale delle entrate e uscite di una categoria."<<endl;
    cout<<"0- Esci."<<endl;
    cout<<"Inserire un numero per effetuare un'operazione: ";
    cin>>s;
    cout<<endl;
}

void fSwitch (int s, string oldFile, Spesa &spesa){

    switch (s)
    {
    case 1:
        richiestaProdotto(oldFile, spesa);
        break;
    case 2:
        stampaEU (spesa);
        break;
    case 3:
        
        break;
    case 4:
        
        break;
    case 5:
       
        break;
    case 6:
        
        break;
    
    default:
        break;
    }
}

void salvaFile(string nomeFile, string oldFile) {
    ifstream file(nomeFile);
    ofstream oldFileStream(oldFile);
    string line, oldLine;

    cout<<endl;

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

void stampaEU (Spesa &spesa){

    cout<<"Il totale delle entrate ammonta a: "<<endl;
    if(spesa.entrata){
        cout<<spesa.prezzo;
    }
    cout<<" euro."<<endl;

    cout<<"Il totale delle uscite ammonta a: "<<endl;
    if(spesa.uscita){
        cout<<spesa.prezzo;
    }
    cout<<" euro."<<endl;

    cout<<endl;
    

}