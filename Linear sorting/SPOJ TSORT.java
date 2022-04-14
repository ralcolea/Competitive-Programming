import java.io.*;
import java.util.*;

/**
 *
 * @author Rubén Alcolea Núñez
 */

public class Main {
    static BufferedReader in;
    static PrintWriter out;
    static StringTokenizer st = new StringTokenizer("");
    
    public static int n;
    public static final int MAX = 1000000;

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        // n and q
        n = nextInt();
        int[] values = new int[n];
        int[] output = new int[n];
        int[] freq = new int[MAX + 5];
        for (int i = 0; i < n; i++) {
            values[i] = nextInt();
            freq[values[i]]++;
        }
        
        for (int i = 1; i <= MAX; i++)
            freq[i] += freq[i-1];
        
        for (int i = n-1; i >= 0; i--) {
            output[freq[values[i]] - 1] = values[i];
            freq[values[i]]--;
        }
        
        for (int i = 0; i < n; i++)
            out.println(output[i]);
        
        out.flush();
    }

    public static String next() throws IOException {
        while (!st.hasMoreTokens()) {
            st = new StringTokenizer(in.readLine());
        }
        return st.nextToken();
    }

    public static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
}
