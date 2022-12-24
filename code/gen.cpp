#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "generadores.hpp"
#include "util.hpp"
#include <chrono>
#include <algorithm>

using namespace std;

const int M = pow(2,12);
const double DELTA = pow(10,-4);

int arit_entera(int x);
float arit_artesanal(float x);
double arit_artesanalD(double x);
int arit_corregida(float x);
double arit_fmod(double x);

template<typename T>
void print_interval(vector<T> vec, int i){
    int szmax = (i<vec.size())? i : vec.size();
    for(unsigned int x=0;x<szmax;x++){
        cout << setw(10) << vec[x];
    }
    cout << endl;
}

template<typename T>
bool is_in(vector<T> vec, T a, T delta=DELTA, bool print=false){
    bool is = false;
    for(unsigned int i=0;i<vec.size();i++){
        if(abs(vec[i]-a)<=delta){
            if(print){
                print_interval<T>(vec,10);
            }
            is = true;
            break;
        }
    }
    return is;
}

int main(int argc, char** argv){
    if(argc<=1){
        cout << "[ERROR]: ./main [print or not](0, 1)" << endl;
        exit(-1);
    }
    int streambuff = atoi(argv[1]);
    const int NUM_types = 5;
    int VECES = 100, MAX_P=50000, SEEDS=5;
    bool print = false;
    if(streambuff == 1){
        VECES = 1; MAX_P=50000; SEEDS=1;
        print = true;
    }
    else if(streambuff==0){
    }else{
        cout << "[ERROR]: Print must be either 0 and 1." << endl;
        exit(-1);
    }
    VECES++;
    // Ir generando los valores para cada aritmética y guardar.
    vector<float> periodos;
    vector<vector<float>> table;
    for(int s=0;s<SEEDS;s++){
        srand((3*s+7)%13);
        periodos.clear();
        for(int i=0;i<NUM_types;i++){
            switch(i){
                case 0:{
                           int v = 1;
                           vector<int> vec;
                           long unsigned int periodo = 0;
                           unsigned int j=0;
                           for(j=1;j<VECES;j++){
                               v = 2*j+1;
                               for(unsigned int z=0;z<MAX_P;z++){
                                   v = arit_entera(v);
                                   if(is_in<int>(vec,v,(int)0, print)){
                                       periodo += vec.size();
                                       break;
                                   }
                                   vec.push_back(v);
                               }
                               vec.clear();
                           }
                           periodos.push_back((1.0*periodo)/(1.0*VECES));
                           vec.clear();
                           break;
                       }
                case 1:{
                           float v = 1.1;
                           vector<float> vec;
                           long unsigned int periodo = 0;
                            unsigned int j=0;
                           for(j=1;j<VECES;j++){
                               v = 2*j+ ( (float) rand() / (float) RAND_MAX + 1)  ;
                               for(unsigned int z=0;z<MAX_P;z++){
                                   v = arit_artesanal(v);
                                   if(is_in<float>(vec,v,DELTA,print)){
                                       periodo += vec.size();
                                       break;
                                   }
                                   vec.push_back(v);
                               }
                               vec.clear();
                           }
                           periodos.push_back((1.0*periodo)/(1.0*VECES));
                           vec.clear();
                           break;
                       }
                case 2:{
                           double v = 1.1;
                           vector<double> vec;
                           long unsigned int periodo = 0;
                           unsigned int j=0;
                           for(j=1;j<VECES;j++){
                               v = 2*j+ ((double) rand() / (double) RAND_MAX ) + 1;
                               for(unsigned int z=0;z<MAX_P;z++){
                                   v = (double) arit_artesanalD(v);
                                   if(is_in<double>(vec,v,DELTA,print)){
                                       periodo += vec.size();
                                       break;
                                   }
                                   vec.push_back(v);
                               }
                               vec.clear();
                           }
                           periodos.push_back((1.0*periodo)/(1.0*VECES));
                           vec.clear();
                           break;
                       }
                case 3:{
                           int v=0; float res;
                           vector<int> vec;
                           long unsigned int periodo = 0;
                           unsigned int j=0;
                           for(j=1;j<VECES;j++){
                               res = 2*j+( (float) rand() / (float) RAND_MAX ) + 1 ;
                               for(unsigned int z=0;z<MAX_P;z++){
                                   v = arit_corregida(res);
                                   if(is_in<int>(vec,v,0,print)){
                                       periodo += vec.size();
                                       break;
                                   }
                                   res = (float) v;
                                   vec.push_back(v);
                               }
                               vec.clear();
                           }
                           periodos.push_back((1.0*periodo)/(1.0*VECES));
                           vec.clear();
                           break;
                       }
                case 4:{
                           double v = 1.1;
                           vector<double> vec;
                           long unsigned int periodo = 0;
                           unsigned int j=0;
                           for(j=1;j<VECES;j++){
                               v = 2*j+( (double) rand() / (double) RAND_MAX ) + 1;
                               for(unsigned int z=0;z<MAX_P;z++){
                                   v = arit_fmod(v);
                                   if(is_in<double>(vec,v,DELTA,print)){
                                       periodo += vec.size();
                                       break;
                                   }
                                   vec.push_back(v);
                               }
                               vec.clear();
                           }
                           periodos.push_back((1.0*periodo)/(1.0*VECES));
                           vec.clear();
                           break;
                       }
            }
        }
        table.push_back(periodos);
    }
    for(unsigned int i=0;i<table.size();i++){
        for(unsigned int j=0;j<table[i].size();j++){
            cout << fixed << setprecision(2) << setw(10) << table[i][j];
        }
        cout << endl;
    }
    return 0;
}

int arit_entera(int x){
    return (1013*x)%M;
}

float arit_artesanal(float x){
    x = (1013.0*x)/(float) M;
    return (x-(int)x)*(float) M ;
}

double arit_artesanalD(double x){
    x = (1013.0*x)/(double) M;
    return (x-(int)x)*(double) M;
}

int arit_corregida(float x){
    x = (1013.0*x)/(float) M;
    x = (x - (int)x)*(float) M;
    return (int)(x+0.5);
}

double arit_fmod(double x){
    return fmod(1013.0*x,(double) M);
}
