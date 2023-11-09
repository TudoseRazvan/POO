#include<iostream>
using namespace std;

class Autor
{
public:
	string numeComplet;
	class DataNastere
	{
		int an;
		int luna;
		int zi;

	public:
		DataNastere(int an, int luna, int zi) :an(an), luna(luna), zi(zi)
		{}

	} dataNastere;

	Autor(string numeComplet, DataNastere dataNastere) :numeComplet(numeComplet), dataNastere(dataNastere)
	{}
};

class Carte
{
public:
	const string titlu;
	const Autor* autor;
	const string editura;
	const int anAparitie;
	const string isbn;
	const string codDeBareUnic;

private:
	int rand;
	int raft;
	int slot;
	bool esteImprumutata;

public:
	Carte(string titlu, Autor* autor, string editura, int anAparitie, string isbn, string codDeBareUnic) :titlu(titlu), autor(autor), editura(editura), anAparitie(anAparitie), isbn(isbn), codDeBareUnic(codDeBareUnic)
	{
		esteImprumutata = false;
		muta(-1, -1, -1);
	}

	void imprumuta()
	{
		esteImprumutata = true;
		muta(-1, -1, -1);
	}

	void returneaza()
	{
		esteImprumutata = false;
	}

	void muta(int rand, int raft, int slot)
	{
		this->rand = rand;
		this->raft = raft;
		this->slot = slot;
	}

	int* getPozitie()
	{
		int* pozitie = new int[3];
		pozitie[0] = this->rand;
		pozitie[1] = this->raft;
		pozitie[2] = this->slot;

		return pozitie;
	}
};


class Biblioteca
{
private:
	int nrRanduri;
	int nrRafturi;
	int nrSloturiCartiPeRaft;
	static Carte**** carti;
public:
	static int numarTotalCarti;

public:
	Biblioteca(int nrRanduri, int nrRafturi, int nrSloturiCartiPeRaft) :nrRanduri(nrRanduri), nrRafturi(nrRafturi), nrSloturiCartiPeRaft(nrSloturiCartiPeRaft)
	{
		carti = new Carte * **[nrRanduri];
		for (int i = 0; i < nrRanduri; i++)
		{
			carti[i] = new Carte * *[nrRafturi];
			for (int j = 0; j < nrRafturi; j++)
			{
				carti[i][j] = new Carte * [nrSloturiCartiPeRaft];
				for (int k = 0; k < nrSloturiCartiPeRaft; k++)
					carti[i][j][k] = NULL;
			}
		}
		//discutie eroare 
		//numarTotalCarti = 0;
	}

	bool adaugaCarte(Carte* carte, int rand, int raft, int slot)
	{
		if (carti[rand][raft][slot] == NULL)
		{
			carte->muta(rand, raft, slot);
			carti[rand][raft][slot] = carte;

			Biblioteca::numarTotalCarti++;

			return true;
		}
		else
			return false;
	}

	void imprumutaCarte(Carte* carte)
	{
		int* pozitie;
		pozitie = carte->getPozitie();

		carte->imprumuta();

		carti[pozitie[0]][pozitie[1]][pozitie[2]] = NULL;
	}

	void returneazaCarte(Carte* carte, int rand, int raft, int slot)
	{
		carte->returneaza();
		adaugaCarte(carte, rand, raft, slot);
	}
};

int Biblioteca::numarTotalCarti = 0;
Carte**** Biblioteca::carti = NULL;

int main()
{
	Biblioteca biblioteca(30, 15, 100);

	Autor a0("Mircea Eliade", Autor::DataNastere(1907, 4, 22));
	Carte c0("Gaudeamus", &a0, "Humanitas", 2004, "9781912545063", "6729875342");

	bool success = biblioteca.adaugaCarte(&c0, 2, 4, 22);
	success = biblioteca.adaugaCarte(&c0, 2, 4, 22);

	biblioteca.imprumutaCarte(&c0);

	biblioteca.returneazaCarte(&c0, 3, 5, 12);

	Biblioteca biblioteca2(30, 15, 100);



	return 0;
}