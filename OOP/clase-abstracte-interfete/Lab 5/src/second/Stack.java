package second;

import first.Task;

import java.util.ArrayList;

public class Stack implements Container{
    ArrayList<Task> list;
    private int size = 0;
    public Stack(){
        list = new ArrayList<Task>();
    }

    @Override
    public Task pop() {
        if (list.isEmpty()) {
            System.out.println("UnderFlow\\nProgram Terminated");
            System.exit(1);
        }
        Task temp = list.get(list.size()-1);
        list.remove(0);
        this.size--;
        return temp;
    }

    @Override
    public void push(Task task) {
        list.add(task);
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

    }
    public ArrayList<first.Task> getTasks() {
        return list;
    }
}
