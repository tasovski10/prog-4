#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct palhasher
{
    long long p=31, mod=1e9+9;
    int n;
    vector<long long> pows, pref, pref_rev;

    palhasher(const string &s)
    {
        n=s.size();
        pows.resize(n+1);
        pref.resize(n+1);
        pref_rev.resize(n+1);

        pows[0]=1;
        for(int i=1;i<=n;i++) pows[i]=(pows[i-1]*p)%mod;

        for(int i=0;i<n;i++)
            pref[i+1]=(pref[i]+(s[i]-'a'+1)*pows[i])%mod;

        string r=s;
        reverse(r.begin(), r.end());

        for(int i=0;i<n;i++)
            pref_rev[i+1]=(pref_rev[i]+(r[i]-'a'+1)*pows[i])%mod;
    }

    long long gethash(int l,int r)
    {
        long long val=(pref[r+1]-pref[l]+mod)%mod;
        return (val*pows[n-r-1])%mod;
    }

    long long getrevhash(int l,int r)
    {
        long long val=(pref_rev[r+1]-pref_rev[l]+mod)%mod;
        return (val*pows[n-r-1])%mod;
    }

    bool ispal(int l,int r)
    {
        int rl=n-1-r, rr=n-1-l;
        return gethash(l,r)==getrevhash(rl,rr);
    }
};

int main()
{
    string s;
    cin>>s;
    int n=s.size();

    palhasher h(s);

    vector<vector<int>> lvl(n, vector<int>(n+1,0));
    vector<long long> cnt(n+2,0);

    for(int len=1;len<=n;len++)
    {
        for(int i=0;i+len-1<n;i++)
        {
            int j=i+len-1;
            if(!h.ispal(i,j)) continue;

            lvl[i][len]=1;

            int half=len/2;
            if(half>0 && h.ispal(i,i+half-1))
                lvl[i][len]=lvl[i][half]+1;
            else
                lvl[i][len]=1;

            cnt[lvl[i][len]]++;
        }
    }

    for(int k=n;k>=1;k--) cnt[k]+=cnt[k+1];

    for(int k=1;k<=n;k++) cout<<cnt[k]<<" ";
    cout<<"\n";

    return 0;
}
