import time
import paho.mqtt.client as mqtt
import subprocess
import os
import shutil

# Server (Subscriber) = Yocto RasPi 4 - 192.168.0.232
# Client (Publisher) = Buildroot RasPi 3 - 192.168.0.195

MQTT_SERVER = "localhost"
MQTT_PATH = "image_transfer"
connection_status = 0

# The callback for when the client receives a connect response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # on_connect() means that if we lose the connection and reconnect then subscriptions will be renewed.
    client.subscribe(MQTT_PATH)
    connection_status = 1

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    f = open('test_recv.jpg', "wb")
    f.write(msg.payload)
    #print("Image Received")
    f.close()

def main():
    print("Hello World! ~Server")

    os.makedirs("captures", exist_ok=True)
    os.makedirs("captures/cam1", exist_ok=True)
    os.makedirs("captures/cam2", exist_ok=True)

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(MQTT_SERVER, 1883, 60)

    client.loop_start()

    img_id = 0
    while True:
        subprocess.call("capture", stdout=subprocess.DEVNULL)

        # open image from server
        proc1 = subprocess.Popen(['display', 'test.jpg'])

        # open image from client
        proc2 = subprocess.Popen(['display', 'test_recv.jpg'])

        for i in range(0, 10):
            os.system("python3 /usr/bin/read_bme280.py")
            time.sleep(1)
        
        proc1.terminate()
        proc2.terminate()

        # archive the current images
        filename = "img" + str(img_id) + ".jpg"

        # copy and rename current server picture
        src1 = "test.jpg"
        dest1 = "captures/cam1/" + filename
        shutil.copyfile(src1, dest1)

        # copy and rename current client picture
        src2 = "test_recv.jpg"
        dest2 = "captures/cam2/" + filename
        shutil.copyfile(src2, dest2)

        img_id += 1

if __name__ == "__main__":
    main()