package eu.vandertil.jerasure.jni;

/**
 * Provides a JNI coupling to the encoding routines of the JErasure library.
 *
 * @author Jos van der Til (JNI coupling)
 * @author James S. Plank (JErasure library)
 * @version 1.0
 * @since 1.0
 */
public class Encoding {

    /**
     * This calculates the parity of 'size' bytes of data from each of nDataDevices regions of memory accessed by data.
     * It puts the result into the 'size' bytes pointed to by parity.
     * Size must be a multiple of sizeof(long) (typically 8).
     *
     * @param numDataDevices The number of dataDevices
     * @param data The data devices (Should be dataDevices
     * @param parity
     * @param size The number of bytes per device to encode.
     */
    public static native void getParity(int numDataDevices, byte[][] data, byte[] parity, int size);

    /**
     * This encodes with a matrix in GF(2^w)
     * @param numDataDevices The number of data devices.
     * @param numCodingDevices The number of coding devices.
     * @param wordSize The word size
     * @param matrix The encoding matrix (for example from eu.vandertil.jerasure.jni.ReedSolomon)
     * @param dataDevices The data (numDataDevices * size)
     * @param codingDevices The resulting coding devices (numCodingDevices * size)
     * @param size The number of bytes per device to encode.
     */
    public static native void encodeWithMatrix(int numDataDevices, int numCodingDevices, int wordSize, int[] matrix, byte[][] dataDevices, byte[][] codingDevices, int size);

    public static native void encodeWithBitMatrix(int numDataDevices, int numCodingDevices, int wordSize, int[] bitMatrix, byte[][] dataDevices, byte[][] codingDevices, int size, int packetSize);

    public static native void encodeWithSchedule(int numDataDevices, int numCodingDevices, int wordSize, int[][] schedule, byte[][] dataDevices, byte[][] codingDevices, int size, int packetSize);
}
