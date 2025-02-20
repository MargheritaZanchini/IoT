package smart.temperature.monitoring;

import java.util.Queue;

import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import javafx.fxml.FXML;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
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

    //private Queue<Integer> temperatureData;

    //private int minTemp = Integer.MAX_VALUE;
    //private int avgTemp = 0;
    //private int maxTemp = Integer.MIN_VALUE;

    @FXML private void initialize() {
        this.vertx = Vertx.vertx();
        this.agent = new HTTPAgent(HTTP_PORT, HTTP_SERVER);
        this.vertx.deployVerticle(agent);
    }

    @FXML private void handleManualButton() {
        JsonObject data = new JsonObject()
            .put("command", "manual")
            .put("value", openingSpinner.getValue())
            .put("timestamp", System.currentTimeMillis());

        agent.sendData(data);
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