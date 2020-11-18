package com.example.smartmirror_android

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import android.util.Log
import kotlinx.android.synthetic.main.activity_main2.*
import org.eclipse.paho.client.mqttv3.MqttMessage

const val SUB_TOPIC = "iot/temperature"
const val PUB_TOPIC = "iot/home/led"
const val SERVER_URI = "tcp://192.168.137.185:1883"

class MainActivity2 : AppCompatActivity() {

    val TAG = "MqttActivity"
    lateinit var mqttClient: Mqtt

    fun onReceived(topic: String, message: MqttMessage) {
        // 토픽 수신 처리
        val msg = String(message.payload)
        Log.d("test", msg)
//        if(msg == "1"){
//            setContentView(R.layout.turn_on)
//        }
    }

    fun publish() {
        mqttClient.publish(PUB_TOPIC, "1")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main2)

        mqttClient = Mqtt(this, SERVER_URI)

        try {
            // mqttClient.setCallback { topic, message ->}
            mqttClient.setCallback(::onReceived)
            mqttClient.connect(arrayOf<String>(SUB_TOPIC))
        } catch (e: Exception) {
            e.printStackTrace()
        }

        led_on.setOnClickListener {
            led_on.apply{
                mqttClient.publish(PUB_TOPIC, "1")
            }
        }
        led_off.setOnClickListener {
            led_off.apply{
                mqttClient.publish(PUB_TOPIC, "0")
            }
        }
    }

}
