//Nume: Porumb Andrei Cornel
package Tasks;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        CandyBag bag = new CandyBag();
        bag.addToBag();
        Area pack = new Area(20, "avrig", bag);
        pack.getBirthdayCadr();



        CandyBox test = new CandyBox();
        test.box1 = bag.cutie1;
        test.box2 = bag.cutie1;
        System.out.println(test.box1.equals(test.box2));
    }
}
