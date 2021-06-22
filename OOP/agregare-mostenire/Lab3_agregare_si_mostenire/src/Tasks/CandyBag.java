//Nume: Porumb Andrei Cornel
package Tasks;

import java.util.ArrayList;

public class CandyBag {
    int i = 0;
    public Lindt cutie1 = new Lindt("cirese", "India", 5, 8, 4);
    public Lindt cutie2 = new Lindt("mere", "Franta", 12, 8, 3);
    public Baravelli cutie3 = new Baravelli("caramel", "Belgia", 3, 4);
    public Baravelli cutie4 = new Baravelli("martipan", "Elvetia", 12, 5);
    public ChocAmor cutie5 = new ChocAmor("ciocolata amara", "UK", 8);
    public ChocAmor cutie6 = new ChocAmor("Ciocolata alpina de la vacuta Milka", "Muntii Alpi ai Elvetiei", 28);
    ArrayList<CandyBox> bag = new ArrayList<CandyBox>(6);
    public void addToBag() {
        bag.add(cutie1);
        bag.add(cutie2);
        bag.add(cutie3);
        bag.add(cutie4);
        bag.add(cutie5);
        bag.add(cutie6);
    }

}
