# BLE Transport Notes — Deferred

**Status:** Not the V0.7.0 primary transport.

The current V0.7.0 direction is Wi-Fi SoftAP + WebSocket for audio streaming. This file is retained to preserve the earlier BLE exploration from the first documentation commit.

Do not implement BLE audio streaming as part of the initial V0.7.0 path. BLE may be considered later for low-rate discovery or control if there is a demonstrated need.

The previous draft's GATT audio framing and notification throughput assumptions are not accepted V0.7.0 requirements. Use [WIFI_WEBSOCKET_PROTOCOL.md](WIFI_WEBSOCKET_PROTOCOL.md) for the current protocol proposal.