package smart.temperature.monitoring.connections;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;
import io.vertx.core.Vertx;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.client.WebClientOptions;
import smart.temperature.monitoring.GraphicalController;

public class HTTPAgent extends AbstractVerticle {
    private final static String DATA_PATH = "/api/data";

    private final Vertx vertx;
    private final int port;
    private final String server;
    private WebClient client;

    private final GraphicalController guiController;

    public HTTPAgent(int port, String server, GraphicalController guiController) {
        this.port = port;
        this.server = server;
        this.vertx = Vertx.vertx();

        this.guiController = guiController;

        WebClientOptions options = new WebClientOptions().setDefaultHost(server).setDefaultPort(port);
        this.client = WebClient.create(vertx, options);
    }

    @Override
    public void start(Promise<Void> startPromise) {
        vertx.setPeriodic(1000, id -> {
            receiveData();
        });
    }

    private void receiveData() {
        this.client.get(this.port, this.server, DATA_PATH).send()
        .onSuccess(response -> {
            JsonObject data = response.bodyAsJsonObject();
            this.guiController.setCurrentData(data);
            System.out.println("Data received successfully: " + data.encodePrettily());
        })
        .onFailure(response -> {
            System.out.println("Error in receiving: " + response.getMessage());
        });
    }

    private void sendData(JsonObject data) {
        this.client.post(this.port, this.server, DATA_PATH).sendJson(data)
        .onSuccess(response -> {
            System.out.println("Data sent successfully");
        })
        .onFailure(response -> {
            System.out.println("Error in sending: " + response.getMessage());
        });
    }

    public void sendResolveAlarm() {
        this.sendData(new JsonObject().put("actionName", "resolveAlarm"));
    }

    public void sendSwitchMode() {
        this.sendData(new JsonObject().put("actionName", "setMode"));
    } 
}