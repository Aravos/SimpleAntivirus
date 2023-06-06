#include <string>
#include <iostream>
#include <bitset>
using namespace std;

//Note passing by refrence is faster and more efficient than passsing by value as it avoids unneccesarily copiying the string
// & indicates this while Const defines that there is no need to modify the string

bool* stringToBinary(const string& text) {
    int N = text.length()*8;
    bool binary[N];

    for (int i=0;i<N;i++) {
        char c = text[i];
        //Seting up a object with bit size 8 as each ch has 8 bits
        int count = 0;
        for(bool a : bitset<8>(c)){
            binary[i*8+count] = a;
        }
    }
    return binary;
}

//RotWord = one-byte left circular shift
bool* Rotword(bool* ){

}
// Subword
// Rcon

// As we are using AES236 we will take 14 rounds
string* KeyScheduler(const string& mainkey, const int& N){
    string roundkeys[14];
    for(int i=0;i<N;i++){

    }
    return roundkeys; 

}

int main(){

    string plaintext;
    cin >> plaintext;
    cout << stringToBinary(plaintext);
    return 0;
}