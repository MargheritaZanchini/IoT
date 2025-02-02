package smart.temperature.monitoring;

import io.vertx.core.*;
import io.vertx.mqtt.*;

import javafx.application.Application;
import javafx.stage.Stage;

import java.io.IOException;

public class App extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}