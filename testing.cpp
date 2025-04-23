#include <iostream>
#include <fstream>
#include <random>
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
        titleArr[indexArr][1] = rating;
        titleArr[indexArr][2] = nRating;
        indexArr++;
    } 
    int count = 1;
    for (int i = 0; i < lineInFile("film.txt"); i++) {
        cout << count << ". " << titleArr[i][0] << endl;
        count++;
    }
    int indexFilm;
    int rating2;
    cout << "Film yang ingin di rating : ";
    cin >> indexFilm;
    cout << "Film yang dipilih : " << titleArr[indexFilm-1][0] << endl
         << "Berikan rating 0-5: ";
    cin >> rating2;
    cout << titleArr[indexFilm-1][1] << endl;
    string temp2 = titleArr[indexFilm-1][1];
    int newRating;
    try {
        newRating = (rating2 + stoi(temp2))/(stoi(temp2) + 1);
        cout << newRating << endl;
    } catch (const std::invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        // Handle the error appropriately, e.g., set newRating to a default value,
        // print an error message, or exit the program.
        newRating = 0; // Example: set to a default value
    } catch (const std::out_of_range& e) {
        cerr << "Out of range: " << e.what() << endl;
        // Handle the error appropriately
        newRating = 0; // Example: set to a default value
    }
    // titleArr[indexFilm-1][1] = newRating;
    dataFilm.close();

    return 0;
}