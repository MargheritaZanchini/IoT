package control.unit;

import control.unit.connections.mqtt.MQTTAgent;

import io.vertx.core.Vertx;

public class App {
    public static void main( String[] args ) throws Exception {
        System.out.println();
        System.out.println("Starting Java Control Unit Backend");
        Vertx vertx = Vertx.vertx();
        MQTTAgent mqttAgent = new MQTTAgent(new TemperatureManager());
        vertx.deployVerticle(mqttAgent);
        System.out.println("Java Control Unit Backend started");
    }
}
