package Exercises;

import java.util.*;

public class Test {
    public static void main(String[] args) {
//        Task 1
        Student student1 = new Student("Williams", "Shahzaib", 1, 8.5);
        Student student2 = new Student("Oconnor", "Carl ", 2, 8.5);
        Student student3 = new Student("Mccaffrey", "Vivaan ", 3, 6.3);
        Student student4 = new Student("Todd", "Travis ", 4, 9.8);
        Student student5 = new Student("Susanna ", "Travis  ", 5, 9.8);
        System.out.println("Task 1: ");
        System.out.println(student1 + " \n" + student2 + "\n " + student1.compareTo(student2));
//        Task 2
        ArrayList<Student> students = new ArrayList<>();
        students.add(student1);
        students.add(student2);
        students.add(student3);
        students.add(student4);
        students.add(student5);
        System.out.println("Task 2: ");
        System.out.println("Before sorting: ");
        for (Student student : students) {
            System.out.println(student);
        }
        Collections.sort(students);
        System.out.println("After sorting: ");
        for (Student student : students) {
            System.out.println(student);
        }
//        Task 3
        ArrayList<Student> students2 = new ArrayList<>();
        students2.add(student1);
        students2.add(student2);
        students2.add(student3);
        students2.add(student4);
        students2.add(student5);
        System.out.println("Task 3: ");
        System.out.println("Before sorting: ");
        for (Student student : students2) {
            System.out.println(student);
        }
        students2.sort(((o1, o2) -> (int) (o2.getAverageGrade() - o1.getAverageGrade())));
        System.out.println("After sorting: ");
        for (Student student : students2) {
            System.out.println(student);
        }

//        Task 4
        System.out.println("Task 4: ");
        PriorityQueue<Student> priorityQueue = new PriorityQueue<>(((o1, o2) -> (int) (o1.getId() - o2.getId())));
        priorityQueue.addAll(students2);
        System.out.println(priorityQueue.poll());
        priorityQueue.forEach(student -> System.out.println(student.toString()));

//        Task 5
        System.out.println("Task 5: ");
        LinkedList<String> classes1 = new LinkedList<>();
        classes1.add("Math");
        classes1.add("Physics");
        classes1.add("OOP");
        LinkedList<String> classes2 = new LinkedList<>();
        classes2.add("Geography");
        classes2.add("History");
        classes2.add("English");
        LinkedList<String> classes3 = new LinkedList<>();
        classes3.add("Math");
        classes3.add("French");
        classes3.add("Chemistry");
        LinkedList<String> classes4 = new LinkedList<>();
        classes4.add("Biology");
        classes4.add("Physics");
        classes4.add("Chemistry");
        LinkedList<String> classes5 = new LinkedList<>();
        classes5.add("Math1");
        classes5.add("Math2");
        classes5.add("Math3");
        HashMap<Student, LinkedList<String>> studentClasses = new HashMap<>();
        studentClasses.put(student1, classes1);
        studentClasses.put(student2, classes2);
        studentClasses.put(student3, classes3);
        studentClasses.put(student4, classes4);
        studentClasses.put(student5, classes5);
        for (Map.Entry<Student, LinkedList<String>> entry : studentClasses.entrySet()) {
            System.out.println(entry.toString());
        }

//        Task 7
        System.out.println("Task 7: ");
        Task7<Integer> numberSet = new Task7<>();
        numberSet.add(1);
        numberSet.add(2);
        numberSet.add(3);
        numberSet.add(4);
        numberSet.add(5);
        for (Integer number : numberSet) {
            System.out.println(number);
        }

    }
}
