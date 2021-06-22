package Tasks;

import java.util.Random;

public class Dealership {
    class BrandOffer implements Offer {

        @Override
        public int getDiscount(Car car) {
            if (car.getType().equals(Car.CarType.TESLA))
                return ((5 * car.getPrice()) / 100);
            else if (car.getType().equals(Car.CarType.BMW))
                return ((15 * car.getPrice()) / 100);
            else  if (car.getType().equals(Car.CarType.VOLKSWAGEN))
                return ((25 * car.getPrice()) / 100);
            else
                return 0;
        }
    }

    class DealerOffer implements Offer {
        @Override
        public int getDiscount(Car car) {
            return 100 * (2020 - car.getYear());
        }
    }

    class SpecialOffer implements Offer {
        Random r = new Random();
        @Override
        public int getDiscount(Car car) {
            return r.nextInt(500);
        }
    }

    public int getFinalPrice(Car car) {
        BrandOffer brandOffer = new BrandOffer();
        DealerOffer dealerOffer = new DealerOffer();
        SpecialOffer specialOffer = new SpecialOffer();
        int price = car.getPrice();

        price -= brandOffer.getDiscount(car);
        price -= dealerOffer.getDiscount(car);
        price -= specialOffer.getDiscount(car);

        car.setPrice(price);

        return price;
    }

    public void negotiate(Car car, Offer offer){
        Random r = new Random();

        car.setPrice(getFinalPrice(car));

        if (r.nextBoolean()) {
            car.setPrice((car.getPrice() - offer.getDiscount(car)));
        }
    }
}
