package control.unit.connections.http;

import control.unit.ValueManager;
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

    private final ValueManager valueManager;

	public HTTPServer(int port, String server, ValueManager valueManager) {
        this.port = port;
        this.server = server;

        this.vertx = Vertx.vertx();
        this.client = WebClient.create(this.vertx);

        this.valueManager = valueManager;
	}

    @Override
    public void start(Promise<Void> startPromise) {
        Router router = Router.router(this.vertx);
        router.route().handler(BodyHandler.create());
        
        // Define routes for sending and receiving data
        router.post(DATA_SENDING_PATH).handler(this::handleDataSending);
        router.post(DATA_RECEIVING_PATH).handler(this::handleDataReceiving);
        
        vertx.createHttpServer().requestHandler(router).listen(this.port, http -> {
            if (http.succeeded()) {
                System.out.println("HTTP Server started on port " + this.port);
                startPromise.complete();
            }
            else {
                System.out.println("HTTP Server failed to start: " + http.cause());
                startPromise.fail(http.cause());
            }
        });
    }

    public void sendData(JsonObject data) {
        this.client.post(this.port, this.server, DATA_SENDING_PATH).sendJsonObject(data, ar -> {
            if(!ar.succeeded()) {
                System.out.println("Couldn't send data successfully: " + ar.result().bodyAsString());
            }
            else {
                System.out.println("Data sent successfully: " + ar.result().bodyAsString());
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

        // Send response back
        context.response()
        .putHeader("content-type", "application/json")
        .end(new JsonObject().put("status", "received").encode());
    }

    public JsonObject prepareData() {
        JsonObject data = new JsonObject()
        .put("temperatures", valueManager.getTemperatures())
        .put("minTemperature", valueManager.getMinTemperature())
        .put("maxTemperature", valueManager.getMaxTemperature())
        .put("avgTemperature", valueManager.getAverageTemperature())
        .put("mode", valueManager.getMode().toString());
        // .put("state", valueManager.getState().toString())
        
        if(valueManager.getMode() == ValueManager.Mode.AUTOMATIC) {
            data.put("aperture", valueManager.getCorrespondingAperture());
        }
        else if(valueManager.getMode() == ValueManager.Mode.MANUAL) {
            data.put("aperture", valueManager.getAperture());
        }
    
        return data;
    }
}