package com.chris.crypt.model;

import java.io.Serializable;
import java.util.ArrayList;

public class TestBean implements Serializable {

	private static final long serialVersionUID = 8273981695334015639L;

	private String packageNames = null;
	private String versionName = null;
	private int versionCode  = 0;
	private ArrayList<String> list = null;
	
	public String getPackageNames() {
		return packageNames;
	}
	public void setPackageNames(String packageNames) {
		this.packageNames = packageNames;
	}
	public String getVersionName() {
		return versionName;
	}
	public void setVersionName(String versionName) {
		this.versionName = versionName;
	}
	public int getVersionCode() {
		return versionCode;
	}
	public void setVersionCode(int versionCode) {
		this.versionCode = versionCode;
	}
	public ArrayList<String> getList() {
		return list;
	}
	public void setList(ArrayList<String> list) {
		this.list = list;
	}
}
