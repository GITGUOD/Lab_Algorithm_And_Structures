package Lab2;

public class Assignment_5_Test {
    public static void main(String[] args) {

        SeparateChainingHashTable table = new SeparateChainingHashTable();

        // STEP 1: force growth
        for (int i = 0; i < 100; i++) {
            table.put("key" + i, 1);
        }

        System.out.println("After inserts: " + table.capacity());

        // STEP 2: force shrink
        for (int i = 0; i < 95; i++) {
            table.remove("key" + i);
        }

        System.out.println("After removals: " + table.capacity());

        // STEP 3: check remaining keys
        for (String k : table.keys()) {
            System.out.println(k + " " + table.get(k));
        }

        System.out.println("Initial capacity check not visible directly, but we test behavior by forcing growth and shrink.");

    }
}
