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
void fSwitch (int s, Spesa &spesa); //funzione con lo switch
void richiestaProdotto(Spesa &spesa);
void stampaEU (Spesa &spesa); //stampa totale entrata e uscite
  

int main(){
    ofstream file("spese.txt", ios::app);
    Spesa spesa;
    int scelta=0;
    string oldFile = "speseOld.txt";

    do{
        menu (scelta);
        fSwitch(scelta, spesa);
    }while(scelta!=0);

    return 0;
}

void richiestaProdotto(Spesa &spesa){
    string nomeFile = "spese.txt";
    ofstream file(nomeFile, ios::app);
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

void fSwitch (int s, Spesa &spesa){

    switch (s)
    {
    case 1:
        richiestaProdotto(spesa);
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



void stampaEU (Spesa &spesa){
    ifstream MyReadFile("spese.txt");

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