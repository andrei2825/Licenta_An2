package Task1;

public class Complex {
    private int real;
    private int imaginary;

    public Complex(int re, int im) {
        this.real = re;
        this.imaginary = im;
    }

    public Complex() {

        this(0, 0);
    }

    public Complex(Complex complex) {
        this.imaginary = complex.imaginary;
        this.real = complex.real;
    }

    public void setReal(int re) {

        real = re;
    }

    public void setImaginary(int im) {

        imaginary = im;
    }

    public int getReal() {

        return real;
    }

    public int getImaginary() {

        return imaginary;
    }

    public void showNumber() {
        System.out.println("Task1.Complex Number:");
        System.out.println(getReal());
        System.out.println(getImaginary());
    }

    public static void main(String[] args) {
        Complex number = new Complex(3, 15);
        number.showNumber();
    }
}
