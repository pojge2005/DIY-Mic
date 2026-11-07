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


async def run_test(address, listen_seconds):
    async with BleakClient(address) as client:
        print(f"Connected: {client.is_connected}")

        status = await client.read_gatt_char(STATUS_UUID)
        show_data("STATUS", status)

        await client.start_notify(
            STATUS_UUID,
            lambda _, data: show_data("STATUS NOTIFY", data),
        )
        await client.start_notify(
            AUDIO_UUID,
            lambda _, data: show_data("AUDIO NOTIFY", data),
        )

        await client.write_gatt_char(CONTROL_UUID, b"PING", response=True)
        print("Control write: completed")

        print(f"Listening for notifications for {listen_seconds} seconds...")
        await asyncio.sleep(listen_seconds)

        await client.stop_notify(STATUS_UUID)
        await client.stop_notify(AUDIO_UUID)


def main():
    parser = argparse.ArgumentParser(description="DIY-Mic ESP32-S3 BLE test")
    parser.add_argument("--address", required=True, help="BLE peripheral address")
    parser.add_argument("--listen-seconds", type=float, default=10)
    args = parser.parse_args()

    asyncio.run(run_test(args.address, args.listen_seconds))


if __name__ == "__main__":
    main()
