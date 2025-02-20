package smart.temperature.monitoring.connections;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;
import io.vertx.core.Vertx;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.client.WebClientOptions;

public class HTTPAgent extends AbstractVerticle {
    private final static String DATA_SENDING_PATH = "/data/to/server";
    private final static String DATA_RECEIVING_PATH = "/data/to/client";

    private final Vertx vertx;
    private final int port;
    private final String server;
    private WebClient client;

    public HTTPAgent(int port, String server) {
        this.port = port;
        this.server = server;
        this.vertx = Vertx.vertx();
    }

    @Override
    public void start(Promise<Void> startPromise) {
        // Configure HTTP client
        WebClientOptions options = new WebClientOptions()
            .setDefaultHost(server)
            .setDefaultPort(port);
            
        client = WebClient.create(vertx, options);

        // Create HTTP server to receive data
        vertx.createHttpServer()
            .requestHandler(req -> {
                if (req.method().name().equals("POST") && req.path().equals(DATA_RECEIVING_PATH)) {
                    req.bodyHandler(body -> {
                        JsonObject data = body.toJsonObject();
                        handleReceivedData(data);
                        
                        // Send response
                        HttpServerResponse response = req.response();
                        response.putHeader("content-type", "application/json");
                        response.end(new JsonObject()
                            .put("status", "success")
                            .put("message", "Data received successfully")
                            .encode());
                    });
                }
            })
            .listen(port, ar -> {
                if (ar.succeeded()) {
                    System.out.println("HTTP server started on port " + port);
                    startPromise.complete();
                } else {
                    System.err.println("Failed to start server: " + ar.cause());
                    startPromise.fail(ar.cause());
                }
            });
    }
    
    private void handleReceivedData(JsonObject data) {
        System.out.println("Received data: " + data.encodePrettily());
        // Add your data processing logic here
    }

    public void sendData(JsonObject data) {
        client.post(DATA_SENDING_PATH)
            .sendJsonObject(data, ar -> {
                if (ar.succeeded()) {
                    System.out.println("Data sent successfully");
                    System.out.println("Response: " + ar.result().bodyAsString());
                } else {
                    System.err.println("Failed to send data: " + ar.cause().getMessage());
                }
            });
    }
}