package control.unit;

import control.unit.ValueManager.Mode;
import control.unit.ValueManager.TemperatureState;
import control.unit.connections.mqtt.MQTTAgent;
import control.unit.connections.serial.SerialAgent;
import control.unit.connections.http.HTTPAgent;

import io.vertx.core.Vertx;

/**
 * ControlManager class
 * 
 * This class is responsible for managing the control unit
 * It is responsible for running the main loops for the serial communication and the system current state
 * It initializes all the communication agents
 * 
 * @see SerialAgent
 * @see MQTTAgent
 * @see HTTPAgent
 */
public class ControlManager extends Thread {
    private boolean firstRun = true;
    private long hotStartTime = 0;

    private Vertx vertx;
    
    private MQTTAgent mqttAgent;
    private SerialAgent serialChannel;
    private HTTPAgent httpAgent;

    private final ValueManager valueManager;

    private final static int SERIAL_BAUD_RATE = 115200;
    private final static String SERIAL_PORT = "COM9";
    private final static int HTTP_PORT = 8080;

    private final static int LOOP_PERIOD = 1000;

    /**
     * Constructor for the ControlManager
     * Initializes the Vertx instance and the ValueManager instance
     * and initializes the SerialAgent, MQTTAgent, and HTTPAgent instances
     * 
     * @throws Exception
     */
    public ControlManager() throws Exception {
        vertx = Vertx.vertx();

        valueManager = new ValueManager();

        serialChannel = new SerialAgent(SERIAL_PORT, SERIAL_BAUD_RATE, valueManager);

        mqttAgent = new MQTTAgent(valueManager);
        vertx.deployVerticle(mqttAgent);

        httpAgent = new HTTPAgent(HTTP_PORT, valueManager);
        vertx.deployVerticle(httpAgent);

        vertx.setPeriodic(LOOP_PERIOD, id -> this.run());
    }

    /**
     * Main loop for the serial communication
     * This loop is responsible for receiving data from the serial port and sending data to the serial port
     */
    public void serialLoop() {
        try {
            if(this.serialChannel.receiveData()) { // Check if there is data to be received
                this.serialChannel.receiveMessage(); // Receive the message
            }
            else { // If there is no data to be received, send current mode
                this.serialChannel.sendMode();
            }

            if(this.serialChannel.getMode() == Mode.MANUAL) { // If the mode is manual, send the temperature
                this.serialChannel.sendTemperature();
            }
            else if(this.serialChannel.getMode() == Mode.AUTOMATIC) { // else if the mode is automatic, send the aperture
                this.serialChannel.sendAperture();
            }
        }
        catch(Exception e) { // Catch any exceptions that occur
            System.out.println("Exception in Serial Loop: " + e.getMessage());
            System.out.println("Stack Trace: ");
            e.printStackTrace();
        }
    }

    /**
     * Main loop for the system state
     * This loop is responsible for changing the state of the system based on the current temperature
     */
    private void stateLoop() {
        double currentTemperature = valueManager.getCurrentTemperature(); // Get the current temperature
        TemperatureState currentState = valueManager.getState(); // Get the current state
 
        switch(currentState) { 
            case NORMAL: { // In normal...
                if(currentTemperature > ValueManager.T1) { // If the temperature is greater than T1, change to hot
                    valueManager.setState(TemperatureState.HOT);
                    mqttAgent.sendFrequency(ValueManager.F2); // Send the frequency F2
                    break;
                }
                if(firstRun) { // If it is the first run, send the frequency F1
                    firstRun = false;
                    mqttAgent.sendFrequency(ValueManager.F1);
                }
                break;
            }
            case HOT: { // In hot...
                if(currentTemperature <= ValueManager.T1) { // If the temperature is less than T1, change to normal
                    valueManager.setState(TemperatureState.NORMAL);
                    mqttAgent.sendFrequency(ValueManager.F1); // Send the frequency F1
                }
                else if(currentTemperature > ValueManager.T2) { // If the temperature is greater than T2, change to too hot
                    valueManager.setState(TemperatureState.TOO_HOT);
                    hotStartTime = 0; // Reset the TOO_HOT timer
                }

                break;
            }
            case TOO_HOT: { // In too hot...
                if(currentTemperature <= ValueManager.T2) { // If the temperature is less than T2, change to hot
                    valueManager.setState(TemperatureState.HOT);
                    break;
                }

                if(hotStartTime == 0) { // If the TOO_HOT timer is not set, set it
                    hotStartTime = System.currentTimeMillis();
                }
                else if((System.currentTimeMillis() - hotStartTime) >= ValueManager.DT) { // If the TOO_HOT timer is greater than DT, change to alarm
                    valueManager.setState(TemperatureState.ALARM);
                    break;
                }
                break;
            }
            case ALARM: {
                // Do nothing
                // This piece of code is not necessary, as the system will remain in the ALARM state until the user resolves it
                // It's kept here for more clarity for the reader
                break;
            }
        }
    }

    /**
     * Main run method
     * This method is responsible for running the main loops
     * 
     * @throws RuntimeException
     */
    public void run() throws RuntimeException {
        if(mqttAgent.getClient() == null) { // Check if the MQTT client is null
            System.out.println("MQTT Client Null");
            return;
        }
        if(serialChannel == null) { // Check if the serial channel is null
            System.out.println("Serial Channel Null");
            return;
        }

        stateLoop(); // Run the state loop
        serialLoop(); // Run the serial loop
    }
}