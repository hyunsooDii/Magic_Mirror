package com.example.smartmirror_android

import android.content.Intent
import android.os.Bundle
import android.os.SystemClock
import androidx.appcompat.app.AppCompatActivity

class SplashActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_splash)
        SystemClock.sleep(300)
        val intent = Intent(this, MainActivity::class.java)
        startActivity(intent)
        finish()

    }
}