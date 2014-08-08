package com.example.ndkdhryv7;

import android.os.Handler;

public class DhryThread extends Thread {
	private native String runNdkDhry(int loops, int threads);
	static {
		System.loadLibrary("ndk1");
	}
	
	private int loopCount;
	private int threadCount;
	private MainActivity mainAct;
	private Handler handle;
	public DhryThread(MainActivity act, Handler hand, int nLoops, int threads) {
		loopCount=nLoops;
		threadCount=threads;
		handle=hand;
		mainAct=act;
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
    	final String res=runNdkDhry(loopCount,threadCount);
    	handle.post(new Runnable() {
    		public void run() {
    	    	mainAct.DhryThreadFinished(true,res);
    		}
    	});
	}
}
