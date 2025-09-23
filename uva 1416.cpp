#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int fw ( vector <vector <int> > a, int v) {
    for (int i=0; i<v; i++) {
        for (int j=0; j<v; j++) {
            for (int k=0; k<v; k++) {
                if (a[j][k]>a[j][i]+a[i][k]) { a[j][k]=a[j][i]+a[i][k]; }
            }
        }
    }
    int br=0;
    for (int i=0; i<v; i++) {
        for (int j=0; j<v; j++) {
            br+=a[i][j];
        }
    }
    return br;
}

int main () {
    int v,e,L;
    cin>>v>>e>>L;
    vector<vector <int> > a(v, vector<int> (v, L));
    for (int i=0 ;i<e; i++) {
        int tmp,tmp1,tmp2;
        cin>>tmp>>tmp1>>tmp2;
        a[tmp-1][tmp1-1]=tmp2;
        a[tmp1-1][tmp-1]=tmp2;
    }
    for (int i=0 ;i<v; i++) { a[i][i]=0; }
    int max=0;
    for (int l=0; l<v; l++) {
        for (int m=0; m<v; m++) {
            int tmp=a[l][m];
            a[l][m]=L;
            a[m][l]=L;
            int br=fw(a, v);
            if (br>max) { max=br; }
            a[l][m]=tmp;
            a[m][l]=tmp;
        }
    }
    cout<<fw(a,v)<<" "<<max;

    return 0;
}