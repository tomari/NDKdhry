package com.example.ndkdhryv7;

import android.os.Handler;

public class DhryThread extends Thread {
	private native String runNdkDhry(int loops);
	static {
		System.loadLibrary("ndk1");
	}
	
	private int loopCount;
	private MainActivity mainAct;
	private Handler handle;
	public DhryThread(MainActivity act, Handler hand, int nLoops) {
		loopCount=nLoops;
		handle=hand;
		mainAct=act;
	}
	public void run() {
    	final String res=runNdkDhry(loopCount);
    	handle.post(new Runnable() {
    		public void run() {
    	    	mainAct.DhryThreadFinished(true,res);
    		}
    	});
	}
}
