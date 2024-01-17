#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
public:
    Person() : name(nullptr), age(0), ip(nullptr) {}
    Person(const string& n, int a, const char* id) : age(a) {
        name = new char[n.size() + 1];
        strcpy_s(name, n.size() + 1, n.c_str());
        this->ip = new char(strlen(id) + 1);
        strcpy_s(ip, strlen(id) + 1, id);
    }

    // Destructor pentru a elibera memoria alocata dinamic
    ~Person() {
        delete[] name;
    }

    // Funcție de serializare
    void Serialize(ofstream& ofs) const {
        size_t nameLength = strlen(name) + 1;
        ofs.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength)); // Scriem lungimea numelui
        ofs.write(name, nameLength);
        ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
        size_t ipLenght = strlen(ip) + 1;
        ofs.write(reinterpret_cast<const char*>(&ipLenght), sizeof(ipLenght));
        ofs.write(ip, ipLenght);
    }

    // Funcție de deserializare
    void Deserialize(ifstream& ifs) {
        size_t nameLength;
        size_t ipLenght;
        ifs.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)); // Citim lungimea numelui
        delete[] name;
        name = new char[nameLength];
        ifs.read(name, nameLength);
        ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
        ifs.read(reinterpret_cast<char*>(&ipLenght), sizeof(ipLenght));
        delete[] ip;
        ip = new char[ipLenght];
        ifs.read(ip, ipLenght);
    }

    void DisplayInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", ID: ";
        for (int i = 0; i < 10; i++)
            cout << ip[i];
        cout << endl;
    }

private:
    char* name;
    int age;
    char* ip;
};

int main() {
    // Salvare obiect într-un fișier binar
    {
        ofstream outputFile("person.dat", ios::binary);
        if (!outputFile) {
            cerr << "Error opening file for writing." << endl;
            return 1;
        }
        //int v[10] = { 1,2,3,4,5,6,7,8,9,10 }

        Person personToSave("Ion Vasile", 25, "4262");
        personToSave.Serialize(outputFile);

        cout << "Object saved successfully." << endl;
    }

    // Restaurare obiect din fișier binar
    {
        ifstream inputFile("person.dat", ios::binary);
        if (!inputFile) {
            cerr << "Error opening file for reading." << endl;
            return 1;
        }

        Person restoredPerson;
        restoredPerson.Deserialize(inputFile);

        cout << "Object restored successfully." << endl;
        restoredPerson.DisplayInfo();
    }

    return 0;
}