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
        this.temperatures.add(temperature);
    }

    public double getTemperature(int index) {
        if(this.temperatures.isEmpty()) {
            // throw new IndexOutOfBoundsException("No temperatures available");
            return -1;
        }
        if(index < 0 || index >= this.temperatures.size()) {
            // throw new IndexOutOfBoundsException("Index out of bounds");
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

    public TemperatureState getTemperatureState() {   
        double currentTemperature = this.getCurrentTemperature();

        if(currentTemperature > 0 && currentTemperature <= 30) return TemperatureState.NORMAL;
        else if(currentTemperature > 30 && currentTemperature <= 32) return TemperatureState.HOT;
        else if(currentTemperature > 32 && currentTemperature <= 35) return TemperatureState.TOO_HOT;
        else if(currentTemperature > 35 && currentTemperature <= 40) return TemperatureState.ALARM;
        else return TemperatureState.ALARM;
    }
}