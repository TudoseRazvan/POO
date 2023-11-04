#include <iostream>
#include <string>
#include <cstring>

using namespace std;

enum finantare
{
	TAXA = 1,
	BUGET = 2,
	BUGET_BURSA = 3
};


class Carte
{
public:

	Carte()
	{

	}

	Carte(const char* _titlu, const char* _autor, double _pret, int _nr_pagini, int* cuv_per_pagina, bool _electronica = 0) :
		electronica(_electronica), pret(_pret), nr_pagini(_nr_pagini)
	{
		titlu = new char[strlen(_titlu) + 1];
		strcpy_s(titlu, strlen(_titlu) + 1, _titlu);

		autor = new char[strlen(_autor) + 1];
		strcpy_s(autor, strlen(_autor) + 1, _autor);

		this->nr_cuvinte_pagina = new int[nr_pagini];

		for (int i = 0; i < nr_pagini; i++)
		{
			this->nr_cuvinte_pagina[i] = cuv_per_pagina[i];
		}
	}

	Carte(const Carte& carte)
	{
		this->electronica = carte.electronica;
		this->nr_pagini = carte.nr_pagini;
		this->pret = carte.pret;

		this->titlu = new char[strlen(carte.titlu) + 1];
		strcpy_s(titlu, strlen(carte.titlu) + 1, carte.titlu);

		this->autor = new char[strlen(carte.autor) + 1];
		strcpy_s(autor, strlen(carte.autor) + 1, carte.autor);

		nr_cuvinte_pagina = new int[nr_pagini];

		for (int i = 0; i < this->nr_pagini; i++)
		{
			this->nr_cuvinte_pagina[i] = carte.nr_cuvinte_pagina[i];
		}

	}

	void setTitlu(char* _titlu) {
		this->titlu = new char[strlen(_titlu) + 1];
		strcpy_s(titlu, strlen(_titlu) + 1, _titlu);
	}

	void setAutor(char* _autor) {
		autor = new char[strlen(_autor) + 1];
		strcpy_s(titlu, strlen(_autor) + 1, _autor);
	}

	void setPret(double _pret)
	{
		this->pret = _pret;
	}

	void pretElectronica(bool _elec)
	{
		this->electronica = _elec;
	}

	void setPagini(int _nr_pagini, int* cuv_per_pagina)
	{
		this->nr_cuvinte_pagina = new int[nr_pagini];

		for (int i = 0; i < nr_pagini; i++)
		{
			this->nr_cuvinte_pagina[i] = cuv_per_pagina[i];
		}
	}

	char* getTitlu() { return this->titlu; }
	char* getAutor() { return this->autor; }
	int* getNrCuv() { return this->nr_cuvinte_pagina; }
	bool getElec() { return this->electronica; }
	int getPag() { return this->nr_pagini; }

	~Carte()
	{
		delete[] titlu;
		delete[] autor;
		delete[] nr_cuvinte_pagina;
	}

private:
	char* titlu;
	char* autor;
	bool electronica;
	int nr_pagini;
	int* nr_cuvinte_pagina;
	double pret;
};

/* Cerinte
set ,get toate atrib
constructor parametrii
constructor de copiere
*/

class Student
{
public:
	string nume;
	char* adresa;
	int varsta;
	int an_studii;

	//constructori
	Student()
	{

	}




	Student(string _nume, char* _adresa, int _varsta, int _an_studii, int* _note, int _numar_materii, string _numar_matricol, finantare _finantare) :
		nume(_nume), varsta(_varsta), an_studii(_an_studii), numar_matricol(_numar_matricol), finantare(_finantare), numar_materii(_numar_materii)
	{
		//care este diferenta?
		// 
		//this->adresa = _adresa;

		this->adresa = new char[strlen(_adresa) + 1];
		strcpy_s(this->adresa, strlen(_adresa) + 1, _adresa);

		this->note = new int[_numar_materii];
		for (int index = 0; index < _numar_materii; index++)
		{
			this->note[index] = _note[index];
		}
	}

	// Implementarea constructorului de copiere va rezolva problema care genereaza exceptiile lansate la executia destructorului - incercarea de a 
				//dezaloca a doua oara aceeasi zona de memorie care a fost anterior dezalocata
	// Aceasta implementare apeleazza constructorul cu parametri. In cadrul constructorului cu parametri alocarea memoriei este facuta corect pentru cele doua variabile membre de tip pointer

	/*
	Student(const Student& student):
		Student(student.nume, student.adresa, student.varsta, student.an_studii, student.note, student.numar_materii, student.numar_matricol, student.finantare)
	{

	}
	*/

	//Sa se implementeze constructorul de copiere fara a apela constructorul cu parametri astfel incat:
   //				- copierea valorilor (in noul obiect) sa se realizeze corect  
   //              - dezalocarea memoriei sa se realizeze fara a genera exceptii


	Student(const Student& Stud)
	{
		this->nume = Stud.nume;
		this->varsta = Stud.varsta;
		this->an_studii = Stud.an_studii;
		this->set_finantare(Stud.finantare);
		this->set_numar_matricol(Stud.numar_matricol);

		this->adresa = new char[strlen(Stud.adresa) + 1];
		strcpy_s(this->adresa, strlen(Stud.adresa) + 1, Stud.adresa);

		this->note = new int[Stud.numar_materii];

		int* _note = Stud.note;
		for (int index = 0; index < Stud.numar_materii; index++)
		{
			this->note[index] = _note[index];
		}
	}


	//setters
	void set_note(int* _note, int _numar_materii)
	{
		this->numar_materii = _numar_materii;
		//this->note = _note;

		this->note = new int[_numar_materii];
		for (int index = 0; index < _numar_materii; index++)
		{
			this->note[index] = _note[index];
		}
	}

	void set_numar_matricol(string _nr_matricol)
	{
		this->numar_matricol = _nr_matricol;
	}

	void set_finantare(finantare _finantare)
	{
		this->finantare = _finantare;
	}


	//getters
	int* get_note() { return this->note; }
	string get_numar_matricol() { return this->numar_matricol; }
	finantare get_finantare() { return this->finantare; }
	int get_numar_materii() { return this->numar_materii; }


	//destructor
	~Student()
	{
		delete[] this->adresa;
		delete[] this->note;
	}
private:
	int* note;
	string numar_matricol;
	finantare finantare;
	int numar_materii;


};


//exemple vizibilitate - constructori/destructori/metode/atribute
//exemplu constructor de copiere

int main()
{
	Student s0;

	s0.nume = "Anghel Mihai";

	s0.adresa = new char[20];
	strcpy_s(s0.adresa, 20, "Bucuresti, Sector 1");

	s0.varsta = 21;
	s0.an_studii = 2;

	//de ce este generata eroarea?
	//s0.note = new int[20];

	s0.set_numar_matricol("A689867");
	s0.set_finantare(finantare::BUGET_BURSA);

	// discutie eroare invalid heap pointer
	int note[10] = { 9,10,10,10,8,9,7,10,5,10 };
	s0.set_note(note, 10);


	Student s1 = Student("Popescu I", (char*)"Bucuresti, Sector 1", 21, 2, note, 10, "A689867", finantare::BUGET_BURSA);

	Student s2 = s1;
	s2.nume = "Ionescu C";

	int pagini[2] = { 1,2 };
	Carte c1("Ceva", "Autor", 2.4, 2, pagini);
	Carte c2 = c1;

}