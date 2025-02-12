package control.unit;

import control.unit.connections.mqtt.MQTTAgent;

import io.vertx.core.Vertx;

public class ControlManager extends Thread {
    private Vertx vertx;
    
    private MQTTAgent mqttAgent;

    private TemperatureManager temperatureManager = new TemperatureManager();

    // private final static int F1 = 3000;
    // private final static int F2 = 1000;

    public ControlManager() throws Exception {
        vertx = Vertx.vertx();
        
        mqttAgent = new MQTTAgent(temperatureManager);

        vertx.deployVerticle(mqttAgent);

        vertx.setPeriodic(1000, id -> this.run());
    }

    public void run() {
        System.out.println("ControlManager running...");

        if(mqttAgent.getClient() == null) {
            System.out.println("MQTT Client Null");
            return;
        }

        switch(temperatureManager.getTemperatureState()) {
            case NORMAL: {
                System.out.println("Case NORMAL");
                break;
            }
            case HOT: {
                System.out.println("Case HOT");
                break;
            }
            case TOO_HOT: {
                System.out.println("Case TOO HOT");
                break;
            }
            case ALARM: default: {
                System.out.println("Case ALARM");
                break;
            }
        }
    }
}