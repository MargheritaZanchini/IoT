package control.unit.connections.http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.handler.BodyHandler;

public class HTTPServer extends AbstractVerticle {
    private final static String DATA_SENDING_PATH = "/data/to/client";
    private final static String DATA_RECEIVING_PATH = "/data/to/server";

    private final Vertx vertx;
    private final int port;
    private final String server;
    private final WebClient client;

	public HTTPServer(int port, String server) {
        this.port = port;
        this.server = server;

        this.vertx = Vertx.vertx();
        this.client = WebClient.create(this.vertx);
	}

    @Override
    public void start(Promise<Void> startPromise) {
        Router router = Router.router(this.vertx);
        router.route().handler(BodyHandler.create());
        
        // Define routes for sending and receiving data
        router.post(DATA_SENDING_PATH).handler(this::handleDataSending);
        router.post(DATA_RECEIVING_PATH).handler(this::handleDataReceiving);
        
        vertx.createHttpServer()
            .requestHandler(router)
            .listen(this.port, http -> {
                if (http.succeeded()) {
                    System.out.println("HTTP Server started on port " + this.port);
                    startPromise.complete();
                } else {
                    System.out.println("HTTP Server failed to start: " + http.cause());
                    startPromise.fail(http.cause());
                }
            });
    }

    public void sendData(JsonObject data) {
        this.client
            .post(this.port, this.server, DATA_SENDING_PATH)
            .sendJsonObject(data, ar -> {
                if (ar.succeeded()) {
                    // System.out.println("Data sent successfully");
                    // System.out.println("Response: " + ar.result().bodyAsString());
                } else {
                    // System.out.println("Failed to send data: " + ar.cause().getMessage());
                }
            });
    }

    private void handleDataSending(RoutingContext context) {
        JsonObject body = context.body().asJsonObject();
        System.out.println("Data received on sending endpoint: " + body.encodePrettily());
        
        // Send response back
        context.response()
            .putHeader("content-type", "application/json")
            .end(new JsonObject().put("status", "success").encode());
    }

    private void handleDataReceiving(RoutingContext context) {
        JsonObject body = context.body().asJsonObject();
        System.out.println("Data received on receiving endpoint: " + body.encodePrettily());
        
        // Process received data here

        // Send response back
        // context.response()
        // .putHeader("content-type", "application/json")
        // .end(new JsonObject().put("status", "received").encode());
    }
}