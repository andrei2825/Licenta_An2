package third;

public class Operation implements Minus, Plus, Mult, Div{

    float num;
    public Operation(float num) {
        this.num = num;
    }
    @Override
    public void div(float number) {
        if (number != 0){
            num /= number;
        }
    }

    @Override
    public void mult(float number) {
        num *= number;
    }

    @Override
    public void minus(float number) {
        num -= number;
    }

    @Override
    public void plus(float number) {
        num += number;
    }

    public float getNumber() {
        return num;
    }
}
