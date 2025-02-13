package control.unit;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class TemperatureManager {
    private final List<Double> temperatures;

    public static enum TemperatureState {
        NORMAL,
        HOT,
        TOO_HOT,
        ALARM
    }

    public TemperatureManager() {
        this.temperatures = new ArrayList<>();
    }

    public void addTemperature(double temperature) {
        if(this.temperatures.size() >= 10) {
            this.temperatures.remove(0);
        }
        this.temperatures.add(temperature);
    }

    public double getTemperature(int index) {
        if(this.temperatures.isEmpty()) { // No temperatures
            return -1;
        }
        if(index < 0 || index >= this.temperatures.size()) { // Index out of bounds
            return -1;
        }

        return this.temperatures.get(index);
    }

    public double getCurrentTemperature() {
        return this.getTemperature(this.temperatures.size()-1);
    }

    public List<Double> getTemperatures() {
        return List.copyOf(this.temperatures);
    }

    public double getMinTemperature() {
        return Collections.min(this.temperatures);
    }

    public double getAverageTemperature() {
        return this.temperatures.stream().mapToDouble(Double::doubleValue).average().orElse(0);
    }

    public double getMaxTemperature() {
        return Collections.max(this.temperatures);
    }
}