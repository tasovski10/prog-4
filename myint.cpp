#include <bits/stdc++.h>
using namespace std;

struct mi{
    string n;
    friend bool operator>=(string a,string b);
    friend mi operator+(mi& a,mi& b);
    friend mi operator-(mi& a,mi& b);
    friend mi operator*(mi& a,mi& b);
    friend mi operator/(mi& a,mi& b);
};

string rn(string s){
    int i=0;
    while(i+1<s.size()&&s[i]=='0') i++;
    return s.substr(i);
}

bool operator>=(string a,string b){
    a=rn(a);
    b=rn(b);
    if(a.size()!=b.size()) return a.size()>b.size();
    return !(a<b);
}

mi operator+(mi& a,mi& b){
    string x=a.n,y=b.n;
    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());

    string r="";
    int o=0;

    for(int i=0;i<max(x.size(),y.size());i++){
        int b1=(i<x.size())?x[i]-'0':0;
        int b2=(i<y.size())?y[i]-'0':0;
        int s=b1+b2+o;
        r.push_back(s%10+'0');
        o=s/10;
    }

    if(o) r.push_back(o+'0');

    reverse(r.begin(),r.end());
    return {rn(r)};
}

mi operator-(mi& a,mi& b){
    string x=a.n,y=b.n;
    if(!(x>=y)) swap(x,y);

    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());

    string r="";
    int br=0;

    for(int i=0;i<x.size();i++){
        int b1=x[i]-'0'-br;
        int b2=(i<y.size())?y[i]-'0':0;

        if(b1<b2){
            b1+=10;
            borrow=1;
        }else borrow=0;

        r.push_back(b1-b2+'0');
    }

    reverse(r.begin(),r.end());
    return {rn(r)};
}

mi operator*(mi& a,mi& b){
    string x=a.n,y=b.n;
    if(x=="0"||y=="0") return {"0"};

    reverse(x.begin(),x.end());
    reverse(y.begin(),y.end());

    vector<int> r(x.size()+y.size(),0);

    for(int i=0;i<x.size();i++){
        for(int j=0;j<y.size();j++){
            r[i+j]+=(x[i]-'0')*(y[j]-'0');
        }
    }

    for(int i=0;i<r.size();i++){
        int c=r[i]/10;
        r[i]%=10;
        if(i+1<r.size()) r[i+1]+=c;
    }

    string s="";
    for(auto& t:r) s.push_back(t+'0');
    reverse(s.begin(),s.end());

    return {rn(s)};
}

mi operator/(mi& a,mi& b){
    string x=rn(a.n);
    string y=rn(b.n);

    if(y=="0"){
        cerr<<"delis so 0?";
        return {"-1012007"};
    }

    string cur="";
    string r="";

    for(int i=0;i<x.size();i++){
        cur.push_back(x[i]);
        cur=rn(cur);

        int cnt=0;
        while(cur>=y){
            mi t1{cur},t2{y};
            cur=(t1-t2).n;
            cnt++;
        }
        r.push_back(cnt+'0');
    }

    return {rn(r)};
}

int main(){
    mi a{"783947389237829467389236782947309876544675445677886589"};
    mi b{"50744673827832738237283723827382372837823"};

    mi c=a+b;
    mi d=a-b;
    mi e=a*b;
    mi f=a/b;

    cout<<c.n<<"\n";
    cout<<d.n<<"\n";
    cout<<e.n<<"\n";
    cout<<f.n<<"\n";

    return 0;
}
