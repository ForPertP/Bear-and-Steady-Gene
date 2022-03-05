#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// From https://www.hackerrank.com/challenges/bear-and-steady-gene/forum By aakashraj416
int steadyGene(string gene)
{
    int n = gene.size();
    int k = n/4;
    int z = 0; 
    
    std::vector<int> M (128, 0);
    for(const auto &i : gene)
    {
        M[i]++;
    }
    
    for (int &i : M)
    {
        i = max(0, i-k);
        z += i;
    }
    
    int l = 0;
    int r = 0;
    int cnt = 0;
    int best = 1e9;
    
    while (r < n)
    {
        if (M[gene[r++]]-- > 0)
            z--;
        
        while (z == 0)
        {
            best = min(best, r-l);
            if (++M[gene[l++]] > 0)
                z++;
        }
    }
    
    return best;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
