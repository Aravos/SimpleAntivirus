#include <string>
#include <iostream>
#include <bitset>
using namespace std;

//Note passing by refrence is faster and more efficient than passsing by value as it avoids unneccesarily copiying the string
// & indicates this while Const defines that there is no need to modify the string

bool* stringToBinary(const string& text) {
    bool* binary = new bool[256];

    for (int i=0;i<32;i++) {
        char c = text[i];
        //Seting up a object with bit size 8 as each ch has 8 bits
        int count = 0;
        
        bitset<8> bits(c);
        for (int j = 0; j < 8; j++) {
            binary[i * 8 + j] = bits[j];
            //cout << bits[j];
        }
    }
    cout << endl;
    //cout << binary << endl;
    return binary;
}

//RotWord = one-byte left circular shift
// bool* Rotword(bool* ){

// }
// Subword
// Rcon

// As we are using AES236 we will take 14 rounds
string* KeyScheduler(const string& K0, const int& N){
    string roundkeys[14];
    bool binary[256];
    //binary = stringToBinary(K0);
    for(int i=0;i<N;i++){

    }
    return roundkeys; 

}

int main(){

    string plaintext;
    cin >> plaintext;
    bool* binary = stringToBinary(plaintext);
    bool b[256];
    for(int i = 0; i<256 ; i++){
        b[i] = *(binary + i);
        cout << b[i];
    }
    return 0;
}