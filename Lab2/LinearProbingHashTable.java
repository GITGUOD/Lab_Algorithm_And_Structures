package Lab2;

public class LinearProbingHashTable extends HashTable {

    public LinearProbingHashTable(double alpha) {
        super(alpha);
    }

    @Override
    protected int findSlot(String key) {

        int i = hash(key);

        while (keys[i] != null && !keys[i].equals(key)) {
            i = (i + 1) % keys.length;
        }

        return i;
    }
}