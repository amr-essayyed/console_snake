#include <iostream>
#include <string>
using namespace std;

class snake_vertebra
{
    int x, y;
};

class screen{

};

class snake{
    //bone head;
}; 

int main(int argc, char const *argv[])
{
    char s[2];
    string b = "abcdefghij";
    cout << b << endl;
    s[0]=b[0];
    s[1]=b[1];
    b[0]='0';
    for(int i =0, j=0; i<b.size(); i++, j=i%2){
        cout << i <<", " << j << "\n";
        b[i+1] = s[j];
        s[j]=b[i+2];

    }

    cout << b << endl;
    return 0;
}
