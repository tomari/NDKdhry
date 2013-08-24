package com.example.ndkdhryv7;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
//import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
//import android.widget.Toast;

public class MainActivity extends Activity {
	private DhryThread dThread = null;
	private Handler handle;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        handle=new Handler();
        setContentView(R.layout.activity_main);
    }

    /*
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    */
    public synchronized void RunButtonClicked(View v) {
    	setRunButtonState(dThread==null);
    	if(dThread==null) {
    		int nLoops=getNumLoops();
    		dThread=new DhryThread(this,handle,nLoops);
    		dThread.start();
    	} else {
    		// No, we cannot interrupt JNI native function. Sorry.
    		dThread.interrupt();
    		dThread=null;
    	}
    }
    public synchronized void DhryThreadFinished(boolean success, String resultText) {
    	if(success) {
    		EditText lField=(EditText) findViewById(R.id.logField);
    		lField.append(resultText);
    	}
    	dThread=null;
    	setRunButtonState(false);
    }
    private int getNumLoops() {
    	EditText rField=(EditText) findViewById(R.id.numRun);
    	int nLoops;
    	try { 
    		nLoops=Integer.valueOf(rField.getText().toString()).intValue();
    	} catch (NumberFormatException e) {
    		nLoops=0;
    	}
    	if(nLoops<1) {
    		nLoops=2000;
    	}
    	return nLoops;
    }
    private void setRunButtonState(boolean isAbort) {
    	Button rButton=(Button) findViewById(R.id.button1);
    	int newText=isAbort?R.string.abort_dhry:R.string.run_dhrystone;
    	rButton.setText(newText);
    	// JNI was not interruptible. Sorry.
    	rButton.setEnabled(!isAbort);
    }
}
