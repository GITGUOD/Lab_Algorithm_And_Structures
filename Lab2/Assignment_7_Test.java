package Lab2;

public class Assignment_7_Test {

    public static void main(String[] args) {

        /*
        Linear a =0.3 time=19.1033 ms
        Linear a =0.5 time=3.7199 ms
        Linear a =0.75 time=5.0205 ms
        Linear a =0.9 time=7.2563 ms

        Linear mean a =0.3 avg=1.388214 ms
        Linear mean a =0.5 avg=1.331024 ms
        Linear mean a =0.75 avg=2.105221 ms
        Linear mean a =0.9 avg=4.17205 ms

        Quadratic a =0.3 time=6.4221 ms
        Quadratic a =0.5 time=4.7359 ms
        Quadratic a =0.75 time=2.6042 ms
        Quadratic a =0.9 time=2.6482 ms

        Quadratic mean a =0.3 avg=0.827161 ms
        Quadratic mean a =0.5 avg=0.686964 ms
        Quadratic mean a =0.75 avg=0.729185 ms
        Quadratic mean a =0.9 avg=0.985124 ms

        Slutsats:
        Linear probing:
            prestanda varierar mycket med α, särskilt a < 0.5, blir instabil
            Sämre spridning, vid a > 0.9 blir det många kollisioner → långsamt
        Quadratic probing:
            mer stabil och snabbare
            bättre spridning
        */

        testLinear(0.3);
        testLinear(0.5);
        testLinear(0.75);
        testLinear(0.9);
        testLinearMean(0.3);
        testLinearMean(0.5);
        testLinearMean(0.75);
        testLinearMean(0.9);

        testQuadratic(0.3);
        testQuadratic(0.5);
        testQuadratic(0.75);
        testQuadratic(0.9);
        testQuadraticMean(0.3);
        testQuadraticMean(0.5);
        testQuadraticMean(0.75);
        testQuadraticMean(0.9);
    }

    public static void testLinear(double alpha) {

        LinearProbingHashTable t = new LinearProbingHashTable(alpha);

        long start = System.nanoTime();

        for (int i = 0; i < 10000; i++)
            t.put("key" + i, i);

        long end = System.nanoTime();

        System.out.println("Linear a =" + alpha +
                " time=" + (end - start) / 1e6 + " ms");
    }

    public static void testQuadratic(double alpha) {

        HashTable t = new QuadraticProbingHashTable(alpha); // to check that we can use the same code for both types of tables
        long start = System.nanoTime();

        for (int i = 0; i < 10000; i++)
            t.put("key" + i, i);

        long end = System.nanoTime();

        System.out.println("Quadratic a =" + alpha +
                " time=" + (end - start) / 1e6 + " ms");
    }

    public static void testLinearMean(double alpha) {

    long total = 0;

    for (int i = 0; i < 100; i++) {

        LinearProbingHashTable t = new LinearProbingHashTable(alpha);

        long start = System.nanoTime();

        for (int j = 0; j < 10000; j++) {
            t.put("key" + j, j);
        }

        long end = System.nanoTime();

        total += (end - start);
    }

    double avg = total / 100.0;

    System.out.println("Linear mean a =" + alpha + " avg=" + avg / 1e6 + " ms");
}

public static void testQuadraticMean(double alpha) {

    long total = 0;

    for (int i = 0; i < 100; i++) {

        QuadraticProbingHashTable t = new QuadraticProbingHashTable(alpha);

        long start = System.nanoTime();

        for (int j = 0; j < 10000; j++) {
            t.put("key" + j, j);
        }

        long end = System.nanoTime();

        total += (end - start);
    }

    double avg = total / 100.0;

    System.out.println("Quadratic mean a =" + alpha + " avg=" + avg / 1e6 + " ms");
}
}