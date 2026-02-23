#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

void pomnozi(const array<float,3>& v,const float mat[3][3],array<float,3>& rez){
    for(int i=0;i<3;i++){
        rez[i]=0;
        for(int j=0;j<3;j++){
            rez[i]+=v[j]*mat[j][i];
        }
    }
}

array<float,3> rotacija(float px,float py,float agol){
    array<float,3> vektor={px,py,1};
    float mat[3][3]={
        {cos(agol),-sin(agol),0},
        {sin(agol),cos(agol),0},
        {0,0,1}
    };
    array<float,3> rez={0,0,0};
    pomnozi(vektor,mat,rez);
    return rez;
}

array<float,3> translacija(float px,float py,float dx,float dy){
    array<float,3> vektor={px,py,1};
    float mat[3][3]={
        {1,0,0},
        {0,1,0},
        {dx,dy,1}
    };
    array<float,3> rez={0,0,0};
    pomnozi(vektor,mat,rez);
    return rez;
}

array<float,3> skaliranje(float px,float py,float k){
    array<float,3> vektor={px,py,1};
    float mat[3][3]={
        {k,0,0},
        {0,k,0},
        {0,0,1}
    };
    array<float,3> rez={0,0,0};
    pomnozi(vektor,mat,rez);
    return rez;
}

int main(){
    string linija;
    ifstream datoteka("square.obj");
    vector<array<float,3>> teminja;

    if(datoteka.is_open()){
        while(getline(datoteka,linija)){
            if(linija.rfind("v ",0)==0){
                istringstream ss(linija);
                char oznaka;
                float x,y,z;
                ss>>oznaka>>x>>y>>z;
                teminja.push_back({x,y,z});
            }
        }
    }

    array<float,3> a=rotacija(teminja[0][0],teminja[0][1],M_PI/4);
    array<float,3> b=translacija(a[0],a[1],2,0);
    array<float,3> c=skaliranje(b[0],b[1],4);

    array<float,3> a1=rotacija(teminja[1][0],teminja[1][1],M_PI/4);
    array<float,3> b1=translacija(a1[0],a1[1],2,0);
    array<float,3> c1=skaliranje(b1[0],b1[1],4);

    array<float,3> a2=rotacija(teminja[2][0],teminja[2][1],M_PI/4);
    array<float,3> b2=translacija(a2[0],a2[1],2,0);
    array<float,3> c2=skaliranje(b2[0],b2[1],4);

    array<float,3> a3=rotacija(teminja[3][0],teminja[3][1],M_PI/4);
    array<float,3> b3=translacija(a3[0],a3[1],2,0);
    array<float,3> c3=skaliranje(b3[0],b3[1],4);

    for(auto& e:c) cout<<e<<" ";
    cout<<endl;
    for(auto& e:c1) cout<<e<<" ";
    cout<<endl;
    for(auto& e:c2) cout<<e<<" ";
    cout<<endl;
    for(auto& e:c3) cout<<e<<" ";

    return 0;
}