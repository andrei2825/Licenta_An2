package Task3;

public class Polygon {
    Point[] points;
    public Polygon(int n) {
        this.points = new Point[n];
    }

    public Polygon(float[] pts) {
        this(pts.length);
        for (int i = 0; i < points.length; i+=2) {
            points[i] = new Point(pts[i], pts[i+1]);
            points[i].printCoords();
        }

    }

    public static void main(String[] args) {
        float[] p = { 5, 6, 10, 11, 23, 23, 33, 34};
        Polygon poli = new Polygon(p);

    }
}
