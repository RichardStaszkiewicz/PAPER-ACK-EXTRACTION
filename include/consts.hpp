#include <vector>
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