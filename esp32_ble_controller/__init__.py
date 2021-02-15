import esphome.codegen as cg
import esphome.config_validation as cv
# from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ['@wifwucite']
# DEPENDENCIES = ['i2c']
# AUTO_LOAD = ['sensor', 'text_sensor']
# MULTI_CONF = True

# CONF_BME680_BSEC_ID = 'bme680_bsec_id'
# CONF_TEMPERATURE_OFFSET = 'temperature_offset'
# CONF_IAQ_MODE = 'iaq_mode'
# CONF_SAMPLE_RATE = 'sample_rate'
# CONF_STATE_SAVE_INTERVAL = 'state_save_interval'

esp32_ble_controller_ns = cg.esphome_ns.namespace('esp32_ble_controller')

# IAQMode = esp32_ble_controller_ns.enum('IAQMode')
# IAQ_MODE_OPTIONS = {
#     'STATIC': IAQMode.IAQ_MODE_STATIC,
#     'MOBILE': IAQMode.IAQ_MODE_MOBILE,
# }

# SampleRate = esp32_ble_controller_ns.enum('SampleRate')
# SAMPLE_RATE_OPTIONS = {
#     'LP': SampleRate.SAMPLE_RATE_LP,
#     'ULP': SampleRate.SAMPLE_RATE_ULP,
# }

ESP32BLEController = esp32_ble_controller_ns.class_('ESP32BLEController', cg.Component, cg.Controller)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ESP32BLEController),
    #cv.Optional(CONF_TEMPERATURE_OFFSET, default=0): cv.temperature,
    # cv.Optional(CONF_IAQ_MODE, default='STATIC'):
    #     cv.enum(IAQ_MODE_OPTIONS, upper=True),
    # cv.Optional(CONF_SAMPLE_RATE, default='LP'):
    #     cv.enum(SAMPLE_RATE_OPTIONS, upper=True),
    # cv.Optional(CONF_STATE_SAVE_INTERVAL, default='6hours'): cv.positive_time_period_minutes,
})#.extend(i2c.i2c_device_schema(0x76))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    # yield i2c.register_i2c_device(var, config)

    # cg.add(var.set_temperature_offset(config[CONF_TEMPERATURE_OFFSET]))
    # cg.add(var.set_iaq_mode(config[CONF_IAQ_MODE]))
    # cg.add(var.set_sample_rate(config[CONF_SAMPLE_RATE]))
    # cg.add(var.set_state_save_interval(config[CONF_STATE_SAVE_INTERVAL].total_milliseconds))

    # cg.add_build_flag('-DUSING_BSEC')
    # cg.add_library('BSEC Software Library', '1.6.1480')