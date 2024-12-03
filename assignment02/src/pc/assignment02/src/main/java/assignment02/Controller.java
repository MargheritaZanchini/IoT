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
    @FXML private ProgressBar toxicWasteLevel; /** Progress Bar for the Toxic Waste Level */
    @FXML private ProgressBar temperatureLevel; /** Progress Bar for the Temperature Level */
    @FXML private Label wasteLevelLabel; /** Label for the Waste Level */
    @FXML private Label temperatureLabel; /** Label for the Temperature */
    @FXML private Button emptyButton; /** Button to Empty the Waste */
    @FXML private Button restoreButton; /** Button to Restore the Temperature */
    
    private SerialDataHandler serialHandler = null; /** Serial Data Handler to Communicate with the Arduino */

    private final static String RESTORE_MESSAGE = "[Action:Restore]"; /** Serial Message to Restore the Temperature */
    private final static String EMPTY_MESSAGE = "[Action:Empty]"; /** Serial Message to Empty the Waste */

    /**
     * Initialize the FXML (Layout) Controller
     * 
     * @throws Exception
     */
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
    
    private final FloatProperty wasteValue = new SimpleFloatProperty(0); /** Waste Level, Value Between 0 and 1 */
    private final FloatProperty temperatureValue = new SimpleFloatProperty(0); /** Temperature, Value Between 0 and 1 */
    private BooleanProperty wasteLevelAlarm = new SimpleBooleanProperty(false); /** Alarm when waste level is above 75% */
    private BooleanProperty temperatureAlarm = new SimpleBooleanProperty(false); /** Alarm when temperature is above 30°C */
    
    /**
     * Binding for the waste value
     * 
     * @apiNote The waste value is displayed in percentage
     */
    private final StringBinding wasteValueBinding = new StringBinding() {
        { super.bind(wasteValue); }
        @Override
        protected String computeValue() {
            return String.format("%.1f%%", wasteValue.get() * 100);
        }
    };

    /**
     * Binding for the Temperature Value
     * 
     * @apiNote The Temperature Value is Displayed in Celsius
     */
    private final StringBinding temperatureValueBinding = new StringBinding() {
        { super.bind(temperatureValue); }
        @Override
        protected String computeValue() {
            return String.format("%.1f°C", temperatureValue.get() * 100);
        }
    };

    /**
     * Binding for the Empty Button
     * 
     * @apiNote The Empty Button is Enabled when the Waste Level Alarm is Active
     */
    private final BooleanBinding emptyButtonBinding = new BooleanBinding() {
        { super.bind(wasteLevelAlarm); }
        @Override
        protected boolean computeValue() {
            return !wasteLevelAlarm.get();
        }
    };

    /**
     * Binding for the Restore Button
     * 
     * @apiNote The Restore Button is Enabled when the Temperature Alarm is Active
     */
    private final BooleanBinding restoreButtonBinding = new BooleanBinding() {
        { super.bind(temperatureAlarm); }
        @Override
        protected boolean computeValue() {
            return !temperatureAlarm.get();
        }
    };
    
    /**
     * Update the Color of the Waste Level Bar Based on the Value
     * 
     * @param wasteLevel
     * @apiNote Green if value < 50%
     * @apiNote Orange if value < 75%
     * @apiNote Red if value >= 75%
     */
    private void updateWasteLevelColor(double wasteLevel) {
        String color = "-fx-accent: #00ff00;";

        if (wasteLevel < 0.5) color = "-fx-accent: #00ff00;";
        else if (wasteLevel < 0.75) color = "-fx-accent: #ffa500;";
        else color = "-fx-accent: #ff0000;";

        this.toxicWasteLevel.setStyle(color);
    }
    
    /**
     * Update the Color of the Temperature Bar Based on the Value
     * 
     * @param temperature
     * @apiNote Green if value < 20°C
     * @apiNote Orange if temp < 30°C
     * @apiNote Red if temp >= 30°C
     */
    private void updateTemperatureLevelColor(double temperature) {
        String color = "-fx-accent: #00ff00;";

        if (temperature < 0.2) color = "-fx-accent: #00ff00;";
        else if (temperature < 0.3) color = "-fx-accent: #ffa500;";
        else color = "-fx-accent: #ff0000;";

        this.temperatureLevel.setStyle(color);
    }
    
    /**
     * Sends a Message to the Serial Port to Empty the Waste
     * @see #EMPTY_MESSAGE
     */
    private void emptyWaste() {
        Platform.runLater(() -> {
            this.serialHandler.sendMessage(EMPTY_MESSAGE);
        });
    }

    /**
     * Sends a Message to the Serial Port to Restore the Temperature
     * @see #RESTORE_MESSAGE
     */
    private void restoreTemperature() {
        Platform.runLater(() -> {
            this.serialHandler.sendMessage(RESTORE_MESSAGE);
        });
    }
}