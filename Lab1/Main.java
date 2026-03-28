import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        try {
            // filnamn
            // String path = "C:\\Users\\Tonny\\OneDrive\\Dokument\\LabbarAlgoritmer\\Lab_Algorithm_And_Structures\\Lab1\\data\\sample\\1.in";
            String path = "C:\\Users\\Tonny\\OneDrive\\Dokument\\LabbarAlgoritmer\\Lab_Algorithm_And_Structures\\Lab1\\data\\secret\\1small1.in";
            //String path = "C:\\Users\\Tonny\\OneDrive\\Dokument\\LabbarAlgoritmer\\Lab_Algorithm_And_Structures\\Lab1\\data\\secret\\2small2.in";
            //String path = "C:\\Users\\Tonny\\OneDrive\\Dokument\\LabbarAlgoritmer\\Lab_Algorithm_And_Structures\\Lab1\\data\\secret\\4medium2.in";

            Scanner scanFile = new Scanner(new File(path));
            System.out.print("Start \n");
            int numberOfWords = scanFile.nextInt();
            System.out.println("nbrWords " + numberOfWords);
            int pairs = scanFile.nextInt();
            System.out.println("pairs: " + pairs);

            scanFile.nextLine();

            String[] words = new String[numberOfWords]; //Vi vill lägga in orden i inputdatan här
            for (int i = 0; i < numberOfWords; i++) {
                words[i] = scanFile.nextLine().trim();
            }

            String[][] queries = new String[pairs][2]; // Samma här fast med paren
            for (int i = 0; i < pairs; i++) {
                queries[i][0] = scanFile.next();
                queries[i][1] = scanFile.next();
            }

            Algorithm algo = new Algorithm();
            HashMap<String, List<String>> graph = algo.buildGraph(words); // Bygga grafen med orden och dess grannar

            // 5. bfs
            for (int i = 0; i < pairs; i++) {
                String start = queries[i][0];
                String end = queries[i][1];

                int svar = algo.bfs(graph, start, end);
                System.out.println(svar);
            }

            scanFile.close();

        } catch (FileNotFoundException e) {
            System.out.println("Filen hittades inte.");
            e.printStackTrace();
        }
    }
}