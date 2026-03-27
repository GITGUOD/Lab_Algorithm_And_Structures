
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
        int length = 5;
        int alphabets = 26;

        int[] word1Letters = new int[alphabets];
        int[] word2Letters = new int[alphabets];

        for (int i = 1; i < length; i++) {
            int wordIndex = word1.charAt(i);
            word1Letters[wordIndex - 'a']++;
            System.out.println(word1);
            System.out.println(wordIndex + " " + Arrays.toString(word1Letters));
        }

        for (int i = 0; i < length; i++) {
            int wordIndex = word2.charAt(i);
            word2Letters[wordIndex - 'a']++;
            System.out.println(word2);
            System.out.println(wordIndex + " " + Arrays.toString(word2Letters));
        }

        for (int i = 0; i < alphabets; i++) {
            if (word1Letters[i] > word2Letters[i]) {
                return false;
            }
        }

        return true;
    }
    

    public int bfs(HashMap<String, List<String>> adj, String start, String target) {
        Queue<String> queue = new LinkedList<>();
        HashMap<String, Integer> dist = new HashMap<>();

        queue.add(start);
        dist.put(start, 0);

        while (!queue.isEmpty()) {
            String node = queue.poll();

            if (node.equals(target)) {
                return dist.get(node);
            }

            for (String neighbor : adj.get(node)) {
                if (!dist.containsKey(neighbor)) {
                    dist.put(neighbor, dist.get(node) + 1);
                    queue.add(neighbor);
                }
            }
        }

        return -1;
    }
}