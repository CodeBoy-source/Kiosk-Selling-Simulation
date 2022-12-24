#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <limits.h>
using namespace std;

//https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void progress_bar(float progress){
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

//https://stackoverflow.com/questions/5525668/how-to-implement-readlink-to-find-the-path
string get_selfpath() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }
    /* handle error condition */
    return "";
}

/*
    path = get_selfpath();
    path = path.substr(0,path.find_last_of("/\\") + 1);

    stringstream oss;
    oss << setprecision(2) << path << "inv_results/val1-" << veces << "-" << spequena << "-" << sgrande << ".txt";
    ofstream data;  data.open(oss.str(),ios::out|ios::trunc);
    data << std::left << setw(10) << spequena << setw(10) << sgrande << endl;

 */
