package Lab2;

abstract class HashTable {

    protected String[] keys;
    protected int[] values;
    protected int size;
    protected double maxLoadFactor = 0.7;

    public HashTable(double maxLoadFactor) {
        this.keys = new String[8];
        this.values = new int[8];
        this.size = 0;
        this.maxLoadFactor = maxLoadFactor;
    }

    protected int hash(String key) {
        return (key.hashCode() & 0x7fffffff) % keys.length;
    }

    // public void put(String key, int value) {

    //     if (size >= keys.length * maxLoadFactor)
    //         resize(keys.length * 2);

    //     int i = findSlot(key, true);

    //     if (keys[i] == null) size++;

    //     keys[i] = key;
    //     values[i] = value;
    // }
    public void put(String key, int value) {

        if (size >= keys.length * maxLoadFactor)
            resize(keys.length * 2);

        int i = findSlot(key);

        if (i == -1) {
            resize(keys.length * 2);
            i = findSlot(key); // retry after resize
        }

        if (keys[i] == null) size++;

        keys[i] = key;
        values[i] = value;
    }

    public int get(String key) {
        int i = findSlot(key);
        return (i == -1) ? 0 : values[i];
    }

    protected abstract int findSlot(String key);

    protected void resize(int newCap) {

        String[] oldK = keys;
        int[] oldV = values;

        keys = new String[newCap];
        values = new int[newCap];
        size = 0;

        for (int i = 0; i < oldK.length; i++) {
            if (oldK[i] != null) {
                put(oldK[i], oldV[i]);
            }
        }
    }
}