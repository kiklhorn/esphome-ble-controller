#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <BLEServer.h>

#include "esphome/core/component.h"
#include "esphome/core/controller.h"
#include "esphome/core/defines.h"
#include "esphome/core/preferences.h"

#include "ble_component_handler_base.h"

using std::string;
using std::unordered_map;
using std::vector;

namespace esphome {
namespace esp32_ble_controller {

class BLEMaintenanceHandler;

enum class BLEMaintenanceMode : uint8_t { BLE_ONLY, MIXED, WIFI_ONLY };

/**
 * Bluetooth Low Energy controller for ESP32.
 * @brief BLE controller for ESP32
 */
class ESP32BLEController : public Component, public Controller {
public:
  void register_component(Nameable* component, const string& serviceUUID, const string& characteristicUUID, bool useBLE2902 = true);

  float get_setup_priority() const override { return setup_priority::PROCESSOR; }

  void setup() override;

  void dump_config() override;

  inline BLEMaintenanceMode get_ble_mode() const { return bleMode; }
  void set_ble_mode(BLEMaintenanceMode mode);
  void set_ble_mode(uint8_t mode);

  // Controller methods:
#ifdef USE_BINARY_SENSOR
  void on_binary_sensor_update(binary_sensor::BinarySensor *obj, bool state) override;
#endif
#ifdef USE_COVER
  void on_cover_update(cover::Cover *obj) override;
#endif
#ifdef USE_FAN
  void on_fan_update(fan::FanState *obj) override;
#endif
#ifdef USE_LIGHT
  void on_light_update(light::LightState *obj) override;
#endif
#ifdef USE_SENSOR
  void on_sensor_update(sensor::Sensor *obj, float state) override;
#endif
#ifdef USE_SWITCH
  void on_switch_update(switch_::Switch *obj, bool state) override;
#endif
#ifdef USE_TEXT_SENSOR
  void on_text_sensor_update(text_sensor::TextSensor *obj, std::string state) override;
#endif
#ifdef USE_CLIMATE
  void on_climate_update(climate::Climate *obj) override;
#endif

private:
  void initialize_ble_mode();

  bool setup_ble();
  void setup_ble_services();
  void setup_ble_services_for_components();
  template <typename C> void setup_ble_services_for_components(const vector<C*>& components, BLEComponentHandlerBase* (*handler_creator)(C*, const BLECharacteristicInfoForHandler&));
  template <typename C> void setup_ble_service_for_component(C* component, BLEComponentHandlerBase* (*handler_creator)(C*, const BLECharacteristicInfoForHandler&));
  template <typename C, typename S> void update_component_state(C* component, S state);

private:
  BLEServer* bleServer;

  BLEMaintenanceMode bleMode;
  ESPPreferenceObject bleModePreference;

  BLEMaintenanceHandler* maintenanceHandler;

  unordered_map<string, BLECharacteristicInfoForHandler> infoForComponent;
  unordered_map<string, BLEComponentHandlerBase*> handlerForComponent;
};

/**
 * The BLE controller singleton.
 */
extern ESP32BLEController* global_ble_controller;

} // namespace esp32_ble_controller
} // namespace esphome