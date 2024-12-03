package assignment02;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.beans.binding.StringBinding;
import javafx.application.Platform;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.BooleanProperty;
import javafx.beans.property.FloatProperty;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleFloatProperty;

public class Controller {
    @FXML private ProgressBar toxicWasteLevel;
    @FXML private ProgressBar temperatureLevel;
    @FXML private Label wasteLevelLabel;
    @FXML private Label temperatureLabel;
    @FXML private Label statusLabel;
    @FXML private Button emptyButton;
    @FXML private Button restoreButton;
    
    private SerialDataHandler serialHandler = null;

    private final static String RESTORE_MESSAGE = "[Action:Restore]";
    private final static String EMPTY_MESSAGE = "[Action:Empty]";

    @FXML public void initialize() throws Exception {
        this.serialHandler = new SerialDataHandler(Launcher.SERIAL_PORT, Launcher.BAUD_RATE, this.wasteValue, this.temperatureValue, this.wasteLevelAlarm, this.temperatureAlarm);
        if (this.serialHandler == null) {
            throw new Exception("Failed to initialize SerialDataHandler");
        }
        this.serialHandler.start();

        this.toxicWasteLevel.progressProperty().bind(this.wasteValue);
        this.temperatureLevel.progressProperty().bind(this.temperatureValue);
        this.wasteLevelLabel.textProperty().bind(this.wasteValueBinding);
        this.temperatureLabel.textProperty().bind(this.temperatureValueBinding);

        this.wasteValue.addListener((observer, oldValue, newValue) -> updateWasteLevelColor(newValue.doubleValue()));
        this.temperatureValue.addListener((observer, oldValue, newValue) -> updateTemperatureLevelColor(newValue.doubleValue()));

        this.emptyButton.setOnAction((event) -> emptyWaste());
        this.emptyButton.disableProperty().bind(emptyButtonBinding);
        this.restoreButton.setOnAction((event) -> restoreTemperature());
        this.restoreButton.disableProperty().bind(restoreButtonBinding);
    }
    
    private final FloatProperty wasteValue = new SimpleFloatProperty(0);
    private final FloatProperty temperatureValue = new SimpleFloatProperty(0);
    private BooleanProperty wasteLevelAlarm = new SimpleBooleanProperty(false);
    private BooleanProperty temperatureAlarm = new SimpleBooleanProperty(false);
    
    private final StringBinding wasteValueBinding = new StringBinding() {
        { super.bind(wasteValue); }
        @Override
        protected String computeValue() {
            return String.format("%.1f%%", wasteValue.get() * 100);
        }
    };

    private final StringBinding temperatureValueBinding = new StringBinding() {
        { super.bind(temperatureValue); }
        @Override
        protected String computeValue() {
            return String.format("%.1f°C", temperatureValue.get() * 100);
        }
    };

    private final BooleanBinding emptyButtonBinding = new BooleanBinding() {
        { super.bind(wasteLevelAlarm); }
        @Override
        protected boolean computeValue() {
            return !wasteLevelAlarm.get();
        }
    };

    private final BooleanBinding restoreButtonBinding = new BooleanBinding() {
        { super.bind(temperatureAlarm); }
        @Override
        protected boolean computeValue() {
            return !temperatureAlarm.get();
        }
    };
    
    private void updateWasteLevelColor(double value) {
        String color = "-fx-accent: #00ff00;";

        if(value < 0.6) color = "-fx-accent: #00ff00;";
        else if(value < 0.8) color = "-fx-accent: #ffa500;";
        else color = "-fx-accent: #ff0000;";

        this.toxicWasteLevel.setStyle(color);
    }
    
    private void updateTemperatureLevelColor(double value) {
        String color = "-fx-accent: #00ff00;";

        if(value < 0.5) color = "-fx-accent: #00ff00;";
        else if(value < 0.8) color = "-fx-accent: #ffa500;";
        else color = "-fx-accent: #ff0000;";

        this.temperatureLevel.setStyle(color);
    }
    
    private void emptyWaste() {
        Platform.runLater(() -> {
            this.serialHandler.sendMessage(EMPTY_MESSAGE);
        });
    }

    private void restoreTemperature() {
        Platform.runLater(() -> {
            this.serialHandler.sendMessage(RESTORE_MESSAGE);
        });
    }
}