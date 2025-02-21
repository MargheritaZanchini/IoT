package control.unit.connections.http;

import control.unit.ValueManager;
import control.unit.ValueManager.TemperatureState;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Promise;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

public class HTTPServer extends AbstractVerticle {
    private final static String DATA_PATH = "/api/data";

    private final int port;
    private final String server;
    private final ValueManager valueManager;

	public HTTPServer(int port, String server, ValueManager valueManager) {
        this.port = port;
        this.server = server;

        this.valueManager = valueManager;
	}

    @Override
    public void start(Promise<Void> startPromise) {
        Router router = Router.router(vertx);
        router.route().handler(BodyHandler.create());
        
        // Define routes for sending and receiving data
        router.post(DATA_PATH).handler(this::receiverHandler);
        router.get(DATA_PATH).handler(this::senderHandler);

        vertx.createHttpServer().requestHandler(router).listen(this.port, ar -> {
            if(ar.succeeded()) {
                System.out.println("HTTP Server started on port " + this.port);
                startPromise.complete();
            }
            else {
                System.out.println("HTTP Server failed to start on port " + this.port);
                startPromise.fail(ar.cause());
            }
        });
    }

    private void receiverHandler(RoutingContext context) {
        HttpServerResponse response = context.response();
        JsonObject body = context.body().asJsonObject();

        System.out.println("Received: " + body.encodePrettily());

        if(body == null || body.isEmpty()) {
            response.setStatusCode(400).end("Invalid request body");
        }
        else {
            if(body.containsKey("actionName")) {
                if(body.getString("actionName").equals("setMode")) {
                    valueManager.switchMode();
                }
                else if(body.getString("actionName").equals("resolveAlarm")) {   
                    valueManager.setState(TemperatureState.NORMAL);
                }
            }
            response.setStatusCode(200).end("Data received successfully");
        }
    }

    private void senderHandler(RoutingContext context) {
        System.out.println("SENDER HANDLER!");
        context
        .response()
        .putHeader("content-type", "application/json")
        .end(prepareData().encode());
    }

    public JsonObject prepareData() {
        JsonObject data = new JsonObject()
        .put("temperatures", valueManager.getTemperatures())
        .put("minTemperature", valueManager.getMinTemperature())
        .put("maxTemperature", valueManager.getMaxTemperature())
        .put("avgTemperature", valueManager.getAverageTemperature())
        .put("mode", valueManager.getMode().toString())
        .put("state", valueManager.getState().toString());
        
        if(valueManager.getMode() == ValueManager.Mode.AUTOMATIC) {
            data.put("aperture", valueManager.getCorrespondingAperture());
        }
        else if(valueManager.getMode() == ValueManager.Mode.MANUAL) {
            data.put("aperture", valueManager.getAperture());
        }
    
        return data;
    }
}



/*
    public void sendData(JsonObject data) {
        this.client.post(this.port, this.server, DATA_PATH).sendJsonObject(data, ar -> {
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

        if(body.containsKey("actionName")) {
            if(body.getString("actionName").equals("setMode")) {
                valueManager.switchMode();
            }
            // TODO Aperture
            // else if(body.getString("actionName").equals("setAperture")) {
            //     valueManager.setAperture(body.getInteger("aperture"));
            // }
            else if(body.getString("actionName").equals("resolveAlarm")) {   
                valueManager.setState(TemperatureState.NORMAL);
            }
        }

        context.response()
        .putHeader("content-type", "application/json")
        .end(new JsonObject().put("status", "received").encode());
    }
    */