#include <cstring>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

vector<int> rk(string& shablon, string& tekst)
{
    int p = 13;
    int mod = 1000000009;
    int n = shablon.length(), m = tekst.length();

    vector<long long> stepen(max(n,m));
    stepen[0] = 1;
    for(int i=1;i<max(n,m);i++)
        stepen[i] = (stepen[i-1] * p) % mod;

    vector<long long> hes(m+1, 0);
    for(int i=0;i<m;i++)
        hes[i+1] = (hes[i] + (tekst[i]-'a'+1) * stepen[i]) % mod;

    long long hes_s = 0;
    for(int i=0;i<n;i++)
        hes_s = (hes_s + (shablon[i]-'a'+1) * stepen[i]) % mod;

    vector<int> pojavi;
    for(int i=0;i+n-1<m;i++)
    {
        long long seg = (hes[i+n] + mod - hes[i]) % mod;
        if(seg==hes_s * stepen[i] % mod)
            pojavi.push_back(i);
    }
    return pojavi;
}

class gerstring {
    uint32_t dolzina;
    char podatok[12];

    bool kratko() const {
        return dolzina <= 12;
    }

    char* ptr() const {
        char* p;
        memcpy(&p, podatok + 4, sizeof(p));
        return p;
    }

    void setptr(char* p) {
        memcpy(podatok + 4, &p, sizeof(p));
    }

public:
    gerstring(const string& s) {
        dolzina = s.size();

        if(kratko()) {
            memcpy(podatok, s.data(), dolzina);
            if(dolzina < 12) memset(podatok + dolzina, 0, 12 - dolzina);
        }
        else {
            memcpy(podatok, s.data(), 4);
            char* h = new char[dolzina];
            memcpy(h, s.data(), dolzina);
            setptr(h);
        }
    }

    gerstring(const gerstring& o) {
        dolzina = o.dolzina;
        if(kratko()) {
            memcpy(podatok, o.podatok, 12);
        } else {
            memcpy(podatok, o.podatok, 4);
            char* h = new char[dolzina];
            memcpy(h, o.ptr(), dolzina);
            setptr(h);
        }
    }

    gerstring& operator=(const gerstring& o) {
        dolzina = o.dolzina;
        if(kratko()) {
            memcpy(podatok, o.podatok, 12);
        } else {
            memcpy(podatok, o.podatok, 4);
            char* h = new char[dolzina];
            memcpy(h, o.ptr(), dolzina);
            setptr(h);
        }
        return *this;
    }

    ~gerstring() {
        if(!kratko())
            delete[] ptr();
    }

    string kako_string() const {
        if(kratko()) return string(podatok, dolzina);
        return string(ptr(), dolzina);
    }

    int getdol() const {
        return dolzina;
    }

    char& operator[](int i) {
        return kratko() ? podatok[i] : ptr()[i];
    }

    bool operator==(const gerstring& o) const {
        if(dolzina!=o.dolzina) return false;
        if(memcmp(podatok, o.podatok, 4)!=0) return false;

        if(kratko())
            return memcmp(podatok,o.podatok,dolzina)==0;

        return memcmp(ptr(), o.ptr(), dolzina)==0;
    }

    char at(int i) {
        return kratko() ? podatok[i] : ptr()[i];
    }

    gerstring operator+(const gerstring& o) const {
        string t = this->kako_string() + o.kako_string();
        return gerstring(t);
    }

    bool find(string s) {
        string a = kako_string();
        vector<int> p = rk(s,a);
        return p.size() != 0;
    }

    bool find(gerstring s) {
        return find(s.kako_string());
    }

    bool empty() const {
        return dolzina == 0;
    }

    void clear() {
        if(!kratko()) delete[] ptr();
        dolzina = 0;
        memset(podatok,0,12);
    }
};

ostream& operator<<(ostream& os, const gerstring& gs) {
    os << gs.kako_string();
    return os;
}

int main() {
    gerstring a("hello");
    cout << a << '\n';

    gerstring b("WorldTest123");
    cout << b.at(3) << '\n';

    gerstring x("the quick brown fox"), y("quick"), z("slow");

    gerstring c = y + z;
    cout << c << '\n';

    cout << (c == x) << " " << (c == c) << '\n';

    cout << c.getdol() << '\n';

    cout << x.find(y) << " " << x.find(z) << '\n';

    string raw = "ABCDE";
    cout << raw[2] << '\n';
    raw[2] = 'Z';
    cout << raw << '\n';

    gerstring k1("Sample text"), k2("short");
    gerstring k3 = k1, k4 = k2;

    cout << k3 << '\n';
    cout << k4 << '\n';

    k3 = k4;
    cout << k3 << '\n';

    cout << x.find(k2) << '\n';
    cout << x.find(y) << '\n';

    return 0;
}