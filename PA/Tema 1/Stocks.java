import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Stocks {
	static int max(int  a, int b) {
		return (a > b) ? a : b;
	}
	//pentru rezolvare am ales algoritmul rucsacului 0-1 pe care 
	//l-am adaptat pentru 3 parametrii
	static int solver(int W, int L, int[] wt, int[] val, int[] low, int n) {
		//astfel am un  3d array in care retin valorile
		int[][][] K = new int[n + 1][W + 1][L + 1];
		for (int i = 0; i <= n; i++) {
			for (int w = 0; w <= W; w++) {
				for (int l = 0; l <= L; l++) {
					//pentru fiecare conditie din algoritmul rucsacului
					//am adaugat si conditia pentru a treia variabile
					//in acest caz, losses
					if (i == 0 || w == 0 || l == 0) {
						K[i][w][l] = 0;
					} else if (wt[i - 1] <= w && low[i - 1] <= l) {
						K[i][w][l] = max(val[i - 1] + K[i - 1][w - wt[i - 1]]
								[l - low[i - 1]], K[i - 1][w][l]);
					} else {
						K[i][w][l] = K[i - 1][w][l];
					}
				}
			}
		}

		return K[n][W][L];
	}

	public static void main(String[] args) throws IOException {
		int i;
		BufferedReader reader = new BufferedReader(new FileReader("stocks.in"));
		String line = reader.readLine();
		String[] nums = line.split(" ");
		i = 0;
		int N = Integer.parseInt(nums[0]);
		int B = Integer.parseInt(nums[1]);
		int L = Integer.parseInt(nums[2]);
		int[] cost = new int[N];
		int[] lows = new int[N];
		int[] highs = new int[N];
		while ((line = reader.readLine()) != null) {
			nums = line.split(" ");
			if (Integer.parseInt(nums[0]) - Integer.parseInt(nums[1]) <= L) {
				if (Integer.parseInt(nums[0]) <= B) {
					//pentru a elimina niste calcule am retinut doart 
					//profitul total si pierderile totale
					cost[i] = Integer.parseInt(nums[0]);
					lows[i] = cost[i] - Integer.parseInt(nums[1]);
					highs[i] = Integer.parseInt(nums[2]) - cost[i];
					i++;
				}
			}
		}
		int n = i;
		PrintWriter fileOut = new PrintWriter(new FileWriter("stocks.out"));
		fileOut.print(solver(B, L, cost, highs, lows, n));
		fileOut.close();
	}
}
