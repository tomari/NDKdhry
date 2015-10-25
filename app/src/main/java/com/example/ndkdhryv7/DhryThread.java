package com.example.ndkdhryv7;

import android.os.Handler;

public class DhryThread extends Thread {
	private native String runNdkDhry(long loops, int threads, String cacheDir);
	public native int killPG();
	private native int maxThreads();
	public static native String getDiagInfo();
	static {
		System.loadLibrary("ndk1");
	}
	
	private long loopCount;
	private int threadCount;
	private MainActivity mainAct;
	private Handler handle;
	private String cacheDir;
	public DhryThread(MainActivity act, Handler hand, long nLoops, int threads, String cacheDir) {
		loopCount=nLoops;
		threadCount=Math.min(threads,maxThreads());
		handle=hand;
		mainAct=act;
		this.cacheDir=cacheDir;
	}
	public void run() {
		try {
			// Wait for UI updates
			Thread.sleep(500);
		} catch (InterruptedException e) {
		
		}
		handle.post(new Runnable() {
			@Override
			public void run() {
				mainAct.setBacklightSwitch(true);
			}
		});
    	final String res=runNdkDhry(loopCount,threadCount,cacheDir);
    	handle.post(new Runnable() {
    		public void run() {
    	    	mainAct.DhryThreadFinished(true,res);
    		}
    	});
	}
}
