package second;

import first.Task;

import java.util.ArrayList;
import java.util.Collections;

public class Queue implements Container{
    ArrayList<Task> list;
    private int size = 0;
    public Queue() {
        this.list = new ArrayList<Task>();
    }

    @Override
    public Task pop() {
        if (list.isEmpty()) {
            System.out.println("UnderFlow\\nProgram Terminated");
            System.exit(1);
        }
        Task temp = list.get(0);
        list.remove(0);
        this.size--;
        return temp;
    }

    @Override
    public void push(Task task) {
        list.add(0, task);
        this.size++;
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public void transferFrom(Container container) {
        int contSize = container.size();
        for (int i = 0; i < contSize; i++) {
            push(container.pop());
        }
    }

    public ArrayList<first.Task> getTasks() {
        return list;
    }
}


