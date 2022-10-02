#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

float color[3] = { 0.12f, 0.12f, 0.13f };
static sf::Color bgColor;

// ������ ���� ���� �� ������������� ������� ���������
static void setColor(float* pDouble) {
    bgColor.r = static_cast<sf::Uint8>(pDouble[0] * 255.f);
    bgColor.g = static_cast<sf::Uint8>(pDouble[1] * 255.f);
    bgColor.b = static_cast<sf::Uint8>(pDouble[2] * 255.f);
}

// ������� �����
int main() {
    // ������ ���� ��� ���������
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Geometry Project 10");
    // ����� ������� ����������� ����
    window.setFramerateLimit(60);
    // ������������� imgui+sfml
    ImGui::SFML::Init(window);

    // ����� ���� ����
    setColor(color);
    // ���������� �������
    sf::Clock deltaClock;
    // ���� ���� �������, ��������� ����������� ����
    while (window.isOpen()) {
        // ������ ������� sfml
        sf::Event event;
        // ���� ���� ��������� �������
        while (window.pollEvent(event)) {
            // ���������� ������� �� ��������� sfml
            ImGui::SFML::ProcessEvent(event);

            // ���� ������� - ��� �������� ����
            if (event.type == sf::Event::Closed) {
                // ��������� ����
                window.close();
            }
        }

        // ��������� ���������� ���� �� ������� � �������� ��������
        ImGui::SFML::Update(window, deltaClock.restart());
        // ������ ������ ���� ����������
        ImGui::Begin("Control");
        // ���������� ������ �����
        if (ImGui::ColorEdit3("Background color", color)) {
            // ��� ���������� ��� ��������� ��������
            // ����� ���� ����
            setColor(color);
        }
        // ����� ��������� ����
        ImGui::End();
        // ������ ���������������� ����

        // ������� ����
        window.clear(bgColor);
        // ������ �� ���� ���������� imgui+sfml
        ImGui::SFML::Render(window);
        // ���������� ��������� �� ����
        window.display();
    }

    // ��������� ������ imgui+sfml
    ImGui::SFML::Shutdown();

    return 0;
}