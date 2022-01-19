import time
from rovecomm_module.rovecomm import RoveComm, get_manifest, RoveCommPacket
from enum import Enum
import lighting
import threading
import queue
from blackbox import black_box
import serial

# Get rovecomm manifest
manifest = get_manifest()

# Initialize rovecomm
rovecomm_node = RoveComm(11000, ("", manifest["Multimedia"]["Port"]))
q = queue.Queue()

def sensor_loop(q):
    ser = serial.Serial('/dev/ttyACM0', 9600)

    data = ""
    count = 0
    while True:
        data = ser.read_until().decode("utf-8")	
        print(data)
        con_per = data[data.find("C:")+3 : data.find("%")]
        print(con_per)
        try:
            con_per = float(con_per)
            q.put(con_per)
        except ValueError:
            pass
        
if __name__ == "__main__":
    # Default to showing no color
    lighting.clear_lights()
    sensor_thread = threading.Thread(target=sensor_loop,args=(q,))
    sensor_thread.start()
    # Subscribe to all available boards
    black_box.subscribe_all(rovecomm_node)

    # Start up blackbox logging to be default rovecomm callback
    rovecomm_node.set_default_callback(black_box.log_packets)

    # Set up the callbacks
    rovecomm_node.set_callback(manifest["Multimedia"]["Commands"]["LEDRGB"]["dataId"], lighting.handle_lighting_commands)
    rovecomm_node.set_callback(manifest["Multimedia"]["Commands"]["LEDPatterns"]["dataId"], lighting.handle_lighting_commands)
    rovecomm_node.set_callback(manifest["Multimedia"]["Commands"]["StateDisplay"]["dataId"], lighting.handle_lighting_commands)

    while True:
        # Keep light panel running
        #print("Running lighting")
        lighting.run_lighting()
        if not q.empty():
            concentration = q.get()
            packet = RoveCommPacket(manifest["ScienceSensors"]["Telemetry"]["Methane"]["dataId"], "f", (concentration,))
            rovecomm_node.write(packet, False)
        

    
