package Task3;

public class Point {
    float x;
    float y;

    public Point(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public void changeCoods(float num1, float num2 ) {
        x = num1;
        y = num2;
    }

    public void printCoords() {
        System.out.println("\nCoords:");
        System.out.println("(" + x);
        System.out.println(y + ")");
    }
}
