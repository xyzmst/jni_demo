/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.example.hellojni;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;


public class HelloJni extends Activity {

    byte[] input = {'0', 1, '1', '1', '0'};

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);
        findViewById(R.id.array_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] input = {0, 1, 2, 3};
                input = arrayTest(input);
                Toast.makeText(HelloJni.this, input[0] + "", Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.relloc_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[] input = {0, 1, 2, 3};
                int temp[] = reallocTest(input);
                Toast.makeText(HelloJni.this, temp[0] + "", Toast.LENGTH_SHORT).show();
            }
        });


    }


    public native String stringFromJNI();

    public native byte[] arrayFromJNI(byte[] input);

    public native int[] arrayTest(int[] input);

    public native int[] reallocTest(int[] input);

    static {
        System.loadLibrary("hello-jni");
    }
}
