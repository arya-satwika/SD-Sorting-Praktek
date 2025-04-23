#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printMovie(string movies[][3], int max);

int lineInFile(string filename){
    ifstream file (filename);
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }
    return count;
}

void printMovie(string movies[][3], int max){
    cout << "Judul : " << movies[max-1][0] << endl
         << "Rating : " << movies[max-1][1] << endl
         << "Jumlah Rating : " << movies[max-1][2] << endl << endl;
    
    if (max != 0)
    {
        printMovie(movies, max-1);    
    }
    
}

void changeRating(double newRating, int newNRating, string title) {
    ifstream file("film.txt");
    ofstream tempFile("temp.txt", ios::app);
    string line;
    while (getline(file, line)) {
        if (line.find(title) != string::npos) { 
            tempFile << title << " " << newRating << " " << newNRating << endl; 
        } else {
            tempFile << line << endl; 
        }
    }
    file.close();
    tempFile.close();
    remove("film.txt"); 
    rename("temp.txt", "film.txt");
}

// The_Batman 2 201
// The_Ghost_and_the_Darkness_Remastered 4 15
// Daredevil 5 14
// // House_MD 4.7 200

void selectSort(string movies[][3]){
    int count = lineInFile("film.txt");
    int minimum;
    //selection sort
    for(int i =0; i < count; i++){
        minimum = i;
        for(int j = i+1; j < count; j++){
            if (movies[minimum][1] > movies[j][1])
            {
                minimum = j;
                
            }
        }
        swap(movies[i][0], movies[minimum][0]);
        swap(movies[i][1], movies[minimum][1]);
        swap(movies[i][2], movies[minimum][2]);
    }
    printMovie(movies, count);
}

int main()
{
    string line;
    string title, rating, nRating;
    int indexArr = 0;
    int sizeArr = lineInFile("film.txt");
    ifstream dataFilm ("film.txt");
    string titleArr[sizeArr][3];
    //masukkin data film ke array
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
    double tempRating;
    cout << "Film yang ingin di rating : ";
    cin >> indexFilm;
    cout << "Film yang dipilih : " << titleArr[indexFilm-1][0] << endl
         << "Berikan rating 0-5: ";
    cin >> tempRating;
    
    double newRating = (tempRating + (stod(titleArr[indexFilm-1][2])*stod(titleArr[indexFilm-1][1])))/(stod(titleArr[indexFilm-1][2]) + 1);
    int newNRating = stoi(titleArr[indexFilm-1][2]) + 1;
    dataFilm.close();
    selectSort(titleArr);
    changeRating(newRating, newNRating, titleArr[indexFilm-1][0]);

    return 0;
}
