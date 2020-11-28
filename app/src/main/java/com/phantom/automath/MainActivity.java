package com.phantom.automath;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	WebView webview;
	EditText number;
	Switch power_switch;
	Button button;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		// Example of a call to a native method
		TextView tv = findViewById(R.id.sample_text);
		tv.setText(stringFromJNI());

		webview = (WebView) findViewById(R.id.webView2);
		number = (EditText) findViewById(R.id.input_nums);
		power_switch = (Switch) findViewById(R.id.pow_switch);
		button = (Button) findViewById(R.id.calc_btn);
	}

	public void btn_onClick(View v){
		try {
			int int_num = Integer.parseInt(number.getText().toString());
			number.setEnabled(false);
			button.setEnabled(false);
			webview.loadData("<html><head></head><body><h2> For big numbers calculation takes time. Calulating....</h2></body></html>",
					"text/html", "utf-8");
			String result = Factorize(int_num, power_switch.isChecked() ? 1:0);
			webview.loadData("<html><head></head><body><h2>"
					+int_num+" = "+ result + "</h2></body></html>",
					"text/html", "utf-8");
			number.setEnabled(true);
			button.setEnabled(true);
		}
		catch (Exception e) {
			webview.loadData("Invalid data", "text/html", "utf-8");
		}

	}
	/**
	 * A native method that is implemented by the 'native-lib' native library,
	 * which is packaged with this application.
	 */
	public native String Factorize(int integer, int in_power);
	public native String stringFromJNI();
}
