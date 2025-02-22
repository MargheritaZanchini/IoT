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

/**
 * HTTPAgent is a Verticle that listens for incoming HTTP requests and sends responses.
 * It is used to receive data from the sensors and send data to the actuators.
 * 
 * @see AbstractVerticle
 */
public class HTTPAgent extends AbstractVerticle {
    private final static String DATA_PATH = "/api/data"; // Path for sending and receiving data

    private final int port;
    private final ValueManager valueManager;

    /**
     * Constructor for the HTTPAgent class.
     * 
     * @param port
     * @param valueManager
     */
	public HTTPAgent(int port, ValueManager valueManager) {
        this.port = port;

        this.valueManager = valueManager;
	}

    @Override
    public void start(Promise<Void> startPromise) {
        // Create a new router
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

    /**
     * Handler for receiving data (actions) from the dashboard.
     * 
     * @param context routing context
     */
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

    /**
     * Handler for sending data to the dashboard.
     * 
     * @param context routing context
     */
    private void senderHandler(RoutingContext context) {
        context
        .response()
        .putHeader("content-type", "application/json")
        .end(prepareData().encode());
    }

    /**
     * Prepares the data to be sent to the dashboard.
     * 
     * @return value data in JSON format
     * @see ValueManager
     */
    public JsonObject prepareData() {
        JsonObject data = new JsonObject()
        .put("temperatures", valueManager.getTemperatures())
        .put("minTemperature", valueManager.getMinTemperature())
        .put("maxTemperature", valueManager.getMaxTemperature())
        .put("avgTemperature", valueManager.getAverageTemperature())
        .put("mode", valueManager.getMode().toString())
        .put("state", valueManager.getState().toString());
        
        // If the mode is set to automatic, send the aperture value that corresponds to the current temperature
        // If the mode is set to manual, send the current aperture value from the potentiometer
        if(valueManager.getMode() == ValueManager.Mode.AUTOMATIC) {
            data.put("aperture", valueManager.getCorrespondingAperture());
        }
        else if(valueManager.getMode() == ValueManager.Mode.MANUAL) {
            data.put("aperture", valueManager.getAperture());
        }
    
        return data;
    }
}