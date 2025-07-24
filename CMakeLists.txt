cmake_minimum_required(VERSION 3.14)
project(mqtt_cpp)

# 只需要 find PahoMqttCpp，后者会自动包含 paho-mqtt（C）
find_package(PahoMqttCpp REQUIRED)

# 自定义变量，指向你的 lib 文件
set(PAHO_LIBRARY "D:/dev/vcpkg/installed/x64-windows/debug/lib/paho-mqtt3a.lib")


add_executable(mqtt_cpp main.cpp)

target_link_libraries(mqtt_cpp
    PRIVATE
    PahoMqttCpp::paho-mqttpp3
    ${PAHO_LIBRARY}
)
