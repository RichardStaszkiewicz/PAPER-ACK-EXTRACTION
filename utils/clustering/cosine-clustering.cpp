#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
using namespace std;

double threshold_of_accpt = 0.02;
double glob_dist_var1 = 0.95;
double glob_dist_var2 = 0.75;
const int MAX_No_OF_DIFF_CONF  = 30000;
string prefix[] = {" ",  "TH ", "WORKSHOP AT ", "WORKSHOP ON ", "WORKSHOP ", "WORKSHOP", "SEMINAR AT ", "CONFERENCE ON ", "CONFEFRENCE ", "PARTICIPANTS AT ", "THE ", "AND ", "AS WELL AS "};


int rep[MAX_No_OF_DIFF_CONF];
vector <string> synonim[MAX_No_OF_DIFF_CONF];
vector <string> conf;
vector <string> ackn;
vector <string> identyfikatory;
vector <string> words;
vector <string> suspicious;
vector <int> id_of_indiv;
vector <vector <int> > freq_matrix;
vector <vector <int> > freq_of_synonims;
string read_text;

int len_prefix_array()
{
    int length = *(&prefix + 1) - prefix;

    return length;
}

void rem_prefix()
{
    int len = len_prefix_array();
    string new_word;

    bool flag;
    bool g;

    for(int i = 0; i < conf.size(); i++)
    {
        g = 0;

        while(g == 0)
        {
            g = 1;
            for(int x = 0; x < len; x++)
            {
                if(conf[i].size() < prefix[x].size())
                {
                    continue;
                }

                flag = 0;

                for(int u = 0; u < prefix[x].size(); u++)
                {
                    if(prefix[x][u] != conf[i][u])
                    {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 1)
                {
                    continue;
                }

                new_word = "";

                for(int u = prefix[x].size(); u < conf[i].size(); u++)
                {
                    new_word += conf[i][u];
                }

                conf[i] = new_word;

                g = 0;
            }
        }
    }

    return;
}

void uniq()
{
    sort(conf.begin(), conf.end());

    vector <string> conf2;

    conf2.push_back(conf[0]);

    for(int i = 1; i < conf.size(); i++)
    {
        if(conf[i] != conf[i - 1])
        {
            conf2.push_back(conf[i]);
        }
    }

    swap(conf2, conf);

    return;
}



int longest_common_subarray(string S1, string S2)
{
    int tab[S1.size() + 1][S2.size() + 1];

    for(int i = 0; i <= S1.size(); i++)
    {
        tab[i][0] = 0;
    }

    for(int i = 0; i <= S2.size(); i++)
    {
        tab[0][i] = 0;
    }

    for(int i = 1; i <= S1.size(); i++)
    {
        for(int x = 1; x <= S2.size(); x++)
        {
            tab[i][x] = max(tab[i - 1][x], tab[i][x - 1]);

            if(S1[i - 1] == S2[x - 1])
            {
                tab[i][x] = max(tab[i][x], tab[i - 1][x - 1] + 1);
            }
        }
    }

    return tab[S1.size()][S2.size()];
}

long double word_distance(string a, string b)
{
    long double part = longest_common_subarray(a, b);
    long double len = min(a.size(), b.size());

    return (part / len);
}

int FIND(int a)
{
    if(rep[a] != a)
    {
        rep[a] = FIND(rep[a]);
    }

    return rep[a];
}

void UNION(int a, int b)
{
    a = FIND(a);
    b = FIND(b);

    if(a == b)
    {
        return;
    }

    if(synonim[a].size() > synonim[b].size())
    {
        swap(a, b);
    }

    rep[a] = b;

    while(synonim[a].size())
    {
        synonim[b].push_back(synonim[a].back());
        synonim[a].pop_back();
    }

    return;
}

map <pair <int, int>, long double> M;

long double connect(int id1, int id2)
{
    id1 = FIND(id1);
    id2 = FIND(id2);

    if(id1 > id2)
    {
        swap(id1, id2);
    }

    if(M[{id1, id2}] == 1)
    {
        return M[{id1, id2}];
    }

    long double ans = 1;

    for(int i = 0; i < synonim[id1].size(); i++)
    {
        for(int x = 0; x < synonim[id2].size(); x++)
        {
            ans = min(ans, word_distance(synonim[id1][i], synonim[id2][x]));
        }
    }

    M[{id1, id2}] = ans;

    return ans;
}

void make_synonims()
{
    sort(conf.begin(), conf.end());

    for(int i =0 ; i < conf.size(); i++)
    {
        cout << conf[i] << endl;
    }
    cout << endl;

    for(int i = 0; i < MAX_No_OF_DIFF_CONF; i++)
    {
        rep[i] = i;
    }

    for(int i = 0; i < conf.size(); i++)
    {
        synonim[i].push_back(conf[i]);
    }

    for(int i = 1; i < conf.size(); i++)
    {
        if(connect(i, i - 1) >= glob_dist_var1)
        {
            UNION(i, i - 1);
        }
    }

    for(int i = 0; i < conf.size(); i++)
    {
        if(rep[i] == i)
        {
            sort(synonim[i].begin(), synonim[i].end());
            id_of_indiv.push_back(i);
        }
    }

    int id;

    for(int i =0 ; i < id_of_indiv.size(); i++)
    {
        id = id_of_indiv[i];

        if(synonim[id].size() == 1)
        {
            continue;
        }

        cout << "(" << synonim[id].size() << ")" << synonim[id][0] << ": " << endl;

        for(int x = 1; x < synonim[id].size(); x++)
        {
            cout << "\t" << synonim[id][x] << endl;
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < conf.size(); i++)
    {
        if(rep[i] == i)
        {
            sort(synonim[i].begin(), synonim[i].end());
            id_of_indiv.push_back(i);
        }
    }

    return;
}

bool in_text(string phrase, string text)
{
    string S = '#' + phrase + '@' + text;

    int tab[S.size()];
    tab[0] = -1;

    int t = -1;

    for(int i = 1; i < S.size(); i++)
    {
        while(t >= 0 && S[t + 1] != S[i])
        {
            t = tab[t];
        }
        t++;

        tab[i] = t;

        if(t == phrase.size())
        {
            return true;
        }
    }

    return false;
}

double probability(int p, int n, int q)
{
    if(n == 1)
    {
        return 1;
    }

    int x = p / n;

    double prob = 1.0000;

    for(int i = 0; i < abs(x - q); i++)
    {
        if(x > q)
        {
            prob *= (q + 1 + i);
            prob /= (p - x + 1 + i);
            prob *= (n - 1);
        }
        else
        {
            prob *= (p - q + 1 + i);
            prob /= (x + 1 + i);
            prob /= (n - 1);
        }
    }

    return prob;
}

void fill_table()
{
    cout << "ackn:";
    cout << ackn.size() << endl;
    int id;

    vector <int> last_row;

    vector <int> pom;

    for(int i = 0; i < ackn.size(); i++)
    {
        last_row.push_back(0);
    }

    vector <int> row;
    int ans;
    int occurs;

    for(int i = 0; i < id_of_indiv.size(); i++)
    {
        cout << i << endl;
        id = id_of_indiv[i];

        freq_of_synonims.push_back(pom);

        for(int x = 0; x < synonim[id].size(); x++)
        {
            freq_of_synonims.back().push_back(0);
        }

        row.clear();
        occurs = 0;

        for(int i = 0; i < ackn.size(); i++)
        {
            row.push_back(0);
        }

        int sum = 0;

        for(int x = 0; x < synonim[id].size(); x++)
        {
            for(int u = 0; u < ackn.size(); u++)
            {
                if(in_text(synonim[id][x], ackn[u]))
                {
                    occurs += 1 - row[u];
                    row[u] = 1;
                    freq_of_synonims.back()[x]++;
                    sum++;
                }
            }
        }

        for(int x = 0; x < synonim[id].size(); x++)
        {
            if(probability(sum, synonim[id].size(), freq_of_synonims.back()[x]) < 0.01 && freq_of_synonims.back()[x] * synonim[id].size() > sum)
            {
             //   cout << synonim[id][x] << " " << sum << " " << synonim[id].size() << " " << freq_of_synonims.back()[x] << endl;
                cout << "SUS - " << synonim[id][x] << endl;
                suspicious.push_back(synonim[id][x]);
            }
        }

        if(occurs >= ackn.size() * threshold_of_accpt)
        {
            freq_matrix.push_back(row);
            words.push_back(conf[id_of_indiv[i]]);
            continue;
        }

        for(int x = 0; x < ackn.size(); x++)
        {
            last_row[x] += row[x];
        }
    }

    freq_matrix.push_back(last_row);

    return;
}

void delete_whitechar(string& S)
{
    string P = "";

    string G = "";

    short f = 0;

    for(int i = 0; i < S.size(); i++)
    {
        if(S[i] == '\n')
        {
             continue;
        }

        if((S[i] > 'Z' || S[i] < 'A') && S[i] != ',' && (S[i] > '9' || S[i] < '0'))
        {
            S[i] = ' ';
        }

        if(S[i] != ' ' && S[i] != ',')
        {
            G += S[i];
            continue;
        }

        if(G == "")
        {
            continue;
        }

        f = 0;

        for(int x = 0; x < G.size(); x++)
        {
            if(G[x] >= '0' && G[x] <= '9')
            {
                f = 1;
                break;
            }
        }

        if(f == 0)
        {
            if(P.size() != 0)
            {
                P += ' ';
            }

            P += G;
        }

        if(S[i] == ',')
        {
            P += ',';
        }

        G = "";
    }

    f = 0;

    for(int x = 0; x < G.size(); x++)
    {
        if(G[x] >= '0' && G[x] <= '9')
        {
            f = 1;
            break;
        }
    }

    if(f == 0 && G != "")
    {
        if(P.size())
        {
            P += ' ';
        }

        P += G;
    }

    swap(S, P);

    return;
}

void separate(string S)
{
    string P = "";

    for(int i = 0; i < S.size(); i++)
    {
        if(S[i] != ',')
        {
            P += S[i];
            continue;
        }

        delete_whitechar(P);

        if(P == "")
        {
            continue;
        }

        conf.push_back(P);
        P.clear();
    }

    delete_whitechar(P);

    if(P == "")
    {
        return;
    }

    conf.push_back(P);

    return;
}

void input()
{
    fstream file;
    file.open("DANE.csv");

    string id, podziek, reczne, maszyna, no_of_people, gpt;

    getline(file, id, '^');
    cout << id << endl;
    cout << "------" << endl;

    getline(file, podziek, '^');
    cout << podziek << endl;
    cout << "------" << endl;

    getline(file, reczne, '^');
    cout << reczne << endl;
    cout << "------" << endl;

    getline(file, no_of_people, '^');
    cout << no_of_people << endl;
    cout << "------" << endl;

    getline(file, maszyna, '^');
    cout << maszyna << endl;
    cout << "------" << endl;

    getline(file, gpt, '^');
    cout << gpt << endl;
    cout << "------" << endl;

    vector <string> separated;

    while(getline(file, id, '^'))
    {
        getline(file, podziek, '^');
        getline(file, reczne, '^');
        getline(file, no_of_people, '^');
        getline(file, maszyna, '^');
        getline(file, gpt, '^');

        if(podziek == "")
        {
            continue;
        }

        identyfikatory.push_back(id);
        separate(maszyna);
        ackn.push_back(podziek);
    }

    return;
}

void clear_data()
{
    rem_prefix();

    uniq();

    return;
}

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
