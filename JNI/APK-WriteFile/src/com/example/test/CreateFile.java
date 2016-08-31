package com.example.test;

public class CreateFile {
	static {
		System.loadLibrary("writefile");
	}

	/**
	 * 生成文件
	 * 
	 * @param filePath
	 *          文件目录
	 */
	public native void createFile(String filePath);

}
