package assignment02;

import javafx.application.Platform;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.FloatProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleFloatProperty;

/**
 * Thread (Daemon) that Handles the Data Received from the Serial Port
 * 
 * @see Thread Thread (Extended Class)
 */
public class SerialDataHandler extends Thread {
    private final static String WASTE_LEVEL_TAG = "[Value:WasteLevel]"; /** Serial Message Header for Waste Level */
    private final static String TEMPERATURE_TAG = "[Value:Temperature]"; /** Serial Message Header for Temperature */
    private final static String WASTE_LEVEL_ALARM_TAG = "[Alarm:WasteLevel]"; /** Serial Message Header for Waste Level Alarm */
    private final static String TEMPERATURE_ALARM_TAG = "[Alarm:Temperature]"; /** Serial Message Header for Temperature Alarm */

    private final CommunicationChannel channel; /** Communication Channel */

    private FloatProperty wasteLevel = new SimpleFloatProperty(0); /** Waste Level Property */
    private FloatProperty temperature = new SimpleFloatProperty(0); /** Temperature Property */
    private BooleanProperty wasteLevelAlarm = new SimpleBooleanProperty(false); /** Waste Level Alarm Property */
    private BooleanProperty temperatureAlarm = new SimpleBooleanProperty(false); /** Temperature Alarm Property */
    
    /**
     * Constructor for SerialDataHandler
     * 
     * @param port Serial Port Name
     * @param rate Baud Rate
     * @param wasteLevel Waste Level Property
     * @param temperature Temperature Property
     * @param wasteLevelAlarm Waste Level Alarm Property
     * @param temperatureAlarm Temperature Alarm Property
     * 
     * @throws Exception
     */
    public SerialDataHandler(final String port, final int rate, final FloatProperty wasteLevel, final FloatProperty temperature, final BooleanProperty wasteLevelAlarm, final BooleanProperty temperatureAlarm) throws Exception {
        this.channel = new SerialChannel(port, rate);

        this.wasteLevel = wasteLevel;
        this.temperature = temperature;
        this.wasteLevelAlarm = wasteLevelAlarm;
        this.temperatureAlarm = temperatureAlarm;

        this.setDaemon(true); // Set as Daemon Thread
    }
    
    @Override
    public void run() throws NumberFormatException {
        while(true) {
            if (!this.channel.isMessageAvailable()) continue;
            
            try {
                final String message = this.channel.receiveMessage().replace("\n", "").replace("\r", "");
                System.out.println("Received Message: " + message);
                
                if (message.startsWith(WASTE_LEVEL_TAG)) {
                    Platform.runLater(() -> this.wasteLevel.set(Float.parseFloat(message.substring(WASTE_LEVEL_TAG.length()))/100));
                }
                else if (message.startsWith(TEMPERATURE_TAG)) {
                    Platform.runLater(() -> this.temperature.set(Float.parseFloat(message.substring(TEMPERATURE_TAG.length()))/100));
                }
                else if (message.startsWith(WASTE_LEVEL_ALARM_TAG)) {
                    Platform.runLater(() -> this.wasteLevelAlarm.set(message.substring(WASTE_LEVEL_ALARM_TAG.length()).equals("true")));
                }
                else if (message.startsWith(TEMPERATURE_ALARM_TAG)) {
                    Platform.runLater(() -> this.temperatureAlarm.set(message.substring(TEMPERATURE_ALARM_TAG.length()).equals("true")));
                }
            } catch (InterruptedException e) {
                System.err.println("Error while Receiving Message: " + e.getMessage());
            }
        }       
    }
    
    /**
     * @see CommunicationChannel#closeChannel()
     */
    public void closeChannel() {
        this.channel.closeChannel();
    }
    
    /**
     * @see CommunicationChannel#sendMessage(String)
     */
    public boolean sendMessage(final String message) {
        return this.channel.sendMessage(message);
    }

    /**
     * Communication Channel Getter
     * 
     * @return Communication Channel in Use
     */
    public CommunicationChannel getChannel() {
        return this.channel;
    }

    /**
     * Waste Level Getter
     * 
     * @return Waste Level Value
     */
    public float getWasteLevel() {
        return this.wasteLevel.get();
    }

    /**
     * Temperature Getter
     * 
     * @return Temperature Value
     */
    public float getTemperature() {
        return this.temperature.get();
    }

    /**
     * Waste Level Alarm Getter
     * 
     * @return If Waste Level Alarm is Active
     */
    public boolean getWasteLevelAlarm() {
        return this.wasteLevelAlarm.get();
    }

    /**
     * Temperature Alarm Getter
     * 
     * @return If Temperature Alarm is Active
     */
    public boolean getTemperatureAlarm() {
        return this.temperatureAlarm.get();
    }
}
