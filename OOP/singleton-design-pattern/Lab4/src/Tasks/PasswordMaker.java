//Nume: Porumb Andrei-Cornel
package Tasks;

import java.util.Random;

public class PasswordMaker {
    private static PasswordMaker instance = null;
    static String name;
    /*da, este nevoie ca acest counter sa fie static deoarece nu ne dorim ca acesta sa poata fi modificat
    in afara acestei clase*/
    static int counter;
    static int MAGIC_NUMBER = 13;
    static RandomStringGenerator rand1 = new RandomStringGenerator(21, "abcdefghijklmnopqrstuvwxyz");
    static String MAGIC_STRING = rand1.next();
    private PasswordMaker(String name){
        this.name = name;
    }
    public static PasswordMaker getInstance(String name) {
        counter++;
        if(instance == null) {
            instance = new PasswordMaker(name);
        }
        return instance;
    }
    public static String getPassword(){
        RandomStringGenerator rand2 = new RandomStringGenerator(10, MAGIC_STRING);
        RandomStringGenerator rand3 = new RandomStringGenerator(MAGIC_NUMBER, rand2.next());
        String sirOne = rand3.next();
        int length = name.length();
        String sirTwo = String.valueOf(length);
        Random rand = new Random();
        int randomNumber = rand.nextInt(100);
        sirTwo = sirTwo + String.valueOf(randomNumber);
        String password = sirOne + sirTwo;
        return password;
    }
}

/*Legat de tema de gandire, cred ca daca am realiza un program paralelizat si am incerca sa
folosim conceptul de singleton pattern, ar putea aparea urmatoarea problema: un thread se poate
opri din rulare pentru a lasa un alt thread sa ruleze dupa ce verifica daca instance este null,
putand sa creeze o instante, astfel in momentul in care priul thread isi reia activitatea, si acesta
va creea o instanta, lucru care ar face utilizarea singletone pattern inutila.
 */