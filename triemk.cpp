#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

struct Trie{
    bool kraj=false; //kazuva ddali ovde zavrsuva cel zbor
    map<string,Trie*> sleden; //strign zosto utf8 a trie pointer do sledno teme
};

string nextRune(const string& s,int& i){
    unsigned char c=s[i]; //od tuka znaeme kolku bajti e znakot
    int b=1; //pretpostavka 1

    //so bitmasks broime bajti
    if((c&0xE0)==0xC0)b=2;
    else if((c&0xF0)==0xE0)b=3;
    else if((c&0xF8)==0xF0)b=4;

    string r=s.substr(i,b); //site bajti sto gi sodrzi znakot
    i+=b;
    return r;
}

void dodadi(Trie* root,const string& zbor){
    Trie* cur=root;
    for(int i=0;i<zbor.size();){ //i se pomestuva preku nextrune
        string r=nextRune(zbor,i); //eden znak
        if(!cur->sleden.count(r))
            cur->sleden[r]=new Trie(); //ako nema pateka ideme novo teme
        cur=cur->sleden[r];
    }
    cur->kraj=true; //ovde zavrsuva zbor
}

void pecati(Trie* t,string pref=""){
    if(t->kraj)
        cout<<pref<<"\n";
    for(auto&p:t->sleden)//odime niz site sledni znaci, dodavame znak na prefiks, prodolzuvame
        pecati(p.second,pref+p.first);
}

int main(){
    Trie* root=new Trie();

    // /Users/angelatasovski/CLionProjects/prog-4/MK-dict.txt
    ifstream fin("MK-dict.txt");
    if(!fin){
        cerr<<"ne moze da se otvori fajlot\n";
        return 1;
    }

    string linija;
    while(getline(fin,linija)){
        if(!linija.empty()&&linija.back()=='\r')
            linija.pop_back(); // za mac, zosto \r go gleda kako del od zborot
        dodadi(root,linija);
    }

    pecati(root);
    return 0;
}
