from serial import Serial
import json

def send_message(json_data):
    pass


def main():
    arduino = Serial('/dev/ttyACM0', 9600)
    
    # first line is garbage
    arduino.readline()

    while True:
        line = arduino.readline().decode('utf-8').strip()

        values = line.split()

        dict = {
            'ppm': values[0],
            'airHumidity': values[1],
            'temperature': values[2],
            'soilHumidity': values[3],
        }

        send_message(json.dumps(dict))


if __name__ == "__main__":
    main()
