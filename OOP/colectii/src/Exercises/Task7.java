package Exercises;

import java.util.LinkedHashSet;

public class Task7<Integer> extends LinkedHashSet<Integer> {
    @Override
    public boolean add(Integer integer) {
        String temp = integer.toString();
        int testVar = java.lang.Integer.parseInt(temp);
        if (testVar % 2 == 0) {
            return super.add(integer);
        }
        return false;
    }
}
