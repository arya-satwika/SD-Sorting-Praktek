#include <iostream>
#include <fstream>
#include <string>
#include <cmath> 
using namespace std;

struct Movies_Tree
{
    string title;
    int number_of_rating;
    double rating;
    Movies_Tree *left;
    Movies_Tree *right;
};

string users[5][2] = {{"", ""}, {"james", "password"},{"", ""},{"", ""}, {"pensil", "keren"}};
Movies_Tree *root = nullptr;

void introMenu();
void mainMenu();
bool login();
void registerUser();
void saveToFile(Movies_Tree *&fRoot);
void movieToTree();
void printMovie(Movies_Tree *&fRoot);
void changeRating(double newRating, Movies_Tree*& root, string title);
void printMovie(string movies[][3], int max);
void insertNewMovie(Movies_Tree *&node);
Movies_Tree* delMovie(Movies_Tree *root, string title, double rating);
void newMovie();

void movieToTree(){
    ifstream file("film.txt");
    string title;
    double rating;
    int number_of_rating;
    while (file >> title >> rating >> number_of_rating) {
        Movies_Tree *newNode = new Movies_Tree;
        newNode->title = title;
        newNode->rating = rating;
        newNode->number_of_rating = number_of_rating;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) {
            root = newNode;
        } else {
            Movies_Tree *current = root;

            while (true) {
                if (rating < current->rating) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        break;
                    }
                    current = current->left;
                } else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        break;
                    }
                    current = current->right;
                }
            }
        }
    }
    file.close();
}

int hashUser(string user){
    int first, second;
    first = (user[0] - '@')%10;
    second = (user[user.length()-1] - '@')%10;
    return (first*10 + second) % 5;
}



void printMovie(Movies_Tree *&fRoot) {
    if (fRoot == nullptr)
        return;
    else{
        printMovie(fRoot->left);
        cout << "=================="<< endl 
             << "Judul : " << fRoot->title << endl
             << "Rating : " << fRoot->rating << endl
             << "Jumlah Rating : " << fRoot->number_of_rating << endl
             << "=================="<< endl;
        printMovie(fRoot->right);
    }
}
void saveToFile(Movies_Tree *&fRoot) {
    
    ofstream file("film.txt", ios::app);
    if (fRoot == nullptr){return;}
    else{
        saveToFile(fRoot->left);
        file << fRoot->title << " " << fRoot->rating << " " << fRoot->number_of_rating << endl;
        file.close();
        saveToFile(fRoot->right);
    }
}

void changeRating(double newRating, Movies_Tree*& fRoot, string title) {
    if (fRoot == nullptr) {
        return;
    }
    
    else if (fRoot->title == title) {
        Movies_Tree *temp = new Movies_Tree;
        temp->rating = (newRating + (fRoot->rating * fRoot->number_of_rating)) / (fRoot->number_of_rating + 1);
        temp->rating = trunc(temp->rating * 10) / 10.0;  
        temp->number_of_rating = fRoot->number_of_rating + 1; 
        temp->title = fRoot->title;
        temp->left = nullptr; 
        temp->right = nullptr;
        cout << "====================================" << endl;        
        cout << "Rating film " << title << " telah diubah menjadi " << temp->rating << endl;
        cout << "====================================" << endl;
        root = delMovie(root, title, fRoot->rating);
        
        insertNewMovie(temp);
        
    }
    else {
        changeRating(newRating, fRoot->left, title);
        changeRating(newRating, fRoot->right, title);
    }
}
    


void insertNewMovie(Movies_Tree*&node) {
    Movies_Tree *curr = root;
    while(true) {
        if (node->rating < curr->rating) {
            if (curr->left == nullptr) {
                curr->left = node;
                break;
            }
            else
            curr = curr->left;
        } else if (node->rating >= curr->rating) {
            if (curr->right == nullptr) {
                curr->right = node;
                break;
            }
            else          
            curr = curr->right;
        }
    }
}

Movies_Tree* delMovie(Movies_Tree *root, string title, double rating) {
    if (root == nullptr) {
        return nullptr;
    }
    if(root->title != title) {
        if (rating < root->rating) {
            root->left = delMovie(root->left, title, rating);
        }
        else if(rating >= root -> rating){
            root->right = delMovie(root->right, title, rating);
        } 
    }
    else if (root->title == title) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->right == nullptr) {
            Movies_Tree *temp = root->left;
            delete root;
            return temp;
        }
        else if (root->left == nullptr) {
            Movies_Tree *temp = root->right;
            delete root;
            return temp;
        }
        else {
            Movies_Tree *temp = root->right;    
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->title = temp->title;
            root->rating = temp->rating;
            root->number_of_rating = temp->number_of_rating;
            root->right = delMovie(root->right, temp->title, rating);
            return root;
        }   
    }
    return root;
}

