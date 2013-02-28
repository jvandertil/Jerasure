package eu.vandertil.jerasure.jni;

import java.util.Random;

/**
 * Created with IntelliJ IDEA.
 * User: Jos
 * Date: 28-2-13
 * Time: 15:13
 * To change this template use File | Settings | File Templates.
 */
public class TestApplication {
    static {
        System.loadLibrary("Jerasure.JNI");
    }

    public static void main(String... args) {
        int[] matrix = ReedSolomon.getVandermondeCodingMatrix(2, 4, 8);
        byte[][] data = new byte[2][8];
        byte[][] coding = new byte[4][8];

        Random rand = new Random();
        for (int i = 0; i < data.length; ++i) {
            rand.nextBytes(data[i]);
        }

        Encoding.encodeWithMatrix(2, 4, 8, matrix, data, coding, 8);
    }
}
