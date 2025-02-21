package control.unit;

import control.unit.ValueManager.Mode;
import control.unit.ValueManager.TemperatureState;
import control.unit.connections.mqtt.MQTTAgent;
import control.unit.connections.serial.SerialAgent;
import control.unit.connections.http.HTTPServer;

import io.vertx.core.Vertx;

public class ControlManager extends Thread {
    private boolean firstRun = true;
    private long hotStartTime = 0;

    private Vertx vertx;
    
    private MQTTAgent mqttAgent;
    private SerialAgent serialChannel;
    private HTTPServer dataService;

    private final ValueManager valueManager;

    private final static int SERIAL_BAUD_RATE = 115200;
    private final static String SERIAL_PORT = "COM9";
    private final static int HTTP_PORT = 8080;
    private final static String HTTP_SERVER= "localhost";

    private final static int LOOP_PERIOD = 1000;

    public ControlManager() throws Exception {
        vertx = Vertx.vertx();

        valueManager = new ValueManager();

        serialChannel = new SerialAgent(SERIAL_PORT, SERIAL_BAUD_RATE, valueManager);

        mqttAgent = new MQTTAgent(valueManager);
        vertx.deployVerticle(mqttAgent);

        dataService = new HTTPServer(HTTP_PORT, HTTP_SERVER, valueManager);
        vertx.deployVerticle(dataService);
        
        vertx.setPeriodic(LOOP_PERIOD, id -> this.run());
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
        if(serialChannel.receiveData()) {
            System.out.println("Data received from Serial");
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
        TemperatureState currentState = valueManager.getState();
 
        switch(currentState) {
            case NORMAL: {
                if(currentTemperature > ValueManager.T1) {
                    valueManager.setState(TemperatureState.HOT);
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
                    valueManager.setState(TemperatureState.NORMAL);
                    mqttAgent.sendFrequency(ValueManager.F1);
                    break;
                }
                if(currentTemperature > ValueManager.T2) {
                    valueManager.setState(TemperatureState.TOO_HOT);
                    hotStartTime = 0;
                    break;
                }
                break;
            }
            case TOO_HOT: {
                if(currentTemperature <= ValueManager.T2) {
                    valueManager.setState(TemperatureState.HOT);
                    break;
                }

                if(hotStartTime == 0) {
                    hotStartTime = System.currentTimeMillis();
                }
                else if((System.currentTimeMillis() - hotStartTime) >= ValueManager.DT) {
                    valueManager.setState(TemperatureState.ALARM);
                    break;
                }
                break;
            }
            case ALARM: {
                break;
            }
        }
    }

    public void run() throws RuntimeException {
        if(mqttAgent.getClient() == null) {
            System.out.println("MQTT Client Null");
            return;
        }
        if(serialChannel == null) {
            System.out.println("Serial Channel Null");
            return;
        }

        stateLoop();
        doSerialTask();
        
        // dataService.sendData(dataService.prepareData());
    }
}