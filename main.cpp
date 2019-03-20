#include <iostream>
#include <fstream>
using namespace std;
class Arbore;

/**clasa Nod**/

class Nod
{
    int info;
    Nod *fiu,*frate;
public:
    Nod(int info,Nod* fiu=0,Nod* frate=0);
    Nod(const Nod &N);
    int getinfo();
    void setInfo(int info);
    Nod* getfiu();
    Nod* getnod();
    void setfiu(Nod* fiu);
    Nod* getfrate();
    void setfrate(Nod* frate);
    void operator = (Nod&);
    int operator == (Nod&);
    int operator != (Nod&);
    int operator < (Nod&);
    friend class Arbore;
};
int Nod::getinfo()
{
    return info;
}
Nod::Nod(int info, Nod* fiu, Nod* frate)
{
    this->info=info;
    this->fiu=fiu;
    this->frate=frate;
}
Nod::Nod(const Nod &N)
{
    this->info=N.info;
    this->fiu=0;
    this->frate=0;
}
Nod* Nod::getfiu()
{
    return fiu;
}
Nod* Nod::getfrate()
{
    return frate ;
}
void Nod::operator = (Nod &N)
{
    this->info=N.info;
    this->fiu=0;
    this->frate=0;
}
int Nod::operator == (Nod &N)
{
    return this->info==N.info;
}
int Nod::operator != (Nod &N)
{
    return this->info!=N.info;
}
int Nod::operator < (Nod &N)
{
    return this->info<N.info;
}

/**Clasa Arbore**/

class Arbore
{
    Nod *radacina;
public:
    int NrNoduri;
    Arbore();
    Arbore(const Arbore &A);
    ~Arbore();
    int isEmpty();
    void addfiu(Nod *M, Nod N);
    void addfrate(Nod *M,Nod N);
    void parcurgereLatime();
    void parcurgereAdancime();
    void parcurgereAdancime1(Nod *N);
    void afisareFrunze();
    void afisareFrunze1(Nod *N);
    int determinareInaltime(Nod *N);
    Nod* getnod(int info);
    void operator + (Arbore &A);
    void operator = (Arbore &A);
    bool operator == (Arbore &A);
    bool operator != (Arbore &A);
    bool operator < (Arbore &A);
    Nod* getradacina();
};
Arbore::Arbore(const Arbore &A)
{
    radacina=0;
    NrNoduri=A.NrNoduri;
    Nod *c,*p;
    addfiu(p,Nod(A.radacina->info));
    Nod *C[NrNoduri+1],*C2[NrNoduri+1];
    int st=0,dr=0;
    C[dr]=A.radacina;
    C2[dr]=radacina;
    while(st<=dr)
    {
        p=C2[st];
        c=C[st];
        st++;
        if(c->frate!=0)
        {
            addfrate(p,Nod(c->frate->info));
            dr++;
            C2[dr]=p->frate;
            C[dr]=c->frate;
        }
        if(c->fiu!=0)
        {
            addfiu(p,Nod(c->fiu->info));
            dr++;
            C2[dr]=p->fiu;
            C[dr]=c->fiu;
        }
    }
}

