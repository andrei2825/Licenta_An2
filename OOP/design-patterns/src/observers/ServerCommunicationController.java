package observers;

import java.util.Observable;
import java.util.Observer;

public class ServerCommunicationController implements Observer {
    @Override
    public void update(Observable o, Object arg) {
        System.out.println("Update  -> server");
    }
}
