#include <iostream>

using namespace std;

char getTableElement(char a, char b) {
    a -= 'a';// 19
    b -= 'a';// 7
    return (a + b) % 26 + 'a';
}

string encrypt(string message, string key) {
    string result = message;
    for(int i=0;i<message.size();i++) {
        if(message[i] == ' ') {
            result[i] = ' ';
        }else{
            result[i] = getTableElement(message[i], key[i%key.size()]);
        }
    }
    return result;
}

int main() {
    for(char i='a';i<='z';i++) {
        for(char j='a';j<='z';j++) {
            cout<<getTableElement(i,j)<<' ';
        }
        cout<<endl;
    }

    string message = "visit beijing tomorrow";
    string cipertext = encrypt(message, "enjoy");
    cout<<cipertext<<endl;
    return 0;
}

