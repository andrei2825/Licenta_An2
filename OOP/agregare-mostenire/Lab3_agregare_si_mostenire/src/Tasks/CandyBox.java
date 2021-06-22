//Nume: Porumb Andrei Cornel
package Tasks;

import java.util.Objects;

public class CandyBox {
    private String flavor;
    private String origin;

    public String getFlavor() {
        return flavor;
    }

    public void setFlavor(String flavor) {
        this.flavor = flavor;
    }

    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }

    public CandyBox(){ }
    public CandyBox(String flavor, String origin) {
        this.flavor = flavor;
        this.origin = origin;
    }
     public float getVolume() {
        return 0;
     }
     public void print(){}

    @Override
    public String toString() {
        return "CandyBox are" +
                "aroma: " + flavor + '\'' +
                ", si originea:" + origin + '\'' +
                '}';
    }
    Lindt box1;
    Lindt box2;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CandyBox)) return false;
        CandyBox candyBox = (CandyBox) o;
        return Objects.equals(box1, candyBox.box1) &&
                Objects.equals(box2, candyBox.box2);
    }

    @Override
    public int hashCode() {
        return Objects.hash(box1, box2);
    }
}



