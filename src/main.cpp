#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <fstream>

// ������ ���������
static const int SET_1 = 0;
// ������ ���������
static const int SET_2 = 1;
// ����������� ��������
static const int SET_CROSSED = 2;
// �������� ��������
static const int SET_SINGLE = 3;

// ������ ����
static const int WINDOW_SIZE_X = 800;
// ������ ����
static const int WINDOW_SIZE_Y = 800;

// �����
struct Point {
    // ���������
    sf::Vector2i pos;
    // ����� ���������
    int setNum;

    // �����������
    Point(const sf::Vector2i& pos, int setNum) : pos(pos), setNum(setNum) {
    }

    static Point randomPoint() {
        return Point(sf::Vector2i(
            rand() % WINDOW_SIZE_X,
            rand() % WINDOW_SIZE_Y),
            rand() % 2
        );
    }
};

// ������������ ������ �����
std::vector<Point> points;

// ���� ����
static sf::Color bgColor;
// �������� ����� �� ���������
float color[3] = { 0.12f, 0.12f, 0.13f };

// �����, �������� ���������� ��������� ����������� �������
int lastAddPosBuf[2] = { 0, 0 };

// ����� ���-�� ��������� �����
int lastRandoCntBuf[1] = { 10 };

// ���� � ����� ������
static const char OUTPUT_PATH[255] = "D:/out.txt";
// ���� � ����� �����
static const char INPUT_PATH[255] = "D:/in.txt";

// ������ ���� ���� �� ������������� ������� ���������
static void setColor(float* pDouble) {
    bgColor.r = static_cast<sf::Uint8>(pDouble[0] * 255.f);
    bgColor.g = static_cast<sf::Uint8>(pDouble[1] * 255.f);
    bgColor.b = static_cast<sf::Uint8>(pDouble[2] * 255.f);
}

// ��������� ���������� �����
void ShowBackgroundSetting() {
    if (!ImGui::CollapsingHeader("Background"))
        return;
    // ���������� ������ �����
    if (ImGui::ColorEdit3("Background color", color)) {
        // ��� ���������� ��� ��������� ��������
        // ����� ���� ����
        setColor(color);
    }
    // ����� ��������� ����
}



