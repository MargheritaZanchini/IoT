package control.unit;

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class TemperatureManager {
    private final List<Double> temperature;
    
    public TemperatureManager() {
        this.temperature = new ArrayList<>();
    }

    public void addTemperature(double temperature) {
        this.temperature.add(temperature);
    }

    public double getTemperature(int index) {
        if(index < 0 || index >= this.temperature.size()) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }

        return this.temperature.get(index);
    }

    public double getCurrentTemperature() {
        return this.getTemperature(this.temperature.size());
    }

    public List<Double> getTemperatures() {
        return List.copyOf(this.temperature);
    }

    public double getMinTemperature() {
        return Collections.min(this.temperature);
    }

    public double getAverageTemperature() {
        return this.temperature.stream().mapToDouble(Double::doubleValue).average().orElse(0);
    }

    public double getMaxTemperature() {
        return Collections.max(this.temperature);
    }
}
