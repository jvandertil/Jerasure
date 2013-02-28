package eu.vandertil.jerasure.jni;

/**
 * Created with IntelliJ IDEA.
 * User: Jos
 * Date: 28-2-13
 * Time: 14:07
 * To change this template use File | Settings | File Templates.
 */
public class Decoding {
    public static native boolean decodeWithMatrix(int numDataDevices, int numCodingDevices, int wordSize, int[] matrix,
                                                  boolean firstRowInMatrixIsAllOnes, int[] erasedDevices,
                                                  byte[][] dataDevices, byte[][] codingDevices, int size);

    /**
     *
     * @param matrix The coding matrix
     * @param deviceStatus The status of each device. If a device is working it should be true, otherwise false.
     *                     An id between 0 and dataDevices.length represents a data device.
     *                     An id between dataDevices.length and (codingDevices.length + dataDevices.length) represents a coding device.
     * @param dataDevices The data devices
     * @param codingDevices The coding devices
     * @return
     */
    public static boolean decodeWithMatrix(int[] matrix, boolean[] deviceStatus, byte[][] dataDevices, byte[][] codingDevices) {
        int expectedArrayLength = dataDevices[0].length;
        for (int i = 0; i < dataDevices.length; ++i) {
            if (dataDevices[i].length != expectedArrayLength)
                throw new IllegalArgumentException("Data devices are not all the same length");
        }

        for (int i = 0; i < codingDevices.length; ++i) {
            if (codingDevices[i].length != expectedArrayLength)
                throw new IllegalArgumentException("Coding devices are not all the same length");
        }

        int numDataDevices = dataDevices.length;
        int numCodingDevices = codingDevices.length;

        if(matrix.length != (numCodingDevices * numDataDevices))
            throw new IllegalArgumentException("Matrix not valid");

        boolean firstRowInMatrixIsAllOnes = true;
        for (int i = 0; i < numCodingDevices; ++i) {
            if (matrix[i] != 1) {
                firstRowInMatrixIsAllOnes = false;
                break;
            }
        }

        int[] erasedDevices = new int[deviceStatus.length];
        int index = 0;
        for(int i = 0; i < deviceStatus.length; ++i)
        {
            if(deviceStatus[i] == false)
                erasedDevices[index++] = i;
        }

        erasedDevices[index] = -1;

        return decodeWithMatrix(numDataDevices, numCodingDevices, 8, matrix, firstRowInMatrixIsAllOnes,
                                erasedDevices, dataDevices, codingDevices, expectedArrayLength);
    }

}
