#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

string rm_nuli(string s);

struct myint{
    string n;

    myint(){}
    myint(const string&s){n=rm_nuli(s);}
    myint(const char*s){n=rm_nuli(string(s));}

    myint&operator=(const myint&o){
        if(this==&o)return *this;
        n=o.n;
        return *this;
    }
    myint&operator=(const string&s){
        n=rm_nuli(s);
        return *this;
    }
    myint&operator=(const char*s){
        n=rm_nuli(string(s));
        return *this;
    }
};

string rm_nuli(string s){
    int i=0;
    while(i+1<s.size()&&s[i]=='0')i++;
    return s.substr(i);
}

ostream&operator<<(ostream&os,const myint&a){
    os<<rm_nuli(a.n);
    return os;
}

istream&operator>>(istream&is,myint&a){
    is>>a.n;
    a.n=rm_nuli(a.n);
    return is;
}

bool operator==(const myint&a,const myint&b){
    return rm_nuli(a.n)==rm_nuli(b.n);
}

bool operator!=(const myint&a,const myint&b){
    return rm_nuli(a.n)!=rm_nuli(b.n);
}

bool operator<(const myint&a,const myint&b){
    string x=rm_nuli(a.n);
    string y=rm_nuli(b.n);
    if(x.size()!=y.size())return x.size()<y.size();
    return x<y;
}

bool operator>(const myint&a,const myint&b){
    string x=rm_nuli(a.n);
    string y=rm_nuli(b.n);
    if(x.size()!=y.size())return x.size()>y.size();
    return x>y;
}

bool operator>=(const myint&a,const myint&b){
    return !(a<b);
}

bool operator<=(const myint&a,const myint&b){
    return(a<b)||(a==b);
}

myint operator+(const myint&a,const myint&b){
    string x=a.n,y=b.n;
    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());
    string r="";
    int o=0;
    for(int i=0;i<max(x.size(),y.size());i++){
        int p1=(i<x.size())?x[i]-'0':0;
        int p2=(i<y.size())?y[i]-'0':0;
        int s=p1+p2+o;
        r.push_back(s%10+'0');
        o=s/10;
    }
    if(o)r.push_back(o+'0');
    reverse(r.begin(),r.end());
    return{rm_nuli(r)};
}

myint operator-(const myint&a,const myint&b){
    string x=a.n,y=b.n;
    if(myint(x)<myint(y))swap(x,y);
    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());
    string r="";
    int br=0;
    for(int i=0;i<x.size();i++){
        int p1=x[i]-'0'-br;
        int p2=(i<y.size())?y[i]-'0':0;
        if(p1<p2){
            p1+=10;
            br=1;
        }else br=0;
        r.push_back(p1-p2+'0');
    }
    reverse(r.begin(),r.end());
    return{rm_nuli(r)};
}

myint operator*(const myint&a,const myint&b){
    string x=a.n,y=b.n;
    if(x=="0"||y=="0")return{"0"};
    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());
    vector<int>r(x.size()+y.size(),0);
    for(int i=0;i<x.size();i++)
        for(int j=0;j<y.size();j++)
            r[i+j]+=(x[i]-'0')*(y[j]-'0');
    for(int i=0;i<r.size();i++){
        int o=r[i]/10;
        r[i]%=10;
        if(i+1<r.size())r[i+1]+=o;
    }
    string s="";
    for(auto&i:r)s.push_back(i+'0');
    reverse(s.begin(),s.end());
    return{rm_nuli(s)};
}

myint operator/(const myint&a,const myint&b){
    string x=rm_nuli(a.n);
    string y=rm_nuli(b.n);
    if(y=="0"){
        cerr<<"KAKO DELIS SO 0?";
        return{"-1012007"};
    }
    string c="",r="";
    for(int i=0;i<x.size();i++){
        c.push_back(x[i]);
        c=rm_nuli(c);
        int cnt=0;
        while(myint(c)>=myint(y)){
            myint t1{c},t2{y};
            c=(t1-t2).n;
            cnt++;
        }
        r.push_back(cnt+'0');
    }
    return{rm_nuli(r)};
}

myint operator%(const myint&a,const myint&b){
    string x=rm_nuli(a.n);
    string y=rm_nuli(b.n);
    if(y=="0"){
        cerr<<"KAKO MODUL SO 0?";
        return{"-1012007"};
    }
    string c="";
    for(int i=0;i<x.size();i++){
        c.push_back(x[i]);
        c=rm_nuli(c);
        while(myint(c)>=myint(y)){
            myint t1{c},t2{y};
            c=(t1-t2).n;
        }
    }
    return{rm_nuli(c)};
}

myint binpow(myint a,myint b){
    myint z{"0"},o{"1"},t{"2"};
    if(b==z)return o;
    myint h=b/t;
    myint r=binpow(a,h);
    if(b%t==o)return r*r*a;
    else return r*r;
}

bool fermatTest(myint p){
    myint z{"0"},o{"1"},t{"2"},h{"3"};
    if(p<=o)return false;
    if(p==t||p==h)return true;
    if(p%t==z)return false;
    myint a{"2"};
    if(p<=a)a="1";
    myint pm=p-o;
    myint ts=binpow(a,pm)%p;
    return ts==o;
}

vector<myint>dijkstraPrimes(myint n){
    vector<pair<myint,myint>>pl;
    vector<myint>pr;
    myint o{"1"},t{"2"};
    for(myint i=t;i<=n;i=i+o){
        bool c=false;
        for(int j=0;j<pl.size();j++){
            while(pl[j].second<i)
                pl[j].second=pl[j].second+pl[j].first;
            if(pl[j].second==i)c=true;
        }
        if(!c){
            pl.push_back({i,i*i});
            pr.push_back(i);
        }
    }
    return pr;
}

int main(){
    myint a{"146738236478392347389234678392345674839234783947389237829467389236782947389"};
    myint b{"50744673827832738237283723827382372837823"};

    myint c=a+b;
    myint d=a-b;
    myint e=a*b;
    myint f=a/b;
    myint g=a%b;

    cout<<c.n<<"\n";
    cout<<d.n<<"\n";
    cout<<e.n<<"\n";
    cout<<f.n<<"\n";
    cout<<g.n<<"\n";

    myint n;
    cin>>n;
    vector<myint>v=dijkstraPrimes(n);
    for(auto&i:v)cout<<i<<" ";

    myint x{"123"},y{"1090"};
    cout<<binpow(x,y)<<"\n";
    cout<<fermatTest("5");
    return 0;
}
