#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cmath>

using namespace std;

struct Spesa {
    string categoria;
    double prezzo;
    bool entrata;
    bool uscita;
};

void menu (int &s);  // Funzione per visualizzare il menu delle operazioni
void fSwitch (int s, Spesa &spesa);  // Funzione per eseguire l'operazione scelta
void richiestaProdotto(Spesa &spesa);  // Funzione per richiedere i dati di una spesa e salvarli nel file di testo
void stampaEU (Spesa &spesa);  // Funzione per stampare il totale delle entrate e uscite 
void stampaEUCat (Spesa &spesa);  // Funzione per stampare il totale delle entrate e uscite per categoria
void portaMaiuscolo (char &lettera);  // Funzione per convertire una lettera minuscola in maiuscolo
void eliminaMovimento();  // Funzione per eliminare un movimento finanziario dal file di testo
void cercaMovimento();  // Funzione per cercare un movimento finanziario nel file di testo
void stampaPercentuali();  // Funzione per stampare le percentuali di entrate e uscite
void resetFile();  // Funzione per resettare il file di testo delle spese
bool contiene(const string& str, const string& sottostringa);// Funzione che verifica se una stringa contiene una sottostringa
string toLower(const string& str);// Funzione per convertire una stringa da maiuscolo a minuscolo

int main(){
    Spesa spesa; 
    int scelta=0;

    do{
        menu (scelta);
        fSwitch(scelta, spesa);
    }while(scelta!=0);

    return 0;
}

// Funzione per richiedere i dati di una nuova spesa e salvarli nel file di testo
void richiestaProdotto(Spesa &spesa){
    char s;
    string nomeFile = "spese.txt";
    ofstream file(nomeFile, ios::app);  // Apre il file in modalità append (sposta il cursore alla fine)

    if (!file) {
        cout<< "Errore nell'apertura del file." << endl;
        return;
    }

    cin.ignore();
    cout << "Inserisci la categoria della spesa: ";
    getline(cin, spesa.categoria);

    do{
        cout << "Inserisci il prezzo della spesa: ";
        cin >> spesa.prezzo;
        if(spesa.prezzo <= 0)
            cout << "Inserimento errato...riprovare." << endl;
    }while(spesa.prezzo <= 0);

    do{
        cout << "Inserisci 'U' per uscita oppure 'E' per entrata: ";
        cin >> s;
        if(islower(s)) 
            portaMaiuscolo(s);
        if (s != 'U' && s != 'E')
            cout << "Inserimento errato...riprovare!" << endl;
    }while (s != 'U' && s != 'E');

    spesa.uscita = (s == 'U');
    spesa.entrata = !spesa.uscita;

    file << "Categoria: " << spesa.categoria << "; prezzo: " << spesa.prezzo << "; ";
    file << (spesa.uscita ? "uscita." : "entrata.") << endl;

    file.close();
}

// Funzione per visualizzare il menu delle operazioni disponibili
void menu (int &s){
    cout << endl << "-----GESTORE DI FINANZA PERSONALE-----" << endl;
    cout << "1- Inserimento di un movimento finanziario." << endl;
    cout << "2- Eliminazione di un movimento finanziario." << endl;
    cout << "3- Cerca un movimento finanziario" << endl;
    cout << "4- Stampa delle entrate e delle uscite" << endl;
    cout << "5- Stampa delle entrate e delle uscite di una categoria." << endl;
    cout << "6- Stampa della percentuale delle entrate e uscite generali." << endl;
    cout << "7- Reset del file di testo." << endl;
    cout << "0- Esci." << endl;
    cout << "Inserire un numero per effettuare un'operazione: ";
    cin >> s;
    cout << endl;
}

// Funzione per eseguire l'operazione scelta nel menu
void fSwitch (int s, Spesa &spesa){
    switch (s)
    {
    case 1:
        richiestaProdotto(spesa);  // Inserimento di un nuovo movimento
        break;
    case 2:
        eliminaMovimento();  // Eliminazione di un movimento
        break;
    case 3:
        cercaMovimento();  // Ricerca di un movimento
        break;
    case 4:
        stampaEU(spesa);  // Stampa delle entrate e uscite totali
        break;
    case 5:
        stampaEUCat(spesa);  // Stampa delle entrate e uscite per categoria
        break;
    case 6:
        stampaPercentuali();  // Stampa delle percentuali di entrate e uscite
        break;
    case 7:
        resetFile();  // Resetta il file di testo
        break;
    default:
        if(s != 0)
            cout << "Inserimento errato...riprovare." << endl;
        break;
    }
}

