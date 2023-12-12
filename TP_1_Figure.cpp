#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <list>
#include "file.cpp"

using namespace std;

class Figure{
    public :
        //**** exo1.1
        //declaration des 2 methodes abstraite
        virtual float perimetre()=0 ;
        virtual void afficherCaracteristiques()=0 ;

        //*** exo1.7 utilisation de variable et methode de classe
        //methode pour recuperer la valeur de la variable de classe
        static int nbrefigure(){
           return N;
        }

        // constructeur incrementant la varible de classe
        Figure(){
            N++;
        }

        virtual ~Figure(){N--;} ;

    protected :
        // variable de classe
        static int N;
};
int Figure::N=0;

//**** exo1.2
class Polygone : public Figure{
    protected :
        int nbCotes ;

    public :
        // constructeurs
        Polygone(int i) :Figure() {
            nbCotes=i;
        }

        virtual void afficherCaracteristiques(){
            cout<<endl<<"caracteristique du polygone : nombre de cotés ="<<nbCotes<<endl;
        }

        virtual ~Polygone(){} ;
};//class Polygone

//*** Exo1.3
class Rectangle : public Polygone{
    protected :
        float longu;
        float large;

    public :
        // constructeurs
        Rectangle(float lo, float la) : Polygone(4) {
            longu=lo;
            large=la;
        }

        void consulter_modifier(float lo, float la){
            longu=lo;
            large=la;
            cout<<"nouvelle longueur : "<<longu<<", et largeur : "<<large<<endl;
        }

        virtual float perimetre() {
            float f=2*longu+2*large;
            return (f);
        }

        virtual void afficherCaracteristiques(){
            Polygone::afficherCaracteristiques();
            cout<<"-rectangle de longueur : "<<longu<<", et de largeur :"<<large<<endl;
            cout<<"-perimetre : "<<perimetre()<<endl;
        }

        virtual ~Rectangle(){} ;
};// class Rectangle

class Carre : public Rectangle{
    public :
        // constructeurs
        Carre(float c) : Rectangle(c,c) {}

        virtual void afficherCaracteristiques(){
            Rectangle::afficherCaracteristiques();
            cout<<"--en fait c'est un carre "<< endl;
        }

        virtual ~Carre(){} ;
};// class Carre

//**** exo1_4
class TriangleEquilateral : public Polygone{
    protected :
        float c ;

    public :
        // constructeurs
        TriangleEquilateral(float a) : Polygone(3){
            c=a;
        }

        virtual float perimetre() {
            float f(3*c);
            return (f);
        }

        virtual void afficherCaracteristiques(){
            Polygone::afficherCaracteristiques();
            cout<<"-triangle equilateral de cotes "<<c<<endl;
            cout<<"-perimetre : "<<perimetre()<<endl;
        }

        virtual ~TriangleEquilateral(){} ;
};// class TriangleEquilateral

//**** Exo1_5 et Exo1_7
class Coloriable{
    protected :
        string couleur;

    public :
        Coloriable(string coul){
            couleur=coul;
        }

        string getCouleur(){
            return couleur;
        }

        void setCouleur(string coul){
            couleur=coul;
        }
};//class Coloriable

class Cercle : public Figure, public Coloriable {
    protected :
        float rayon ;
    public :
        // constructeurs
        Cercle(float i, string coul) : Coloriable(coul) {
        rayon=i;
        }
        
        void consulter_modifier(float r){
        rayon=r;
        cout<<"nouveau rayon : "<<rayon<<endl;
        }

        float perimetre(){
        return (3.14*2*rayon);
        }

        virtual void afficherCaracteristiques(){
            cout<<endl<<"-cercle de rayon:"<<rayon<<" et de couleur :"<<getCouleur()<<endl;
            cout<<"-perimetre : "<<perimetre()<<endl;
        }

        virtual ~Cercle(){} ;
};//class Cercle

void test_question_exo1_3(){
    Rectangle R(2,3);
    Carre C(4);
    cout <<"\n ** test Rectangle et Carre\n";
    R.afficherCaracteristiques();
    C.afficherCaracteristiques();
}

void test_question_exo1_4(){
    TriangleEquilateral T(4);
    cout <<"\n ** test TriangleEquilateral\n";
    T.afficherCaracteristiques();
}

void test_question_exo1_5_8(){
    Cercle C(4,string("bleu"));
    cout <<"\n ** test Cercle\n";
    C.afficherCaracteristiques();
}

void test_question_exo1_6(){
    Figure *tab[4];
    int i;
    cout <<"\n ** test polymorphisme\n";
    tab[0]=new Rectangle(2,3);
    tab[1]=new Carre(4);
    tab[2]=new TriangleEquilateral(4);
    tab[3]=new Cercle(4,string("bleu"));

    for (i=0;i<4;i++){
        tab[i]->afficherCaracteristiques();
        cout << "perimetre de la figure "<<i<<" : "<<tab[i]->perimetre()<<endl;
    }

    for (i=0;i<4;i++){
        delete tab[i];
    }
}

void test_question_exo1_7(){
    Rectangle R(2,3);
    Carre Ca(4);
    TriangleEquilateral T(4);
    cout <<"\n ** test varialbe de classe\n";
    cout <<endl<< "nombre de figure creees encore en memoire : "<<Figure::nbrefigure()<<endl;
}

void test_file(void){
    File<int> f;
    cout <<"\n ** test de la file de base\n";
    f.inserer(3);
    f.inserer(4);
    f.inserer(5);
    f.inserer(8);
    f.afficher();
    f.supprimer();
    f.afficher();
    cout << f.queue()<<endl;
    cout << f.tete()<< endl;
    f.supprimer();
    f.supprimer();
    f.supprimer();
}

//**** Exo2.4_5
void test_question_exo2_4_longue(){
    File<Figure*> f;

    cout <<"\n ** test de typeid et liste personnel\n";
    f.inserer(new Rectangle(2,3));
    f.inserer(new Carre(4));
    f.inserer(new TriangleEquilateral(4));
    f.inserer(new Cercle(4,string("bleu")));

    while(!f.vide()){
        (f.tete())->afficherCaracteristiques();
        cout << "perimetre de la figure : "<<(f.tete())->perimetre()<<endl;
        
        if(typeid(*(f.tete()))==typeid(Cercle)){
            cout << " la couleur est : "<<((Cercle*)(f.tete()))->getCouleur()
            <<endl;
        }

        f.supprimer();
    }
}

void test_question_exo2_4_courte(){
    list<Figure*> f;
    list<Figure*>::iterator it;
    cout <<"\n ** test de typeid liste STL\n";
    f.push_back(new Rectangle(2,3));
    f.push_back(new Carre(4));
    f.push_back(new TriangleEquilateral(4));
    f.push_back(new Cercle(4,string("bleu")));
    for(it=f.begin();it!=f.end();it++){
        (*it)->afficherCaracteristiques();
        cout << "perimetre de la figure : "<<(*it)->perimetre()<<endl;
        if(typeid(*(*it))==typeid(Cercle)){
            cout << " la couleur est : "<<((Cercle*)(*it))->getCouleur() <<endl;
        }
    }
    while (!f.empty()){
        delete f.back();
        f.pop_back();
    }
}

int main(){
    test_question_exo1_3();
    test_question_exo1_4();
    test_question_exo1_5_8();
    test_question_exo1_6();
    test_question_exo1_7();
    test_file();
    test_question_exo2_4_longue();
    test_question_exo2_4_courte();
    return 0;
}
