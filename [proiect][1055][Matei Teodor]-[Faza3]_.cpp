#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <set>
#include <vector>
#include <list>

/*
configurator moto
clase:
-motociclete: ne ofera date despre acestea(char* marca; char model[20]; int putere; const int anFabricatie;int nrIntrari; int service[20];)
-dotari: dotarile alese(char* marca; char model[20]; bool scaunIncalzit; bool keylessRide; bool alarma; bool franeCeramice; bool evacuareSport; bool cruiseControl;)
-elemente estetice: toate optiunile de estetica care pot fi alese(char* marca; char model[20]; string culoarePrimara; string culoareSecundara; int dimensiuneRoti; bool spoilerMotor;)
-asigurare: daca este asigurat vehiculul si valoarea politei de asigurare(char* marca; char model[20]; bool rca; bool casco; float valRca; float valCasco;)
-contract: datele necesare pentru incheierea contractului(char* marca; char model[20]; string nume; float suma;)
*/


using namespace std;
class Motocicleta
{
private:
	char* marca;
	char model[20];
	int putere;
	const int anFabricatie;
	int nrIntrari;
	int service[20];
public:
	void writeToFile(ofstream& f)
	{
		int l = strlen(this->marca) + 1;
		f.write((char*)&l, sizeof(int));
		f.write((char*)&this->marca, l * sizeof(char));

		f.write((char*)&this->model, sizeof(char));

		f.write((char*)&this->putere, sizeof(int));

		//f.write((char*)&this->anFabricatie, sizeof(int));

		f.write((char*)&this->nrIntrari, sizeof(int));

		for (int i = 0; i < this->nrIntrari; i++)
		{
			f.write((char*)&this->service[i], sizeof(int));
		}



	}

	void readFromFile(ifstream& f)
	{
		int l;
		f.read((char*)&l, sizeof(int));
		if (!this->marca)
		{
			delete[] this->marca;
		}
		this->marca = new char[l];
		f.read((char*)&this->marca, l * sizeof(char));

		f.read((char*)&this->model, sizeof(char));

		f.read((char*)&this->putere, sizeof(int));

		//f.read((char*)&this->anFabricatie, sizeof(int));

		f.read((char*)&this->nrIntrari, sizeof(int));

		for (int i = 0; i < this->nrIntrari; i++)
		{
			f.read((char*)&this->service[i], sizeof(int));
		}



	}


