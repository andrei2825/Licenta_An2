//Nume: Porumb Andrei Cornel
package Tasks;

public class Lindt extends CandyBox {
    float length;
    float width;
    float height;
    public Lindt(){ }
    public Lindt(String flv, String org, float length, float width, float height) {
        super.setFlavor(flv);
        super.setOrigin(org);
        this.height = height;
        this.length = length;
        this.width = width;
    }

    public void print() {
        System.out.println("The length is: " + this.length + ", the height is: "
                           + this.height + " and the width is: " + this.width);

    }

    @Override
    public float getVolume() {
        return length * height * width;
    }

    @Override
    public String toString() {
        return "The " + getOrigin() +
                " " + getFlavor() +
                " has volume " + getVolume() +
                "\n";
    }
}