// ��������� ������ �� ��������� ���� �� �� ���� ����������
void RenderTask() {
    // ����� ����� ������� ���� ���������� ����
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    // ����� ������ ������ ���� ���������� ����
    ImGui::SetNextWindowSize(ImVec2(WINDOW_SIZE_X, WINDOW_SIZE_Y));
    // ������ ��������� ����
    ImGui::Begin("Overlay", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
    // �������� ������ ����������, ������� ����� ����������
    auto pDrawList = ImGui::GetWindowDrawList();

    // ���������� ����� �� ������������� ������� �����
    for (auto point : points) {
        ImColor clr;
        // ������������� ���� �� ������ ���������
        switch (point.setNum) {
        case SET_1:
            clr = ImColor(200, 100, 150);
            break;
        case SET_2:
            clr = ImColor(100, 200, 150);
            break;
        case SET_CROSSED:
            clr = ImColor(100, 150, 200);
            break;
        case SET_SINGLE:
            clr = ImColor(150, 200, 100);
            break;
        }
        // ��������� � ������ ��������� ����
        pDrawList->AddCircleFilled(
            sf::Vector2i(point.pos.x, point.pos.y),
            3,
            clr,
            20
        );
    }
    // ����������� ��������� ����
    ImGui::End();
}

// ������ ���������� ���������
void ShowAddElem() {
    // ���� �� �������� ������ `Add Elem`
    if (!ImGui::CollapsingHeader("Add Elem"))
        // ����������� ����������
        return;


    // ���������� ������ �����
    if (ImGui::DragInt2("Coords", lastAddPosBuf)) {
        // ������� �������� �� ���������, ����������
        // ��� ��������� ������, ������� imGui ���������
        // �������������
    }

    // ��������� id ������ 0 ��� ������� ��������
    ImGui::PushID(0);
    // ���� ������ ������ `Set 1`
    if (ImGui::Button("Set 1"))
        // ��������� �� ��������� � ������ �����, ������������� ������� ���������
        points.emplace_back(Point(sf::Vector2i(lastAddPosBuf[0], lastAddPosBuf[1]), SET_1));
    // ��������������� ����� id
    ImGui::PopID();

    // ������� imGui, ��� ��������� ������� ����� �������� �� ��� �� �����
    ImGui::SameLine();
    // ����� id, ������ ������
    ImGui::PushID(1);
    // ���� ������ ������ `Set 2`
    if (ImGui::Button("Set 2"))
        // ��������� �� ��������� � ������ �����, ������������� ������� ���������
        points.emplace_back(Point(sf::Vector2i(lastAddPosBuf[0], lastAddPosBuf[1]), SET_2));
    // ��������������� ����� id
    ImGui::PopID();

}

// �������� �������� ���-�� ��������� �����
void randomize(int cnt) {
    for (int i = 0; i < cnt; i++) {
        points.emplace_back(Point::randomPoint());
    }
}

// ������ ���������� ��������� �����
void ShowRandomize() {
    // ���� �� �������� ������ `Randomize`
    if (!ImGui::CollapsingHeader("Randomize"))
        // ����������� ����������
        return;

    // ������ ������� � ������
    ImGui::PushID(0);

    // ���������� ������ ���-��
    if (ImGui::DragInt("Count", lastRandoCntBuf, 0.1, 0, 100)) {

    }
    // ��������������� ������ id
    ImGui::PopID();
    // ��������� ������� ����� �� ��� �� �������
    ImGui::SameLine();
    // ������ �������
    ImGui::PushID(1);
    // ������ ������ ����������
    if (ImGui::Button("Add"))
        // �� ����� ��������� �������� ����� ��������� �����
        randomize(lastRandoCntBuf[0]);
    ImGui::PopID();
}

// �������� �� �����
void loadFromFile() {
    // ��������� ����� ������ ��� ������ �� �����
    std::ifstream input(INPUT_PATH);
    // ������� ������ �����
    points.clear();
    // ���� �� ��������� ����� �����
    while (!input.eof()) {
        int x, y, s;
        input >> x; // ������ x ����������
        input >> y; // ������ y ����������
        input >> s; // ������ ����� ���������
        // ��������� � ������������ ������ ����� �� ������ ����������� ������
        points.emplace_back(Point(sf::Vector2i(x, y), s));
    }
    // ��������� ����
    input.close();
}

// ������ � ����
void saveToFile() {
    // ��������� ����� ������ ��� ������ � ����
    std::ofstream output(OUTPUT_PATH);

    // ���������� �����
    for (auto point : points) {
        // ������� ����� ������ ���������: x-����������, y-���������� � ����� ���������
        output << point.pos.x << " " << point.pos.y << " " << point.setNum << std::endl;
    }

    // ���������
    output.close();
}

// ������ � �������
void ShowFiles() {
    // ���� �� �������� ������ `Files`
    if (!ImGui::CollapsingHeader("Files"))
        // ����������� ����������
        return;

    // ������ ������� � �����
    ImGui::PushID(0);
    // ������ ������ ��������
    if (ImGui::Button("Load")) {
        // ��������� ������ �� �����
        loadFromFile();
    }
    // ��������������� ����� id
    ImGui::PopID();

    // ��������� ������� ����� �� ��� �� �������
    ImGui::SameLine();
    // ������ �������
    ImGui::PushID(1);
    // ������ ������ ����������
    if (ImGui::Button("Save")) {
        // ��������� ������ � ����
        saveToFile();
    }
    // ��������������� ����� id
    ImGui::PopID();
}

// ������� ������
void solve() {
    // � ����������� �� ����������� ����� ������ ��������� �� SET_CROSSED
    for (int i = 0; i < points.size(); i++)
        for (int j = i + 1; j < points.size(); j++)
            if (points[i].pos == points[j].pos)
                points[i].setNum = points[j].setNum = SET_CROSSED;

    // � ���� �����, � ������� ��������� �� SET_CROSSED, ����� ��������� SET_SINGLE
    for (auto& point : points)
        if (point.setNum != SET_CROSSED)
            point.setNum = SET_SINGLE;

}

// ������� ������
void ShowSolve() {
    // ���� �� �������� ������ `Solve`
    if (!ImGui::CollapsingHeader("Solve"))
        return;
    // ������ ������� � �����
    ImGui::PushID(0);
    // ������ ������ �������
    if (ImGui::Button("Solve")) {
        solve();
    }

    // ��������������� ����� id
    ImGui::PopID();

    // ��������� ������� ����� �� ��� �� �������
    ImGui::SameLine();
    // ������ �������
    ImGui::PushID(1);

    // ������ ������ �������
    if (ImGui::Button("Clear")) {
        // ������� ��� �����
        points.clear();
    }
    // ��������������� ����� id
    ImGui::PopID();
}

// ������� �����
int main() {
    // ������ ���� ��� ���������
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Geometry Project 10");
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



            // ���� ������� - ��� ���� �����
            if ((event.type == sf::Event::MouseButtonPressed) && (!ImGui::GetIO().WantCaptureMouse)) {
                // ���� ����� ������ ����
                lastAddPosBuf[0] = event.mouseButton.x;
                lastAddPosBuf[1] = event.mouseButton.y;
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    points.emplace_back(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), SET_1);
                else
                    points.emplace_back(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), SET_2);
            }

            // ���� ������� - ��� �������� ����
            if (event.type == sf::Event::Closed) {
                // ��������� ����
                window.close();
            }
        }

        // ��������� ���������� ���� �� ������� � �������� ��������
        ImGui::SFML::Update(window, deltaClock.restart());

        // ��������� �������
        RenderTask();

        // ������ ���� ��������������
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12f, 0.12f, 0.13f, 0.8f));

        // ������ ���� ����������
        ImGui::Begin("Control");

        // ��������� ���������� �����
        ShowBackgroundSetting();

        // ������ ���������� ���������
        ShowAddElem();
        ShowRandomize();
        ShowFiles();
        ShowSolve();

        // ����� ��������� ����
        ImGui::End();

        // ���������� ���� ���� � ���������
        ImGui::PopStyleColor();

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