// Funzione per stampare il totale delle entrate e uscite
void stampaEU(Spesa &spesa) {
    // Apre il file in modalità lettura
    ifstream file("spese.txt");

    if (!file) {
        cout << "Errore nell'aprire il file per la lettura." << endl;
        return;
    }

    string riga;
    double totaleEntrate = 0, totaleUscite = 0;

    // Legge ogni riga del file e calcola il totale di entrate e uscite
    while (getline(file, riga)) {
        int posPrezzo = riga.find("prezzo: ");
        if (posPrezzo >= 0 && posPrezzo < riga.length()) {
            string prezzoStr = riga.substr(posPrezzo + 8, riga.find(';', posPrezzo) - (posPrezzo + 8));
            double prezzo = stod(prezzoStr);

            if (contiene(riga, "entrata"))
                totaleEntrate += prezzo;
            else if (contiene(riga, "uscita"))
                totaleUscite += prezzo;
        }
    }

    // Stampa delle entrate e delle uscite totali

    cout << "Il totale delle entrate ammonta a: " << totaleEntrate << " euro." << endl;
    cout << "Il totale delle uscite ammonta a: " << totaleUscite << " euro." << endl;
}

// Funzione per stampare il totale delle entrate e uscite di una categoria specifica
void stampaEUCat(Spesa &spesa) {
    // Apre il file in modalità lettura
    ifstream file("spese.txt");

    if (!file) {
        cout << "Errore nell'apertura del file." << endl;
        return;
    }

    string categoria;
    double totale = 0.0; 
    string riga;

    // Richiede all'utente di inserire la categoria da cercare
    cout << "Inserisci la categoria per cui vuoi stampare il totale delle spese: ";
    cin.ignore();
    getline(cin, categoria);

    string categoriaLower = toLower(categoria);
    bool trovato = false;

    // Legge il file riga per riga
    while (getline(file, riga)) {
        // Trova la posizione della parola "Categoria: " nella riga
        int inizioCategoria = riga.find("Categoria: "); 
        // Trova la posizione della parola "prezzo: " nella riga
        int inizioPrezzo = riga.find("prezzo: ");

        // Se entrambe le parole "Categoria: " e "prezzo: " esistono nella riga
        if (inizioCategoria >= 0 && inizioCategoria < riga.length() && inizioPrezzo >= 0 && inizioPrezzo < riga.length()) {
            // Estrae la categoria dalla riga dopo "Categoria: "
            string cat = riga.substr(inizioCategoria + 10, riga.find(';', inizioCategoria) - (inizioCategoria + 10));
            // Rimuove eventuali spazi all'inizio della categoria
            while (!cat.empty() && cat[0] == ' ')  // Controlla se la categoria inizia con spazi
                cat.erase(0, 1);  // Rimuove il primo carattere che è uno spazio finché ci sono spazi
            // Estrae il prezzo dalla riga dopo "prezzo: "
            string prezzoStr = riga.substr(inizioPrezzo + 8, riga.find(';', inizioPrezzo) - (inizioPrezzo + 8));
            // Converte il prezzo da stringa a numero decimale di tipo double
            double prezzoLetto = stod(prezzoStr);

            if (toLower(cat) == categoriaLower) {
                trovato = true; 
                totale += prezzoLetto; 
            }
        }
    }

    file.close();

    if (trovato) {
        cout << "Il totale delle spese per la categoria '" << categoria << "' e': " << totale << " euro." << endl;
    } else {
        cout << "Non sono state trovate spese per la categoria '" << categoria << "'." << endl;
    }
}

// Funzione per convertire una lettera in maiuscolo
void portaMaiuscolo (char &lettera){
    lettera=toupper(lettera);
}

