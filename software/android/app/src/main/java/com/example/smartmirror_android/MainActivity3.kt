package com.example.smartmirror_android

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main3.*

class MainActivity3 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main3)

        fan_on.setOnClickListener {
            fan_on.apply{
                var intent = Intent(Intent.ACTION_VIEW, Uri.parse("http://blynk-cloud.com/68O8QXywAHetPvqMhh0iH56GYVDbX2IQ/update/V0?value=on"))
                startActivity(intent)

                intent.flags = Intent.FLAG_ACTIVITY_CLEAR_TOP
            }
        }

        fan_off.setOnClickListener {
            fan_on.apply{
                var intent = Intent(Intent.ACTION_VIEW, Uri.parse("http://blynk-cloud.com/68O8QXywAHetPvqMhh0iH56GYVDbX2IQ/update/V0?value=off"))
                intent.flags = Intent.FLAG_ACTIVITY_CLEAR_TOP
                startActivity(intent)
                finish()

            }
        }
    }
}
