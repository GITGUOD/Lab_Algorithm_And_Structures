
import java.util.*;

public class Algorithm {

    public Algorithm() {

    }

    public HashMap<String, List<String>> buildGraph(String[] words) {
        HashMap<String, List<String>> list = new HashMap<>();

        for(String word: words) {
            list.put(word, new ArrayList<>());
        }

        // Bygga noderna eller grannarna
        for (String w : words) {
            for (String w2 : words) {
                if (!w.equals(w2) && hasEdge(w, w2)) {
                    list.get(w).add(w2);
                }
            }
        }

        return list;
    }

    public boolean hasEdge(String word1, String word2) {
        /*
            Jämförelse mellan de sista 4 bokstäverna i startordet
            med alla bokstäver i det andra ordet.
            T.ex:
            w1 = hello -> sista fyra = ello, två "l", ett "e" och ett "o"
            w2 = lolem -> Alla fem = två "l", ett "o", ett "e" och ett "m", vi har ett "m" som skillnad
            medan alla andra bokstäver finns med, då finns edge med.
        */
        int length = 5;
        int alphabets = 26;

        int[] word1Letters = new int[alphabets];
        int[] word2Letters = new int[alphabets];

        // Bygga första ordet
        for (int i = 1; i < length; i++) {
            int wordIndex = word1.charAt(i);
            word1Letters[wordIndex - 'a']++;
            //debugging
            // System.out.println(word1);
            // System.out.println(wordIndex + " " + Arrays.toString(word1Letters));
        }

        // Bygga andra ordet
        for (int i = 0; i < length; i++) {
            int wordIndex = word2.charAt(i);
            word2Letters[wordIndex - 'a']++;
            //debugging
            // System.out.println(word2);
            // System.out.println(wordIndex + " " + Arrays.toString(word2Letters));
        }

        // Om det finns fler bokstäver än den andra, är de inte grannar
        for (int i = 0; i < alphabets; i++) {
            if (word1Letters[i] > word2Letters[i]) {
                return false;
            }
        }

        return true;
    }
    

    public int bfs(HashMap<String, List<String>> graph, String start, String target) {
        Queue<String> queue = new LinkedList<>(); // Skapa en kö för BFS
        HashMap<String, Integer> dist = new HashMap<>(); // Skapa en hash map för att hålla avståndet från startnoden till varje nod

        queue.add(start);
        dist.put(start, 0); 

        // BFS loop där vi besöker varje nod och dess grannar så länge kön inte är tom
        while (!queue.isEmpty()) {
            String node = queue.poll(); 

            if (node.equals(target)) {
                return dist.get(node);
            }
            // Gå igenom alla grannar till den aktuella noden
            for (String neighbor : graph.get(node)) {
                if (!dist.containsKey(neighbor)) {
                    dist.put(neighbor, dist.get(node) + 1);
                    queue.add(neighbor);
                }
            }
        }

        return -1;
    }
}