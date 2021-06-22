//Nume: Porumb Andrei Cornel
package Tasks;

public class Baravelli extends CandyBox {
    float radius;
    float height;
    float pi = (float) 3.14;
    public Baravelli() { }
    public Baravelli(String flv, String org, float radius, float height) {
        super.setFlavor(flv);
        super.setOrigin(org);
        this.height = height;
        this.radius = radius;
    }

    public void print() {
        System.out.println("The radius is: " + this.radius + " and height is: " + this.height);
    }

    @Override
    public float getVolume() {
        return pi * height * radius * radius;
    }

    @Override
    public String toString() {
        return "The " + getOrigin() +
                " " + getFlavor() +
                " has volume " + getVolume() +
                "\n";
    }
}
