using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;

class Result
{

    /*
     * Complete the 'steadyGene' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts STRING gene as parameter.
     */


    public static int steadyGene(string gene)
    {
        int n = gene.Length;
        int target = n / 4;

        Span<int> cnt = stackalloc int[4];
        Span<int> excess = stackalloc int[4];
        Span<int> window = stackalloc int[4];

        static int Map(char c) => c switch
        {
            'A' => 0,
            'C' => 1,
            'G' => 2,
            _   => 3
        };

        foreach (char c in gene)
            cnt[Map(c)]++;

        bool noExcess = true;

        for (int i = 0; i < 4; i++)
        {
            int v = cnt[i] - target;
            if (v > 0)
            {
                excess[i] = v;
                noExcess = false;
            }
        }

        if (noExcess)
            return 0;

        int left = 0;
        int ans = n;

        ReadOnlySpan<char> s = gene.AsSpan();

        for (int right = 0; right < n; right++)
        {
            window[Map(s[right])]++;

            while (window[0] >= excess[0] &&
                window[1] >= excess[1] &&
                window[2] >= excess[2] &&
                window[3] >= excess[3])
            {
                int length = right - left + 1;
                if (length < ans)
                    ans = length;

                window[Map(s[left])]--;
                left++;
            }
        }

        return ans;
    }


    public static int steadyGene2(string gene)
    {
        int n = gene.Length;
        int target = n / 4;
        int[] cnt = new int[4];

        int idx(char c)
        {
            if (c == 'A') return 0;
            if (c == 'C') return 1;
            if (c == 'G') return 2;
            return 3;
        }

        foreach (char c in gene)
            cnt[idx(c)]++;

        int[] excess = new int[4];
        for (int i = 0; i < 4; i++)
            excess[i] = Math.Max(0, cnt[i] - target);

        if (excess[0] == 0 && excess[1] == 0 && excess[2] == 0 && excess[3] == 0)
            return 0;

        int ans = n;
        int[] window = new int[4];
        int left = 0;

        for (int right = 0; right < n; right++)
        {
            window[idx(gene[right])]++;

            while (window[0] >= excess[0] &&
                   window[1] >= excess[1] &&
                   window[2] >= excess[2] &&
                   window[3] >= excess[3])
            {
                ans = Math.Min(ans, right - left + 1);

                window[idx(gene[left])]--;
                left++;
            }
        }

        return ans;
    }
}


class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        int n = Convert.ToInt32(Console.ReadLine().Trim());

        string gene = Console.ReadLine();

        int result = Result.steadyGene(gene);

        textWriter.WriteLine(result);

        textWriter.Flush();
        textWriter.Close();
    }
}
