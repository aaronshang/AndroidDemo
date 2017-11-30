/**
 * 
 */
package com.sk.hellojni;

/**
 * @author aaron
 *
 */
public class HelloJni {

	static {
		
		System.loadLibrary("hellojni");
	}
	public native int AddNumber(int a,  int b);
}
