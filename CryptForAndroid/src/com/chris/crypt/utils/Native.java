package com.chris.crypt.utils;

public class Native {

	/******************************************************
	 * Encode (DES -> BASE64 -> ZIP)
	 * 
	 * @param key: encrypt key (default: 12345678)
	 * @param src: String
	 * @return output: Binary  
	 ******************************************************/
	public static native byte[] dbz(String key, String src);
	
	/******************************************************
	 * Encode (DES -> BASE64)
	 * 
	 * @param key: encrypt key (default: 12345678)
	 * @param src: String
	 * @return output: Base64 String  
	 ******************************************************/
	public static native String db(String key, String src);
	
	/******************************************************
	 * Decode (ZIP -> BASE64 -> DES)
	 * 
	 * @param key: encrypt key (default: 12345678)
	 * @param src: Binary
	 * @return output: String 
	 ******************************************************/
	public static native String uuu(String key, byte[] src);
	
	/******************************************************
	 * Decode (BASE64 -> DES)
	 * 
	 * @param key: encrypt key (default: 12345678)
	 * @param src: Base64 String
	 * @return output: String 
	 ******************************************************/
	public static native String uu(String key, String src);
	
	static {  
        System.loadLibrary("crypt");
    }
}
