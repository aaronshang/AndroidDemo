package com.example.test;

public class CreateFile {
	static {
		System.loadLibrary("writefile");
	}

	/**
	 * �����ļ�
	 * 
	 * @param filePath
	 *          �ļ�Ŀ¼
	 */
	public native void createFile(String filePath);

}
