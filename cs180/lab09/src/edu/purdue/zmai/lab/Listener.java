// package edu.purdue.zmai.lab;

import android.view.View.*;
import android.view.View;
import java.util.*;
import android.os.*;
import android.widget.*;

public class Listener implements OnClickListener {
  @Override
  public void onClick(View arg) {
    Button b = (Button) arg;
    String c = b.getText().toString();
    if (c.equals("Reset") || c.equals("Time") || c.equals("Serial"))
      StartActivity.logIt(c);
  }
}