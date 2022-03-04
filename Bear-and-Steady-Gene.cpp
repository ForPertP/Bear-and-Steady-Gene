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
