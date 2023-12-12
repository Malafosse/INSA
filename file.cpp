#include <iostream>
#include <string>
using namespace std;

//**** Exo2_1
template <typename element> 
class Cellule {
    public :
        Cellule(element val) : valeur(val),suivant(NULL) {}
    public:
        element valeur;
        Cellule * suivant;
};

//Exo2_2 et 3
template <typename element> 
class File {
    public :
        class Erreur {
            private:
            string code;
            public:
            Erreur(string ch):code(ch){}
                string getErreur(){
                return code;
                }
        };

        File() : premier(NULL),dernier(NULL),nb_elements(0) {}
    
        void inserer(element val){
            if (premier==NULL) {
                premier=new Cellule<element>(val);
                dernier=premier;
            }
            else {
                dernier->suivant=new Cellule<element>(val);
                dernier=dernier->suivant;
            }
            nb_elements++;
        }

        void afficher(){
            // méthode qui suppose que l'operateur << existe pour les elelemnts stockes dans la file
            Cellule<element> * aux=premier;

            while (aux!=NULL) {
                cout << aux->valeur << " ";
                aux=aux->suivant;
            }
            cout << endl;
        }
        
        void supprimer() {
            if (nb_elements!=0){
                if (premier==dernier){
                    delete premier;
                    premier=NULL;
                    dernier=NULL;
                    nb_elements=0;
                }
                else{
                    Cellule<element> * aux;
                    aux=premier;
                    premier=premier->suivant;
                    delete aux;
                    nb_elements--;
                }
            }
        }

        element tete(){
            element resultat;
            if (premier){
                resultat = premier->valeur;
            }
            else{
                throw Erreur(string("pas de valeur en tete"));
            }
            return resultat;
        }

        element queue(){
            element resultat;
            if (dernier){
                resultat = dernier->valeur;
            }
            else{
                throw Erreur(string("pas de valeur en queue"));
            }
            return resultat;
        }

        int nombreElement(){
            return nb_elements;
        }

        bool vide(){
            return(nb_elements==0);
        }

    protected :
        Cellule<element> * premier;
        Cellule<element> * dernier;
        int nb_elements;
};