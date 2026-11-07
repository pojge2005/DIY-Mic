import argparse
import asyncio

from bleak import BleakClient

STATUS_UUID = "7b3a0002-6d7b-4f21-9a11-6e4d594d4943"
CONTROL_UUID = "7b3a0003-6d7b-4f21-9a11-6e4d594d4943"
AUDIO_UUID = "7b3a0004-6d7b-4f21-9a11-6e4d594d4943"


def show_data(label, data):
    raw = bytes(data)
    print(f"{label}: {raw.hex(' ')}")
    print(f"{label} ASCII: {raw.decode('ascii', errors='replace')}")


def notification(label):
    return lambda _, data: show_data(label, data)


async def run_test(address, listen_seconds):
    async with BleakClient(address) as client:
        print(f"Connected: {client.is_connected}")

        status = await client.read_gatt_char(STATUS_UUID)
        show_data("STATUS", status)

        services = client.services
        status_char = services.get_characteristic(STATUS_UUID)
        control_char = services.get_characteristic(CONTROL_UUID)
        audio_char = services.get_characteristic(AUDIO_UUID)

        if status_char and "notify" in status_char.properties:
            await client.start_notify(STATUS_UUID, notification("STATUS NOTIFY"))

        if audio_char and "notify" in audio_char.properties:
            await client.start_notify(AUDIO_UUID, notification("AUDIO NOTIFY"))
        else:
            print("Audio notifications are not supported by this characteristic.")

        if not control_char:
            raise RuntimeError("Control characteristic was not found.")

        response = "write" in control_char.properties
        if not response and "write-without-response" not in control_char.properties:
            raise RuntimeError("Control characteristic does not support writing.")

        await client.write_gatt_char(CONTROL_UUID, b"PING", response=response)
        print("Control write completed: PING")

        print(f"Listening for {listen_seconds} seconds...")
        await asyncio.sleep(listen_seconds)


def main():
    parser = argparse.ArgumentParser(description="DIY-Mic ESP32-S3 BLE test")
    parser.add_argument("--address", required=True, help="BLE peripheral address")
    parser.add_argument("--listen-seconds", type=float, default=10)
    args = parser.parse_args()

    asyncio.run(run_test(args.address, args.listen_seconds))


if __name__ == "__main__":
    main()
