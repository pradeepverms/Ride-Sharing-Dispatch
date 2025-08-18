#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

class Message {
private:
    std::string sender;
    std::string content;
    std::time_t timestamp;
public:
    Message(const std::string& sender, const std::string& content)
        : sender(sender), content(content), timestamp(std::time(nullptr)) {}

    void display() const {
        std::cout << "[" << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S") << "] "
                  << sender << ": " << content << std::endl;
    }
};

class Chat {
private:
    std::vector<Message> messages;
public:
    void sendMessage(const std::string& sender, const std::string& content) {
        messages.emplace_back(sender, content);
    }
    void displayChat() const {
        std::cout << "Chat History:" << std::endl;
        for (const auto& message : messages)
            message.display();
    }
};

int main() {
    Chat chat;
    chat.sendMessage("Alice", "Hello, Bob!");
    chat.sendMessage("Bob", "Hi Alice! How are you?");
    chat.sendMessage("Alice", "I'm good, thanks! What about you?");
    chat.sendMessage("Bob", "Doing well, just working on some projects.");

    chat.displayChat();
    return 0;
}