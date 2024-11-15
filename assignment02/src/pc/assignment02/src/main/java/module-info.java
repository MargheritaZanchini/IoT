module assignment02 {
    requires javafx.controls;
    requires javafx.fxml;
    requires transitive javafx.graphics;

    opens assignment02 to javafx.fxml;
    exports assignment02;
}
