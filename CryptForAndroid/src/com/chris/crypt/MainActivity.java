package com.chris.crypt;

import java.util.ArrayList;

import android.app.Activity;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;

import com.chris.crypt.model.TestBean;
import com.chris.crypt.utils.Native;
import com.google.gson.Gson;

public class MainActivity extends Activity {

	private final String KEY = "!~crypt!";
	private final String TAG = "ChrisCrypt";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		init();
	}
	
	private void init(){
		TextView clk = (TextView) findViewById(R.id.clk);
		clk.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				TestBean bean = getTestBean();
				Gson gson = new Gson();
				testCrypt(gson.toJson(bean));
			}
		});
	}
	
	private TestBean getTestBean(){
		PackageInfo info = null;
		try {
			info = getPackageManager().getPackageInfo(getPackageName(), 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		
		TestBean bean = new TestBean();
		if(info != null){
			bean.setPackageNames(info.packageName);
			bean.setVersionName(info.versionName);
			bean.setVersionCode(info.versionCode);
			
			ArrayList<String> list = new ArrayList<String>();
			list.add("com");
			list.add("chris");
			list.add("crypt");
			bean.setList(list);
		}
		return bean;
	}
	
	/************************************************************************************************
	 * 
	 * The encrypt/decrypt's key can be null
	 * 
	 ************************************************************************************************/
	private void testCrypt(String json){
		Log.d(TAG, "-------------------{Base64}Encode(Key)----------------------");
		String strBase64WithKey = Native.db(KEY, json);
		Log.d(TAG, "[base64] = " + strBase64WithKey.toString() + "\r\n{size = " + strBase64WithKey.length() + "}");
		Log.d(TAG, "-------------------{Base64}Decode(Key)----------------------");
		String dstForBase64WithKey = Native.uu(KEY, strBase64WithKey);
		Log.d(TAG, "[dstbase64] = " + dstForBase64WithKey.toString() + "\r\n{size = " + dstForBase64WithKey.length() + "}");
		
		Log.d(TAG, "-------------------{Base64}Encode(NonKey)----------------------");
		String strBase64WithoutKey = Native.db(null, json);
		Log.d(TAG, "[base64] = " + strBase64WithoutKey.toString() + "\r\n{size = " + strBase64WithoutKey.length() + "}");
		Log.d(TAG, "-------------------{Base64}Decode(NonKey)----------------------");
		String dstForBase64WithoutKey = Native.uu(null, strBase64WithoutKey);
		Log.d(TAG, "[dstbase64] = " + dstForBase64WithoutKey.toString() + "\r\n{size = " + dstForBase64WithoutKey.length() + "}");
		
		Log.d(TAG, "-------------------{Zip}Encode(Key)----------------------");
		byte[] strZipWithKey = Native.dbz(KEY, json);
		Log.d(TAG, "[zip] = " + strZipWithKey.toString() + "\r\n{size = " + strZipWithKey.length + "}");
		Log.d(TAG, "-------------------{UnZip}Decode(Key)----------------------");
		String dstForZipWithKey = Native.uuu(KEY, strZipWithKey);
		Log.d(TAG, "[dstZip] = " + dstForZipWithKey + "\r\n{size = " + dstForZipWithKey.length() + "}");
		
		Log.d(TAG, "-------------------{Zip}Encode(NonKey)----------------------");
		byte[] strZipWithoutKey = Native.dbz(null, json);
		Log.d(TAG, "[zip] = " + strZipWithoutKey.toString() + "\r\n{size = " + strZipWithoutKey.length + "}");
		Log.d(TAG, "-------------------{UnZip}Decode(NonKey)----------------------");
		String dstForZipWithoutKey = Native.uuu(null, strZipWithoutKey);
		Log.d(TAG, "[dstZip] = " + dstForZipWithoutKey + "\r\n{size = " + dstForZipWithoutKey.length() + "}");
	}
}
