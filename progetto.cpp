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
double differenzaEU (Spesa &spesa); //fa la differenza tra entrate e uscite
void stampaDifferenzaEU (double diff); //stampa differenza entrate e uscite
void stampaEUCat (Spesa &spesa); //stampa entrate e uscite per categoria
double differenzaEUCat (Spesa &spesa, string cat); //fa la differenza tra entrate e uscite di una categoria
void stampaDifferenzaEUCat (double diff, string cat); //stampa differenza entrate e uscite
  

int main(){
    Spesa spesa;
    int scelta=0;

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

    cout<<endl<<"-----GESTORE DI SPESE PERSONALI-----"<<endl;
    cout<<"1- Inserimento di un prodotto."<<endl;
    cout<<"2- Stampa delle entrate e delle uscite"<<endl;
    cout<<"3- Stampa differenza tra entrate e uscite"<<endl;
    cout<<"4- Stampa delle entrate e delle uscite di una categoria."<<endl;
    cout<<"5- Stampa differenza tra entrate e uscite di una categoria."<<endl;
    cout<<"6- Stampa della percentuale delle entrate e uscite di una categoria."<<endl;
    cout<<"0- Esci."<<endl;
    cout<<"Inserire un numero per effetuare un'operazione: ";
    cin>>s;
    cout<<endl;
}

void fSwitch (int s, Spesa &spesa){
    double diff=0;
    string categoria;

    switch (s)
    {
    case 1:
        richiestaProdotto(spesa);
        break;
    case 2:
        stampaEU (spesa);
        break;
    case 3:
        diff=differenzaEU(spesa);
        stampaDifferenzaEU(diff);
        break;
    case 4:
        stampaEUCat (spesa);
        break;
    case 5:
        differenzaEUCat (spesa, categoria);
        stampaDifferenzaEUCat (diff, categoria);
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

double differenzaEU (Spesa &spesa){
    double entrate=0, uscite=0, diff=0;

    if(spesa.entrata)
        entrate+=spesa.prezzo;
    else if(spesa.uscita)
        uscite+=spesa.prezzo;
    
    diff=entrate-uscite;


    

    return diff;
}

void stampaDifferenzaEU (double diff){
    cout<<"La differenza tra le entrate e le uscite è di: "<<diff<<" euro"<<endl;
}

void stampaEUCat (Spesa &spesa){
    string cat;

    do{
        cout<<"Inserisci il nome della categoria da cercare: ";
        cin>>cat;
        if(cat!=spesa.categoria)
            cout<<"Inserimento errato...riprova."<<endl;
    }while(cat!=spesa.categoria);

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

double differenzaEUCat (Spesa &spesa, string cat){
    double entrate=0, uscite=0, diff=0;
    
    do{
        cout<<"Inserisci il nome della categoria da cercare: ";
        cin>>cat;
        if(cat!=spesa.categoria)
            cout<<"Inserimento errato...riprova."<<endl;
    }while(cat!=spesa.categoria);

    if(spesa.entrata)
        entrate+=spesa.prezzo;
    else if(spesa.uscita)
        uscite+=spesa.prezzo;
    
    diff=entrate-uscite;    

    return diff;
}

void stampaDifferenzaEUCat (double diff, string cat){
    cout<<"La differenza tra le entrate e le uscite della categoria: "<<cat<<" è di: "<<diff<<" euro"<<endl;
}