	Motocicleta() :anFabricatie(2010)
	{
		this->marca = new char[strlen("n/a") + 1];
		strcpy(this->marca, "n/a");
		strcpy(this->model, "n/a");
		this->putere = 0;
		this->nrIntrari = 0;
		this->service[0] = { 0 };
	}
	Motocicleta(const char* mar, const char* mod, int put, int anFab, int nrIn, int* serv) :anFabricatie(anFab)
	{
		if (strlen(mar) > 2)
		{
			this->marca = new char[strlen(mar) + 1];
			strcpy(this->marca, mar);
		}
		else
		{
			this->marca = new char[strlen("n/a") + 1];
			strcpy(this->marca, "n/a");
			throw new exception("marca introdusa este gresita!");
		}

		if (strlen(mod) > 2)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
			throw new exception("model introdus gresit!");
		}
		if (put > 30 && put < 400)
		{
			this->putere = put;
		}
		else
		{
			this->putere = 0;
			throw new exception("puterea nu a fost introdusa corect!");
		}
		this->nrIntrari = nrIn;
		for (int i = 0;i < nrIn;i++)
		{
			this->service[i] = serv[i];
		}
	}
	~Motocicleta()
	{
		delete[] this->marca;
	}
	char* getMarca()
	{
		return this->marca;
	}
	char* getModel()
	{
		return this->model;
	}
	int getPutere()
	{
		return this->putere;
	}
	int getAnFabricatie()
	{
		return this->anFabricatie;
	}
	int getNrIntrari()
	{
		return this->nrIntrari;
	}
	int* getService()
	{
		return this->service;
	}
	void setMarca(const char* mar)
	{
		delete[] this->marca;
		if (strlen(mar) > 2)
		{
			this->marca = new char[strlen(mar) + 1];
			strcpy(this->marca, mar);
		}
		else
		{
			this->marca = new char[strlen("n/a") + 1];
			strcpy(this->marca, "n/a");
			throw new exception("marca introdusa este gresita!");
		}
	}
	void setModel(const char* mod)
	{
		if (strlen(mod) > 0)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
			throw new exception("model introdus gresit!");
		}
	}
	void setPutere(int put)
	{
		if (put > 30 && put < 400)
		{
			this->putere = put;
		}
		else
		{
			this->putere = 0;
			throw new exception("puterea nu a fost introdusa corect!");
		}
	}
	void setService(int nrIn, int* serv)
	{
		if (nrIn > 0 && serv != NULL)
		{
			this->nrIntrari = nrIn;
			for (int i = 0;i < nrIn;i++)
			{
				this->service[i] = serv[i];
			}
		}
		else
		{
			this->nrIntrari = 0;
			this->service[0] = NULL;
		}


	}

	Motocicleta(const Motocicleta& sursa) :anFabricatie(sursa.anFabricatie)
	{
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->putere = sursa.putere;
		this->nrIntrari = sursa.nrIntrari;
		for (int i = 0;i < sursa.nrIntrari;i++)
		{
			this->service[i] = sursa.service[i];
		}
	}
	Motocicleta& operator=(const Motocicleta& sursa)
	{
		delete[] this->marca;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->putere = sursa.putere;
		this->nrIntrari = sursa.nrIntrari;
		for (int i = 0;i < sursa.nrIntrari;i++)
		{
			this->service[i] = sursa.service[i];
		}
		return *this;
	}
	friend ostream& operator <<(ostream& out, Motocicleta sursa)
	{
		out << sursa.marca << endl;
		out << sursa.model << endl;
		out << sursa.putere << endl;
		out << sursa.anFabricatie << endl;
		out << sursa.nrIntrari << endl;
		for (int i = 0; i < sursa.nrIntrari;i++)
		{
			out << sursa.service[i] << endl;
		}
		out << endl;
		return out;
	}
	friend istream& operator >>(istream& in, Motocicleta& sursa)
	{
		cout << "marca: ";
		char buffer[20];
		in.getline(buffer, 19);
		strcpy(sursa.marca, buffer);
		cout << "model: ";
		in >> sursa.model;
		cout << "putere: ";
		in >> sursa.putere;
		cout << "nr intrari: ";
		in >> sursa.nrIntrari;
		for (int i = 0;i < sursa.nrIntrari;i++)
		{
			cout << "intrarea " << i + 1 << ": ";
			in >> sursa.service[i];
		}
		return in;
	}
	//void titlu(char )
	Motocicleta& operator++()
	{
		this->putere += 10;
		return *this;
	}
	Motocicleta operator++(int)
	{
		Motocicleta copie = *this;
		this->putere += 10;
		return copie;
	}
	bool operator==(Motocicleta sursa)
	{
		bool gasit = true;
		if (strcmp(this->marca, sursa.marca) != 0)
		{
			gasit = false;
		}
		if (strcmp(this->model, sursa.model) != 0)
		{
			gasit = false;
		}
		return gasit;
	}
	void afisare()
	{
		cout << this->marca << " ";
		cout << this->model << endl;

		cout << putere << endl;
		cout << anFabricatie << endl;
		cout << nrIntrari << endl;
		for (int i = 0; i < nrIntrari;i++)
		{
			cout << service[i] << endl;
		}
		cout << endl;


	}
	bool operator<(Motocicleta sursa)
	{
		if (this->nrIntrari < sursa.nrIntrari)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool  operator! ()
	{
		if (this->nrIntrari > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	explicit operator int()
	{
		return this->putere;
	}

	int& operator [](int nrIntrari)
	{
		return service[nrIntrari];

	}
	//op+

	void raportMotocicleta(const char* sursa)
	{
		ofstream fout;
		fout.open(sursa, ofstream::out);
		fout << "titlu: " << this->getMarca() << " " << this->getModel() << " " << this->getAnFabricatie();
		fout << endl;


	}

};

class ElementeEstetice
{
private:
	char* marca;
	char model[20];
	string culoarePrimara;
	string culoareSecundara;
	int dimensiuneRoti;
	bool spoilerMotor;
public:
	void writeToFile(ofstream& f)
	{
		int l = strlen(this->marca) + 1;
		f.write((char*)&l, sizeof(int));
		f.write((char*)&this->marca, l * sizeof(char));

		f.write((char*)&this->model, sizeof(char));

		l = this->culoarePrimara.length() + 1;
		f.write((char*)&l, sizeof(int));
		f.write(this->culoarePrimara.data(), l * sizeof(char));

		l = this->culoareSecundara.length() + 1;
		f.write((char*)&l, sizeof(int));
		f.write(this->culoareSecundara.data(), l * sizeof(char));


		f.write((char*)&this->dimensiuneRoti, sizeof(this->dimensiuneRoti));

		f.write((char*)&this->spoilerMotor, sizeof(this->spoilerMotor));

	}

	void readFromFile(ifstream& f)
	{
		int l;
		f.read((char*)&l, sizeof(int));
		if (!this->marca)
		{
			delete[] this->marca;
		}
		this->marca = new char[l];
		f.read((char*)&this->marca, l * sizeof(char));

		f.read((char*)&this->model, sizeof(char));

		f.read((char*)&l, sizeof(int));
		char* buffer = new char[l];
		f.read(buffer, l * sizeof(char));
		this->culoarePrimara = buffer;
		delete[] buffer;

		/*f.read((char*)&l, sizeof(int));
		char* buffer = new char[l];
		f.read(buffer, l * sizeof(char));
		this->culoareSecundara = buffer;
		delete[] buffer;*/

		f.read((char*)&this->dimensiuneRoti, sizeof(this->dimensiuneRoti));

		f.read((char*)&this->spoilerMotor, sizeof(this->spoilerMotor));



	}
	ElementeEstetice()
	{
		this->marca = new char[strlen("n/a") + 1];
		strcpy(this->marca, "n/a");
		strcpy(this->model, "n/a");
		this->culoarePrimara = "-";
		this->culoareSecundara = "-";
		this->dimensiuneRoti = 0;
		this->spoilerMotor = 0;
	}
	ElementeEstetice(const char* mar, const char* mod, string cprim, string csec, int dim, bool sm)
	{
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
		strcpy(this->model, mod);
		this->culoarePrimara = cprim;
		this->culoareSecundara = csec;
		this->dimensiuneRoti = dim;
		this->spoilerMotor = sm;
	}
	~ElementeEstetice()
	{
		delete[] this->marca;
	}
	char* getMarca()
	{
		return this->marca;
	}
	char* getModel()
	{
		return this->model;
	}
	string getCuloarePrimara()
	{
		return this->culoarePrimara;
	}
	string getCuloareSecundara()
	{
		return this->culoareSecundara;
	}
	int getDimensiuneRoti()
	{
		return this->dimensiuneRoti;
	}
	bool getSpoilerMotor()
	{
		return this->spoilerMotor;
	}
	void setMarca(const char* mar)
	{
		delete[] this->marca;
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
	}
	void setModel(const char* mod)
	{
		if (strlen(mod) > 0)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
		}
	}
	void setCuloarePrimara(string cprim)
	{
		if (cprim.length() > 2)
		{
			this->culoarePrimara = cprim;
		}
		else
		{
			this->culoarePrimara = "-";
		}
	}
	void setCuloareSecundara(string csec)
	{
		if (csec.length() > 2)
		{
			this->culoareSecundara = csec;
		}
		else
		{
			this->culoareSecundara = "-";
		}
	}
	void setDimensiuneRoti(int dim)
	{
		if (dim > 0)
			this->dimensiuneRoti = dim;

	}
	void setSpoilerMotor(bool sm)
	{
		this->spoilerMotor = sm;
	}
	ElementeEstetice(const ElementeEstetice& sursa)
	{
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->culoarePrimara = sursa.culoarePrimara;
		this->culoareSecundara = sursa.culoareSecundara;
		this->dimensiuneRoti = sursa.dimensiuneRoti;
		this->spoilerMotor = sursa.spoilerMotor;
	}
	ElementeEstetice& operator=(const ElementeEstetice& sursa)
	{
		delete[]this->marca;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->culoarePrimara = sursa.culoarePrimara;
		this->culoareSecundara = sursa.culoareSecundara;
		this->dimensiuneRoti = sursa.dimensiuneRoti;
		this->spoilerMotor = sursa.spoilerMotor;
		return*this;
	}
	friend ostream& operator<<(ostream& out, ElementeEstetice sursa)
	{
		out << sursa.marca << endl;
		out << sursa.model << endl;
		out << sursa.culoarePrimara << endl;
		out << sursa.culoareSecundara << endl;
		out << sursa.dimensiuneRoti << endl;
		out << sursa.spoilerMotor << endl;
		return out;
	}
	friend istream& operator>>(istream& in, ElementeEstetice& sursa)
	{
		/*cout << "marca: ";
		char buffer[20];
		in.getline(buffer, 19);
		strcpy(sursa.marca, buffer);
		cout << "model: ";
		in >> sursa.model;*/
		cout << "culoare primara: ";
		in >> sursa.culoarePrimara;
		cout << "culoare secundara: ";
		in >> sursa.culoareSecundara;
		cout << "dimensiune roti: ";
		in >> sursa.dimensiuneRoti;
		cout << "spoiler motor: ";
		in >> sursa.spoilerMotor;
		return in;
	}
	ElementeEstetice& operator++()
	{
		this->dimensiuneRoti++;
		return *this;
	}
	ElementeEstetice operator++(int)
	{
		ElementeEstetice copie = *this;
		this->dimensiuneRoti++;
		return copie;
	}
	bool operator==(ElementeEstetice sursa)
	{
		bool gasit = true;
		if (strcmp(this->marca, sursa.marca) != 0)
		{
			gasit = false;
		}
		if (strcmp(this->model, sursa.model) != 0)
		{
			gasit = false;
		}
		return gasit;
	}
	void afisare()
	{
		cout << this->marca << endl;
		cout << this->model << endl;
		cout << this->culoarePrimara << endl;
		cout << this->culoareSecundara << endl;
		cout << this->dimensiuneRoti << endl;
		cout << this->spoilerMotor << endl;


	}
	bool  operator! ()
	{
		if (this->dimensiuneRoti > 10 && this->dimensiuneRoti < 20)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator<(ElementeEstetice sursa)
	{
		if (this->dimensiuneRoti < sursa.dimensiuneRoti)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	explicit operator string()
	{
		return this->culoarePrimara;
	}

	void raportEstetica(const char* sursa)
	{
		ofstream fout;
		fout.open(sursa, ofstream::out);
		fout << "culoare primara: " << this->getCuloarePrimara() << endl;
		fout << "culoare secundara: " << this->getCuloareSecundara() << endl;
		fout << "dimensiune roti: " << this->getDimensiuneRoti() << " '' " << endl;
		fout << "spoiler motor: ";
		if (this->getSpoilerMotor() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;

	}
};

class Dotari
{
private:
	char* marca;
	char model[20];
	bool scaunIncalzit;
	bool keylessRide;
	bool alarma;
	bool franeCeramice;
	bool evacuareSport;
	bool cruiseControl;
public:
	void writeToFile(ofstream& f)
	{
		int l = strlen(this->marca) + 1;
		f.write((char*)&l, sizeof(int));
		f.write((char*)&this->marca, l * sizeof(char));

		f.write((char*)&this->model, sizeof(char));

		f.write((char*)&this->scaunIncalzit, sizeof(bool));

		f.write((char*)&this->keylessRide, sizeof(bool));

		f.write((char*)&this->alarma, sizeof(bool));

		f.write((char*)&this->franeCeramice, sizeof(bool));

		f.write((char*)&this->evacuareSport, sizeof(bool));

		f.write((char*)&this->cruiseControl, sizeof(bool));

	}

	void readFromFile(ifstream& f)
	{
		int l;
		f.read((char*)&l, sizeof(int));
		if (!this->marca)
		{
			delete[] this->marca;
		}
		this->marca = new char[l];
		f.read((char*)&this->marca, l * sizeof(char));

		f.read((char*)&this->scaunIncalzit, sizeof(bool));

		f.read((char*)&this->keylessRide, sizeof(bool));

		f.read((char*)&this->alarma, sizeof(bool));

		f.read((char*)&this->franeCeramice, sizeof(bool));

		f.read((char*)&this->evacuareSport, sizeof(bool));

		f.read((char*)&this->cruiseControl, sizeof(bool));



	}
	Dotari()
	{
		this->marca = new char[strlen("n/a") + 1];
		strcpy(this->marca, "n/a");
		strcpy(this->model, "n/a");
		this->scaunIncalzit = 0;
		this->keylessRide = 0;
		this->alarma = 0;
		this->franeCeramice = 0;
		this->evacuareSport = 0;
		this->cruiseControl = 0;
	}
	Dotari(const char* mar, const char* mod, bool si, bool klr, bool al, bool fc, bool es, bool cc)
	{
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
		strcpy(this->model, mod);
		this->scaunIncalzit = si;
		this->keylessRide = klr;
		this->alarma = al;
		this->franeCeramice = fc;
		this->evacuareSport = es;
		this->cruiseControl = cc;
	}
	~Dotari()
	{
		delete[] this->marca;
	}
	char* getMarca()
	{
		return this->marca;
	}
	char* getModel()
	{
		return this->model;
	}
	bool getScaunIncalzit()
	{
		return this->scaunIncalzit;
	}
	bool getKeylessRide()
	{
		return this->keylessRide;
	}
	bool getAlarma()
	{
		return this->alarma;
	}
	bool getFraneCeramice()
	{
		return this->franeCeramice;
	}
	bool getEvacuareSport()
	{
		return this->evacuareSport;
	}
	bool getCruiseControl()
	{
		return this->cruiseControl;
	}
	void setMarca(const char* mar)
	{
		delete[] this->marca;
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
	}
	void setModel(const char* mod)
	{
		if (strlen(mod) > 0)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
		}
	}
	void setScaunIncalzit(bool sc)
	{
		this->scaunIncalzit = sc;
	}
	void setKeylessRide(bool klr)
	{
		this->keylessRide = klr;
	}
	void setAlarma(bool al)
	{
		this->alarma = al;
	}
	void setFraneCeramice(bool fc)
	{
		this->franeCeramice = fc;
	}
	void setEvacuareSport(bool es)
	{
		this->evacuareSport = es;
	}
	void setCruiseControl(bool cc)
	{
		this->cruiseControl = cc;
	}
	Dotari(const Dotari& sursa)
	{
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->scaunIncalzit = sursa.scaunIncalzit;
		this->keylessRide = sursa.keylessRide;
		this->alarma = sursa.alarma;
		this->franeCeramice = sursa.franeCeramice;
		this->evacuareSport = sursa.evacuareSport;
		this->cruiseControl = sursa.cruiseControl;
	}
	Dotari& operator=(const Dotari& sursa)
	{
		delete[] this->marca;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->scaunIncalzit = sursa.scaunIncalzit;
		this->keylessRide = sursa.keylessRide;
		this->alarma = sursa.alarma;
		this->franeCeramice = sursa.franeCeramice;
		this->evacuareSport = sursa.evacuareSport;
		this->cruiseControl = sursa.cruiseControl;
		return*this;
	}
	friend ostream& operator<<(ostream& out, Dotari sursa)
	{
		out << sursa.marca << endl;
		out << sursa.model << endl;
		out << sursa.scaunIncalzit << endl;
		out << sursa.keylessRide << endl;
		out << sursa.alarma << endl;
		out << sursa.franeCeramice << endl;
		out << sursa.evacuareSport << endl;
		out << sursa.cruiseControl << endl;

		return out;

	}
	friend istream& operator>>(istream& in, Dotari& sursa)
	{
		/*cout << "marca: ";
		char buffer[20];
		in.getline(buffer, 19);
		strcpy(sursa.marca, buffer);
		cout << "model: ";
		in >> sursa.model;*/
		cout << "scaun incalzit: ";
		in >> sursa.scaunIncalzit;
		cout << "keyless ride: ";
		in >> sursa.keylessRide;
		cout << "alarma: ";
		in >> sursa.alarma;
		cout << "frane ceramice: ";
		in >> sursa.franeCeramice;
		cout << "evacuare sport: ";
		in >> sursa.evacuareSport;
		cout << "cruise control: ";
		in >> sursa.cruiseControl;
		return in;
	}
	Dotari& operator++()
	{
		this->scaunIncalzit = 1;
		this->keylessRide = 1;
		this->alarma = 1;
		this->franeCeramice = 1;
		this->evacuareSport = 1;
		this->cruiseControl = 1;
		return *this;
	}
	bool operator==(Dotari sursa)
	{
		bool gasit = true;
		if (strcmp(this->marca, sursa.marca) != 0)
		{
			gasit = false;
		}
		if (strcmp(this->model, sursa.model) != 0)
		{
			gasit = false;
		}
		return gasit;
	}
	explicit operator bool()
	{
		return this->franeCeramice;
	}
	void afisare()
	{
		cout << this->marca << " ";
		cout << this->model << endl;
		cout << scaunIncalzit << endl;
		cout << keylessRide << endl;
		cout << alarma << endl;
		cout << franeCeramice << endl;
		cout << evacuareSport << endl;
		cout << cruiseControl << endl;

	}

	void raportDotari(const char* sursa)
	{
		ofstream fout;
		fout.open(sursa, ofstream::out);
		fout << "scaunIncalzit: ";
		if (this->getScaunIncalzit() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;
		fout << "keylessRide: ";
		if (this->getKeylessRide() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;
		fout << "alarma: ";
		if (this->getAlarma() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;
		fout << "franeCeramice: ";
		if (this->getFraneCeramice() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;
		fout << "evacuareSport: ";
		if (this->getEvacuareSport() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;
		fout << "cruiseControl: ";
		if (this->getCruiseControl() == 1)
		{
			fout << "da";
		}
		else
		{
			fout << "nu";
		}
		fout << endl;


	}

};

class Asigurare
{
private:
	char* marca;
	char model[20];
	bool rca;
	bool casco;
	float valRca;
	float valCasco;

public:
	void writeToFile(ofstream& f)
	{
		;
		int l = strlen(this->marca) + 1;
		f.write((char*)&l, sizeof(int));
		f.write((char*)&this->marca, l * sizeof(char));

		f.write((char*)&this->model, sizeof(char));

		f.write((char*)&this->rca, sizeof(bool));

		f.write((char*)&this->casco, sizeof(bool));

		f.write((char*)&this->valRca, sizeof(float));

		f.write((char*)&this->valCasco, sizeof(float));

	}

	void readFromFile(ifstream& f)
	{



		int l;
		f.read((char*)&l, sizeof(int));
		if (!this->marca)
		{
			delete[] this->marca;
		}
		this->marca = new char[l];
		f.read((char*)&this->marca, l * sizeof(char));

		f.read((char*)&this->model, sizeof(char));

		f.read((char*)&this->rca, sizeof(bool));

		f.read((char*)&this->casco, sizeof(bool));

		f.read((char*)&this->valRca, sizeof(float));

		f.read((char*)&this->valCasco, sizeof(float));



	}
	Asigurare()
	{
		this->marca = new char[strlen("n/a") + 1];
		strcpy(this->marca, "n/a");
		strcpy(this->model, "n/a");
		this->rca = 0;
		this->casco = 0;
		this->valCasco = 0;
		this->valRca = 0;
	}
	Asigurare(const char* mar, const char* mod, bool r, bool c, float vr, float vc)
	{
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
		strcpy(this->model, mod);
		this->rca = r;
		this->casco = c;
		this->valRca = vr;
		this->valCasco = vc;
	}
	~Asigurare()
	{
		delete[]this->marca;
	}
	char* getMarca()
	{
		return this->marca;
	}
	char* getModel()
	{
		return this->model;
	}
	bool getRca()
	{
		return this->rca;
	}
	bool getCasco()
	{
		return this->casco;
	}
	float getValRca()
	{
		return this->valRca;
	}
	float getValCasco()
	{
		return this->valCasco;
	}
	void setMarca(const char* mar)
	{
		delete[] this->marca;
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
	}
	void setModel(const char* mod)
	{
		if (strlen(mod) > 0)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
		}
	}

	void setRca(bool r, float vr)
	{
		if (r == 1 && vr > 0)
		{
			this->valRca = vr;
			this->rca = 1;
		}
		else
		{
			this->valRca = 0;
			this->casco = 0;
		}
	}
	void setCasco(bool c, float vc)
	{
		if (c == 1 && vc > 0)
		{
			this->valCasco = vc;
			this->casco = 1;
		}
		else
		{
			this->valCasco = 0;
			this->casco = 0;
		}
	}
	Asigurare(const Asigurare& sursa)
	{
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->rca = sursa.rca;
		this->casco = sursa.casco;
		this->valRca = sursa.valRca;
		this->valCasco = sursa.valCasco;
	}
	Asigurare& operator=(const Asigurare& sursa)
	{
		delete[] this->marca;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->rca = sursa.rca;
		this->casco = sursa.casco;
		this->valRca = sursa.valRca;
		this->valCasco = sursa.valCasco;
		return *this;
	}
	friend ostream& operator<<(ostream& out, Asigurare sursa)
	{
		out << sursa.marca << endl;
		out << sursa.model << endl;
		out << sursa.rca << endl;
		out << sursa.casco << endl;
		out << sursa.valRca << endl;
		out << sursa.valCasco << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Asigurare& sursa)
	{
		cout << "marca: ";
		char buffer[20];
		in.getline(buffer, 19);
		strcpy(sursa.marca, buffer);
		cout << "model: ";
		in >> sursa.model;
		cout << "rca: ";
		in >> sursa.rca;
		cout << "casco: ";
		in >> sursa.casco;
		cout << "valoare rca: ";
		in >> sursa.valRca;
		cout << "valoare casco: ";
		in >> sursa.valCasco;
		return in;
	}
	Asigurare& operator++()
	{
		this->valRca++;
		return*this;
	}
	Asigurare operator++(int)
	{
		Asigurare copie = *this;
		this->valRca++;
		return copie;
	}
	bool operator==(Asigurare sursa)
	{
		bool gasit = true;
		if (strcmp(this->marca, sursa.marca) != 0)
		{
			gasit = false;
		}
		if (strcmp(this->model, sursa.model) != 0)
		{
			gasit = false;
		}
		return gasit;
	}

	explicit operator float()
	{
		return this->valRca;
	}
	void afisare()
	{
		cout << this->marca << " ";
		cout << this->model << " ";
		cout << this->rca << " ";
		cout << this->casco << " ";
		cout << this->valRca << " ";
		cout << this->valCasco << " ";
	}
	bool operator<(Asigurare sursa)
	{
		if (this->valRca < sursa.valRca)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool  operator! ()
	{
		if (this->valRca > 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

class Contract
{
private:
	char* marca;
	char model[20];
	static int nrContracte;
	string nume;
	float suma;
public:
	void writeToFile(ofstream& f)
	{
		int l = strlen(this->marca) + 1;
		f.write((char*)&l, sizeof(int));
		f.write((char*)&this->marca, l * sizeof(char));

		f.write((char*)&this->model, sizeof(char));


		l = this->nume.length() + 1;
		f.write((char*)&l, sizeof(int));
		f.write(this->nume.data(), l * sizeof(char));



		f.write((char*)&this->suma, sizeof(float));

	}

	void readFromFile(ifstream& f)
	{
		int l;
		f.read((char*)&l, sizeof(int));
		if (!this->marca)
		{
			delete[] this->marca;
		}
		this->marca = new char[l];
		f.read((char*)&this->marca, l * sizeof(char));

		f.read((char*)&this->model, sizeof(char));

		f.read((char*)&l, sizeof(int));
		char* buffer = new char[l];
		f.read(buffer, l * sizeof(char));
		this->nume = buffer;
		delete[] buffer;

		f.read((char*)&this->suma, sizeof(float));



	}
	Contract()
	{
		nrContracte++;
		this->marca = new char[strlen("n/a") + 1];
		strcpy(this->marca, "n/a");
		strcpy(this->model, "n/a");
		this->nume = "-";
		this->suma = 0;
	}
	Contract(const char* mar, const char* mod, string n, float s)
	{
		nrContracte++;
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
		strcpy(this->model, mod);
		this->nume = n;
		this->suma = s;
	}
	~Contract()
	{
		delete[]this->marca;
	}
	static int getNrContracte()
	{
		return Contract::nrContracte;
	}
	char* getMarca()
	{
		return this->marca;
	}
	char* getModel()
	{
		return this->model;
	}
	string getNume()
	{
		return this->nume;
	}

	float getSuma()
	{
		return this->suma;
	}
	void setMarca(const char* mar)
	{
		delete[] this->marca;
		this->marca = new char[strlen(mar) + 1];
		strcpy(this->marca, mar);
	}
	void setModel(const char* mod)
	{
		if (strlen(mod) > 0)
		{
			strcpy(this->model, mod);
		}
		else
		{
			strcpy(this->model, "n/a");
		}
	}
	void setNume(string n)
	{
		if (n.length() > 2)
		{
			this->nume = n;
		}
		else
		{
			this->nume = "-";
		}
	}

	void setSuma(float s)
	{
		if (s > 0)
		{
			this->suma = s;
		}
		else
		{
			this->suma = 0;
		}

	}
	Contract(const Contract& sursa)
	{
		nrContracte++;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->nume = sursa.nume;
		this->suma = sursa.suma;
	}
	Contract& operator=(const Contract& sursa)
	{
		delete[]this->marca;
		this->marca = new char[strlen(sursa.marca) + 1];
		strcpy(this->marca, sursa.marca);
		strcpy(this->model, sursa.model);
		this->nume = sursa.nume;
		this->suma = sursa.suma;
		return*this;
	}
	friend ostream& operator<<(ostream& out, Contract sursa)
	{
		out << sursa.marca << endl;
		out << sursa.model << endl;
		out << sursa.nrContracte << endl;
		out << sursa.nume << endl;
		out << sursa.suma << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Contract& sursa)
	{
		/*cout << "marca: ";
		char buffer[20];
		in.getline(buffer, 19);
		strcpy(sursa.marca, buffer);
		cout << "model: ";
		in >> sursa.model;*/
		cout << "nume: ";
		in >> sursa.nume;
		cout << "suma: ";
		in >> sursa.suma;
		return in;
	}
	Contract operator++()
	{
		this->suma++;
		return *this;
	}
	Contract operator++(int)
	{
		Contract copie = *this;
		this->suma++;
		return copie;
	}
	bool operator==(Contract sursa)
	{
		bool gasit = true;
		if (strcmp(this->marca, sursa.marca) != 0)
		{
			gasit = false;
		}
		if (strcmp(this->model, sursa.model) != 0)
		{
			gasit = false;
		}
		return gasit;
	}
	void afisare()
	{
		cout << this->marca << endl;
		cout << this->model << endl;
		cout << this->nume << endl;
		cout << this->suma << endl;


	}
	bool operator<(Contract sursa)
	{
		if (this->suma < sursa.suma)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool  operator! ()
	{
		if (this->suma > 100)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	explicit operator float()
	{
		return this->suma;
	}
};
int Contract::nrContracte = 0;

class gestiuneFis
{

public:
	void writeToFile(ofstream& fout, Motocicleta sursa)
	{

		sursa.writeToFile(fout);

	}
	void readFromFile(ifstream& fin, Motocicleta& sursa)
	{

		sursa.readFromFile(fin);

	}

	void writeToFile(ofstream& fout, ElementeEstetice sursa)
	{

		sursa.writeToFile(fout);

	}
	void readFromFile(ifstream& fin, ElementeEstetice& sursa)
	{

		sursa.readFromFile(fin);

	}

	void writeToFile(ofstream& fout, Dotari sursa)
	{

		sursa.writeToFile(fout);

	}
	void readFromFile(ifstream& fin, Dotari& sursa)
	{

		sursa.readFromFile(fin);

	}

	void writeToFile(ofstream& fout, Asigurare sursa)
	{

		sursa.writeToFile(fout);

	}
	void readFromFile(ifstream& fin, Asigurare& sursa)
	{

		sursa.readFromFile(fin);

	}

	void writeToFile(ofstream& fout, Contract sursa)
	{

		sursa.writeToFile(fout);

	}
	void readFromFile(ifstream& fin, Contract& sursa)
	{

		sursa.readFromFile(fin);

	}
};


class Meniu
{
public:
	static void afisMeniu()
	{

		cout << endl;
		cout << "1. Modele Valabile" << endl;
		cout << "2. Start configurator" << endl;
		cout << "3. Motociclete rulate" << endl;
		cout << "4. Exit" << endl;
	}
};

class Scuter : public Motocicleta
{
	int nrRoti = 2;
	string tip = "combustie";

public:
	Scuter(const char* mar, const char* mod, int put, int anFab, int nrIn, int* serv, int nrR, string t) :Motocicleta(mar, mod, put, anFab, nrIn, serv)
	{
		this->nrRoti = nrR;
		this->tip = t;
	}
	Scuter(const Scuter& sursa) :Motocicleta(sursa)
	{
		this->nrRoti = sursa.nrRoti;
		this->tip = sursa.tip;
	}

	Scuter& operator=(const Scuter& sursa)
	{
		Motocicleta::operator=(sursa);
		this->nrRoti = sursa.nrRoti;
		this->tip = sursa.tip;
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Scuter& sursa)
	{
		out << (Motocicleta)sursa;
		out << "\nNumar roti: " << sursa.nrRoti;
		out << "\nTip " << sursa.tip;
		return out;
	}
};



class Vehicul
{
	string nume = "anonim";
public:
	Vehicul(string n)
	{
		this->nume = n;
	}

	virtual void Merge() = 0;
	virtual void Viteza() = 0;
	virtual void Franeaza()
	{
		cout << "\nFraneaza!";

	}
	virtual void Claxon()
	{
		cout << "\nFace Beep!";
	}

};

class Moped : public Vehicul
{
	int km;
public:
	Moped(string num, int k) :Vehicul(num)
	{
		this->km = k;
	}
	void Merge()
	{
		cout << "\nMopedul se deplaseaza ";
	}
	void Viteza()
	{
		cout << "cu 30 km/h";
	}

	void Claxon()
	{
		cout << "\nAcest moped nu are claxon!";
	}

	void Franeaza()
	{
		cout << "\nMopedul incetineste!";
	}
};

class ATV : public Vehicul
{
	int km;
public:
	ATV(string num, int k) :Vehicul(num)
	{
		this->km = k;
	}
	void Merge()
	{
		cout << "\nAtv-ul se deplaseaza ";
	}
	void Viteza()
	{
		cout << "cu 50 km/h";
	}

	void Claxon()
	{
		cout << "\nAtv-ul claxoneaza!";
	}

	void Franeaza()
	{
		cout << "\nAtv-ul incetineste!";
	}
};

int main()
{


	//Motocicleta m1; //constructor default
	//int aux[] = { 10000, 30000 };
	//Motocicleta m2("Kawasaki", "Ninja", 200, 2017, 2, aux); //constructor toti param
	//Motocicleta m3;
	//cout << m2.getMarca() << endl; //metode get
	//for (int i = 0;i < m2.getNrIntrari();i++)
	//	cout << m2.getService()[i] << " ";
	//cout << endl;
	//Motocicleta m3(m2); //constructor copiere
	//m3.setMarca("BMW"); //metoda set
	//cout << m3.getMarca() << " ";
	//m3.setModel("R18");
	//cout << m3.getModel();
	//cout << endl;
	//Motocicleta m4;
	//m4 = m2; //operator=
	//cout << m4.getMarca() << endl;
	//Motocicleta m5;
	//cin >> m5; //op>>
	//cout << m5; //op<<
	//m5++;
	//cout << m5;
	//m2.afisare();

	/*ElementeEstetice e1;
	e1.setSpoilerMotor(1);
	ElementeEstetice e2("bmw", "x5", "verde", "negru", 17, 1);
	ElementeEstetice e3(e2);

	ElementeEstetice e4;
	e4.setDimensiuneRoti(12);
	e4++;
	cout << e4;*/

	/*Dotari d1;
	Dotari d2("BMW", "R18", 1, 0, 0, 1, 1, 0);
	Dotari d3(d2);
	Dotari d4;
	d4 = d2;
	cout << d4.getScaunIncalzit();
	cout << endl;
	cout << d2;
	Dotari d5;
	cout << endl;
	cin >> d5;
	cout << d5;*/

	/*Contract c1;
	Contract c2("kawasaki", "ninja", "popescu ionel", 2000);
	Contract c3;
	cin >> c3;
	cout << c3;
	c3++;
	cout << c3;*/

	/*Asigurare a1;
	Asigurare a2("kawasaki", "ninja", 1, 0, 800, 0);
	a1.setCasco(0, 10);
	cout << a2;
	a2++;
	cout << a2;*/

	//Scuter s1("Yamaha", "Jog", 5, 2017, 2, aux, 2, "combustie");
	//cout << s1;

	/*Vehicul* v1 = new Moped();
	v1->Merge();
	v1->Viteza();
	v1->Franeaza();
	v1->Claxon();*/

	/*Moped m1("da", 0);
	Moped m2("sally", 0);
	ATV a1("gica", 0);
	Vehicul* v[10] = { &m1, &m2, &a1 };
	for (int i = 0; i < 3; i++)
	{

		v[i]->Merge();
		v[i]->Viteza();
		v[i]->Franeaza();
		v[i]->Claxon();

	}*/

	//STL
//cout << "\n---------- STL LIST ----------\n";
//list<Motocicleta> l2;
//l2.push_back(m1);
//l2.push_front(m2);
//l2.push_back(m3);
//list<Motocicleta>::reverse_iterator it2;
//for (it2 = l2.rbegin(); it2 != l2.rend(); it2++)
//{
//	cout << *it2 << " ";
//}
//cout << endl;

	int aux[] = { 10000, 30000 };
	Motocicleta m1("Kawasaki", "Ninja", 200, 2017, 2, aux);

	ElementeEstetice e1("Kawasaki", "Ninja", "verde", "negru", 17, 1);

	Dotari d1("Kawasaki", "Ninja", 1, 0, 0, 1, 1, 0);

	Asigurare a1("Kawasaki", "Ninja", 1, 0, 800, 0);

	Contract c1("Kawasaki", "Ninja", "Popescu Ionel", 200000);

	m1.raportMotocicleta("raportMotocicleta1.txt");

	e1.raportEstetica("raportEstetica1.txt");

	d1.raportDotari("raportDotari1.txt");

	bool Activ = true;
	unsigned int p;
	while (Activ == true)
	{
		int alegere;
		Meniu::afisMeniu();
		cin >> alegere;
		switch (alegere)
		{
		case 1:
		{

			cout << "Kawasaki Ninja 2022" << endl;
			cout << "Kawasaki Ninja 650 ABS '21 - Reinnoita pentru a oferi continuitate," << endl;
			cout << "Ninja 650 ABS vine la pachet cu un motor sportiv de 649 cc, tehnologie avansata si actualizari de stil." << endl;
			cout << "Dispune de un sistem de transmisie cu 6 trepte si ambreiaj ultramodern Assist and Slipper, suspensii optimizate, " << endl;
			cout << "ofera un nivel ridicat de manevrabilitate si adaptabilitate la traseu.Beneficiaza in acelasi timp de emblematicul design Ninja." << endl;
			cout << endl;
			cout << endl;
			cout << "Bmw R18 2022" << endl;
			cout << "R 18 Classic este o motocicleta de touring care trezeste nostalgia. Ea aminteste de inceputurile primelor cruisere potrivite pentru tururi." << endl;
			cout << "In plus, comemoreaza caracteristicile atemporale ale istoriei noastre Motorrad. Inima vehiculului este in mod clar motorul boxer cu cea mai mare" << endl;
			cout << "capacitate cilindrică pe care l - am construit vreodata." << endl;
			cout << endl;
			break;
		}

		case 2:
		{

			unsigned int pret;
			bool n;
			cout << "tastati modelul dorit: " << endl;
			cout << "0 Kawasaki Ninja" << endl;
			cout << "1 Bmw R18" << endl;

			cin >> n;
			if (n == 0)
			{
				Motocicleta m2("Kawasaki", "Ninja", 210, 2022, 0, { 0 });
				cout << m2;
				pret = 220000;

			}
			else
			{
				Motocicleta m2("Bmw", "R18", 120, 2022, 0, { 0 });
				cout << m2;
				pret = 150000;
			}
			ElementeEstetice e2;
			Dotari d2;
			cin >> e2;
			cin >> d2;

			if (e2.getSpoilerMotor() == 1)
			{
				pret += 800;
			}
			if (d2.getScaunIncalzit() == 1)
			{
				pret += 1200;
			}
			if (d2.getKeylessRide() == 1)
			{
				pret += 600;
			}
			if (d2.getAlarma() == 1)
			{
				pret += 1400;
			}
			if (d2.getFraneCeramice() == 1)
			{
				pret += 1850;
			}
			if (d2.getEvacuareSport() == 1)
			{
				pret += 1650;
			}
			if (d2.getCruiseControl() == 1)
			{
				pret += 600;
			}
			cout << endl;
			cout << "pret final: " << pret << endl;
			cout << endl;
			n = 0;
			cout << "doriti sa aflati cam cat va costa asigurare?" << endl;
			cin >> n;
			if (n == 1)
			{
				int perm;
				cout << "de cati ani aveti permis?" << endl;
				cin >> perm;
				cout << "Rca: " << 0.002 * pret - perm * 5 << endl;
				cout << "Casco: " << 0.004 * pret - perm * 6 << endl;
			}
			cout << endl;
			time_t now = time(0);
			//char* date_time = ctime(&now);
			/*cout << "Contract" << endl;
			cout << date_time << endl;*/
			Contract c2;
			cin >> c2;




			//cout << "contractul numarul " << c2.getNrContracte() << endl;
			/*cout << c2.getNume() << endl;
			cout << c2.getSuma() << endl;*/
			cout << endl;
			if (c2.getSuma() == pret)
			{
				time_t now = time(0);
				char* date_time = ctime(&now);
				cout << date_time << endl;

				cout << "Contract Incheiat!" << endl;;
				cout << "semnatura:          M.   " << endl;
			}
			else
			{
				cout << "Contractul nu s a putu incheia!" << endl;
			}


			break;

		}

		case 3:
		{

			cout << m1.getMarca() << " " << m1.getModel() << " " << m1.getAnFabricatie() << endl;
			cout << "culoare/culori:" << e1.getCuloarePrimara() << ", " << e1.getCuloareSecundara() << endl;
			cout << "roti: " << e1.getDimensiuneRoti() << endl;
			cout << "spoiler motor: ";
			if (e1.getSpoilerMotor() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "scaunIncalzit: ";
			if (d1.getScaunIncalzit() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "keylessRide: ";
			if (d1.getKeylessRide() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "alarma: ";
			if (d1.getAlarma() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "franeCeramice: ";
			if (d1.getFraneCeramice() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "evacuareSport: ";
			if (d1.getEvacuareSport() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}
			cout << "cruiseControl: ";
			if (d1.getCruiseControl() == 1)
			{
				cout << "da" << endl;
			}
			else
			{
				cout << "nu" << endl;
			}

			cout << endl;
			cout << c1.getSuma() << endl;
			break;



		}

		case 4:
		{

			Activ = false;
			cout << "Aplicatia a fost inchisa cu succes!";
			break;

		}

		default:
		{
			Activ = false;
			cout << "Aplicatia a fost inchisa cu succes!";
			break;

		}

		}
	}




	return 0;
}