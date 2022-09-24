#include <iostream>

using namespace std;

string encrypt(string message, int key) {
    string result = message;
    for(int i=0;i<result.size();i++) {
        if(message[i] == ' ') continue;
        result[i] = ((message[i] - 'a' + key) % 26) + 'a';
    }
    return result;
}

string decrypt(string message, int key) {
    return encrypt(message, -key+26);
}


int main() {
    string c = "rjjy  rj  ts  ymj  xfggfym bj bnqq inxhzxxymj uqfs";
    for(int i=0;i<26;i++) {
        cout<<i<<". "<<decrypt(c, i)<<endl;
    }
    return 0;
}