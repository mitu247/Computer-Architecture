
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ll;
typedef double db;

ll mod = 4294964296;

ll binpow(ll a, ll b){
    if(b==0) return 1;
    ll k = binpow(a,b/2);
    k*=k; k%=mod;
    if(b%2==1) k*=a;
    return k%mod;
}



ll pt[36], grs[16]={0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1};

ll merj(ll a, ll b, ll c){
    return a*pt[31] + b*pt[19] + c;

}

void binrep(ll n){
    for(ll i=31; i>=0; i--){
        ((n&pt[i])==0)? cout<< "0" : cout<< "1";
        if(i%4==0) cout<< " ";
    if(i==0) break;
    }
}

int main(){
        ofstream out("fpa_test.txt");
    streambuf *coutbuf = std::cout.rdbuf();
    cout.rdbuf(out.rdbuf());

    pt[0]=1;
    for(ll i=1; i<36; i++){
        pt[i]=pt[i-1]+pt[i-1];
    }
    ll g = 3, h = 9, m=400;

    while(m--){
        ll g1 , g2, g3;
        ((g&pt[31]))? g1 = 1 : g1 = 0;
        g2 = (g/pt[19])%(pt[12]);
        g3 = g%(pt[19]);
        //cout<< g1<< " "<< g2<< " "<< g3<< endl;
        binrep(g);
        cout<< " + ";
        g+=4000000001;
        g%=(pt[32]);


        ll h1 , h2, h3;
        ((h&pt[31]))? h1 = 1 : h1 = 0;
        h2 = (h/pt[19])%(pt[12]);
        h3 = h%(pt[19]);
        //cout<< h1<< " "<< h2<< " "<< h3<< endl;
        binrep(h);
        cout<< " = ";
        h+=4000008001;
        if(m==100 || m==300) h+=pt[31];
        if(m%200==0) h+=pt[23];
        h%=(pt[32]);

        ll a1, a2, a3;
        ll b1, b2, b3;
        if(g2>h2 || (g2==h2 && g3>=h3)){
            a1 = g1;
            a2 = g2;
            a3 = g3;
            b1 = h1;
            b2 = h2;
            b3 = h3;
        }
        else if(g2<h2 || (g2==h2 && g3<h3)){
            a1 = h1;
            a2 = h2;
            a3 = h3;
            b1 = g1;
            b2 = g2;
            b3 = g3;
        }
        b3*=pt[12];
        a3*=pt[12];
        b3+=pt[31];
        a3+=pt[31];

        while(b2<a2){
            b3/=2;
            b2++;
            if(b3==0) b2=a2;
        }
        ll f1 = a1, f2 = a2, f3;
        if((a1^b1)==1){
            f3 = a3-b3;
        }
        else{
            f3 = a3+b3;
        }
        f2++;
        while((f3&pt[32])==0){
            f3*=2;
            f2--;
        }
        f3-=pt[32];
        //binrep(merj(f1,f2,f3/pt[19]));
        //cout<< endl;
        f3*=4;
        for(ll i=0; i<5; i++){
            ll r=f3%16;
            f3/=8;
            f3+=grs[r];
        }
        ll f = merj(f1,f2,f3);
        binrep(f);
        cout<< endl;
    }
}
// 0110 1111 1110 0111 1010 1000 0101 0100  + 0110 1111 1111 0001 1000 1011 1001 1010  = 0110 1111 1111 0101 0111 0101 1010 1111
