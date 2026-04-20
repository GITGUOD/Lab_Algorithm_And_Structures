package Lab2;

public class Assignment_6_Test {
    public static void main(String[] args) {

        double a = 0.5; // Insert time: 11.3956 ms
        double a2 = 0.75; // Insert time: 14.6228 ms
        double a3 = 0.9; // Insert time: 17.7837 ms
        // 0.5	resize early → table stays empty
        // 0.7	medium fullness
        // 0.9	very full before resizing

        // When table is full:
            // insert → many collisions → many steps → slow

        // When table is empty:
            // insert → few collisions → fast

        HashTable t = new LinearProbingHashTable(a);
        long start = System.nanoTime();

        for (int i = 0; i < 1000; i++) {
            t.put("key" + i, i);
        }

        System.out.println(t.get("key500")); // should print 500 as we want to check that the value is correct and not just a default value
        System.out.println(t.get("key999")); // should print 999

        long end = System.nanoTime();

    System.out.println("Insert time: " + (end - start)/1e6 + " ms");
    }
}
