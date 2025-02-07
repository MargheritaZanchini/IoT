package control.unit.connections.http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;

	public DataService(int port) {
		this.port = port;
	}

	@Override
	public void start() {		

	}
	
	private void handleAddNewData(RoutingContext routingContext) {

	}
	
	private void handleGetData(RoutingContext routingContext) {

	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
	}

	private void log(String msg) {
		System.out.println("[DATA SERVICE] " + msg);
	}
}