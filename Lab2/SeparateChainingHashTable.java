package Lab2;

import java.util.ArrayList;

public class SeparateChainingHashTable {

    private static class Node {
        String key;
        int value;
        Node next;

        Node(String key, int value, Node next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }
    }

    private Node[] table;
    private int size; // number of key-value pairs

    public SeparateChainingHashTable() {
        table = new Node[1];   // assignment says start with one element
        size = 0;
    }

    public int capacity() {
        return table.length;
    }

    // Assignment 5: add method to get current size (number of key-value pairs) and refactoring it depending on its length
    private int hash(String key) {
        return (key.hashCode() & 0x7fffffff) % table.length;
    
    }

    public boolean contains(String key) {
        return getNode(key) != null;
    }

    public int get(String key) {
        Node n = getNode(key);
        return (n == null) ? 0 : n.value;
    }

    private Node getNode(String key) {
        int index = hash(key);
        Node current = table[index];

        while (current != null) {
            if (current.key.equals(key))
                return current;
            current = current.next;
        }

        return null;
    }

    public void put(String key, int value) {
        int index = hash(key);
        Node current = table[index];

        while (current != null) {
            if (current.key.equals(key)) {
                current.value = value;
                return;
            }
            current = current.next;
        }

        table[index] = new Node(key, value, table[index]);
        size++;

        if (size > table.length)
            resize(table.length * 2);
    }

    public void remove(String key) {
        int index = hash(key);

        Node current = table[index];
        Node prev = null;

        while (current != null) {
            if (current.key.equals(key)) {

                if (prev == null)
                    table[index] = current.next;
                else
                    prev.next = current.next;

                size--;
                
                // Assignment 5: resize down, shrink
                if (table.length > 1 && size < table.length / 4)
                    resize(table.length / 2);

                return;
            }

            prev = current;
            current = current.next;
        }
    }

    private void resize(int newCapacity) {
        if (newCapacity < 1)
            newCapacity = 1;

        Node[] oldTable = table;
        table = new Node[newCapacity];
        size = 0;

        for (Node head : oldTable) {
            while (head != null) {
                put(head.key, head.value);
                head = head.next;
            }
        }
    }

    public Iterable<String> keys() {
        ArrayList<String> list = new ArrayList<>();

        for (Node head : table) {
            while (head != null) {
                list.add(head.key);
                head = head.next;
            }
        }

        return list;
    }
}
