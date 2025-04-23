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


void inserimentoProdoto();
void menu (int s);
void fSwitch (int s);
void stampaEU ();

void richiestaProdotto();
void salvaFile(string nomeFile);

int main(){
    int scelta=0;

    do{
        menu (scelta);
        fSwitch(scelta);
    }while(scelta!=0);

    

    return 0;
}

void inserimentoProdoto(){
    Spesa spesa;
    string nomeFile = "spese.txt";
    ofstream file(nomeFile);
    char s;

    if (!file) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    cout << "Inserisci la categoria della spesa: ";
    cin >> spesa.categoria;

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
        salvaFile(nomeFile);
    file.close();
}

void menu (int s){

    cout<<"Inserire un numero per effetuare un'operazione: "<<endl;
    cout<<"1- Inserimento di un prodotto."<<endl;
    cout<<"2- Stampa delle entrate e delle uscite mensili."<<endl;
    cout<<"3- Stampa differenza tra entrate e uscite mensili."<<endl;
    cout<<"4- Stampa delle entrate e delle uscite mensili di una categoria."<<endl;
    cout<<"5- Stampa differenza tra entrate e uscite mensili di una categoria."<<endl;
    cout<<"6- Stampa della percentuale delle entrate e uscite di una categoria."<<endl;
    cout<<"0- Esci."<<endl;
    cin>>s;
}

void fSwitch (int s){

    switch (s)
    {
    case 1:
        inserimentoProdoto ();
        break;
    case 2:
        inserimentoProdoto ();
        break;
    case 3:
        inserimentoProdoto ();
        break;
    case 4:
        inserimentoProdoto ();
        break;
    case 5:
        inserimentoProdoto ();
        break;
    case 6:
        inserimentoProdoto ();
        break;
    
    default:
        break;
    }
}
void salvaFile(string nomeFile){
    string testoFile;
    ifstream file(nomeFile);
    while(getline(file, testoFile)){
        cout<<testoFile;
    }
}