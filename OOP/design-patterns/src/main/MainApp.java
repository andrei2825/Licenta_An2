package main;

import observers.ConsoleLogger;
import observers.DataAggregator;
import observers.ServerCommunicationController;
import storage.DataRepository;
import storage.SensorData;

import java.util.Scanner;

public class MainApp {

    public static void main(String[] args) {

        System.out.println("Choose a strategy: type 'basic or 'filtered");
        Scanner scanner = new Scanner(System.in);
        String strategyType = scanner.next();
        scanner.close();

        DataRepository dataRepository = new DataRepository();
        // TODO: use the StepCountStrategyFactory to create a strategy

        // TODO: add observers to the dataRepository
        // don't forget to provide the strategy to the DataAggregator observer

        DataAggregator dataAggregator = new DataAggregator(strategyType);
        ConsoleLogger consoleLogger = new ConsoleLogger();
        ServerCommunicationController serverCommunicationController =
                new ServerCommunicationController();
        dataRepository.addObserver(dataAggregator);
        dataRepository.addObserver(consoleLogger);
        dataRepository.addObserver(serverCommunicationController);

        long baseTimestamp = System.currentTimeMillis();

        dataRepository.addData(new SensorData(10, baseTimestamp + 1));
        System.out.println();

        dataRepository.addData(new SensorData(20, baseTimestamp + 2));
        System.out.println();

        dataRepository.addData(new SensorData(30, baseTimestamp + 3));
        System.out.println();

        // TODO: after the first successful run, change this to baseTimestamp + 40000 and check the result
        dataRepository.addData(new SensorData(4000, baseTimestamp + 4));
        System.out.println();

        dataRepository.addData(new SensorData(50, baseTimestamp + 5));
        System.out.println();

        dataRepository.addData(new SensorData(-100, baseTimestamp + 6));
        System.out.println();

        dataRepository.addData(new SensorData(500, baseTimestamp + 600));
        System.out.println();

    }
}
