package edu.purdue.cs180.safewalk;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

/**
 * TabsPagerAdapter to respond to Fragment request changes by the MainActivity.
 * 
 * @author jtk
 * 
 */
public class TabsPagerAdapter extends FragmentPagerAdapter {

    public TabsPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int index) {
        switch (index) {
        case 0:
            return new RequesterFragment();
        case 1:
            return new VolunteerFragment();
        }

        return null;
    }

    @Override
    public int getCount() {
        return 2; // must agree with switch statement above
    }
}
