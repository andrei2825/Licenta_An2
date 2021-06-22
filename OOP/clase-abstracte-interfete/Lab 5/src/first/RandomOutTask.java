package first;

import java.util.Random;

public class RandomOutTask implements Task{
    int randInt;
    public RandomOutTask (){
        Random rand = new Random();
        this.randInt = rand.nextInt();
    }
    public void execute() {
        System.out.println(randInt);
    }
}
