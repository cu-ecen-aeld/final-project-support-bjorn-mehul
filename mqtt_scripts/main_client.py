import time
import paho.mqtt.publish as publish
import os

# Server (Subscriber) = Yocto RasPi 4 - 192.168.0.232
# Client (Publisher) = Buildroot RasPi 3 - 192.168.0.195

MQTT_SERVER = "192.168.0.232"
MQTT_PATH = "image_transfer"

def main():
    print("Hello World! ~Client")

    while True:
        os.system("raspistill -w 1280 -h 960 -o cur.jpg")
        f=open("cur.jpg", "rb")
        fileContent = f.read()
        byteArr = bytearray(fileContent)
        publish.single(MQTT_PATH, byteArr, hostname=MQTT_SERVER)
        print("Sent image")
        time.sleep(7)

if __name__ == "__main__":
    main()