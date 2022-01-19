import csv
from datetime import datetime
import os
from rovecomm_module.rovecomm import RoveComm, get_manifest

type_mapping = {
    0: "Commands",
    1: "Telemetry",
    2: "Error",
}


class BlackBox:
    def __init__(self):
        timestamp = datetime.now().strftime("%Y%m%d-%H%M%S")
        dt = datetime.today()
        path = f"./logs/{dt.year}/{dt.month}/{dt.day}/"

        os.makedirs(path, exist_ok=True)
        self.csv_file = open(path + f"{timestamp}.csv", "w", newline="")

        # Setting up writer and csv header
        self.fieldnames = ["timestamp", "board", "ip", "data id", "data id name", "data type", "data count", "data"]
        self.writer = csv.DictWriter(self.csv_file, fieldnames=self.fieldnames)
        self.writer.writeheader()

        self.manifest = get_manifest()

    def subscribe_all(self, rovecomm_node: RoveComm):
        # UDP Subscribe to all boards listed in the manifest
        for board in self.manifest:
            rovecomm_node.udp_node.subscribe(self.manifest[board]["Ip"])

    def log_packets(self, packet):
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        boardName = "N/A"
        dataIdName = "N/A"

        for board in self.manifest:
            if self.manifest[board]["Ip"] == packet.ip_address[0]:
                boardName = board

                # The type of the data id is specified by the 100s place
                # (mapped in type_mapping) unless it is a system level packet
                if len(str(packet.data_id)) >= 3:
                    idtype = type_mapping[int(str(packet.data_id)[-3])]
                else:
                    continue

                for dataID in self.manifest[board][f"{idtype}"]:
                    if self.manifest[board][f"{idtype}"][dataID]["dataId"] == packet.data_id:
                        dataIdName = dataID

        self.writer.writerow(
            {
                "timestamp": f"{timestamp}",
                "board": f"{boardName}",
                "ip": f"{packet.ip_address[0]}",
                "data id": f"{packet.data_id}",
                "data id name": f"{dataIdName}",
                "data type": f"{packet.data_type}",
                "data count": f"{packet.data_count}",
                "data": f"{packet.data}",
            }
        )

    def close(self):
        self.csv_file.close()


black_box = BlackBox()
