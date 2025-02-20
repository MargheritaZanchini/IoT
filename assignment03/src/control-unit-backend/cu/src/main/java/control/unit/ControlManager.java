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

    private boolean sendModeExecuted = false;

    private void sendModeOnce() {
        if(sendModeExecuted) {
            return;
        }
        serialChannel.sendMode();
        sendModeExecuted = true;
    }

    public void doSerialTask() {
        if(serialChannel.receiveMode()) {
            sendModeExecuted = false; // send to HTTP
        }
        else {
            sendModeOnce(); // Else, send it to Serial
        }

        if(serialChannel.getMode() == Mode.MANUAL) {
            serialChannel.sendTemperature();
        }
        else if(serialChannel.getMode() == Mode.AUTOMATIC) {
            serialChannel.sendAperture();
        }
    }

    private void stateLoop() {
        double currentTemperature = valueManager.getCurrentTemperature();

        switch(state) {
            case NORMAL: {
                if(currentTemperature > ValueManager.T1) {
                    state = TemperatureState.HOT;
                    mqttAgent.sendFrequency(ValueManager.F2);
                    break;
                }
                if(firstRun) {
                    firstRun = false;
                    mqttAgent.sendFrequency(ValueManager.F1);
                }
                break;
            }
            case HOT: {
                if(currentTemperature <= ValueManager.T1) {
                    state = TemperatureState.NORMAL;
                    mqttAgent.sendFrequency(ValueManager.F1);
                    break;
                }
                if(currentTemperature > ValueManager.T2) {
                    state = TemperatureState.TOO_HOT;
                    hotStartTime = 0;
                    break;
                }
                break;
            }
            case TOO_HOT: {
                if(currentTemperature <= ValueManager.T2) {
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
                if(currentTemperature <= ValueManager.T2) {
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

    public void run() {
        if(mqttAgent.getClient() == null) {
            System.out.println("MQTT Client Null");
            return;
        }
        if(serialChannel == null) {
            System.out.println("Serial Channel Null");
            return;
        }

        stateLoop();
        // doSerialTask();
    }
}