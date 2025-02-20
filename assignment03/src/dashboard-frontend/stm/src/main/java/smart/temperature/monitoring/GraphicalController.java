package smart.temperature.monitoring;

import java.util.Queue;

import io.vertx.core.Vertx;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Spinner;
import smart.temperature.monitoring.connections.HTTPAgent;

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

    private final static int HTTP_PORT = 8080;
    private final static String HTTP_SERVER = "localhost";

    private Vertx vertx;
    private HTTPAgent agent;

    @FXML public void setCurrentData(JsonObject data) {
        Platform.runLater(() -> {
            // Update temperature labels
            minTemperature.setText(String.format("Min: %.2f°C", data.getDouble("minTemperature")));
            maxTemperature.setText(String.format("Max: %.2f°C", data.getDouble("maxTemperature")));
            avgTemperature.setText(String.format("Avg: %.2f°C", data.getDouble("avgTemperature")));
            
            // Update current state (mode)
            currentState.setText("Mode: " + data.getString("mode"));
            
            // Update spinner value with current aperture
            openingSpinner.getValueFactory().setValue(data.getInteger("aperture"));
            
            xAxis.setAutoRanging(false);
            xAxis.setLowerBound(0);
            xAxis.setUpperBound(9);
            xAxis.setTickUnit(1);
    
            yAxis.setAutoRanging(false);
            yAxis.setLowerBound(Math.floor(10));  // 5 gradi sotto il minimo
            yAxis.setUpperBound(Math.ceil(50));   // 5 gradi sopra il massimo
            yAxis.setTickUnit(5);

            temperatureChart.setAnimated(false);

            // Update chart with temperature array
            temperatureChart.getData().clear();
            XYChart.Series<Number, Number> series = new XYChart.Series<>();
            series.setName("Temperature");
            
            // Get temperature array from JSON
            JsonArray temperatures = data.getJsonArray("temperatures");
            for(int i = 0; i < temperatures.size(); i++) {
                series.getData().add(new XYChart.Data<>(i, temperatures.getDouble(i)));
            }
            
            temperatureChart.getData().add(series);
        });
    }

    @FXML private void initialize() {
        this.vertx = Vertx.vertx();
        this.agent = new HTTPAgent(HTTP_PORT, HTTP_SERVER, this);
        this.vertx.deployVerticle(agent);
    }

    @FXML private void handleManualButton() {
    }

    /*
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

    private void updateMaxTemperature() {}
    */
}