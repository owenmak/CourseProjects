package edu.purdue.cs180.safewalk;

import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.app.ActionBar;
import android.app.ActionBar.Tab;
import android.app.FragmentTransaction;

/**
 * MainActivity -- the starting point for the Android application. Creates tabs for the Requester and Volunteer
 * Fragments.
 * 
 * @author jtk
 * 
 */
public class MainActivity extends FragmentActivity implements ActionBar.TabListener {
    private ViewPager viewPager;
    private TabsPagerAdapter mAdapter;
    private ActionBar actionBar;
    private String[] tabs = { "Requester", "Volunteer" };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialization...
        viewPager = (ViewPager) findViewById(R.id.pager);
        actionBar = getActionBar();
        mAdapter = new TabsPagerAdapter(getSupportFragmentManager());

        viewPager.setAdapter(mAdapter);
        actionBar.setHomeButtonEnabled(false);
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

        // Adding Tabs
        for (String tab_name : tabs) {
            actionBar.addTab(actionBar.newTab().setText(tab_name).setTabListener(this));
        }

        viewPager.setOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrollStateChanged(int arg0) {
                // nothing to do
            }

            @Override
            public void onPageScrolled(int arg0, float arg1, int arg2) {
                // nothing to do
            }

            @Override
            public void onPageSelected(int position) {
                actionBar.setSelectedNavigationItem(position);
            }
        });
    }

    @Override
    public void onTabReselected(Tab tab, FragmentTransaction ft) {
        // nothing to do
    }

    @Override
    public void onTabSelected(Tab tab, FragmentTransaction ft) {
        viewPager.setCurrentItem(tab.getPosition());
    }

    @Override
    public void onTabUnselected(Tab tab, FragmentTransaction ft) {
        // nothing to do
    }

    /**
     * Creates an AndroidChannel for communication with the server at the given host and port. This method is static so
     * that it can be called at initialization time by each of the Requester and Volunteer Fragments.
     * 
     * @return androidChannel
     */
    public static AndroidChannel initializeChannel() {
        return new AndroidChannel("local host", 8888);
    }

}
