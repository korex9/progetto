#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cmath>

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
void stampaEUCat (Spesa &spesa); //stampa entrate e uscite per categoria
void portaMaiuscolo (char &lettera); //porta la lettera che indentifica il tipo in maiuscolo
void eliminazione (Spesa &spesa); //eliminazione di una spesa
//void ricerca (Spesa &spesa);
int main(){
    Spesa spesa;
    int scelta=0;

    do{
        menu (scelta);
        fSwitch(scelta, spesa);
    }while(scelta!=0);

    return 0;
}

void menu (int &s){

    cout<<endl<<"-----GESTORE DI FINANZA PERSONALE-----"<<endl;
    cout<<"1- Inserimento di un movimento finanziario."<<endl;
    cout<<"2- Eliminazione di un movimento finanziario."<<endl;
    cout<<"3- Cerca un movimento finanziario"<<endl;
    cout<<"4- Stampa delle entrate e delle uscite"<<endl;
    cout<<"5- Stampa delle entrate e delle uscite di una categoria."<<endl;
    cout<<"6- Stampa della percentuale delle entrate e uscite generali."<<endl;
    cout<<"7- Reset del file di testo."<<endl;
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
        eliminazione (spesa);
        break;
    case 3:
        //ricerca
        break;
    case 4:
        stampaEU (spesa);
        break;
    case 5:
        stampaEUCat (spesa);
        break;
    case 6:
        //percentuale EU
        break;
    case 7:
        //reset
        break;
    default:
        if(s!=0)
            cout<<"Inserimento errato...riprova."<<endl;
        break;
    }
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
    cout << "Inserisci la categoria del movimento: ";
    getline(cin, spesa.categoria);

    do{
        cout << "Inserisci il totale del movimento: ";
        cin>> spesa.prezzo;
        if(spesa.prezzo<=0)
            cout<<"Inserimento errato...riprova."<<endl;
    }while(spesa.prezzo<=0);

    do{
        cout << "Inserisci 'U' se il movimento e' un'uscita oppure 'E' se e' un'entrata: ";
        cin >> s;
        portaMaiuscolo (s);
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

    //scrive nel file
    if(spesa.uscita)
        file <<"Categoria: "<<spesa.categoria << "; prezzo: " << spesa.prezzo << "; uscita." << endl;
    else if(spesa.entrata)
        file <<"Categoria: "<<spesa.categoria << "; prezzo: " << spesa.prezzo << "; entrata." << endl;


    file.close();
}




void stampaEU(Spesa &spesa) {
    ifstream file("spese.txt");
    if (!file) {
        cout << "Errore nell'aprire il file per la lettura." << endl;
        return;
    }

    string riga;
    double totaleEntrate = 0, totaleUscite = 0;

    while (getline(file, riga)) {
        int pos = -1;

        // Cerca "prezzo: " a mano
        for (int i = 0; i < riga.length() - 7; i++) {
            if (riga[i] == 'p' &&
                riga[i+1] == 'r' &&
                riga[i+2] == 'e' &&
                riga[i+3] == 'z' &&
                riga[i+4] == 'z' &&
                riga[i+5] == 'o' &&
                riga[i+6] == ':' &&
                riga[i+7] == ' ') {
                pos = i + 8;
            }
        }



        // Legge i caratteri del numero
        string numero = "";
        while (pos < riga.length() && riga[pos] != ';' && riga[pos] != ' ') {
            numero += riga[pos];
            pos++;
        }

        double prezzo = atof(numero.c_str());

        // Verifica se la riga finisce con "entrata." o "uscita." a mano
        int len = riga.length();
        if (len >= 8 &&
            riga[len - 8] == 'e' &&
            riga[len - 7] == 'n' &&
            riga[len - 6] == 't' &&
            riga[len - 5] == 'r' &&
            riga[len - 4] == 'a' &&
            riga[len - 3] == 't' &&
            riga[len - 2] == 'a' &&
            riga[len - 1] == '.') {
            totaleEntrate += prezzo;
        } else if (len >= 8 &&
                   riga[len - 8] == 'u' &&
                   riga[len - 7] == 's' &&
                   riga[len - 6] == 'c' &&
                   riga[len - 5] == 'i' &&
                   riga[len - 4] == 't' &&
                   riga[len - 3] == 'a' &&
                   riga[len - 2] == '.' &&
                   riga[len - 1] == '\0') {
            totaleUscite += prezzo;
        } else if (len >= 7 &&
                   riga[len - 7] == 'u' &&
                   riga[len - 6] == 's' &&
                   riga[len - 5] == 'c' &&
                   riga[len - 4] == 'i' &&
                   riga[len - 3] == 't' &&
                   riga[len - 2] == 'a' &&
                   riga[len - 1] == '.') {
            totaleUscite += prezzo;
        }
    }

    cout << "Il totale delle entrate ammonta a: " << totaleEntrate << " euro." << endl;
    cout << "Il totale delle uscite ammonta a: " << totaleUscite << " euro." << endl;
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

void portaMaiuscolo (char &lettera){
    if(islower(lettera))
        lettera=toupper(lettera);
}

void eliminazione (Spesa &spesa){
    ifstream file("spese.txt");
    if (!file) {
        cout<<"Errore nell'aprire il file per la lettura."<<endl;
        return;
    }

    string sceltaCat, tipo;
    double sceltaPrezzo;
    char s;

    cin.ignore();

    //Categoria
    do {
        cout<<"Inserisci la categoria del movimento da eliminare: ";
        getline(cin, sceltaCat);
        if (sceltaCat.empty())
            cout<<"La categoria non puo' essere vuota. Riprova."<<endl;
    } while (sceltaCat.empty());

    //Prezzo
    do{
        cout<<"Inserisci il prezzo del movimento da eliminare: ";
        cin>>sceltaPrezzo;
        if(sceltaPrezzo<=0)
            cout<<"Inserimento errato...riprova."<<endl;
    }while(sceltaPrezzo<=0);

    //Tipo
    do {
        cout <<"La spesa da eliminare e' un'entrata (E) o un'uscita (U)?";
        cin>>s;
        portaMaiuscolo(s);
        if (s!='E' && s!='U')
            cout<<"Inserimento errato...riprova."<<endl;
    } while (s!='E' && s!='U');

    if (s=='E')
        tipo="entrata.";
    else
        tipo="uscita.";

    ofstream temp("temp.txt");
    string riga;
    bool movimentoTrovato=false;

    while (getline(file, riga)) {
        size_t posPrezzo = riga.find("prezzo: ");
        size_t posTipo = riga.find("; ", posPrezzo);
        string prezzoStr = riga.substr(posPrezzo + 8, posTipo - (posPrezzo + 8));
        double prezzoLetto = atof(prezzoStr.c_str());

        if (riga.find("Categoria: " + sceltaCat) != string::npos && fabs(prezzoLetto - sceltaPrezzo) < 0.01 && riga.find(tipo) != string::npos && !movimentoTrovato) {
            movimentoTrovato = true;
            continue;
        }

        temp << riga << endl;
    }

    file.close();
    temp.close();

    remove("spese.txt");
    rename("temp.txt", "spese.txt");

    if (movimentoTrovato)
        cout << "Movimento eliminato correttamente." << endl;
    else
        cout << "Movimento non trovato." << endl;
}


