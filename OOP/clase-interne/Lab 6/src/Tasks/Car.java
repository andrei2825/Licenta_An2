package Tasks;

public class Car {
    private int price;
    private int year;
    private CarType type;
    public Car(int type, int price, int year){
        this.price = price;
        this.year = year;
        this.type = CarType.getType(type);

    }
    public enum CarType{
        TESLA(1),
        BMW(2),
        VOLKSWAGEN(3);

        private final int value;
        private CarType(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }
        public static CarType getType(int id) {
            CarType car = null;
            switch (id) {
                case 1:
                    car = TESLA;
                    break;
                case 2:
                    car = BMW;
                    break;
                case 3:
                    car = VOLKSWAGEN;
                    break;
                default:
                    break;
            }
            return car;
        }
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public CarType getType() {
        return type;
    }

    public void setType(CarType type) {
        this.type = type;
    }
}
