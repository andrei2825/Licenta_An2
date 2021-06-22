package Tasks;

import java.util.ArrayList;

public class Test {
    public static void main(String[] args) {
        Car car1 = new Car(1, 50000, 2019);
        Car car2 = new Car(2, 75000, 2018);
        Car car3 = new Car(3, 23000, 2012);
        Dealership dealership = new Dealership();
        System.out.println("Car:" + car1.getType() + " production year: " + car1.getYear() +
                " price: " + car1.getPrice() + " discount: " +
                (car1.getPrice() - dealership.getFinalPrice(car1)) + " final price: " +
                dealership.getFinalPrice(car1));
        System.out.println("Car:" + car2.getType() + " production year: " + car2.getYear() +
                " price: " + car2.getPrice() + " discount: " +
                (car2.getPrice() - dealership.getFinalPrice(car2)) + " final price: " +
                dealership.getFinalPrice(car2));
        System.out.println("Masina:" + car3.getType() + " production year: " + car3.getYear() +
                " price: " + car3.getPrice() + " discount: " +
                (car3.getPrice() - dealership.getFinalPrice(car3)) + " final price: " +
                dealership.getFinalPrice(car3));
        Offer offer = new Offer() {
            @Override
            public int getDiscount(Car car) {
                return 600;
            }
        };
        dealership.negotiate(car1, offer);
        dealership.negotiate(car2, offer);
        dealership.negotiate(car3, offer);
        System.out.println("Final price after negotiation for " + car1.getType() + " is: " +
                car1.getPrice());
        System.out.println("Final price after negotiation for " + car2.getType() + " is: " +
                car2.getPrice());
        System.out.println("Final price after negotiation for " + car3.getType() + " is: " +
                car3.getPrice());

        System.out.println("Before filter: ");
        ArrayList<Car> cars= new ArrayList<>();
        cars.add(car1);
        cars.add(car2);
        cars.add(car3);

        for (int  i = 0; i < 3; i++) {
            System.out.println(cars.get(i).getType());
        }
        System.out.println("After filter: ");
        cars.removeIf(car -> car.getPrice() > 35000);
        cars.forEach((car -> System.out.println(car.getType())));
    }
}
//s-au generat clasele Car, Dealership si Test