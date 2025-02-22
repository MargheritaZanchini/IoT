package smart.temperature.monitoring;

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
import javafx.scene.control.TextField;
import smart.temperature.monitoring.connections.HTTPAgent;

/***
 * 
 * Platform.runLater() needed to update JavaFX components
 * because the method is called from a different thread !
 * Move the execution from Java thread to JavaFX thread !
 * 
***/

/**
 * Graphical Controller Class
 * 
 * @see FXML
 */
public class GraphicalController {
    @FXML private LineChart<Number, Number> temperatureChart; // Temperature Chart Component
    @FXML private NumberAxis xAxis; // Chart X-Axis
    @FXML private NumberAxis yAxis; // Chart Y-Axis

    @FXML private Label minTemperature; // Minimum Temperature Component
    @FXML private Label avgTemperature; // Average Temperature Component
    @FXML private Label maxTemperature; // Maximum Temperature Component
    @FXML private Label currentState; // Current State Component

    @FXML private TextField apertureLabel; // Aperture TextField Component

    @FXML private Button manualButton; // Manual/Auto Button Component
    @FXML private Button problemSolver; // Alarm Solver Button Component

    private final static int HTTP_PORT = 8080; // HTTP Server Port
    private final static String HTTP_SERVER = "localhost"; // HTTP Server Address

    private Vertx vertx;
    private HTTPAgent agent;
    
    /**
     * Method to set the current data to the GUI.
     * 
     * @param data received data (JSON)
     */
    @FXML public void setCurrentData(JsonObject data) {
        Platform.runLater(() -> {
            // Update temperature values
            String minTemperatureValue = String.format("Min: %.2f°C", data.getDouble("minTemperature"));
            String maxTemperatureValue = String.format("Max: %.2f°C", data.getDouble("maxTemperature"));
            String avgTemperatureValue = String.format("Avg: %.2f°C", data.getDouble("avgTemperature"));

            // Get mode and state values
            String modeValue = data.getString("mode").toLowerCase();
            String stateValue = data.getString("state").toLowerCase();

            // Update temperature labels
            minTemperature.setText(minTemperatureValue);
            maxTemperature.setText(maxTemperatureValue);
            avgTemperature.setText(avgTemperatureValue);
            
            // Update textfield value with current aperture
            apertureLabel.setText(data.getInteger("aperture").toString());

            // Manual / Auto button
            manualButton.setText(modeValue.equals("manual") ? "MANUAL" : "AUTO");

            // Update current state (mode)
            currentState.setText("State: " + stateValue.toUpperCase().replace("_", " "));

            // State Button
            problemSolver.setDisable(!stateValue.equals("alarm"));

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

    /**
     * Initialize the Graphical Controller
     * and all the components.
     */
    @FXML private void initialize() {
        this.vertx = Vertx.vertx();
        this.agent = new HTTPAgent(HTTP_PORT, HTTP_SERVER, this);
        this.vertx.deployVerticle(agent);

        // Chart settings
        xAxis.setAutoRanging(false);
        xAxis.setLowerBound(0);
        xAxis.setUpperBound(9);
        xAxis.setTickUnit(1);
            
        yAxis.setAutoRanging(false);
        yAxis.setLowerBound(Math.floor(10));
        yAxis.setUpperBound(Math.ceil(50));
        yAxis.setTickUnit(5);
        
        temperatureChart.setAnimated(false); // Disable animation for the chart
    }

    /**
     * Method to handle the manual/auto mode switch.
     */
    @FXML private void modeHandler() {
        Platform.runLater(() -> {
            agent.sendSwitchMode();
        });
    }

    /**
     * Method to handle the alarm resolve.
     */
    @FXML private void alarmHandler() {
        Platform.runLater(() -> {
            agent.sendResolveAlarm();
        });
    }
}