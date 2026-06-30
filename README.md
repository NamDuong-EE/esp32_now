# ESP32 ESP-NOW Long Range

Dự án ESP-NOW sử dụng chế độ Long Range (LR) với tính năng test băng thông và packet loss.

## Cách sử dụng:
- Nạp `sketch_esp32_gui.ino` vào ESP32 **gửi**
- Nạp `sketch_jesp32_nhan.ino` vào ESP32 **nhận**

## Kết nối WiFi xem debug:
- SSID: `ESP32_DEBUG`
- Password: `12345678`
- Mở trình duyệt: http://192.168.4.1

## Test băng thông:
1. Kết nối Serial Monitor vào ESP32 **gửi** (115200 baud)
2. Gõ lệnh:
   - `test` → Gửi 100 gói test
   - `test 500` → Gửi 500 gói test (tối đa 10000)
3. Kết quả hiển thị trên:
   - **Serial Monitor** (cả bên gửi và nhận)
   - **Trang web** http://192.168.4.1 (bên nhận)

## Thông số đo được:
| Thông số | Mô tả |
|----------|--------|
| Packet Loss | Tỷ lệ gói bị mất (%) |
| Throughput | Băng thông (KB/s) |
| Packets/sec | Số gói mỗi giây |
| RSSI | Cường độ tín hiệu (dBm) |
| RSSI Min/Max | Khoảng dao động RSSI |

## Lưu ý:
- ESP-NOW LR Mode giảm tốc độ nhưng tăng tầm xa (~1km)
- Cả 2 board đều phải bật LR mode
- AP phát WiFi thường (11b/g/n) để điện thoại kết nối xem debug
- Nhấn nút **Reset Test** trên web để xóa kết quả cũ

## Tham khảo:
- [ESP-NOW Tutorial](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/)
- [ESP-IDF WiFi Protocol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html)
