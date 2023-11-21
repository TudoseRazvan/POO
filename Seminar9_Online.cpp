/*
Sa se implementeze o clasa Spital, conform urmatoarelor cerinte:
clasa are cel putin urmatoarele atribute:
	* cif (cod de identificare fiscala) - valoare de tip sir de caractere - se atribuie valoarea la crearea obiectului si e nemodificabila
	* nume - sir de caractere
	* adresa - sir de caractere
	* medici - vector de siruri de char (vectori de valori string alocat dinamic)
	* nrMedici
	* nrSpitale - va retine nr de obiecte de tip spital instantiate vreodata - static int

	Se vor implementa:
	-constructor fara parametri
	-constructor cu toti parametrii neceseari instantierii unui obiect complet
	-constructori de copiere
	-destructor

	-supraincarcare operator=
	-supraincarcare operator de citire << si  scriere >> din/in consola
	-supraincarcare op [] - returneaza medicul de pe o pozitie data - atat in mod scriere cat si in mod citire
	-supraincarcare operator!
	-cast explicit int - returneaza numarul de spitale instantiate

	-metode de get si set
	-cel putin unul dintre dintre atributele de tip sir de char trebuie sa fie de tip char*
	-toate atributele trebuie sa fie private
*/
#include <iostream>
#include <string>

using namespace std;

class Spital {
private:
	const string cif;
	char* nume;
	string adresa;
	string* medici;
	int nrMedici;
	static int nrSpitale;
public:
	//Constructor fara parametrii
	Spital() :cif("") {
		this->nume = nullptr;
		this->adresa = "";
		this->medici = nullptr;
		this->nrMedici = 0;
		Spital::nrSpitale++;
	}
	//Constructor cu toti parametrii
	Spital(string _cif, const char* _nume, string _adresa, string* _medici, int _nrMedici)
		:cif(_cif), adresa(_adresa), nrMedici(_nrMedici) {
		if (_nume != nullptr) {
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else
			this->nume = nullptr;
		this->medici = new string[_nrMedici];
		for (int i = 0; i < _nrMedici;i++) {
			this->medici[i] = _medici[i];
		}
		Spital::nrSpitale++;
	}
	//Constructor de copiere
	Spital(Spital& s)
		:Spital(s.cif, s.nume, s.adresa, s.medici, s.nrMedici) {
		//Spital::nrSpitale--;
	}

	//Destructor
	~Spital() {
		delete[] this->nume;
		delete[] this->medici;
		Spital::nrSpitale--; //Daca cerinte ar fi ca nrSpitale sa retina spitalele active (obiecte instantiate care nu au fost sterse)

	}

	Spital& operator=(const Spital& s) {
		if (this == &s)
			return *this; //Verifica auto-assignment-ul

		delete[] this->nume;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);

		delete[] this->medici;
		this->nrMedici = s.nrMedici;
		this->medici = new string[s.nrMedici];
		for (int i = 0; i < s.nrMedici; i++) {
			this->medici[i] = s.medici[i];
		}

		this->adresa = s.adresa;

		return *this;
	}

	void setNume(const char* _nume) {
		if (_nume != nullptr)
		{
			delete[] this->nume;
			this->nume = new char[strlen(_nume) + 1];
			strcpy_s(this->nume, strlen(_nume) + 1, _nume);
		}
		else
			this->nume = nullptr;
	}

	void setAdresa(string _adresa) {
		this->adresa = _adresa;
	}

	void setMedici(const string* _medici, int _nrMedici) {
		if (_medici != nullptr && _nrMedici > 0) {
			delete[] this->medici;
			this->medici = new string[_nrMedici];
			for (int i = 0; i < _nrMedici; i++) {
				this->medici[i] = _medici[i];
			}
		}
		else {
			this->medici = nullptr;
			this->nrMedici = 0;
		}
	}

	char* getNume() {
		char* buff = new char[strlen(this->nume) + 1];
		strcpy_s(buff, strlen(this->nume) + 1, this->nume);
		return buff;
	}

	string getCIF() {
		return cif;
	}

	friend ostream& operator<<(ostream& os, Spital s);
	friend istream& operator>>(istream& is, Spital& s);

};

int Spital::nrSpitale = 0; // pt ca e static

ostream& operator<<(ostream& os, Spital s) {
	os << "CIF: " << s.cif << endl;
	os << "Nume: " << s.nume << endl;
	os << "Adresa: " << s.adresa << endl;
	os << "Nr medici: " << s.nrMedici << endl;
	for (int i = 0; i < s.nrMedici;i++)
		os << s.medici[i] << "   ";
	return os;
}

istream& operator>>(istream& is, Spital& s) {
	char* temp = new char[256];
	cout << "Nume: " << endl;
	is.getline(temp, 256);
	s.setNume(temp);
	cout << "Adresa: " << endl;
	is.getline(temp, 256);
	s.setAdresa(temp);
	cout << "Numar medici: ";
	is >> s.nrMedici;
	is.getline(temp, 256);

	cout << "Medici: " << endl;

	int tempNr;
	is >> tempNr;
	is.getline(temp, 256);

	string* medici = new string[tempNr];
	for (int i = 0;i < tempNr;i++) {
		is.getline(temp, 256);
		medici[i] = (string)temp; //cast;
	}
	s.setMedici(medici, tempNr);
	return is;
}


int main()
{
	string* medici = new string[3];
	medici[0] = "Medic 1";
	medici[1] = "Medic 2";
	medici[2] = "Medic 3";

	Spital s1, s2("RO1234", "Floreasca", "Bucuresti", medici, 3);

	s2 = s2; //auto-assignment

	s1 = s2;
	s1.setNume("Alt nume");


	cout << s2;
	Spital s3;

	Spital s4 = s2;
	cin >> s3;

	//cout << endl << (int)s3;

	return 0;
}