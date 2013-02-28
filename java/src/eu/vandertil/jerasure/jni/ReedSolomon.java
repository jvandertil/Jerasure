package eu.vandertil.jerasure.jni;

/**
 * This class provides JNI coupling to the JErasure ReedSolomon encoding.
 *
 * @author Jos van der Til (JNI coupling)
 * @author James S. Plank (JErasure library)
 * @version 1.0
 * @since 1.0
 */
public class ReedSolomon {
    /**
     * This returns the last m rows of the distribution matrix
     * in GF(2^w), based on an extended Vandermonde matrix.
     * The first row of this matrix is guaranteed to be all ones. The first column is also
     * guaranteed to be all ones.
     *
     * @param dataDevices   The number of data devices.
     * @param codingDevices The number of coding devices.
     * @param wordSize      The word size of the data (byte = 8 / short = 16 / int = 32 / etc)
     *
     * @return A m * k matrix that can be used with the matrix routines in Jerasure.
     */
    public static native int[] getVandermondeCodingMatrix(int dataDevices, int codingDevices, int wordSize);

    /**
     * Convenience method for getVandermondeCodingMatrix with wordsize 8.
     */
    public static int[] getVandermondeCodingMatrixForBytes(int dataDevices, int codingDevices) {
        return getVandermondeCodingMatrix(dataDevices, codingDevices, 8);
    }

    /**
     * This creates an extended Vandermonde matrix with rows rows and cols columns in GF(2^w).
     *
     * @param rows     The requested number of rows
     * @param cols     The requested number of columns
     * @param wordSize The word size.
     *
     * @return an extended Vandermonde matrix with 'rows' rows and 'cols' columns in GF(2^w).
     */
    public static native int[] getExtendedVandermondeMatrix(int rows, int cols, int wordSize);

    /**
     * This converts the extended matrix from getExtendedVandermondeMatrix into a distribution matrix so that the top 'cols' rows compose an identity matrix,
     * and the remaining rows are in the format returned by getVandermondeCodingMatrix.
     *
     * @param rows     The requested number of rows
     * @param cols     The requested number of columns
     * @param wordSize The word size.
     *
     * @return
     */
    public static native int[] getBigVandermondeDistributionMatrix(int rows, int cols, int wordSize);
}
