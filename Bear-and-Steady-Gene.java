import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;

class Result {

    /*
     * Complete the 'steadyGene' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts STRING gene as parameter.
     */

    public static int steadyGene(String gene) {
        int n = gene.length();
        int target = n / 4;
        int[] cnt = new int[4];

        java.util.function.IntUnaryOperator idx = c -> {
            if (c == 'A') return 0;
            if (c == 'C') return 1;
            if (c == 'G') return 2;
            return 3;
        };

        for (char c : gene.toCharArray()) {
            cnt[idx.applyAsInt(c)]++;
        }

        int[] excess = new int[4];
        for (int i = 0; i < 4; i++) {
            excess[i] = Math.max(0, cnt[i] - target);
        }

        if (excess[0] == 0 && excess[1] == 0 && excess[2] == 0 && excess[3] == 0) {
            return 0;
        }

        int ans = n;
        int[] window = new int[4];
        int left = 0;

        for (int right = 0; right < n; right++) {
            window[idx.applyAsInt(gene.charAt(right))]++;

            while (window[0] >= excess[0] &&
                window[1] >= excess[1] &&
                window[2] >= excess[2] &&
                window[3] >= excess[3]) {

                ans = Math.min(ans, right - left + 1);

                window[idx.applyAsInt(gene.charAt(left))]--;
                left++;
            }
        }

        return ans;
    }
}


public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int n = Integer.parseInt(bufferedReader.readLine().trim());

        String gene = bufferedReader.readLine();

        int result = Result.steadyGene(gene);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
