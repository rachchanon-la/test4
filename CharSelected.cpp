#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

struct Character {
    std::string name;
    std::string job;
    int hp;
    bool isSelected = false;

    Character(std::string n, std::string j, int h) : name(n), job(j), hp(h) {}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Party Selection - Turn Based Game");
    sf::Font font;
    
    // อย่าลืมโหลด Font (ในเครื่องต้องมีไฟล์ .ttf)
    if (!font.loadFromFile("arial.ttf")) return -1;

    // สร้างตัวละคร 6 ตัว
    std::vector<Character> pool = {
        {"Arthur", "KNIGHT", 150}, {"Robin", "ARCHER", 100},
        {"Morgana", "MAGE", 80},   {"Braum", "TANK", 250},
        {"Mercy", "SUPPORT", 90},  {"Joker", "SPECIAL", 110}
    };

    std::vector<Character> party;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // ตรวจสอบการคลิกเมาส์
            if (event.type == sf::Event::MouseButtonPressed && party.size() < 3) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                // ตรวจเช็คว่าคลิกโดนบรรทัดไหน (Logic แบบง่าย)
                for (int i = 0; i < pool.size(); ++i) {
                    if (mousePos.y > 50 + (i * 40) && mousePos.y < 90 + (i * 40) && !pool[i].isSelected) {
                        pool[i].isSelected = true;
                        party.push_back(pool[i]);
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        // วาดรายการตัวละคร 6 คน
        for (int i = 0; i < pool.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setPosition(50, 50 + (i * 40));
            text.setString(std::to_string(i+1) + ". " + pool[i].name + " [" + pool[i].job + "]");
            
            // ถ้าเลือกแล้วให้เปลี่ยนเป็นสีเทา
            text.setFillColor(pool[i].isSelected ? sf::Color(100, 100, 100) : sf::Color::White);
            window.draw(text);
        }

        // วาดรายชื่อ Party ที่เลือกแล้ว
        sf::Text status;
        status.setFont(font);
        status.setPosition(400, 50);
        status.setString("Your Party (" + std::to_string(party.size()) + "/3):");
        window.draw(status);

        for (int i = 0; i < party.size(); ++i) {
            sf::Text pMember;
            pMember.setFont(font);
            pMember.setCharacterSize(20);
            pMember.setPosition(400, 100 + (i * 30));
            pMember.setFillColor(sf::Color::Cyan);
            pMember.setString("- " + party[i].name);
            window.draw(pMember);
        }

        window.display();
    }

    return 0;
}