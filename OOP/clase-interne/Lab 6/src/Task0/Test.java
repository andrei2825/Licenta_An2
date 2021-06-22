package Task0;

interface Engine {
    int getFuelCapacity();
}

class Car {
    class OttoEngine implements Engine {
        private int fuelCapacity;

        public OttoEngine(int fuelCapacity) {
            this.fuelCapacity = fuelCapacity;
        }

        public int getFuelCapacity() {
            return fuelCapacity;
        }
    }

    public OttoEngine getEngine() {
        OttoEngine engine = new OttoEngine(11);
        return engine;
    }
}

class Car2 {
    public Engine getEngine(int fuelCapacity) {
        return new Engine () {
            private int fuelCapacity = 11;

            public int getFuelCapacity() {
                return fuelCapacity;
            }
        };
    }
}

public class Test {
    public static void main(String[] args) {
        Car car = new Car();

        Car.OttoEngine firstEngine = car.getEngine();
        Car.OttoEngine secondEngine = car.new OttoEngine(10);

        Car2 car2 = new Car2();
        int fuel = car2.getEngine(5).getFuelCapacity();

        System.out.println(firstEngine.getFuelCapacity());
        System.out.println(secondEngine.getFuelCapacity());

        System.out.println("test anonim " + fuel);
    }
}