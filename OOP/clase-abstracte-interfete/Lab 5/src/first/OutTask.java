package first;

public class OutTask implements Task{
    private String task;
    public OutTask (String task) {
        this.task = task;
    }
    public void execute() {
        System.out.println(task);
    }
}
