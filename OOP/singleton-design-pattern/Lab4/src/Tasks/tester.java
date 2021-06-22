//Nume: Porumb Andrei-Cornel
package Tasks;

import java.util.ArrayList;

public class tester {
    public static void main(String[] args){
        /*PasswordMaker maker = PasswordMaker.getInstance("Andrei");
        System.out.println(maker.getPassword());*/
        ArrayList<Integer> list = new ArrayList<>();
        list.add(4);
        list.add(13);
        list.add(31);
        MyImmutableArray arr = new MyImmutableArray(list);
        ArrayList<Integer> list2 = new ArrayList<>();
        /* urmatoarea linie ar genera o eraore daca as incerca sa modific un element din immutableArray
        list2.add(1, 5);*/
        list2.add(14);
        list2.add(32);
        MyImmutableArray arr2 = new MyImmutableArray(list2);
        System.out.println(arr.getArray());
        System.out.println(arr2.getArray());
    }
}
