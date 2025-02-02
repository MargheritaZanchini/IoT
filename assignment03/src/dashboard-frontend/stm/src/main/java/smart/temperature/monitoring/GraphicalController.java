package smart.temperature.monitoring;

import java.util.Queue;

import javafx.fxml.FXML;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Spinner;

/**
 * Graphical Controller Class
 * 
 * @see FXML
 */
public class GraphicalController {
    @FXML private LineChart<Number, Number> temperatureChart;
    @FXML private NumberAxis xAxis;
    @FXML private NumberAxis yAxis;

    @FXML private Label minTemperature;
    @FXML private Label avgTemperature;
    @FXML private Label maxTemperature;
    @FXML private Label currentState;

    @FXML private Spinner<Integer> openingSpinner;

    @FXML private Button manualButton;
    @FXML private Button problemSolver;

    private Queue<Integer> temperatureData;

    private int minTemp = Integer.MAX_VALUE;
    private int avgTemp = 0;
    private int maxTemp = Integer.MIN_VALUE;

    @FXML private void initialize() {
        // updateMinTemperature();
        // updateAvgTemperature();
        // updateMaxTemperature();
    }

    private void updateMinTemperature(int temp) {
        if(temp < minTemp) {
            minTemp = temp;
            minTemperature.setText("Min: " + String.valueOf(minTemp));
        }
    }

    private void updateAvgTemperature() {
        avgTemp = temperatureData.stream().mapToInt(Integer::intValue).sum() / temperatureData.size();
        avgTemperature.setText("Avg: " + String.valueOf(avgTemp));
    }

    private void updateMaxTemperature() {
        
    }
}