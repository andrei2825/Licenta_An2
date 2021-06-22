package observers;

import dataprocessing.BasicStepCountStrategy;
import dataprocessing.FilteredStepCountStrategy;
import storage.SensorData;

import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;

public class DataAggregator implements Observer {
    String strategy = new String();

    public DataAggregator(String strategy) {
        this.strategy = strategy;
    }

    @Override
    public void update(Observable o, Object arg) {
        if (this.strategy.equals("filtered")) {
            FilteredStepCountStrategy filter = new FilteredStepCountStrategy((ArrayList<SensorData>) arg);
            System.out.println(strategy + filter.getTotalSteps());
        } else {
            BasicStepCountStrategy basic = new BasicStepCountStrategy((ArrayList<SensorData>) arg);
            System.out.println(strategy + basic.getTotalSteps());
        }
    }
}
