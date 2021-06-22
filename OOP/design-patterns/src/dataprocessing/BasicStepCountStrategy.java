package dataprocessing;

import storage.SensorData;

import java.util.ArrayList;

public class BasicStepCountStrategy implements StepCountStrategy{
    int steps;

    public  BasicStepCountStrategy(ArrayList<SensorData> data) {
        for (SensorData sensorData : data) {
            this.steps += sensorData.getStepsCount();
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
