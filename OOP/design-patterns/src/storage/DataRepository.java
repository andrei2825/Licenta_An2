package storage;


import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

/**
 * Persists sensor data. Observable, its observers are notified when data is added it to.
 */
public class DataRepository extends Observable { // TODO make this an Observable
    ArrayList<SensorData> sensorData = new ArrayList<>();
    private List<Observer> observers = new ArrayList<>();
    public void addData(SensorData dataRecord){
        // TODO
        // store data (e.g. in a List)
        sensorData.add(dataRecord);
        setChanged();
        // notifiy observers
        notifyObservers(sensorData);
    }

    // TODO implement a method to get the stored data (needed by the strategies)

    public ArrayList<SensorData> getSensorData() {
        return sensorData;
    }
}


