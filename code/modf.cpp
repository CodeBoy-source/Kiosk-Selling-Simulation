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
using namespace std;

float raNge1(unsigned int a, unsigned int b);

int main(int argc, char**argv){
    srand(140421);
    if(argc<=4){
        cerr << "[ERROR]: ./main [x] [y] [z] [P]"  << endl;
        exit(-1);
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    int z = atoi(argv[3]);
    double* tablademanda;
    char p = *argv[4];
    switch(p){
        case 'A':
            tablademanda = construye_prop_a(100);
            break;
        case 'B':
            tablademanda = construye_prop_b(100);
            break;
        case 'C':
            tablademanda = construye_prop_c(100);
            break;
    }
    int streambuffer = 0;
    if(argc>5){
        streambuffer = atoi(argv[5]);
    }

    string path = get_selfpath();
    path = path.substr(0,path.find_last_of("/\\") + 1);

    stringstream oss;
    oss << path << "monte_res/modf/modSP" << p << "-" << x << "-" << y << "-" << z << ".txt";
    ofstream data;
    if(streambuffer==0)
        data.open(oss.str(),ios::out|ios::trunc);
    if(!data.is_open()){
        cerr << "[ERROR]: Couldn't open file to save results" << endl;
        streambuffer = 1;
    }

    const int POINTS = 6, max_d = 100;
    int s, d, best_s;
    vector<int> veces = {100,500,1000,10000,500000};
    vector<int> suma_veces;
    suma_veces.push_back(0);
    for(unsigned int i=1;i<veces.size()+1;i++){
        suma_veces.push_back(suma_veces[i-1] + veces[i-1]);
    }
    double sum, sum2, ganancia, gananciaesperada, desviaciont, \
           oldgesperada, bestgesperada;
    for(unsigned int j=0;j<veces.size();j++){
        for(unsigned int _=0; _<POINTS;_++){
            bestgesperada = oldgesperada = gananciaesperada = 0;
            desviaciont = 0;
            for(s = 1; s<max_d; s++){
                sum = 0;
                sum2 = 0;
                for(unsigned int i=0;i<veces[j];i++){
                    d = genera_demanda(tablademanda,max_d);
                    if (d<s){
                        ganancia = x*d - y*d - min(z,y*(s-d));
                    }else{
                        ganancia = x*s - y*s;
                    }
                    sum += ganancia;
                    sum2 += ganancia*ganancia;
                }
                gananciaesperada = sum/veces[j];
                desviaciont = sqrt((sum2-veces[j]*gananciaesperada*gananciaesperada)/(veces[j]-1));
                if(gananciaesperada >= oldgesperada){
                    oldgesperada = gananciaesperada;
                    if(gananciaesperada > bestgesperada){
                        bestgesperada = gananciaesperada;
                        best_s = s;
                    }
                }
                progress_bar(
                        raNge1(
                            (s + _*max_d) + j*POINTS*max_d,
                            veces.size()*max_d*POINTS
                            )
                        );
            }
            if(streambuffer==0)
                data << setprecision(3) << setw(10) << veces[j] << setw(10) << best_s << setw(10) << bestgesperada << setw(10) << d << endl;
        }
        if(streambuffer==0 and j!=veces.size()-1){
            // Generate new block for gnuplot
            data << "\n\n";
        }
    }
    cout << endl;
    return 0;
}

float raNge1(unsigned int a, unsigned int b){
    if(a>b) {
        unsigned int temp = a;
        a = b;
        b = a;
    }
    return float(a) / float(b);
}
