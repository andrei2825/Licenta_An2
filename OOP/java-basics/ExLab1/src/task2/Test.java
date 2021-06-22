//Nume: Porumb Andrei Cornel
package task2;

import java.util.Arrays;

public class Test {
    public static void main(String[] args) {
        //Task 2
        Course Course = new Course();
        Student Stud1 = new Student();
        Student Stud2 = new Student();
        Student Stud3 = new Student();
        Stud1.setName("Alex");
        Stud1.setYear(2020);
        Stud2.setName("Max");
        Stud2.setYear(2020);
        Stud3.setName("Jeff");
        Stud3.setYear(2021);
        Course.setTitle("java");
        Course.setDescription("cool programing language");
        Course.students[0] = Stud1;
        Course.students[1] = Stud2;
        Course.students[2] = Stud3;
        Student[] listStudents = new Student[4];
        listStudents = Course.filterYear(2020);
        System.out.println(Arrays.toString(listStudents));

        //Task 3
        Student Student1 = new Student();
        Student Student2 = new Student();
        Student1.setYear(2020);
        Student1.setName("Andrei");
        Student2.setYear(2020);
        Student2.setName("Andrei");
        System.out.println((Student1.equals(Student2)));
    }
}
