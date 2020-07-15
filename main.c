#include <iostream>
#include <vector>
#include <fstream>
int zaehlerEintrag = 0; 

// Struktur für Telefonbucheinträge
typedef struct {
	std::string name; 
	std::string telefonnummer; 
} Eintrag;

// Funktion zum Schreiben der Einträge in eine Textdatei 
void schreibeInDatei(std::vector<Eintrag> &telefonbuch) {
	std::ofstream ausDatei; 
	ausDatei.open("Telefonbuch.txt"); 
	for (int i = 0; i <= zaehlerEintrag-1; i++) {
		ausDatei << telefonbuch[i].name << " " << telefonbuch[i].telefonnummer << std::endl; 
	}
	ausDatei.close(); 
} 

// Funktion zum Anfügen eines Eintrags in das Telefonbuch
void einfuegenEintrag(std::vector<Eintrag> &telefonbuch) {
	// neuen leeren Eintrag erstellen
	telefonbuch.push_back(Eintrag());
	// dem Eintrag einen Namen hinzufügen
	std::string neuerName; 
	std::cout << std::endl; 
	std::cout << "Gib einen Namen ein: "; 
	std::cin >> neuerName;
	telefonbuch[zaehlerEintrag].name = neuerName; 
	// dem Eintrag eine Telefonnummer hinzufügen
	std::string neueTelefonnummer; 
	std::cout << "Gib eine Telefonnummer ein: "; 
	std::cin >> neueTelefonnummer;
	telefonbuch[zaehlerEintrag].telefonnummer = neueTelefonnummer;
	std::cout << std::endl;
	zaehlerEintrag++; 
	// Schreiben in Datei 
	schreibeInDatei(telefonbuch);
}

// Funktion zum Ausgeben des Telefonbuchs
void ausgebenTelefonbuch(std::vector<Eintrag> &telefonbuch) {
	std::cout << std::endl; 
	for (int i = 0; i <= zaehlerEintrag-1; i++) {
		std::cout << telefonbuch[i].name << ", " << telefonbuch[i].telefonnummer << std::endl;
	}
	std::cout << std::endl; 
}

// Funktion zum Lesen der Einträge aus Datei
void leseVonDatei(std::vector<Eintrag> &telefonbuch) {
	std::ifstream inDatei; 
	inDatei.open("Telefonbuch.txt"); 
	// Prüfen ob Datei vorhanden 
	if (!inDatei) {
		std::cerr << "Error: Kann Datei 'Telefonbuch.txt' nicht finden"; 
		exit(1); 
	}
	// Lesevorgang
	std::string text;
	int zaehlerTyp = 1; // gerade -> Name; ungerade -> Telefonnummer
	while (inDatei >> text) {
		if (zaehlerTyp%2 == 1) {
			telefonbuch.push_back(Eintrag());
			telefonbuch[zaehlerEintrag].name = text;
			zaehlerTyp++; 
			continue;
		}
		telefonbuch[zaehlerEintrag].telefonnummer = text; 
		zaehlerTyp++;
		zaehlerEintrag++;
	}
	inDatei.close(); 
}

// Funktion zum Suchen einer Nummer von einem Namen 
void sucheNummer(std::vector<Eintrag> telefonbuch) {
	std::string zuSuchenderName; 
	// Abfrage 
	std::cout << "\nDie Nummer wessen Namen suchen Sie? "; 
	std::cin >> zuSuchenderName;
	for (int i = 0; i <= zaehlerEintrag-1; i++) {
		if (telefonbuch[i].name == zuSuchenderName) {
			std::cout << telefonbuch[i].telefonnummer << std::endl;
			std::cout << std::endl;
			return; 
		}
	}
	std::cout << "Zu diesem Namen konnte keine Nummer gefunden werden.\n" << std::endl;
}

int main(void) {
	// Anlegen des leeren Telefonbuch
	std::vector<Eintrag> telefonbuch;

	// Einlesen aus Datei 
	leseVonDatei(telefonbuch);

	// Hauptprogrammschleife
	bool run = true; 
	while(run) {
		std::cout << "--------------------------------------------------------------------\n\n";
		std::cout << "Was möchten Sie in Ihrem Telefonbuch tun?" << std::endl; 
		std::cout << std::endl; 
		std::cout << 
			"Eintrag in Telefonbuch einfügen (1)\n" << 
			"Nummer zu einem Namen suchen (2)\n" << 
			"Alle Einträge ausgeben (3)\n" << 
			"Programm beenden (4)\n" << std::endl; 
		int decision; 
		std::cin >> decision; 
		switch(decision) {
			case 1: einfuegenEintrag(telefonbuch); break; 
			case 2: sucheNummer(telefonbuch); break;
			case 3: ausgebenTelefonbuch(telefonbuch); break; 
			case 4: run = false;
		}
	}

	return 0; 
}
