#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene) {
    int n = gene.size();
    int target = n / 4;
    vector<int> cnt(4, 0);
    
    auto idx = [&](char c){
        if (c == 'A') return 0;
        if (c == 'C') return 1;
        if (c == 'G') return 2;
        return 3;
    };
    
    for(char c : gene) cnt[idx(c)]++;
    
    vector<int> excess(4);
    for(int i = 0; i < 4; i++)
        excess[i] = max(0, cnt[i] - target);

    if(excess[0] == 0 && excess[1] == 0 && excess[2] == 0 && excess[3] == 0)
        return 0;

    int ans = n;
    vector<int> window(4, 0);
    int left = 0;
    
    for(int right = 0; right < n; right++){
        window[idx(gene[right])]++;

        while(window[0] >= excess[0] &&
              window[1] >= excess[1] &&
              window[2] >= excess[2] &&
              window[3] >= excess[3])
        {
            ans = min(ans, right - left + 1);
            window[idx(gene[left])]--;
            left++;
        }
    }

    return ans;
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

string ltrim(const string &str)
{
    string s(str);
    s.erase(
        s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); })
    );
    return s;
}

string rtrim(const string &str)
{
    string s(str);
    s.erase(
        find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end()
    );
    return s;
}

std::vector<string> split(const string &str)
{
    vector<string> tokens;
    string_view str_view(str);
    size_t start = 0;
    size_t end = 0;

    while ((end = str_view.find(' ', start)) != string_view::npos)
    {
        if (end > start)
        {
            tokens.emplace_back(str_view.substr(start, end - start));
        }
        start = end + 1;
    }

    if (start < str_view.size())
    {
        tokens.emplace_back(str_view.substr(start));
    }

    return tokens;
}
