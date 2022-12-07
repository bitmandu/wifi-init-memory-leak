# wifi-init-memory-leak

This example ESP-IDF application relates to [issue
#8446][8446], and demonstrates a memory leak using the `esp_wifi_init()` and `esp_wifi_deinit()` functions.

## Configuration

    $ idf.py menuconfig

From the `Component config` ⇨ `Heap memory debugging`⇨ `Heap tracing`
menu, select `Standalone`.

## Output

    664 bytes 'leaked' in trace (13 allocations)
    total allocations 64 total frees 68


[8446]: https://github.com/espressif/esp-idf/issues/8446
