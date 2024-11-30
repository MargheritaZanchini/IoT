package assignment02;

import javafx.application.Platform;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.FloatProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleFloatProperty;

public class SerialDataHandler extends Thread {
    private final static String WASTE_LEVEL_TAG = "[Value:WasteLevel]";
    private final static String TEMPERATURE_TAG = "[Value:Temperature]";
    private final static String WASTE_LEVEL_ALARM_TAG = "[Alarm:WasteLevel]";
    private final static String TEMPERATURE_ALARM_TAG = "[Alarm:Temperature]";

    private final CommunicationChannel channel;

    private FloatProperty wasteLevel = new SimpleFloatProperty(0);
    private FloatProperty temperature = new SimpleFloatProperty(0);
    private BooleanProperty wasteLevelAlarm = new SimpleBooleanProperty(false);
    private BooleanProperty temperatureAlarm = new SimpleBooleanProperty(false);
    
    public SerialDataHandler(final String port, final int rate, final FloatProperty wasteLevel, final FloatProperty temperature, final BooleanProperty wasteLevelAlarm, final BooleanProperty temperatureAlarm) throws Exception {
        this.channel = new SerialChannel(port, rate);

        this.wasteLevel = wasteLevel;
        this.temperature = temperature;
        this.wasteLevelAlarm = wasteLevelAlarm;
        this.temperatureAlarm = temperatureAlarm;

        this.setDaemon(true);
    }
    
    @Override
    public void run() throws NumberFormatException {
        while(true) {
            if(!this.channel.isMessageAvailable()) continue;
            
            try {
                final String message = this.channel.receiveMessage().replace("\n", "").replace("\r", "");
                System.out.println("Received Message: " + message);
                
                if(message.startsWith(WASTE_LEVEL_TAG)) {
                    Platform.runLater(() -> this.wasteLevel.set(Float.parseFloat(message.substring(WASTE_LEVEL_TAG.length()))/100));
                }
                else if(message.startsWith(TEMPERATURE_TAG)) {
                    Platform.runLater(() -> this.temperature.set(Float.parseFloat(message.substring(TEMPERATURE_TAG.length()))/100));
                }
                else if(message.startsWith(WASTE_LEVEL_ALARM_TAG)) {
                    Platform.runLater(() -> this.wasteLevelAlarm.set(message.substring(WASTE_LEVEL_ALARM_TAG.length()).equals("true")));
                }
                else if(message.startsWith(TEMPERATURE_ALARM_TAG)) {
                    Platform.runLater(() -> this.temperatureAlarm.set(message.substring(TEMPERATURE_ALARM_TAG.length()).equals("true")));
                }
            } catch (InterruptedException e) {
                System.err.println("Error while Receiving Message: " + e.getMessage());
            }
        }       
    }
    
    public void closeChannel() {
        this.channel.closeChannel();
    }
    
    public void sendMessage(final String message) {
        this.channel.sendMessage(message);
    }

    public CommunicationChannel getChannel() {
        return this.channel;
    }

    public float getWasteLevel() {
        return this.wasteLevel.get();
    }

    public float getTemperature() {
        return this.temperature.get();
    }

    public boolean getWasteLevelAlarm() {
        return this.wasteLevelAlarm.get();
    }

    public boolean getTemperatureAlarm() {
        return this.temperatureAlarm.get();
    }
}
