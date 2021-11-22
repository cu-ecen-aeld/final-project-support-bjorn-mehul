import time
import paho.mqtt.publish as publish

MQTT_SERVER = "192.168.0.195"
MQTT_PATH = "test_channel"

def main():
    print("Hello World! ~Client")
    i = 0

    while (1):
        publish.single(MQTT_PATH, "I2C Data publish", hostname=MQTT_SERVER)
        i = i + 1
        print("Data publshed " + i)
        time.sleep(5)

if __name__ == "__main__":
    main()