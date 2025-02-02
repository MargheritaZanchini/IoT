module smart.temperature.monitoring {
    requires io.vertx.core;

    requires javafx.controls;
    requires javafx.base;
    requires javafx.fxml;

    requires transitive javafx.graphics;

    opens smart.temperature.monitoring to javafx.fxml;
    exports smart.temperature.monitoring;
}
