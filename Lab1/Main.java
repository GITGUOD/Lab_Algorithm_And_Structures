import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        try {
            // Ange filnamn här
            String path = "C:\\Users\\Tonny\\OneDrive\\Dokument\\LabbarAlgoritmer\\Lab_Algorithm_And_Structures\\Lab1\\data\\sample\\1.in";
            Scanner scanFile = new Scanner(new File(path));
            System.out.print("Start \n");
            // 1. Läs in antal ord (N) och antal queries (Q)
            int N = scanFile.nextInt();
            int Q = scanFile.nextInt();
            scanFile.nextLine(); // ta bort newline

            // 2. Läs in orden
            String[] words = new String[N];
            for (int i = 0; i < N; i++) {
                words[i] = scanFile.nextLine().trim();
            }

            // 3. Läs in queries
            String[][] queries = new String[Q][2];
            for (int i = 0; i < Q; i++) {
                queries[i][0] = scanFile.next();
                queries[i][1] = scanFile.next();
            }

            // 4. Bygg grafen
            Algorithm algo = new Algorithm();
            HashMap<String, List<String>> graph = algo.buildGraph(words);

            // 5. Kör BFS för varje query
            for (int i = 0; i < Q; i++) {
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