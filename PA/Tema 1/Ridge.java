import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Ridge {
	public static void main(String[] args) throws IOException {
		int N, k;
		k = 0;
		BufferedReader reader = new BufferedReader(new FileReader("ridge.in"));
		String line = reader.readLine();
		String[] nums = line.split(" ");
		N = Integer.parseInt(nums[0]);
		int[] height = new int[N];
		int[] cost = new int[N];
		long[][] possibleValues = new long[N][3];
		while ((line = reader.readLine()) != null) {
			nums = line.split(" ");
			height[k] = Integer.parseInt(nums[0]);
			cost[k] = Integer.parseInt(nums[1]);
			k++;
		}
		//calculez cazul de baza
		possibleValues[0][0] = 0;
		possibleValues[0][1] = cost[0];
		possibleValues[0][2] = 2 * cost[0];
		//matricea in de Nx3 in care retin elementele este sub urmatoarea forma:
		//pe liniile de la 0 la N, pe prima coloana este inaltimea curenta,
		//pe a doua coloana este inaltimea -1 iar pe a treia coloana, este
		// inaltimea -2, acestea fiint toate posibilitatile
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < 3; j++) {
				long minimum = Long.MAX_VALUE;
				//compar elemetrul curent -j cu elementul precedent neschimbat
				if (height[i] - j != height[i - 1]) {
					minimum = Math.min(minimum, possibleValues[i - 1][0]);
				}
				//compar elemetrul curent -j cu elementul precedent -1
				if (height[i] - j != height[i - 1] - 1) {
					minimum = Math.min(minimum, possibleValues[i - 1][1]);
				}
				//compar elemetrul curent -j cu elementul precedent -2
				if (height[i] - j != height[i - 1] - 2) {
					minimum = Math.min(minimum, possibleValues[i - 1][2]);
				}
				//daca elementul nu scadfe sub 0, efectuez calculele
				if (height[i] - j >= 0) {
					possibleValues[i][j] = (long) j * cost[i] + minimum;
				} else  {
					possibleValues[i][j] = Long.MAX_VALUE;
				}
			}
		}
		//calculez costul total
		long sum = Long.MAX_VALUE;
		for (int i = 0; i < 3; i++) {
			sum = Math.min(sum, possibleValues[N - 1][i]);
		}
		PrintWriter fileOut = new PrintWriter(new FileWriter("ridge.out"));
		fileOut.print(sum);
		System.out.println(sum);
		fileOut.close();
	}
}
