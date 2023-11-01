#include <iostream>
#include <cstring>

class Carte {
private:
	char* titlu;
	std::string autor;
	int nrpag;
	double pret;
	bool electronica;
	int* CuvPerPag;
public:
	//constructori
	Carte();
	Carte(char* _titlu, std::string _autor, int _np, double _pret, bool _electronica, int* CuvPP) : autor(_autor), nrpag(_np), electronica(_electronica), pret(_pret) {
		setTitlu(_titlu);
		setCPP(CuvPP, _np);
	}
	Carte(const Carte& c) {
		this->setTitlu(c.titlu);
		this->setCPP(c.CuvPerPag, c.nrpag);
		this->setAutor(c.autor);
		this->nrpag = c.nrpag;
		this->electronica = c.electronica;
		this->pret = c.pret;
	}
	// destructori
	~Carte() {
		delete[] titlu;
		delete[] CuvPerPag;
	}

	//setteri
	void setTitlu(char* t) {
		titlu = new char[strlen(t) + 1];
		strcpy_s(titlu, strlen(t) + 1, t);
	}

	void setAutor(std::string autor) {
		this->autor = autor;
	}

	void setNP(int np) {
		nrpag = np;
	}

	void setE(bool e) {
		electronica = e;
	}

	void setPret(double _p) {
		pret = _p;
	}

	void setCPP(int* _CuvPerPag, int _nrpag) {
		nrpag = _nrpag;
		CuvPerPag = new int[nrpag];
		for (int i = 0; i < nrpag; i++)
			CuvPerPag[i] = _CuvPerPag[i];
	}

	//getteri

	char* getTitlu() {
		return titlu;
	}

	std::string getAutor() {
		return autor;
	}

	int gsetNP() {
		return nrpag;
	}

	bool getE() {
		return electronica;
	}

	double getPret() {
		return pret;
	}

	int* getCPP() {
		return CuvPerPag;
	}

};

int main() {
	int v[4] = { 1,2,3,4 };
	char b[4] = "CCT";
	Carte a(b, "IC", 4, 10.2, false, v);
	Carte carte(a);
	std::cout << "hi";
}