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

    private static final String TOPIC_STRING = "temperature";
    private static final MqttQoS QUALITY_OF_SERVICE = MqttQoS.EXACTLY_ONCE;

    private static final int RECONNECT_INTERVAL = 3000;

    private final MqttClient client;
    private final TemperatureManager temperatureManager;

    public MQTTAgent(TemperatureManager temperatureManager) {
        this.client = MqttClient.create(vertx);
        this.temperatureManager = temperatureManager;
    }

    @Override
    public void start() {
        client.connect(BROKER_PORT, BROKER_ADDRESS, ch -> this.connectionHandler(ch));
    }

    public void connectionHandler(AsyncResult<MqttConnAckMessage> ch) {
        if(!ch.succeeded()) {
            vertx.setTimer(RECONNECT_INTERVAL, h -> start());
            return;
        }

        this.client.publishHandler(ph -> this.receiveTemperature(ph)).subscribe(TOPIC_STRING, QUALITY_OF_SERVICE.value());
    }

    public void receiveTemperature(MqttPublishMessage h) {
        double t = 0;

        try {
            t = Double.parseDouble(h.payload().toString());
        } catch(NumberFormatException e) { }

        this.temperatureManager.addTemperature(t);
    }

    public void sendFrequency(int frequency) {
        if(!this.client.isConnected()) {
            return;
        }

        this.client.publish(TOPIC_STRING, Buffer.buffer(String.valueOf(frequency)), QUALITY_OF_SERVICE, false, false);
   }
}