import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class Crypto {
	public static void main(String[] args) throws IOException {
		int N;
		int B;
		int i;
		BufferedReader reader = new BufferedReader(new FileReader("crypto.in"));
		String line = reader.readLine();
		String[] nums = line.split(" ");
		N = Integer.parseInt(nums[0]);
		int[] miningRate = new int[N];
		int[] cost = new int[N];
		B = Integer.parseInt(nums[1]);
		int min = Integer.MAX_VALUE;
		i = 0;
		while ((line = reader.readLine()) != null){
			nums = line.split(" ");
			miningRate[i] = Integer.parseInt(nums[0]);
			if(miningRate[i] < min) {
				min = miningRate[i];
			}
			cost[i] = Integer.parseInt(nums[1]);
			i++;
		}
		int sum = 0;
		while(sum < B) {
			for (i = 0; i < N; i++) {
				if(miningRate[i] == min) {
					sum += cost[i];
					if (sum >= B) {
						break;
					}
					miningRate[i]++;
				}
			}
			min++;
		}
		BufferedWriter fileOut = new BufferedWriter(new FileWriter("crypto.out"));
		String data = String.valueOf(min - 1);
		fileOut.write(data);
		fileOut.close();
	}
}
