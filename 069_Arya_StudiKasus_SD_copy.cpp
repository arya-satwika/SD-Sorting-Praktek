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
void login();
void registerUser();
void saveToFile(Movies_Tree *&fRoot);
void movieToTree();
void printMovie(Movies_Tree *&fRoot);
void changeRating(double newRating, Movies_Tree*& root, string title);
void printMovie(string movies[][3], int max);
void insertNewMovie(Movies_Tree *&node);
Movies_Tree* delMovie(Movies_Tree *root, string title, double rating);

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
            Movies_Tree *parent = nullptr;

            while (true) {
                parent = current;
                if (rating < current->rating) {
                    current = current->left;
                    if (current == nullptr) {
                        parent->left = newNode;
                        break;
                    }
                } else {
                    current = current->right;
                    if (current == nullptr) {
                        parent->right = newNode;
                        break;
                    }
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

// int nodesInTree(Movies_Tree *root) {
//     if (root == nullptr) {
//         return 0;
//     } else {
//         return 1 + nodesInTree(root->left) + nodesInTree(root->right);
//     }
    
// }

void printMovie(Movies_Tree *&fRoot) {
    if (fRoot == nullptr)
        return;
    else{
        printMovie(fRoot->left);
        cout << "Judul : " << fRoot->title << endl
             << "Rating : " << fRoot->rating << endl
             << "Jumlah Rating : " << fRoot->number_of_rating << endl
             << endl;
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
        
        cout << "Rating film " << title << " telah diubah menjadi " << temp->rating << endl;
        
        root = delMovie(root, title, fRoot->rating);
        cout << "deleted" << endl;
        
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
                cout << "curr =" << curr->left->title << endl;
                break;
            }
            else
            curr = curr->left;
        } else if (node->rating >= curr->rating) {
            if (curr->right == nullptr) {
                curr->right = node;
                cout << "curr =" << curr->right->title << endl;
                break;
            }
            else          
            curr = curr->right;
        }
    }
    cout << "inserted" << endl;
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

void mainMenu(){
    int choice;
    string title;
    double rating;
    cout << "1. Lihat Film" << endl;
    cout << "2. Ubah Rating Film" << endl;
    cout << "3. Tambah Film" << endl;
    cout << "4. Keluar" << endl;
    cout << "Pilih menu: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            printMovie(root);
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
            // Implement delete movie functionality
            break;
        case 4:
            cout << "Terima kasih telah menggunakan aplikasi ini" << endl;
            saveToFile(root);
            exit(0);
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
    }
}

void login(){
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
            mainMenu();
        }
        else
        {
            cout << "Login Gagal" << endl;

        }
    }
    else{
        cout << "Login Gagal" << endl;
    }
}

int linearProbing(int oldHash, int newHash){
    if (oldHash == newHash)
    {
        cout << "Hash table penuh" << endl;
        return -1;
    }
    else if (users[newHash][0] != "")
    {
        linearProbing(oldHash, newHash+1);
    }
    else
    {
        return newHash;
    }
    return -1;
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
        cout << "Register Berhasil" << endl;
        return;
    }
    else if (users[hash][0] == username)
    {
        cout << "Username sudah terdaftar" << endl;
        registerUser();
        return;
    }
    else if (users[hash][0] != "")
    {
        int newHash = linearProbing(hash, hash+1);
        if (newHash != -1)
        {
            users[newHash][0] = username;
            users[newHash][1] = password;
            cout << "Register Berhasil" << endl;
            return;
        }
        else{
            cout << "Silahkan login dengan username yang sudah terdaftar" << endl;
            return;
        }

    }
}
void introMenu(){
    cout << "Selamat datang di aplikasi film" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih menu: ";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        login();
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
