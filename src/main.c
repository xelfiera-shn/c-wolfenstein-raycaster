#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "macros.h"
#include "map.h"
#include "player.h"

void framebufferSizeCallback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void clearDisplay();
void renderView(Player* p);
void renderMinimap(Player* p);
void handleInput(GLFWwindow* w, Player* p);

int main(int argc, const char* argv[]) {
    if (!glfwInit()) return 0;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Ray Casting", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Player player;
    player.Pos.x = 200.f;
    player.Pos.y = 300.f;
    player.Angle = PI / 2.f;

    while (!glfwWindowShouldClose(window)) {
        clearDisplay();
        renderMinimap(&player);

        // renderView(&player);
        
        handleInput(window, &player);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void clearDisplay() {
    glClearColor(0.45f, 0.45f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderView(Player* p) {

}

void renderMinimap(Player* p) {
    int w = DISPLAY_WIDTH * MINIMAP_WIDTH_RATIO;
    int h = DISPLAY_HEIGHT * MINIMAP_HEIGHT_RATIO;
    int sx = DISPLAY_WIDTH - w;
    int sy = DISPLAY_HEIGHT - h;

    glColor3f(0.24f, 0.24f, 0.36f);
    glBegin(GL_QUADS);
    glVertex2i(sx, sy);
    glVertex2i(sx, sy + h);
    glVertex2i(sx + w, sy + h);
    glVertex2i(sx + w, sy);
    glEnd();

    for (int y = 0; y < mapH; y++) {
        for (int x = 0; x < mapW; x++) {
            if (map[y * mapW + x] == 0) {
                glColor3f(0.f, 0.f, 0.f);
            } else {
                glColor3f(1.f, 1.f, 1.f);
            }

            int ox = CELL_SIZE * MINIMAP_WIDTH_RATIO;
            int oy = CELL_SIZE * MINIMAP_HEIGHT_RATIO;
            int tlx = sx + x * ox;
            int tly = sy + y * oy;

            glBegin(GL_QUADS);
            glVertex2i(tlx + 1, tly + 1);
            glVertex2i(tlx + 1, tly + oy - 1);
            glVertex2i(tlx + ox - 1, tly + oy - 1);
            glVertex2i(tlx + ox - 1, tly + 1);
            glEnd();
        }
    }

    // Render player position
    int px = sx + p->Pos.x * MINIMAP_WIDTH_RATIO;
    int py = sy + p->Pos.y * MINIMAP_HEIGHT_RATIO;

    glColor3f(1.f, 0.f, 1.f);
    glPointSize(PLAYER_SIZE);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + 20 * cos(p->Angle), py - 20 * sin(p->Angle));
    glEnd();
}

void handleInput(GLFWwindow* w, Player* p) {
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
        float newX = p->Pos.x + p->Delta.x;
        float newY = p->Pos.y - p->Delta.y;

        int cellX = newX / CELL_SIZE;
        int cellY = newY / CELL_SIZE;
        if (map[cellY * mapW + cellX] == 0) {
            p->Pos.x = newX;
            p->Pos.y = newY;
        }
    }

    else if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
        float newX = p->Pos.x - p->Delta.x;
        float newY = p->Pos.y + p->Delta.y;

        int cellX = newX / CELL_SIZE;
        int cellY = newY / CELL_SIZE;
        if (map[cellY * mapW + cellX] == 0) {
            p->Pos.x = newX;
            p->Pos.y = newY;
        }
    }

    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
        p->Angle += PLAYER_ANGLE_DELTA;

        if (p->Angle >= 2 * PI) p->Angle -= 2 * PI;

        p->Delta.x = PLAYER_MOVE_DELTA * cos(p->Angle);
        p->Delta.y = PLAYER_MOVE_DELTA * sin(p->Angle);
    }

    else if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
        p->Angle -= PLAYER_ANGLE_DELTA;

        if (p->Angle < 0) p->Angle += 2 * PI;

        p->Delta.x = PLAYER_MOVE_DELTA * cos(p->Angle);
        p->Delta.y = PLAYER_MOVE_DELTA * sin(p->Angle);
    }
}