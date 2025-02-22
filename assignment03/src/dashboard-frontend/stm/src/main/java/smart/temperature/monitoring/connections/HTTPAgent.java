package smart.temperature.monitoring.connections;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.client.WebClientOptions;
import smart.temperature.monitoring.GraphicalController;

/**
 * HTTPAgent class is responsible for sending and receiving data from the server.
 */
public class HTTPAgent extends AbstractVerticle {
    private final static String DATA_PATH = "/api/data"; // Path to send and receive data from the server
    private final static int LOOP_TIME = 1000; // Time interval to receive data from the server

    private final Vertx vertx;
    private final int port;
    private final String server;
    private WebClient client;

    private final GraphicalController guiController;

    /**
     * Constructor for HTTPAgent class.
     * 
     * @param port
     * @param server
     * @param guiController
     */
    public HTTPAgent(int port, String server, GraphicalController guiController) {
        this.port = port;
        this.server = server;
        this.vertx = Vertx.vertx();

        this.guiController = guiController;

        WebClientOptions options = new WebClientOptions().setDefaultHost(server).setDefaultPort(port); // Set the host and port for the WebClient
        this.client = WebClient.create(vertx, options); // Create a WebClient object, with given options, to send and receive data
    }

    @Override
    public void start(Promise<Void> startPromise) {
        vertx.setPeriodic(LOOP_TIME, id -> {
            receiveData(); // Receive data from the server every LOOP_TIME (default = 1000) milliseconds
        });
    }

    /**
     * Method to receive data from the server.
     */
    private void receiveData() {
        this.client.get(this.port, this.server, DATA_PATH).send() // Send a GET request to the server to receive data
        .onSuccess(response -> { // If the request is successful
            JsonObject data = response.bodyAsJsonObject(); // Get the data received from the server
            this.guiController.setCurrentData(data);
            System.out.println("Data received successfully: " + data.encodePrettily());
        })
        .onFailure(response -> { // Else, print the error message
            System.out.println("Error in receiving: " + response.getMessage());
        });
    }

    /**
     * Method to send data to the server.
     * 
     * @param data Data to be sent to the server (JSON)
     */
    private void sendData(JsonObject data) {
        this.client.post(this.port, this.server, DATA_PATH).sendJson(data) // Send a POST request to the server to send data
        .onSuccess(response -> { // If the request is successful
            System.out.println("Data sent successfully"); // Print a success message
        })
        .onFailure(response -> { // Else, print the error message
            System.out.println("Error in sending: " + response.getMessage());
        });
    }

    /**
     * Method to send the alarm resolve signal to the control unit.
     */
    public void sendResolveAlarm() {
        // Create a JSON object with the key "actionName" and a "resolveAlarm" value, and send it to the c.u.
        this.sendData(new JsonObject().put("actionName", "resolveAlarm"));
    }

    /**
     * Method to send the alarm signal to the control unit.
     */
    public void sendSwitchMode() {
        // Create a JSON object with the key "actionName" and a "resolveAlarm" value, and send it to the c.u.
        this.sendData(new JsonObject().put("actionName", "setMode"));
    } 
}