package com.example.ndkdhryv7;

import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.content.Context;
import android.view.KeyEvent;
//import android.view.Menu;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	private DhryThread dThread = null;
	private Handler handle;
	private final String SAVELABEL_RUNLOGS="log";
	private final String SAVELABEL_NRUNS="nrun";
	private final String SAVELABEL_SCROLLPOS="scrpos";
	private float savedScreenBrightness=-1.f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        handle=new Handler();
        setContentView(R.layout.activity_main);
		TextView lField=(TextView) findViewById(R.id.logField);
		final ScrollView scrV=(ScrollView) findViewById(R.id.scrollView);
		EditText rField=(EditText) findViewById(R.id.numRun);
		rField.setOnEditorActionListener(new EditText.OnEditorActionListener() {
			@Override
			public boolean onEditorAction(TextView v, int actionId,
					KeyEvent event) {
				RunButtonClicked(v);
				return true;
			}
		});
		if(savedInstanceState!=null) {
			lField.setText(savedInstanceState.getCharSequence(SAVELABEL_RUNLOGS));
			rField.setText(savedInstanceState.getCharSequence(SAVELABEL_NRUNS));
			final int scrollY= savedInstanceState.getInt(SAVELABEL_SCROLLPOS,0);
			scrV.post(new Runnable() {
				@Override
				public void run() {
					scrV.scrollTo(0,scrollY);
				}
			});
		}
    }

	@Override
	public void onSaveInstanceState(Bundle savedInstanceState) {
		TextView lField=(TextView) findViewById(R.id.logField);
		ScrollView scrV=(ScrollView) findViewById(R.id.scrollView);
		EditText rField=(EditText) findViewById(R.id.numRun);
		savedInstanceState.putCharSequence(SAVELABEL_RUNLOGS, lField.getText());
		savedInstanceState.putCharSequence(SAVELABEL_NRUNS, rField.getText());
		savedInstanceState.putInt(SAVELABEL_SCROLLPOS, scrV.getScrollY());
	}
	public void setBacklightSwitch(boolean sw) {
		Window w=getWindow();
		WindowManager.LayoutParams layoutP=w.getAttributes();
		if(sw) {
			layoutP.screenBrightness=savedScreenBrightness;
		} else {
			savedScreenBrightness=layoutP.screenBrightness;
			layoutP.screenBrightness=0.f;
		}
		w.setAttributes(layoutP);
	}
    public synchronized void RunButtonClicked(View v) {
		hideKeyboard();
    	setRunButtonState(dThread==null);
		CheckBox backlightBox=(CheckBox) findViewById(R.id.backlightCheckbox);
		if(backlightBox.isChecked()) {
			setBacklightSwitch(false);
		}
    	if(dThread==null) {
    		int nLoops=getNumFromField(R.id.numRun);
    		int nThreads=getNumFromField(R.id.numThreads);
    		if(nLoops<1 || nThreads<1) {
    			Toast.makeText(getApplicationContext(), R.string.invalid_input, Toast.LENGTH_SHORT).show();
    	    	setRunButtonState(false);
    	    	return;
    		}
    		dThread=new DhryThread(this,handle,nLoops,nThreads);
    		dThread.start();
    	} else {
    		// we cannot interrupt JNI native function.
			android.os.Process.killProcess(android.os.Process.myPid());
    	}
    }
    public synchronized void DhryThreadFinished(boolean success, String resultText) {
		final TextView lField=(TextView) findViewById(R.id.logField);
		final ScrollView scrV=(ScrollView) findViewById(R.id.scrollView);
    	if(success) {
    		lField.append(resultText);
    		scrV.post(new Runnable() {
    			public void run() {
					scrV.smoothScrollTo(0, lField.getHeight());
    			}
    		});
    	}
    	dThread=null;
    	setRunButtonState(false);
    }
    private int getNumFromField(int fldId) {
		EditText rField=(EditText) findViewById(fldId);
    	int nLoops;
    	try { 
    		nLoops=Integer.valueOf(rField.getText().toString()).intValue();
    	} catch (NumberFormatException e) {
    		nLoops=-1;
    	}
    	return nLoops;
    }
    private void setRunButtonState(boolean isAbort) {
    	Button rButton=(Button) findViewById(R.id.button1);
    	EditText rField=(EditText) findViewById(R.id.numRun);
    	EditText tField=(EditText) findViewById(R.id.numThreads);
    	int newText=isAbort?R.string.abort_dhry:R.string.run_dhrystone;
    	rButton.setText(newText);
    	// JNI was not interruptible. Sorry.
    	//rButton.setEnabled(!isAbort);
    	rField.setEnabled(!isAbort);
    	tField.setEnabled(!isAbort);
    }
	private void hideKeyboard() {
		InputMethodManager imm=(InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		if(imm!=null) {
			imm.hideSoftInputFromWindow(getCurrentFocus().getWindowToken(),InputMethodManager.HIDE_NOT_ALWAYS);
		}
	}
}
