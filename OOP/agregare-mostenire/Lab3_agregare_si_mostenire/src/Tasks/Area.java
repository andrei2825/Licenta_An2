//Nume: Porumb Andrei Cornel
package Tasks;

import java.util.Arrays;

public class Area {
    CandyBag bag = new CandyBag();
    int number;
    String street;
    public Area() {}
    public Area(int number, String street, CandyBag bag) {
       this.number = number;
       this.street = street;
       this.bag = bag;
    }
    CandyBox box = new CandyBox();
    public void getBirthdayCadr() {
        System.out.println(street + number);
        System.out.println("la multi ani");
        for (int i = 0; i < bag.bag.size(); i++) {
            System.out.println(bag.bag.get(i));
        }
        for (int i = 0; i < bag.bag.size(); i++) {
            bag.bag.get(i).print();
        }
    }


}
