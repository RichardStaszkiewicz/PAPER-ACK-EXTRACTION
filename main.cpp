#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
#include "consts.hpp"
using namespace std;


map <pair <int, int>, long double> M;



int main()
{
    input();

    cout << endl << endl;
    cout << "LIST OF CONFERENCES" << endl;
    cout << conf.size() << endl;

    for(int i = 0; i < conf.size(); i++)
    {
        cout << conf[i] << endl;
    }
    cout << endl << endl;

    clear_data();

    cout << "LIST OF CONFERENCES (CLEARED)" << endl;

    cout << conf.size() << endl;

    for(int i = 0; i < conf.size(); i++)
    {
        cout << "\"" << conf[i] << "\"" << endl;
    }
    cout << endl;

    cout << endl << endl << endl;

    cout << conf.size() << endl;

    make_synonims();

    cout << id_of_indiv.size() << endl;

    fill_table();

    cout << freq_matrix.size() << "x" << freq_matrix[1].size() << endl;

    for(int i = 0; i < words.size(); i++)
    {
        cout << words[i] << endl;
    }
    cout << endl;

    return 0;
}
