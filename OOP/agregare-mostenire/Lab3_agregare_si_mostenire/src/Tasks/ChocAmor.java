//Nume: Porumb Andrei Cornel
package Tasks;

public class ChocAmor extends CandyBox {
    float length;
    public ChocAmor() { }
    public ChocAmor(String flv, String org, float length) {
        super.setFlavor(flv);
        super.setOrigin(org);
        this.length = length;
    }

    public void print() {
        System.out.println("The length is: " + this.length);
    }

    @Override
    public float getVolume() {
        return length * length * length;
    }

    @Override
    public String toString() {
        return "The " + getOrigin() +
                " " + getFlavor() +
                " has volume " + getVolume() +
                "\n";
    }
}
