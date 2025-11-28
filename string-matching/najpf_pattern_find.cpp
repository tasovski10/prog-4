#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

vector<int> rabinkarp(string& txt, string& s)
{
    int p = 13;
    int mod = 1e9 + 9;
    int slen = s.length(), tlen = txt.length();

    vector<long long> stepen(max(slen, tlen));
    stepen[0] = 1;
    for (int i = 1; i < max(slen, tlen); i++)
    {
        stepen[i] = (stepen[i-1] * p) % mod;
    }

    vector<long long> htekst(tlen + 1, 0);
    for (int i = 0; i < tlen; i++)
    {
        htekst[i + 1] = (htekst[i] + (txt[i] - 'a' + 1) * stepen[i]) % mod;
    }

    long long hstring = 0;
    for (int i = 0; i < slen; i++)
    {
        hstring = (hstring + (s[i] - 'a' + 1) * stepen[i]) % mod;
    }

    vector<int> pojavi;
    for (int i = 0; i + slen - 1 < tlen; i++)
    {
        long long curr = (htekst[i + slen] + mod - htekst[i]) % mod;
        if (curr == hstring * stepen[i] % mod)
        {
            pojavi.push_back(i);
        }
    }
    return pojavi;
}

int main()
{
    int t;
    cin >> t;

    vector<pair<int, vector<int>>> rez;

    for (int i = 0; i < t; i++)
    {
        string a, b;
        cin >> a >> b;
        vector<int> tmp = rabinkarp(a, b);
        rez.push_back({ tmp.size(), tmp });
    }

    for (int i = 0; i < t; i++)
    {
        if (rez[i].first == 0)
        {
            cout << "Not Found\n\n";
        }
        else
        {
            cout << rez[i].first << '\n';
            for (int& idx : rez[i].second)
            {
                cout << idx + 1 << " ";
            }
            cout << "\n\n";
        }
    }
    return 0;
}