void newMovie(){
    Movies_Tree* newMovie = new Movies_Tree;
    newMovie->left = nullptr;
    newMovie->right = nullptr;
    cout << "Masukkan Judul film: ";
    cin >> newMovie->title;
    cout << "Masukkan Rating: ";
    cin >> newMovie -> rating;
    newMovie->number_of_rating = 1;
    insertNewMovie(newMovie);
}


void mainMenu(){
    int choice;
    string title;
    double rating;
    cout << "====================================" << endl;
    cout << "1. Lihat Film" << endl;
    cout << "2. Ubah Rating Film" << endl;
    cout << "3. Tambah Film" << endl;
    cout << "4. Log Out " << endl;
    cout << "5. exit" << endl;
    cout << "Pilih menu: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            printMovie(root);
            mainMenu();
            break;
        case 2:
            printMovie(root);
            cout << "Masukkan judul film yang ingin diubah ratingnya: ";
            cin >> title;
            cout << "Masukkan rating baru: ";
            cin >> rating;
            changeRating(rating, root, title);
            mainMenu();
            break;
        case 3:
            newMovie();
            mainMenu();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan aplikasi ini" << endl;
            saveToFile(root);
            exit(0);
            break;
        case 4:
            introMenu();

        default:
            cout << "Pilihan tidak valid." << endl;
    }
}

bool login(){
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    int hash = hashUser(username);
    if (users[hash][0] == username)
    {
        if (users[hash][1] == password)
        {
            cout << "Login Berhasil" << endl;
            movieToTree();
            return true;
        }
        else
        {
            cout << "LOGIN GAGAL!!" << endl;
            return false;

        }
    }
    else{
        cout << "Login Gagal" << endl;
        return false;
    }
}

int linearProbing(int oldHash, int newHash, string username){
    if (oldHash == newHash)
    {
        cout << "Hash table penuh" << endl;
        return -1;
    }
    else if (users[newHash][0] == "")
    {
        return newHash;
    }
    else if (users[newHash][0] == username)
    {
        return -1;
    }
    else
    {
        return linearProbing(oldHash, (newHash+1) % 5, username);
    }
    return -1;
}

int existingUser(string username, int hash){
    if (users[hash][0] == username)
    {
        return hash;
    }
    else if (users[hash][0] == "")
    {
        return -1;    
    }
    else
    {
        int newHash = (hash+1) % 5;
        if (hashUser(username) == newHash)
        {
            cout << "Hash table penuh" << endl;
            return -1;
        }
        else 
        return existingUser(username, newHash);
    }
    
}

void registerUser(){
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;
    int hash = hashUser(username);
    if (users[hash][0] == "")
    {
        users[hash][0] = username;
        users[hash][1] = password;
        cout << "====================================" << endl;
        cout << "Username: " << users[hash][0] << endl;
        cout << "Register Berhasil" << endl;
        return;
    }
    else if (users[hash][0] == username)
    {
        cout << "====================================" << endl;
        cout << "Username sudah terdaftar!" << endl;
        registerUser();
        return;
    }
    else 
    {
        int newHash = linearProbing(hash, (hash+1) % 5, username);
        if (newHash != -1)
        {
            users[newHash][0] = username;
            users[newHash][1] = password;
            cout << "Register Berhasil" << endl;
            return;
        }
        else{
            cout << "Silahkan login dengan username yang sudah terdaftar" << endl;
            registerUser();
            return;
        }
        
    }
}

void deleteUser(){
    string username,password;
    cout << "Masukkan username yang ingin dihapus: ";
    cin >> username;
    int find = existingUser(username, hashUser(username));
    
    if(find != -1)
    {
        cout << "Konfirmasi Password:";
        cin >> password;
        if (users[find][1] != password)
        {
            cout << "Password salah" << endl;
            deleteUser();
        }
        else
        users[find][0] = "-1";
        users[find][1] = "-1";
        cout << "User berhasil dihapus" << endl;
        return;
    }   
    else
    {
        cout << "User tidak ditemukan" << endl;
        return;
    }
    return;
}

void introMenu(){
    cout << "Selamat datang di aplikasi film" << endl;
    cout << "====================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Keluar" << endl;
    cout << "4. Delete User" << endl;
    cout << "Pilih menu: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        while(!login()){
            cout << "Silahkan coba lagi" << endl;
            cout << "====================================" << endl;
        }
        mainMenu();
        break;
    case 2:
        registerUser();
        mainMenu();
        break;
    case 3:
        cout << "Terima kasih telah menggunakan aplikasi ini" << endl;
        exit(0);
        break;
    case 4:
        deleteUser();
        introMenu();
        break;
    default:
        break;
    }
}



int main()
{
    movieToTree();
    ofstream clear("film.txt");
    clear.close();
    introMenu();
    return 0;
}
