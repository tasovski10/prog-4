#include <bits/stdc++.h>
using namespace std;

string pomos(string& tekst,int dolzina){
    if(dolzina==0)return "";
    int p=256,mod=1e9+7,n=tekst.size();

    long long hstepen=1;
    for(int i=0;i<dolzina-1;i++)
        hstepen=(hstepen*p)%mod;

    long long hesh=0;
    for(int i=0;i<dolzina;i++)
        hesh=(hesh*p+tekst[i])%mod;

    unordered_map<long long,vector<int>> mapa; // cuva listw od site poz kaj sto e najden toj hasj
    mapa[hesh]={0};

    for(int i=1;i<=n-dolzina;i++){
        hesh=(p*(hesh-tekst[i-1]*hstepen%mod+mod)+tekst[i+dolzina-1])%mod;
        if(hesh<0)
            hesh+=mod;
        if(mapa.find(hesh)!=mapa.end()){
            for(int j:mapa[hesh])
                if(tekst.substr(j,dolzina)==tekst.substr(i,dolzina))
                    return tekst.substr(i,dolzina);
        }
        mapa[hesh].push_back(i);
    }
    return "";
}

string najdolgduplikat(string tekst){
    int levo=1,desno=tekst.size()-1;
    string odgovor;

    while(levo<=desno){
        int sredina=(levo+desno)/2;
        string rezultat=pomos(tekst,sredina);

        if(!rezultat.empty()){
            if(rezultat.size()>odgovor.size())odgovor=rezultat;
            levo=sredina+1;
        }else desno=sredina-1;
    }
    return odgovor;
}
