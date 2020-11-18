package com.example.smartmirror_android

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ImageButton

class MainActivity : AppCompatActivity() {

    private lateinit var imageButton: ImageButton

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        imageButton = findViewById(R.id.imageBtn2) as ImageButton
        imageButton = findViewById(R.id.imageBtn1) as ImageButton


    }

    fun onClickButton(view: View) {
        var intent = Intent(this, MainActivity2::class.java)
        startActivity(intent)

    }

    fun onClickButton2(view: View) {
        var intent = Intent(this, MainActivity3::class.java)
        startActivity(intent)

    }
}