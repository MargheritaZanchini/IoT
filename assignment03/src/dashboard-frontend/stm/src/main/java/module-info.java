module smart.temperature.monitoring {
    requires io.vertx.mqtt;
    requires transitive io.vertx.core;

    requires javafx.controls;
    requires javafx.base;
    requires javafx.fxml;

    requires io.vertx.web;
    requires io.vertx.web.client;

    requires transitive javafx.graphics;

    opens smart.temperature.monitoring to javafx.fxml;
    exports smart.temperature.monitoring;
}