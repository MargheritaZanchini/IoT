package control.unit;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

/**
 * TemperatureManager Class
 */
public class TemperatureManager {
    private final List<Double> temperatures;

    public final static float T1 = 30; /** First Temperature Alert */
    public final static float T2 = 40; /** Second Temperature Alert */

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

    /**
     * TemperatureManager Constructor
     */
    public TemperatureManager() {
        this.temperatures = new ArrayList<>();
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

        if(aperture < 0) {
            return 0;
        }
        else if(aperture > 100) {
            return 100;
        }

        return aperture;
    }
}