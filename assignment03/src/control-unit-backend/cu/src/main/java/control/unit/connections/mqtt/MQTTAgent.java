package control.unit.connections.mqtt;

import control.unit.TemperatureManager;
import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.AsyncResult;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

import io.vertx.mqtt.messages.MqttPublishMessage;
import io.vertx.mqtt.messages.MqttConnAckMessage;

public class MQTTAgent extends AbstractVerticle {
    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private static final int BROKER_PORT = 1883;

    private static final String MQTT_TOPIC = "a03monitoring";
    private static final MqttQoS QUALITY_OF_SERVICE = MqttQoS.EXACTLY_ONCE;

    private static final int RECONNECT_INTERVAL = 3000;

    private MqttClient client;

    private final TemperatureManager temperatureManager;

    public MQTTAgent(TemperatureManager temperatureManager) {
        this.temperatureManager = temperatureManager;
    }

    @Override
    public void start() {
        this.client = MqttClient.create(vertx);
        this.client.connect(BROKER_PORT, BROKER_ADDRESS, ch -> this.connectionHandler(ch));
        System.out.println("MQTT Agent STARTED");
    }

    public void connectionHandler(AsyncResult<MqttConnAckMessage> ch) {
        if(!ch.succeeded()) {
            System.out.println("Failed to connect to MQTT broker. Retrying...");
            vertx.setTimer(RECONNECT_INTERVAL, h -> start());
        }

        this.client.publishHandler(ph -> this.receiveTemperature(ph)).subscribe(MQTT_TOPIC, QUALITY_OF_SERVICE.value());
    }

    public void receiveTemperature(MqttPublishMessage h) {
        String message = h.payload().toString();
        if (message.startsWith("frequency:")) {
            return;
        }

        double t = 0;

        try {
            t = Double.parseDouble(message.replace("temperature:", ""));
            System.out.println("Received temperature: " + t);
        } catch (NumberFormatException e) {
            System.out.println("Can't parse: " + message);
        }

        this.temperatureManager.addTemperature(t);
        }

        public void sendFrequency(int frequency) {
        if(!this.client.isConnected()) {
            System.out.println("MQTT client is not connected. Can't send frequency.");
            return;
        }
        this.client.publish(MQTT_TOPIC, Buffer.buffer("frequency:" + String.valueOf(frequency)), QUALITY_OF_SERVICE, false, true);
    }

    public MqttClient getClient() {
        return this.client;
    }
}