#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

long long hashiraj(int start,int kraj,vector<long long>& pref,vector<long long>& pw,int n,long long mod)
{
    long long v=(pref[kraj+1]-pref[start]+mod)%mod;
    v=(v*pw[n-start])%mod;
    return v;
}

int main()
{
    string s,dozvoleni;
    int maxlosi;
    cin>>s>>dozvoleni>>maxlosi;

    int n=s.size();
    vector<int> losi(n+1,0);

    for(int i=0;i<n;i++)
    {
        if(dozvoleni[s[i]-'a']=='0')
            losi[i+1]=losi[i]+1;
        else
            losi[i+1]=losi[i];
    }

    long long mod=1e9+9;
    long long p=31;

    vector<long long> pw(n+1,1);
    for(int i=1;i<=n;i++)
        pw[i]=(pw[i-1]*p)%mod;

    vector<long long> pref(n+1,0);
    for(int i=0;i<n;i++)
        pref[i+1]=(pref[i]+(s[i]-'a'+1)*pw[i])%mod;

    unordered_set<long long> unikat;
    unikat.reserve(1e5);

    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            int losiBroj=losi[j+1]-losi[i];
            if(losiBroj>maxlosi) break;
            long long h=hashiraj(i,j,pref,pw,n,mod);
            unikat.insert(h);
        }
    }

    cout<<unikat.size();
    return 0;
}
