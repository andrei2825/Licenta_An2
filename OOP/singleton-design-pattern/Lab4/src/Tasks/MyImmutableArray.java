//Nume: Porumb Andrei-Cornel
package Tasks;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public  class MyImmutableArray {
    final private  ArrayList<Integer> immutableArray = new ArrayList<Integer>();
    public MyImmutableArray(ArrayList<Integer> arr) {
        for (int i = 0; i < arr.size(); i++) {
            immutableArray.add(arr.get(i));
        }
    }
    /*public ArrayList<Integer> getArray() {
        return new ArrayList<Integer>(immutableArray);
    }*/
    public List<Integer> getArray() {
        return Collections.unmodifiableList(immutableArray);
    }
}
