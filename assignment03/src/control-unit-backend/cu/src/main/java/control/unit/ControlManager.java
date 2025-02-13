package control.unit;

import control.unit.TemperatureManager.TemperatureState;
import control.unit.connections.mqtt.MQTTAgent;

import io.vertx.core.Vertx;

public class ControlManager extends Thread {
    private TemperatureState _state;
    private boolean _firstRun = true;
    private long _hotStartTime;

    private Vertx vertx;
    
    private MQTTAgent mqttAgent;

    private TemperatureManager temperatureManager = new TemperatureManager();

    private final static int F1 = 3000;
    private final static int F2 = 1000;

    public ControlManager() throws Exception {
        vertx = Vertx.vertx();
        
        mqttAgent = new MQTTAgent(temperatureManager);

        vertx.deployVerticle(mqttAgent);

        vertx.setPeriodic(1000, id -> this.run());

        _state = TemperatureState.NORMAL;
        
        _hotStartTime = 0;
    }

    public void run() {
        System.out.println("ControlManager running...");

        if(mqttAgent.getClient() == null) {
            System.out.println("MQTT Client Null");
            return;
        }

        switch(_state) {
            case NORMAL: {
                if(temperatureManager.getCurrentTemperature() > 24) {
                    _state = TemperatureState.HOT;
                    System.out.println("Case HOT");
                    mqttAgent.sendFrequency(F2);
                }
                if(_firstRun) {
                    _firstRun = false;
                    mqttAgent.sendFrequency(F1);
                }
                System.out.println("Case NORMAL");
                break;
            }
            case HOT: {
                if(temperatureManager.getCurrentTemperature() <= 24) {
                    _state = TemperatureState.NORMAL;
                    System.out.println("Case NORMAL");
                    mqttAgent.sendFrequency(F1);
                }
                if(temperatureManager.getCurrentTemperature() > 26) {
                    _state = TemperatureState.TOO_HOT;
                    System.out.println("Case TOO HOT");
                    _hotStartTime = 0;
                }
                System.out.println("Case HOT");
                break;
            }
            case TOO_HOT: {
                if(temperatureManager.getCurrentTemperature() <= 26) {
                    _state = TemperatureState.HOT;
                    System.out.println("Case HOT");
                }

                if(_hotStartTime == 0) {
                    _hotStartTime = System.currentTimeMillis();
                }
                else if(temperatureManager.getCurrentTemperature() > 26.4 && (System.currentTimeMillis() - _hotStartTime) >= 3000) {
                    _state = TemperatureState.ALARM;
                    System.out.println("Case ALARM");
                }
                System.out.println("Case TOO HOT");
                break;
            }
            case ALARM: {
                if(temperatureManager.getCurrentTemperature() <= 26.4) {
                    _state = TemperatureState.TOO_HOT;
                    System.out.println("Case TOO HOT");
                    _hotStartTime = 0;
                }
                System.out.println("Case ALARM");
                break;
            }
        }
    }
}