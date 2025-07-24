#include <iostream>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS = "tcp://39.108.140.117:1883";
const std::string CLIENT_ID = "cpp_demo_client"; // 确保每个客户端都有唯一的ID
const std::string USERNAME = "admin";
const std::string PASSWORD = "1qaz@4321";
const std::string TOPIC = "drone/device/861556077125838/osd";

class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        std::cout << "收到消息: " << msg->get_topic() << " -> " << msg->to_string() << std::endl;
    }
};

int main() {
    try {
        mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
        Callback cb;

        // 设置连接选项
        mqtt::connect_options conn_opts;
        conn_opts.set_clean_session(true);
        conn_opts.set_user_name(USERNAME);
        conn_opts.set_password(PASSWORD);

        // 设置回调函数
        client.set_callback(cb);

        std::cout << "正在连接服务器..." << std::endl;
        client.connect(conn_opts)->wait();
        std::cout << "已成功连接！" << std::endl;

        // 订阅主题
        client.subscribe(TOPIC, 1)->wait();
        std::cout << "已订阅主题: " << TOPIC << std::endl;

        // 这里可以添加一个简单的循环，保持程序运行以便持续接收消息
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
    catch (const mqtt::exception& exc) {
        std::cerr << "MQTT 错误: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}