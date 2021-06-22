import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Valley {
	public static void main(String[] args) throws IOException {
		int N;
		BufferedReader reader = new BufferedReader(new FileReader("valley.in"));
		String line = reader.readLine();
		String[] nums = line.split(" ");
		N = Integer.parseInt(nums[0]);
		int[] heights = new int[N];
		line = reader.readLine();
		nums = line.split(" ");
		int check = Integer.parseInt(nums[0]);
		boolean repeat = true;
		int min = Integer.MAX_VALUE;
		for (int i = 0; i < N; i++) {
			heights[i] = Integer.parseInt(nums[i]);
			if (heights[i] < min) {
				min = heights[i];
			}
			if (heights[i] != check) {
				repeat =  false;
			}
		}
		//daca arrayul are doar elemente identce, este o vale si returnez
		if (repeat) {
			PrintWriter fileOut = new PrintWriter(new FileWriter("valley.out"));
			fileOut.print(0);
			fileOut.close();
			return;
		}
		long moves = 0;
		int index = 0;
		//verific cazurile particulare(minim este pe prima sau ultima pozitie)
		//daca este pe prima sau ultima pozitie, voi transforma si elementrul 
		//de langa acesta in minim si apoi voi continua rezolvarea
		if (heights[0] == min) {
			moves += (heights[1] - min);
			heights[1] = min;
			//pentrua  face verificarile corect voi parcurge mereu dinspre capete spre
			//elementrul curent
			for (int i = N - 1; i > 1; i--) {
				if (heights[i] < heights[i - 1]) {
					moves += heights[i - 1] - heights[i];
					heights[i - 1] = heights[i];
				}
			}
		} else if (heights[N - 1] == min) {
			moves += (heights[N - 2] - min);
			heights[N - 2] = min;
			for (int i = 0; i < N - 2; i++) {
				if (heights[i] < heights[i + 1]) {
					moves += heights[i + 1] - heights[i];
					heights[i + 1] = heights[i];
				}
			}
		} else {
			for (int i = 0; i < N - 1; i++) {
				if (heights[i] == min) {
					index = i;
					break;
				}
			}
			for (int i = 0; i < index - 1; i++) {
				if (heights[i] < heights[i + 1]) {
					moves += heights[i + 1] - heights[i];
					heights[i + 1] = heights[i];
				}
			}
			for (int i = N - 1; i > index + 1; i--) {
				if (heights[i] < heights[i - 1]) {
					moves += heights[i - 1] - heights[i];
					heights[i - 1] = heights[i];
				}
			}
		}
		PrintWriter fileOut = new PrintWriter(new FileWriter("valley.out"));
		fileOut.print(moves);
		fileOut.close();
	}
}
