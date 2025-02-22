package control.unit.connections.mqtt;

import control.unit.ValueManager;
import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.AsyncResult;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

import io.vertx.mqtt.messages.MqttPublishMessage;
import io.vertx.mqtt.messages.MqttConnAckMessage;

/**
 * MQTTAgent class is responsible for handling the connection to the MQTT broker.
 * Sends and receives messages from the broker.
 */
public class MQTTAgent extends AbstractVerticle {
    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com"; // Broker address
    private static final int BROKER_PORT = 1883; // Broker port

    private static final String MQTT_TOPIC = "a03monitoring"; // Topic to subscribe to
    private static final MqttQoS QUALITY_OF_SERVICE = MqttQoS.EXACTLY_ONCE; // Quality of service

    private static final int RECONNECT_INTERVAL = 3000; // Reconnect interval in milliseconds

    private MqttClient client;

    private final ValueManager valueManager;

    /**
     * Constructor for MQTTAgent
     * 
     * @param valueManager
     */
    public MQTTAgent(ValueManager valueManager) {
        this.valueManager = valueManager;
    }

    @Override
    public void start() {
        this.client = MqttClient.create(vertx);
        this.client.connect(BROKER_PORT, BROKER_ADDRESS, ch -> this.connectionHandler(ch));
        System.out.println("MQTT Agent STARTED");
    }

    /**
     * Connection handler for MQTT client
     * 
     * @param ch connection acknowledgement message
     */
    public void connectionHandler(AsyncResult<MqttConnAckMessage> ch) {
        if(!ch.succeeded()) { // If connection failed
            System.out.println("Failed to connect to MQTT broker. Retrying...");
            vertx.setTimer(RECONNECT_INTERVAL, h -> start()); // Retry connection
        }

        // Else (connection successful) subscribe to topic
        this.client.publishHandler(ph -> this.receiveTemperature(ph)).subscribe(MQTT_TOPIC, QUALITY_OF_SERVICE.value());
    }

    /**
     * Receive temperature from MQTT broker
     * 
     * @param h MQTT publish message
     */
    public void receiveTemperature(MqttPublishMessage h) {
        String message = h.payload().toString();
        if(message.startsWith("frequency:")) {
            return; // Ignore frequency messages
        }

        double t = 0;

        // Parse temperature value, if not a number print error and current message
        try {
            t = Double.parseDouble(message.replace("temperature:", ""));
        }
        catch(NumberFormatException e) {
            System.out.println("Can't parse: " + message);
        }

        this.valueManager.addTemperature(t); // Add temperature to value manager
    }

    /**
     * Send frequency to MQTT broker
     * 
     * @param frequency frequency value
     */
    public void sendFrequency(int frequency) {
        if(!this.client.isConnected()) {
            System.out.println("MQTT client is not connected. Can't send frequency.");
            return;
        }
        this.client.publish(MQTT_TOPIC, Buffer.buffer("frequency:" + String.valueOf(frequency)), QUALITY_OF_SERVICE, false, true);
    }

    /**
     * Get MQTT client
     * 
     * @return MQTT client
     * @see MqttClient
     */
    public MqttClient getClient() {
        return this.client;
    }
}