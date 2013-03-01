package eu.vandertil.jerasure;
/**
 * Created with IntelliJ IDEA.
 * User: Jos
 * Date: 1-3-13
 * Time: 13:46
 * To change this template use File | Settings | File Templates.
 */
public class Decoding {
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

        /*return eu.vandertil.jerasure.jni.Decoding.decodeWithMatrix(numDataDevices, numCodingDevices, 8, matrix, firstRowInMatrixIsAllOnes,
                erasedDevices, dataDevices, codingDevices, expectedArrayLength);
        */
        return true;
    }
}
