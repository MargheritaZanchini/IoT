package control.unit;

import control.unit.ValueManager.Mode;
import control.unit.ValueManager.TemperatureState;
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

    private final ValueManager valueManager;

    private final static int SERIAL_BAUD_RATE = 115200;
    private final static String SERIAL_PORT = "COM9";

    public ControlManager() throws Exception {
        vertx = Vertx.vertx();

        valueManager = new ValueManager();

        serialChannel = new SerialChannel(SERIAL_PORT, SERIAL_BAUD_RATE, valueManager);

        mqttAgent = new MQTTAgent(valueManager);
        vertx.deployVerticle(mqttAgent);
        vertx.setPeriodic(1000, id -> this.run());

        state = TemperatureState.NORMAL;
        
        hotStartTime = 0;
    }

    public void doSerialTask() {
        // if(!serialChannel.isOpened()) {
        //     return;
        // }

        // if(serialChannel.isMessageAvailable()) {
        //     try {
        //         String msg = serialChannel.receiveMessage();
        //         System.out.println("Received: " + msg);
        //     } catch (InterruptedException e) {
        //         e.printStackTrace();
        //     }
        // }

        serialChannel.receiveMode();

        System.out.println("Mode: " + serialChannel.getMode());

        serialChannel.sendMode();

        serialChannel.sendAperture();
        if(serialChannel.getMode() == Mode.MANUAL) {
            serialChannel.sendTemperature();
        }
    }

    public void run() {
        // System.out.println("ControlManager running...");

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
                if(valueManager.getCurrentTemperature() > ValueManager.T1) {
                    state = TemperatureState.HOT;
                    // System.out.println("Case HOT");
                    mqttAgent.sendFrequency(ValueManager.F2);
                    break;
                }
                if(firstRun) {
                    firstRun = false;
                    mqttAgent.sendFrequency(ValueManager.F1);
                }
                // System.out.println("Case NORMAL");
                break;
            }
            case HOT: {
                if(valueManager.getCurrentTemperature() <= ValueManager.T1) {
                    state = TemperatureState.NORMAL;
                    // System.out.println("Case NORMAL");
                    mqttAgent.sendFrequency(ValueManager.F1);
                    break;
                }
                if(valueManager.getCurrentTemperature() > ValueManager.T2) {
                    state = TemperatureState.TOO_HOT;
                    // System.out.println("Case TOO HOT");
                    hotStartTime = 0;
                    break;
                }
                // System.out.println("Case HOT");
                break;
            }
            case TOO_HOT: {
                if(valueManager.getCurrentTemperature() <= ValueManager.T2) {
                    state = TemperatureState.HOT;
                    System.out.println("Case HOT");
                    break;
                }

                if(hotStartTime == 0) {
                    hotStartTime = System.currentTimeMillis();
                }
                else if((System.currentTimeMillis() - hotStartTime) >= ValueManager.DT) {
                    state = TemperatureState.ALARM;
                    System.out.println("Case ALARM");
                    break;
                }
                System.out.println("Case TOO HOT");
                break;
            }
            case ALARM: { // TODO Modify
                if(valueManager.getCurrentTemperature() <= ValueManager.T2) {
                    state = TemperatureState.TOO_HOT;
                    System.out.println("Case TOO HOT");
                    hotStartTime = 0;
                    break;
                }
                System.out.println("Case ALARM");
                break;
            }
        }

        doSerialTask();
    }
}