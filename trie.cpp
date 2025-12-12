//
// Created by Angela Tasovski on 12.12.25.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

struct Trie{
    Trie* d[26]={nullptr};
    bool kraj=false;
    string lbl=""; // patricia label
};

void dodadi(Trie* root,const string& s){
    Trie* cur=root;
    for(char ch:s){
        char c=tolower(ch);
        if(c<'a'||c>'z')continue;
        int i=c-'a';
        if(!cur->d[i])cur->d[i]=new Trie();
        cur=cur->d[i];
    }
    cur->kraj=true;
}

// kompresija vo patricia (post-order)
void patricia(Trie* t){
    if(!t)return;

    for(int i=0;i<26;i++)
        if(t->d[i])patricia(t->d[i]); //rekurzivno gi obrabotuva site deca postorder

    int children=0,idx=-1;
    for(int i=0;i<26;i++)
        if(t->d[i]){children++;idx=i;}

    if(children!=1)return;

    Trie* c=t->d[idx];
    t->lbl.push_back('a'+idx); //dodavame vo label na roditel potoa i lableot na deteto
    t->lbl+=c->lbl;

    for(int i=0;i<26;i++)
        t->d[i]=c->d[i]; // skokame node eden

    t->kraj=c->kraj;
    delete c; //go briseme staroto dete oti go vgradivme vo roditelot
}

void pecatiTrie(Trie* t,string& cur){
    if(!t)return;
    if(t->kraj)cout<<cur<<"\n";

    for(int i=0;i<26;i++){
        if(t->d[i]){
            cur.push_back('a'+i);
            pecatiTrie(t->d[i],cur);
            cur.pop_back();
        }
    }
}

void pecatiPat(Trie* t,string& cur){
    if(!t)return;
    cur+=t->lbl;
    if(t->kraj)cout<<cur<<"\n";

    for(int i=0;i<26;i++)
        if(t->d[i])pecatiPat(t->d[i],cur); //rekurzija po deca

    cur.erase(cur.size()-t->lbl.size()); //trgame label sto go dodadovme
}

bool barajTrie(Trie* root,const string& s){
    Trie* cur=root;
    for(char ch:s){
        char c=tolower(ch);
        if(c<'a'||c>'z')return false;
        int i=c-'a';
        if(!cur->d[i])return false; //ako patekata ne postoi zborot ne postoi
        cur=cur->d[i];
    }
    return cur->kraj;
}

bool barajPat(Trie* t,const string& s,int p=0){
    if(!t)return false;

    int l=t->lbl.size();
    if(s.size()-p<l)return false;

    for(int i=0;i<l;i++)
        if(tolower(s[p+i])!=t->lbl[i])return false; //proveruva dali sledniot del od zborot se poklopuva so lbelot

    p+=l;
    if(p==s.size())return t->kraj;

    char c=tolower(s[p]);
    if(c<'a'||c>'z')return false;
    return barajPat(t->d[c-'a'],s,p); //zema sledna bukva i odi soodvetno dete
}

int main(){
    Trie* root=new Trie();
    // /Users/angelatasovski/CLionProjects/prog-4/wiki-100k.txt
    ifstream fin("./wiki-100k.txt");
    if(!fin){
        cerr<<"ne moze fajlot\n";
        return 1;
    }

    vector<string> w;
    string line;
    while(getline(fin,line)){
        if(line.empty()||line[0]=='#')continue;
        w.push_back(line);
    }

    for(auto&s:w)dodadi(root,s);

    string tmp="";
    pecatiTrie(root,tmp);

    patricia(root);
    pecatiPat(root,tmp);

    return 0;
}
