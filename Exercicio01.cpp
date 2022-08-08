#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
using std::endl;
using std::getline;
using std::ios;
using std::ofstream;
using std::ifstream;
using namespace std;
#define TAM 1001

//Rodrigo Berti;

struct dados{   //Struct para armazenar os dados do filmes

    string title;
    string rating;
    string rating_Level;
    int rating_Description; //int
    int release_year; //int
    int user_rating_score;
    int user_rating_size; //int
    

};

 typedef struct dados dados;

int main(){

    dados filmes[TAM];
    dados aux;
    string str;
    dados filmesrep[TAM];
    string titulos[TAM];
    bool rep;
    int i, temp=0;

    ifstream inNetflix_all("netflix_all.csv", ios::in); //Abre o arquivo a ser analisado

    if (!inNetflix_all){
        cout<<"O arquivo nao existe"<<endl;
    }else{

        //lendo os dados do Arquivo
        //1)
        for(i=0;i<TAM;i++){
            getline(inNetflix_all, filmes[i].title,';');
            getline(inNetflix_all, filmes[i].rating,';');
            getline(inNetflix_all, filmes[i].rating_Level,';');

            getline(inNetflix_all, str,';');
            stringstream ss1;                  //Função stringstream para converter uma string para um inteiro
            ss1 << str;
            ss1 >> filmes[i].rating_Description;

            str = " ";
            getline(inNetflix_all, str,';');
            stringstream ss2;
            ss2 << str;
            ss2 >> filmes[i].release_year;

            str = " ";
            getline(inNetflix_all, str,';');
            stringstream ss3;
            ss3 << str;
            ss3 >> filmes[i].user_rating_score;

            str = " ";
            getline(inNetflix_all, str,';');
            stringstream ss4;
            ss4 << str;
            ss4 >> filmes[i].user_rating_size; 
            
        }


        //Filtrando os Filmes Repetidos
        for(i=0; i<TAM;i++){

            rep = find(begin(titulos), end(titulos), filmes[i].title) != end(titulos);

            if(rep){
                continue;
            }
            else{

                titulos[temp] = filmes[i].title;
                filmesrep[temp].title = filmes[i].title;
                filmesrep[temp].rating = filmes[i].rating;
                filmesrep[temp].rating_Level = filmes[i].rating_Level;
                filmesrep[temp].rating_Description = filmes[i].rating_Description;
                filmesrep[temp].release_year = filmes[i].release_year;
                filmesrep[temp].user_rating_score = filmes[i].user_rating_score;
                filmesrep[temp].user_rating_size = filmes[i].user_rating_size;
                temp++;
            }
        }

        for (int i = 0; i < temp; i++)  //For para ordenar o vetor pelo rating score do menor para o menor
        {
            for (int j =i+1; j < temp; j++)
            {
                if (filmesrep[i].user_rating_score < filmesrep[j].user_rating_score)
                {
                    aux.title = filmesrep[i].title;
                    aux.rating = filmesrep[i].rating;
                    aux.rating_Level = filmesrep[i].rating_Level;
                    aux.rating_Description = filmesrep[i].rating_Description;
                    aux.release_year = filmesrep[i].release_year;
                    aux.user_rating_score = filmesrep[i].user_rating_score;
                    aux.user_rating_size = filmesrep[i].user_rating_size;

                    filmesrep[i].title = filmesrep[j].title;
                    filmesrep[i].rating = filmesrep[j].rating;
                    filmesrep[i].rating_Level = filmesrep[j].rating_Level;
                    filmesrep[i].rating_Description = filmesrep[j].rating_Description;
                    filmesrep[i].release_year = filmesrep[j].release_year;
                    filmesrep[i].user_rating_score = filmesrep[j].user_rating_score;
                    filmesrep[i].user_rating_size = filmesrep[j].user_rating_size;

                    filmesrep[j].title = aux.title;
                    filmesrep[j].rating = aux.rating;
                    filmesrep[j].rating_Level = aux.rating_Level;
                    filmesrep[j].rating_Description = aux.rating_Description;
                    filmesrep[j].release_year = aux.release_year;
                    filmesrep[j].user_rating_score = aux.user_rating_score;
                    filmesrep[j].user_rating_size = aux.user_rating_size;
                    
                }
                
            }
            
        }

    
        //Ex 2
        cout<<endl;
        string vetR[13]={"G","NR","PG","PG-13","R","TV-14","TV-G","TV-MA","TV-PG","TV-Y","TV-Y7","TV-Y7-FV","UR"};
        int cont_F=0;
        cout<<"|-----------|"<<endl;
        cout<<"|Ex 2)-"<<endl;
        cout<<"|-----------|"<<endl;
        for(int j =0;j<13;j++){
            for (int i = 0; i < 82; i++)
            {
                cont_F=0;
                for (int k = 0; k < TAM; k++)
                {
                    if (filmesrep[k].release_year == i+1940)
                    {
                        if (filmesrep[k].rating == vetR[j])
                        {

                            cont_F++;           //Faz um contador dos filmes com os ratings para cada ano
                        }

                    }

                }
                if(cont_F > 0){

                    cout<<"filmes de "<<i+1940<<":"<<cont_F<<" de: "<<vetR[j]<<endl;   //Printa na tela os filmes que para cada rating de cada ano
                }
            }
        }
        
        cout<<"\n|============================================================================================|\n"<<endl;

        //Ex 3
        cout<<"|-----------|"<<endl;
        cout<<"|Ex 3)-"<<endl;
        cout<<"|-----------|"<<endl;
        int soma_f=0;
        cout<<"3) - Videos Lançados a Cada Ano: "<<endl;
        for(int a=1940; a<2018;a++){
            soma_f=0;
            for (i = 0; i < TAM; i++)
            {
                if(filmesrep[i].release_year == a){
                    soma_f += 1;                        //Contador da quantidade de filmes lançados a cada ano
                }
                
            }
        
            if(soma_f == 0){            //Esse if filtra se n tiver nem um filme no ano ele não imprimi

            }else{
                cout<<"Ano "<< a <<" = "<<soma_f<<endl;
            }
            
        }
        
        cout<<"\n|============================================================================================|\n"<<endl;

        cout<<"|-----------|"<<endl;
        cout<<"|Ex 4)-"<<endl;
        cout<<"|-----------|"<<endl;
        //Ex4
        ofstream filmeFile("MelhoresFilmes.Txt",ios::out);      //Cria um arquivo Txt com os melhores filmes de cada ano

        for (int i = 1940; i < 2018; i++)
        {
            int cont=0;
            
            for (int j = 0; j < temp; j++)
            {
                if (filmesrep[j].release_year == i)
                {
                    
                    if (cont < 10)
                    {
                        filmeFile << filmesrep[j].title <<" "<<"("<<filmesrep[j].release_year<<")"<<endl;   //Salva os dados nos arquivos
                            
                    }
                    cont++;
                }
                
            }
            
        }
        cout<<"Arquivo Com os 10 Melhores Filmes Foi Criado!"<<endl;

        cout<<"\n|============================================================================================|\n"<<endl;

        cout<<"|-----------|"<<endl;
        cout<<"|Ex 5)-"<<endl;
        cout<<"|-----------|"<<endl;
        //Ex 5
        float somarV=0;
        float somarS=0;
        cout<<"5)-"<<endl;
        for(i=0;i<TAM;i++){
            size_t verifica1=filmesrep[i].rating_Level.find("violence");        //Faz uma verificação da no rating lavel de violencia e entra em um contador dps
            size_t verifica2=filmesrep[i].rating_Level.find("sexual content");  //Faz uma verificação da no rating lavel de sexual content
        
            if(verifica1!=string::npos){
                somarV += 1;
            }

            if(verifica2!=string::npos){
                somarS += 1;
            }
            
        }
        cout<<"O Total de Filmes Violentos é: "<< somarV <<" - "<< (somarV * 100)/497<<"%"<<endl;     //Printa na tela e calcula a % de violentos
        cout<<"O Total de Filmes com sexual content: "<<somarS<<" - "<< (somarS * 100)/497<<"%"<<endl;//Printa na tela e calcula a % de sexual content
        cout<<endl;

        cout<<"\n|============================================================================================|\n"<<endl;

        cout<<"|-----------|"<<endl;
        cout<<"|Ex 6)-"<<endl;
        cout<<"|-----------|"<<endl;
        //Ex 6
        string busca;
        cout<<"6)-";
        cout<<"Qual Filme deseja buscar"<<endl;     //O usuario entra com a busca de um filme para ser pesquisado se tem o filme nos arquivos
        getline(cin, busca);

        for(i=0;i<TAM;i++){
            size_t buscaF=filmesrep[i].title.find(busca);
            
        
            if(buscaF!=string::npos){
                cout<<filmesrep[i].title<<" "<<filmesrep[i].rating<<" "<<filmesrep[i].rating_Description<<endl;
            }
            
        }
    }

    return 0;
}