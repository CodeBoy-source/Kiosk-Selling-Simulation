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
using namespace std::chrono;

int binary_search(double* tabla, int max_d);
int immediate_value(double *tabla, int max_d);
void construye_ordenado_b(double *tabla, int* d, int max_d);
void construye_ordenado_c(double *tabla, int* d, int max_d);
float raNge1(unsigned int a, unsigned int b);

int func_wrap(int (*func)(double*,int), double* tabla, int* d, int max_d, bool ordenada=false);

int main(int argc,char** argv){
    srand(140421);
    const int AVG_SZ = 10000, max_d = 10000, POINTS=20;
    if(argc<=2){
        cerr << "[ERROR]: ./main [P] [O]"  << endl;
        exit(-1);


    }
    char p = *argv[1];
    char o = *argv[2];
    int (*func)(double*,int);
    func = &genera_demanda;
    bool ordenada = false;
    switch(o){
        case '3':
            if(p!='A'){
                cerr << "[ERROR]: Optimization value only valid for case A" << endl;
                exit(-1);
            }
            func = &immediate_value;
            break;
        case '2':
            func = &binary_search;
            // std::sort(tablademanda,tablademanda+max_d,greater<int>());
            break;
        case '1':
            ordenada = true;
            break;
    }

    double* tablademanda;
    int* d;

    if ((tablademanda = (double*) malloc(max_d*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }
    switch(p){
        case 'A':
            tablademanda = construye_prop_a(max_d);
            ordenada = false;
            break;
        case 'B':
            if(ordenada) {
                if ((d = (int*) malloc(max_d*sizeof(int))) == NULL)
                {
                    fputs("Error reservando memoria para generador proporcional\n",stderr);
                    exit(1);
                }

                construye_ordenado_b(tablademanda,d,max_d);
            }else{
                tablademanda = construye_prop_b(max_d);
            }
            break;
        case 'C':
            if(ordenada) {
                if ((d = (int*) malloc(max_d*sizeof(int))) == NULL)
                {
                    fputs("Error reservando memoria para generador proporcional\n",stderr);
                    exit(1);
                }
                construye_ordenado_c(tablademanda,d,max_d);
            }else{
                tablademanda = construye_prop_c(max_d);
            }
            break;
    }


    int streambuffer = 0;
    if(argc>3){
        streambuffer = atoi(argv[3]);
    }

    string path = get_selfpath();
    path = path.substr(0,path.find_last_of("/\\") + 1);

    string s(1,p);
    string s2(1,o);
    stringstream oss, os2;
    oss << path << "monte_res/perf/perf" << s+s2 << ".txt";
    os2 << path << "monte_res/perf/P(D)" << s + s2 << ".txt";
    ofstream data,dist;
    if(streambuffer==0){
        data.open(oss.str(),ios::out|ios::trunc);
        dist.open(os2.str(),ios::out|ios::trunc);
    }
    if(!data.is_open()){
        cerr << "[ERROR]: Couldn't open file to save results" << endl;
        streambuffer = 1;
    }


    int demanda;
    double sum;
    for(unsigned int _=0;_<POINTS;_++){
        sum = 0;
        for(unsigned int i=0;i<AVG_SZ;i++){
            auto start = high_resolution_clock::now();
            demanda = func_wrap(func,tablademanda,d, max_d,ordenada);
            auto stop = high_resolution_clock::now();
            chrono::duration<double, std::micro>  duration = stop - start;
            sum +=  duration.count();
        }
        progress_bar(
                raNge1(
                    _*AVG_SZ , (POINTS)*AVG_SZ
                    )
                );
        if(streambuffer==0){
            data << fixed << setprecision(10) << setw(20) << _ <<  demanda << setw(20) << sum / (float) AVG_SZ << endl;
        }else{
            cout << "[DURATION]: " << to_string(sum/(float)AVG_SZ) << endl;
        }
    }
    if(dist.is_open()){
        long unsigned int* P;
        if ((P = (long unsigned int*) malloc(max_d*sizeof(long unsigned int))) == NULL)
        {
            fputs("Error reservando memoria para generador proporcional\n",stderr);
            exit(1);
        }
        for(unsigned int i=0;i<max_d;i++){
            P[i] = 0;
        }
        for(unsigned int i=0;i<AVG_SZ;i++){
            demanda = func_wrap(func,tablademanda,d, max_d,ordenada);
            P[demanda] += 1;
        }
        for(unsigned int i=0;i<max_d;i++){
            dist << fixed << setprecision(8) << setw(20) << i << setw(20) << raNge1(P[i] , AVG_SZ ) << endl;
        }
    }
        progress_bar(
                raNge1(
                    1,1
                    )
                );
    cout << endl;
    return 0;
}

int func_wrap(int (*func)(double*,int), double* tablademanda, int* d, int max_d, bool ordenada){
    if(!ordenada){
        return func(tablademanda,max_d);
    }else{
        double u = uniforme();
        unsigned int i=0;
        while((i<max_d) && (u>=tablademanda[i])){
            i++;
        }
        return d[i];
    }
}

class sort_indices{
    private:
        double* mparr;
    public:
        sort_indices(double* parr) : mparr(parr){}
        bool operator()(int i, int j) const{ return mparr[i]>mparr[j];}
};

void construye_ordenado_b(double *tabla, int* d, int n){
    int i, max;
    double* temp;
    double* seg;
    if ((seg = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }

    max = (n+1)*n/2;
    for(i=0;i<n;i++){
        seg[i] = (double)(i+1)/max;
        d[i] = i;
    }
    std::sort(d,d+n,sort_indices(seg));

    tabla[0] = seg[d[0]];
    for(i=0;i<n;i++){
        tabla[i] = tabla[i-1] + seg[d[i]];
    }

    delete(temp);
    delete(seg);
}

void construye_ordenado_c(double *tabla, int* d,  int n){
    int i, max;
    double* temp;
    double* seg;
    if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }
    if ((seg = (double*) malloc(n*sizeof(double))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n",stderr);
        exit(1);
    }

    max = n*n/4;
    for (i=0;i<(n/2);i++){
        seg[i] = (double)i/max;
        d[i] = i;
    }
    for (i=(n/2);i<n;i++){
        seg[i] =(double)(n-i)/max;
        d[i] = i;
    }

    std::sort(d,d+n,sort_indices(seg));

    tabla[0] = seg[d[0]];
    for (i=1;i<(n/2);i++)
        tabla[i] = tabla[i-1] + seg[d[i]];
    for (i=(n/2);i<n;i++)
        tabla[i] = tabla[i-1] + seg[d[i]];

    delete(temp);
    delete(seg);
}

int immediate_value(double *tabla, int max_d) {
    double u = uniforme();
    int index = u / (1.0/(float)max_d);
    return index;
}

int binary_search(double *tabla, int max_d) {
    int index = 0, a = 0, b = max_d-1, step = (max_d-1)/2;
    double u = uniforme();
    bool not_found = true;
    char h;
    int i = 0;
    while(not_found){
        i += 1;
        if( u <= tabla[step] and u>=tabla[step-1]){
            index = step;
            not_found = false;
            break;
        }
        else if(u>tabla[step]){
            a = step;
            step = step + ((b-a)/2.0+0.5);
        }
        else if(u< tabla[step-1]){
            b = step-1;
            step = step - ((b-a)/2.0+0.5);
        }
    }
    return index;
}

float raNge1(unsigned int a, unsigned int b){
    if(a>b) {
        unsigned int temp = a;
        a = b;
        b = a;
    }
    return float(a) / float(b);
}
