#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

// ������� �����
int main() {
    // ������ ���� ��� ���������
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ImGui + SFML = <3");
    // ����� ������� ����������� ����
    window.setFramerateLimit(60);
    // ������������� imgui+sfml
    ImGui::SFML::Init(window);

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

        // ������ ���������������� ����
        ImGui::ShowDemoWindow();

        // ������� ����
        window.clear();
        // ������ �� ���� ���������� imgui+sfml
        ImGui::SFML::Render(window);
        // ���������� ��������� �� ����
        window.display();
    }

    // ��������� ������ imgui+sfml
    ImGui::SFML::Shutdown();

    return 0;
}