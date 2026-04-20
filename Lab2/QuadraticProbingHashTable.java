package Lab2;

public class QuadraticProbingHashTable extends HashTable {

    public QuadraticProbingHashTable(double alpha) {
        super(alpha);
    }

    @Override
    protected int findSlot(String key) {

        int base = hash(key);
        int j = 0;

        while (j < keys.length) {

            int i = (base + j * j) % keys.length;

            if (keys[i] == null)
                return i;

            if (keys[i].equals(key))
                return i;

            j++;
        }

        return -1;
    }
}