

#include <iostream>
#include <map>
#include <fstream>
using namespace std;

map<double, double> csvFileToMap(char filename[]) {
    map<double, double> myMap;
    ifstream file(filename);
    if (file.fail()) {
        cout << "ERROR: file read error\nfilename: " << filename << endl;
        return myMap;
    }

    string line;
    while (getline(file, line)) {
        bool first = true;
        string str1, str2;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] != ',') {
                if (first) str1 += line[i];
                else str2 += line[i];
            }
            else first = false;
        }
        double val1 = stod(str1);
        double val2 = stod(str2);
        myMap[val1] = val2;
    }

    file.close();
    return myMap;
}

class Tables {
public:
    static map<double, double> aMap;
};

map<double, double> Tables::aMap = csvFileToMap("machToDragTable.csv");

int main() {
    for (auto it : Tables::aMap)
        cout << it.first << " " << it.second << endl;
}