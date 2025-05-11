#include <iostream>
#include <cmath> // For std::trunc
#include <fstream>
using namespace std;

int hashUser(string user){
    int first, second;
    first = (user[0] - '@')%10;
    second = (user[user.length()-1] - '@')%10;
    return (first*10 + second) % 5;
}

int main() {
    cout  << hashUser("james");
    
}