// Funzione per eliminare un movimento finanziario dal file
void eliminaMovimento() {
    ifstream fileIn("spese.txt");
    ofstream fileOut("temp.txt");


    if (!fileIn || !fileOut) {
        cout << "Errore nell'apertura del file." << endl;
        return; 
    }

    string categoria;  
    double prezzo;     
    string riga;       

    // Richiede all'utente di inserire la categoria della spesa da eliminare
    cin.ignore();
    cout << "Inserisci la categoria da eliminare: ";
    getline(cin, categoria);

    // Richiede all'utente di inserire il prezzo della spesa da eliminare
    cout << "Inserisci il prezzo da eliminare: ";
    cin >> prezzo;

    string categoriaLower = toLower(categoria);
    bool trovato = false;

    // Legge il file riga per riga
    while (getline(fileIn, riga)) {
        // Trova la posizione della parola "Categoria: " nella riga
        int inizioCategoria = riga.find("Categoria: ");
        // Trova la posizione della parola "prezzo: " nella riga
        int inizioPrezzo = riga.find("prezzo: ");

        // Se entrambe le parole "Categoria: " e "prezzo: " esistono nella riga
        if (inizioCategoria >= 0 && inizioCategoria < riga.length() && inizioPrezzo >= 0 && inizioPrezzo < riga.length()) {
            // Estrae la categoria dalla riga dopo "Categoria: "
            string cat = riga.substr(inizioCategoria + 10, riga.find(';', inizioCategoria) - (inizioCategoria + 10));
            // Rimuove eventuali spazi all'inizio della categoria
            while (!cat.empty() && cat[0] == ' ')  // Controlla se la categoria inizia con spazi
                cat.erase(0, 1);  // Rimuove il primo carattere che è uno spazio finché ci sono spazi
            // Estrae il prezzo dalla riga dopo "prezzo: "
            string prezzoStr = riga.substr(inizioPrezzo + 8, riga.find(';', inizioPrezzo) - (inizioPrezzo + 8));
            // Converte il prezzo da stringa a numero decimale di tipo double
            double prezzoLetto = stod(prezzoStr);

            /* Controlla se la categoria letta corrisponde a quella che l'utente vuole eliminare
            e se il prezzo corrisponde a quello fornito dall'utente. */
            if (toLower(cat) == categoriaLower && fabs(prezzoLetto - prezzo) < 0.01) {
                trovato = true;  // Se troviamo una corrispondenza, segniamo che il movimento è stato trovato
                continue;
            }
        }

        // Se la riga non corrisponde al movimento da eliminare, la scriviamo nel file temporaneo
        fileOut << riga << endl;
    }

    // Chiude entrambi i file (il file di input e il file di output)
    fileIn.close();
    fileOut.close();

    // Rimuove il file originale
    remove("spese.txt");
    // Rinomina il file temporaneo al nome originale del file di spese
    rename("temp.txt", "spese.txt");

    // Se è stato trovato e rimosso un movimento, lo comunica all'utente
    if (trovato)
        cout << "Movimento eliminato con successo." << endl;
    else
        cout << "Movimento non trovato." << endl;
}

// Funzione per cercare e stampare i movimenti di una categoria
void cercaMovimento() {
    // Apre il file di testo in modalità lettura
    ifstream file("spese.txt");
    if (!file) {
        cout << "Errore nell'apertura del file." << endl;
        return;
    }

    string categoria;
    cout << "Inserisci la categoria da cercare: ";
    cin.ignore();
    getline(cin, categoria); 
    string categoriaLower = toLower(categoria); 

    string riga;
    bool trovata = false;

    // Legge il file e stampa i movimenti che corrispondono alla categoria cercata
    while (getline(file, riga)) {
        int inizioCategoria = riga.find("Categoria: ");
        if (inizioCategoria >= 0 && inizioCategoria < riga.length()) {
            string cat = riga.substr(inizioCategoria + 10, riga.find(';', inizioCategoria) - (inizioCategoria + 10));
            while (!cat.empty() && cat[0] == ' ')  // Rimuove gli spazi iniziali
                cat.erase(0, 1);
            if (toLower(cat) == categoriaLower) {
                cout << riga << endl;
                trovata = true;
            }
        }
    }
    
    // Se non è stato trovato nessun movimento, viene informato l'utente
    if (!trovata)
        cout << "Nessun movimento trovato per la categoria." << endl;
}

// Funzione per stampare le percentuali di entrate e uscite rispetto al totale
void stampaPercentuali() {
    // Apre il file di testo in modalità lettura
    ifstream file("spese.txt");
    if (!file) {
        cout << "Errore nell'apertura del file." << endl;
        return;
    }

    string riga;
    double entrate = 0, uscite = 0;
    double totale=0;

    // Legge il file e calcola il totale di entrate e uscite
    while (getline(file, riga)) {
        int posPrezzo = riga.find("prezzo: ");
        if (posPrezzo >= 0 && posPrezzo < riga.length()) {
            string prezzoStr = riga.substr(posPrezzo + 8, riga.find(';', posPrezzo) - (posPrezzo + 8));
            double prezzo = stod(prezzoStr);
            if (contiene(riga, "entrata"))
                entrate += prezzo;
            else if (contiene(riga, "uscita"))
                uscite += prezzo;
        }
    }

    totale = entrate + uscite; // Variabile per memorizzare il totale 
    if (totale == 0) {
        cout << "Nessun movimento registrato." << endl;
        return;
    }

    // Calcola e stampa le percentuali di entrate e uscite
    cout << "Entrate: " << (entrate / totale) * 100 << "%" << endl;
    cout << "Uscite: " << (uscite / totale) * 100 << "%" << endl;
}

// Funzione per resettare il file delle spese
void resetFile() {
    ofstream file("spese.txt", ios::trunc);  // Apre il file in modalità di sovrascrittura (trunc serve a tronacre il contenuto)
    if (!file) {
        cout << "Errore nel reset del file." << endl;
        return;
    }
    cout << "File resettato con successo." << endl;
}

// Funzione che verifica se una stringa contiene una sottostringa
bool contiene(const string& str, const string& sottostringa) {
    return str.find(sottostringa) < str.length();
}

// Funzione per convertire una stringa in minuscolo
string toLower(const string& str) {
    string risultato = str;
    for (int i = 0; i < risultato.length(); ++i)
        risultato[i] = tolower(risultato[i]);
    return risultato;
}
