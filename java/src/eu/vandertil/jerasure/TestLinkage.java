package eu.vandertil.jerasure;

import eu.vandertil.jerasure.jni.*;
/**
 * Created with IntelliJ IDEA.
 * User: Jos
 * Date: 1-3-13
 * Time: 22:45
 * To change this template use File | Settings | File Templates.
 */
public class TestLinkage {
    public static void main(String[] args) {
        System.loadLibrary("Jerasure.jni");
        System.out.println("Correctly loaded libJerasure.jni");
    }
}