void Arbore::operator + (Arbore &A)
{
    Nod* p;
    NrNoduri+=A.NrNoduri;
    p=radacina;
    if(p->fiu==0)p->fiu=A.radacina;
    else
    {
        p=p->fiu;
        while(p->frate!=0)p=p->frate;
        p->frate=A.radacina;
    }
}
void Arbore::operator=(Arbore &A)
{
    NrNoduri=A.NrNoduri;
    radacina=0;
    Nod *c,*p;
    addfiu(p,Nod(A.radacina->info));
    Nod *C[NrNoduri+1],*C2[NrNoduri+1];
    int st=0,dr=0;
    C[dr]=A.radacina;
    C2[dr]=radacina;
    while(st<=dr)
    {
        p=C2[st];
        c=C[st];
        st++;
        if(c->frate!=0)
        {
            addfrate(p,Nod(c->frate->info));
            dr++;
            C2[dr]=p->frate;
            C[dr]=c->frate;
        }
        if(c->fiu!=0)
        {
            addfiu(p,Nod(c->fiu->info));
            dr++;
            C2[dr]=p->fiu;
            C[dr]=c->fiu;
        }
    }
}
bool Arbore::operator==(Arbore &A)
{
    if (NrNoduri!=A.NrNoduri)return false;
    Nod *c,*p;
    // addfiu(p,Nod(A.radacina->info));
    Nod *C[NrNoduri+1],*C2[NrNoduri+1];
    int st=0,dr=0;
    C[dr]=A.radacina;
    C2[dr]=radacina;
    while(st<=dr)
    {
        p=C2[st];
        c=C[st];
        if(p->info!=c->info)return false;
        st++;
        if(c->frate!=0&&p->frate!=0)
        {
            dr++;
            C2[dr]=p->frate;
            C[dr]=c->frate;
        }
        if(c->fiu!=0&&p->fiu!=0)
        {
            dr++;
            C2[dr]=p->fiu;
            C[dr]=c->fiu;
        }
    }
    if(dr!=NrNoduri-1)return false;
    return true;
}
bool Arbore::operator!=(Arbore &A)
{
    return !(*this==A);
}
bool Arbore::operator<(Arbore &A)
{
    return NrNoduri<A.NrNoduri;
}
void Arbore::parcurgereLatime()
{
    Nod *c;
    Nod *C[NrNoduri+1],*C2[NrNoduri+1];
    int st=0,dr=0,dr2=0,st2=1;
    C[dr]=radacina;
    cout<<"\nParcurgerea in latime: ";
    while(st<=dr)
    {
        c=C[st];
        cout<<c->info<<" ";
        if(c->fiu!=0)
        {
            dr2++;
            C2[dr2]=c->fiu;
        }
        st++;
        if(c->frate!=0)
        {
            dr++;
            C[dr]=c->frate;
        }

        else
        {
            if(st2<=dr2)
            {
                dr++;
                C[dr]=C2[st2];
                st2++;
            }
        }
    }
}
void Arbore::parcurgereAdancime()
{
    cout<<"\nParcurgerea in adancime: ";
    parcurgereAdancime1(radacina);
}
void Arbore::parcurgereAdancime1(Nod* N)
{
    cout<<N->info<<" ";
    if(N->fiu!=0)parcurgereAdancime1(N->fiu);
    if(N->frate!=0)parcurgereAdancime1(N->frate);
}
void Arbore::afisareFrunze()
{
    cout<<"\nFrunzele arborelui sunt: ";
    afisareFrunze1(radacina);
}
void Arbore::afisareFrunze1(Nod* N)
{
    if(N->fiu==0)cout<<N->info<<" ";
    if(N->fiu!=0)afisareFrunze1(N->fiu);
    if(N->frate!=0)afisareFrunze1(N->frate);

}
int Arbore::determinareInaltime(Nod* N)
{
    if(N->fiu!=0)return 1+determinareInaltime(N->fiu);
    if(N->frate!=0)return determinareInaltime(N->frate);
    if(N->fiu==0&&N->frate==0)return 1;
}
Nod* Arbore::getnod(int info)
{
    int i;
    Nod *C[NrNoduri+1],*c;
    int st=0,dr=0;
    C[dr]=radacina;
    while(C[st]!=0)
    {
        c=C[st];
        if(c->info==info)return c;
        st++;
        if(c->fiu!=0)
        {
            dr++;
            C[dr]=c->fiu;
        }
        if(c->frate!=0)
        {
            dr++;
            C[dr]=c->frate;
        }
    }
}
istream & operator >>(istream & i, Arbore &A)
{
    int info,nrnod,j,info_t;
    Nod *p;
    i>>nrnod;
    A.NrNoduri=nrnod;
    i>>info;
    A.addfiu(p,Nod(info));
    for(j=2; j<=nrnod; j++)
    {
        i>>info>>info_t;
        p=A.getnod(info_t);
        if((*p).getfiu()!=0)
        {
            p=(*p).getfiu();
            while((*p).getfrate()!=0)p=(*p).getfrate();
            A.addfrate(p,Nod(info));
        }
        else A.addfiu(p,Nod(info));
    }
}
ostream& operator<<(ostream& out, Arbore &A)
{
    int info,t;
    Nod *p,*c,*ct;
    Nod *C[A.NrNoduri+1],*Ct[A.NrNoduri+1];
    int st=0,dr=0;
    out<<(*A.getradacina()).getinfo()<<"\n";
    p=A.getradacina();
    C[dr]=p;
    Ct[dr]=0;
    while(st<=dr)
    {
        c=C[st];
        ct=Ct[st];
        if(ct!=0)out<<(*c).getinfo()<<" "<<(*ct).getinfo()<<"\n";
        st++;
        if((*c).getfiu()!=0)
        {
            dr++;
            C[dr]=(*c).getfiu();
            Ct[dr]=c;
        }
        if((*c).getfrate()!=0)
        {
            dr++;
            C[dr]=(*c).getfrate();
            Ct[dr]=ct;
        }
    }
}
Arbore::Arbore()
{
    radacina=0;
    NrNoduri=0;
}
Arbore::~Arbore()
{
    Nod *c;
    Nod *C[NrNoduri+1];
    int st=0,dr=0;
    C[dr]=radacina;
    while(st<=dr)
    {
        c=C[st];
        st++;
        if(c->frate!=0)
        {
            dr++;
            C[dr]=c->frate;
        }
        if(c->fiu!=0)
        {
            dr++;
            C[dr]=c->fiu;
        }
        //delete c;
    }
}

int Arbore::isEmpty()
{
    return radacina==0;
}
void Arbore::addfiu(Nod *M,Nod N)
{
    Nod *p;
    p=new Nod(N.info);
    if(isEmpty())
        radacina=p;
    else
        M->fiu=p;
}
void Arbore::addfrate(Nod *M,Nod N)
{
    Nod *p;
    p=new Nod(N.info);
    if(isEmpty())
        radacina=p;
    else
        M->frate=p;
}
Nod* Arbore::getradacina()
{
    return radacina;
}
int main()
{
    ifstream fin("fisier.in");
    Arbore L,R,Q;
    fin>>L;
    cout<<"Continutul Arborelui:\n"<<L;
    L.parcurgereLatime();
    L.parcurgereAdancime();
    cout<<"\n"<<L.determinareInaltime(L.getradacina());
    L.afisareFrunze();
    fin>>R;
    L+R;
    cout<<"\nContinutul Arborelui:\n"<<L;
    Q=L;
    cout<<"\nContinutul Arborelui:\n"<<Q;
    cout<<(L<Q);

    return 0;
}
