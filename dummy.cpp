#include <iostream>
#include <fstream>

using namespace std;

int lineInFile(string filename){
    ifstream file (filename);
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }
    return count;
}
void changeRating(string filename, string title, string rating) {
    string line, nRating, title_file, rating_file;
    ifstream readFile (filename);
    ofstream writeFile ("dummy.txt");

    if (!readFile.is_open() || !writeFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return; // Exit if files cannot be opened
    }
    while (readFile >> title_file >> rating_file >> nRating) {
        if (title_file == title) { 
            // nRating = stoi(nRating) + 1;
            // rating = int(stoi(rating_file) + stoi(rating)) / stoi(nRating);
            writeFile << title_file << rating_file << nRating << endl; 
        }
        else {
            writeFile << title_file << " " << rating_file << " " << nRating << endl;
        }
    }
    writeFile.close();
    readFile.close();
}

int main()
{
    // ofstream inputFilm ("film.txt");
    string line;
    string title, rating, nRating;
    int indexArr = 0;
    int sizeArr = 0;
    ifstream dataFilm ("film.txt");
    string titleArr[lineInFile("film.txt")][3];
    
    while(dataFilm >> title >> rating >> nRating) {
        cout << title << " " << rating << " " << nRating << endl;
        titleArr[indexArr][0] = title;
        indexArr++;
    } 
    int count = 1;
    for (int i = 0; i < lineInFile("film.txt"); i++) {
        cout << count << ". " << titleArr[i][0] << endl;
        count++;
    }
    int indexFilm;
    cout << "Film yang ingin di rating : ";
    cin >> indexFilm;
    cout << "Film yang dipilih : " << titleArr[indexFilm-1][0] << endl
         << "Berikan rating 0-5: ";
    cin >> rating;
    changeRating("film.txt", titleArr[indexFilm-1][0], rating);


    return 0;
}
