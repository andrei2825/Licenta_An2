package dataprocessing;

import storage.SensorData;

import java.util.ArrayList;

public class FilteredStepCountStrategy implements  StepCountStrategy{

    int steps;

    public  FilteredStepCountStrategy(ArrayList<SensorData> data) {
        for (SensorData sensorData : data) {
            if (sensorData.getStepsCount() > 0 && sensorData.getStepsCount() < 1000) {
                if (sensorData.getTimestamp() > 1) {
                    this.steps += sensorData.getStepsCount();
                }
            }
        }
    }

    @Override
    public int getTotalSteps() {
        return steps;
    }

    @Override
    public String getStrategyDescription() {
        return null;
    }
}
