package control.unit;

import control.unit.TemperatureManager.TemperatureState;
import control.unit.connections.mqtt.MQTTAgent;
import control.unit.connections.serial.SerialChannel;

import io.vertx.core.Vertx;

public class ControlManager extends Thread {
    private TemperatureState state;
    private boolean firstRun = true;
    private long hotStartTime;

    private Vertx vertx;
    
    private MQTTAgent mqttAgent;
    private SerialChannel serialChannel;

    private TemperatureManager temperatureManager = new TemperatureManager();

    private final static int SERIAL_BAUD_RATE = 115200;
    private final static String SERIAL_PORT = "COM8";

    private final static int F1 = 3000;
    private final static int F2 = 1000;

    private final static float T1 = 24;
    private final static float T2 = 26;

    private final static long DT = 5000;

    public ControlManager() throws Exception {
        vertx = Vertx.vertx();
        
        mqttAgent = new MQTTAgent(temperatureManager);

        vertx.deployVerticle(mqttAgent);

        vertx.setPeriodic(1000, id -> this.run());

        serialChannel = new SerialChannel(SERIAL_PORT, SERIAL_BAUD_RATE);

        state = TemperatureState.NORMAL;
        
        hotStartTime = 0;
    }

    public void run() {
        System.out.println("ControlManager running...");

        if(mqttAgent.getClient() == null) {
            System.out.println("MQTT Client Null");
            return;
        }
        if(serialChannel == null) {
            System.out.println("Serial Channel Null");
            return;
        }

        switch(state) {
            case NORMAL: {
                if(temperatureManager.getCurrentTemperature() > T1) {
                    state = TemperatureState.HOT;
                    System.out.println("Case HOT");
                    mqttAgent.sendFrequency(F2);
                    break;
                }
                if(firstRun) {
                    firstRun = false;
                    mqttAgent.sendFrequency(F1);
                }
                System.out.println("Case NORMAL");
                break;
            }
            case HOT: {
                if(temperatureManager.getCurrentTemperature() <= T1) {
                    state = TemperatureState.NORMAL;
                    System.out.println("Case NORMAL");
                    mqttAgent.sendFrequency(F1);
                    break;
                }
                if(temperatureManager.getCurrentTemperature() > T2) {
                    state = TemperatureState.TOO_HOT;
                    System.out.println("Case TOO HOT");
                    hotStartTime = 0;
                    break;
                }
                System.out.println("Case HOT");
                break;
            }
            case TOO_HOT: {
                if(temperatureManager.getCurrentTemperature() <= T2) {
                    state = TemperatureState.HOT;
                    System.out.println("Case HOT");
                    break;
                }

                if(hotStartTime == 0) {
                    hotStartTime = System.currentTimeMillis();
                }
                else if((System.currentTimeMillis() - hotStartTime) >= DT) {
                    state = TemperatureState.ALARM;
                    System.out.println("Case ALARM");
                    break;
                }
                System.out.println("Case TOO HOT");
                break;
            }
            case ALARM: { // TO-DO Modify
                if(temperatureManager.getCurrentTemperature() <= T2) {
                    state = TemperatureState.TOO_HOT;
                    System.out.println("Case TOO HOT");
                    hotStartTime = 0;
                    break;
                }
                System.out.println("Case ALARM");
                break;
            }
        }
    }
}