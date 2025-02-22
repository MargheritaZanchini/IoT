package control.unit;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

/**
 * ValueManager class
 * 
 * This class is responsible for managing the values of the control unit
 */
public class ValueManager {
    public final static float T1 = 39; /** First Temperature Alert */
    public final static float T2 = 41; /** Second Temperature Alert */

    public final static int F1 = 3000; /** First Frequency */
    public final static int F2 = 1000; /** Second Frequency */

    public final static long DT = 3000; /** Time Interval to go to Alarm */

    private final List<Double> temperatures; /** Temperature List */
    private TemperatureState state;
    private Mode mode;

    private int aperture;

    /**
     * TemperatureState Enum
     * 
     * @see #NORMAL
     * @see #HOT
     * @see #TOO_HOT
     * @see #ALARM
     */
    public static enum TemperatureState {
        NORMAL, /** Normal */
        HOT, /** Hot */
        TOO_HOT, /** Too Hot */
        ALARM /** Alarm */
    }

    public static enum Mode {
        MANUAL, /** Manual Mode */
        AUTOMATIC /** Auto Mode */
    }

    /**
     * TemperatureManager Constructor
     */
    public ValueManager() {
        this.temperatures = new ArrayList<>();
        this.state = TemperatureState.NORMAL;
        this.mode = Mode.AUTOMATIC;
        this.aperture = 0;
    }

    /**
     * Add Temperature to Queue
     * 
     * @param temperature Temperature
     */
    public void addTemperature(double temperature) {
        if(this.temperatures.size() >= 10) {
            this.temperatures.remove(0);
        }
        this.temperatures.add(temperature);
    }

    /**
     * Get Temperature by Index
     * 
     * @param index Index
     * @return Temperature
     */
    public double getTemperature(int index) {
        if(this.temperatures.isEmpty()) { // No temperatures
            return -1;
        }
        if(index < 0 || index >= this.temperatures.size()) { // Index out of bounds
            return -1;
        }

        return this.temperatures.get(index);
    }

    /**
     * Get Current Temperature
     * 
     * @return Current Temperature
     */
    public double getCurrentTemperature() {
        return this.getTemperature(this.temperatures.size()-1);
    }

    /**
     * Get Temperatures
     * 
     * @return Temperature List
     * @see #temperatures
     */
    public List<Double> getTemperatures() {
        return List.copyOf(this.temperatures);
    }

    /**
     * Get Minimum Temperature
     * 
     * @return Minimum Temperature
     * @see Collections#min
     */
    public double getMinTemperature() {
        if(this.temperatures.isEmpty()) {
            return -1;
        }
        return Collections.min(this.temperatures);
    }

    /**
     * Get Average Temperature
     * 
     * @return Average Temperature
     */
    public double getAverageTemperature() {
        return this.temperatures.stream().mapToDouble(Double::doubleValue).average().orElse(0);
    }

    /**
     * Get Maximum Temperature
     * 
     * @return Maximum Temperature
     * @see Collections#max
     */
    public double getMaxTemperature() {
        if(this.temperatures.isEmpty()) {
            return -1;
        }
        return Collections.max(this.temperatures);
    }

    /**
     * Get Corresponding Aperture, mapping temperature to aperture value (0 - 100)
     * 
     * @return Corresponding Aperture
     * @see #T1
     * @see #T2
     */
    public int getCorrespondingAperture() {
        int aperture = (int) ((getCurrentTemperature() - T1) / (T2 - T1) * 100);

        if(aperture < 0 || this.state == TemperatureState.NORMAL) {
            return 0;
        }
        else if(aperture > 100 || this.state == TemperatureState.ALARM) {
            return 100;
        }

        return aperture;
    }

    /**
     * Get Mode
     * 
     * @return Mode
     * @see #mode
     */
    public Mode getMode() {
        return this.mode;
    }

    /**
     * Set Mode
     * 
     * @param mode Mode
     * @see #mode
     */
    public void setMode(String mode) {
        this.mode = mode.equals("manual") ? Mode.MANUAL : Mode.AUTOMATIC;
    }

    /**
     * Switch Mode
     * 
     * @see #mode
     */
    public void switchMode() {
        this.mode = this.mode == Mode.MANUAL ? Mode.AUTOMATIC : Mode.MANUAL;
    }

    /**
     * Get Aperture
     * 
     * @return Aperture
     * @see #aperture
     */
    public int getAperture() {
        return this.aperture;
    }

    /**
     * Set Aperture
     * 
     * @param aperture Aperture
     * @see #aperture
     */
    public void setAperture(int aperture) {
        this.aperture = aperture;
    }

    /**
     * Get State
     * 
     * @return State
     * @see #state
     */
    public TemperatureState getState() {
        return this.state;
    }

    /**
     * Set State
     * 
     * @param state State
     * @see #state
     */
    public void setState(TemperatureState state) {
        this.state = state;
    }
}