import smbus2
import bme280
import datetime

port = 1
address = 0x77
bus = smbus2.SMBus(port)

calibration_params = bme280.load_calibration_params(bus, address)

# the sample method will take a single reading and return a
# compensated_reading object
data = bme280.sample(bus, address, calibration_params)

timestamp = datetime.datetime.today().replace(microsecond=0)
output_str = "{}:   Temp = {:.2f} {}C   Humidity = {:.2f} %   Pressure = {:.2f} psi"
print(output_str.format(timestamp, data.temperature, u"\N{DEGREE SIGN}", data.humidity, data.pressure))

