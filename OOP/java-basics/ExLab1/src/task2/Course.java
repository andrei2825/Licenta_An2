//Nume: Porumb Andrei Cornel
package task2;

public class Course {
    public int getI() {
        return i;
    }

    public void setI(int i) {
        this.i = i;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    private int i;
    private String title;
    private String description;
    Student[] students = new Student[3];
    Student[] listStudenti = new Student[3];

    public Student[] filterYear(int year) {
        int j = 0;
        for (i = 0; i < students.length; i++) {
            if (students[i].getYear() == year) {
                listStudenti[j++] = students[i];
            }

        }
        return listStudenti;
    }
}
