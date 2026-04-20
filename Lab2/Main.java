package Lab2;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        SeparateChainingHashTable d = new SeparateChainingHashTable();

        int i = 0;

        while (sc.hasNextLine()) {
            String word = sc.nextLine().trim();

            boolean isPresent = d.contains(word);
            boolean removeIt = (i % 16 == 0);

            if (isPresent) {
                if (removeIt) {
                    d.remove(word);
                } else {
                    d.put(word, d.get(word) + 1);
                }
            } else if (!removeIt) {
                d.put(word, 1);
            }

            i++;
        }

        String bestWord = "";
        int bestCount = -1;

        for (String key : d.keys()) {
            int count = d.get(key);

            if (count > bestCount ||
               (count == bestCount && key.compareTo(bestWord) < 0)) {
                bestCount = count;
                bestWord = key;
            }
        }

        System.out.println(bestWord + " " + bestCount);
        
    }
}