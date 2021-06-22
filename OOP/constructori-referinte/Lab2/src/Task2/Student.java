//Nume: Porumb Andrei Cornel
package Task2;

class Student {

    private String name;
    public int averageGrade;

    public Student(String n, int avg) {
        this.name = n;
        this.averageGrade = avg;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static void main(String[] args) {
        // ERROR: the implicit constructor is hidden by the constructor with parameters
        Student s = new Student("David", 5);
    }
}