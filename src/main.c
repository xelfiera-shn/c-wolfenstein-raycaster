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
    player.Pos.y = 700.f;
    player.Angle = PI / 2.f;

    while (!glfwWindowShouldClose(window)) {
        clearDisplay();
        
        renderView(&player);
        renderMinimap(&player);
        
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
    int pCellX = p->Pos.x / CELL_SIZE;
    int pCellY = p->Pos.y / CELL_SIZE;
    float da = PLAYER_VIEW_ANGLE / DISPLAY_WIDTH;

    float ra = p->Angle + PLAYER_VIEW_ANGLE / 2.0;

    for (int i = 0; i < DISPLAY_WIDTH; i++) {
        if (ra < 0) ra += 2 * PI;
        else if (ra >= 2 * PI) ra -= 2 * PI;

        int dv, dh, ov, oh;
        if (ra < PI) {
            dh = -1;
            oh = -1;
        } else {
            dh = 1;
            oh = CELL_SIZE;
        }

        if (ra > PI / 2 && ra < 3 * PI / 2) {
            dv = -1;
            ov = -1;
        } else {
            dv = 1;
            ov = CELL_SIZE;
        }

        float rTan = tan(ra);

        // Calculate horizontal hits
        float distH = 100000;
        int hx = p->Pos.x;
        int hy = p->Pos.y;
        if (ra != 0 && ra != PI) {
            for (int h = 0; h < mapH; h++) {
                hy = (pCellY + h * dh) * CELL_SIZE + oh;
                hx = ((p->Pos.y - hy) / rTan) + p->Pos.x;

                int cx = hx / CELL_SIZE;
                int cy = hy / CELL_SIZE;
                if (cx < 0 || cx >= mapW || cy < 0 || cy >= mapH) break;

                if (map[cy * mapW + cx] > 0) {
                    distH = sqrt((p->Pos.x - hx) * (p->Pos.x - hx) + (p->Pos.y - hy) * (p->Pos.y - hy));
                    break;
                }
            }
        }

        // Calculate vertical hits
        float distV = 100000;
        int vx = p->Pos.x;
        int vy = p->Pos.y;
        if (ra != PI / 2 && ra != 3 * PI / 2) {
            for (int v = 0; v < mapW; v++) {
                vx = (pCellX + v * dv) * CELL_SIZE + ov;
                vy = ((p->Pos.x - vx) * rTan) + p->Pos.y;

                int cx = vx / CELL_SIZE;
                int cy = vy / CELL_SIZE;
                if (cx < 0 || cx >= mapW || cy < 0 || cy >= mapH) break;

                if (map[cy * mapW + cx] > 0) {
                    distV = sqrt((p->Pos.x - vx) * (p->Pos.x - vx) + (p->Pos.y - vy) * (p->Pos.y - vy));
                    break;
                }
            }
        }

        // Compute valid ray
        int rx, ry, rl;
        if (distH < distV) {
            rx = hx; ry = hy; rl = distH;
        } else {
            rx = vx; ry = vy; rl = distV;
        }

        float ca = p->Angle - ra;
        if (ca < 0) ca += 2 * PI;
        else if (ca >= 2 * PI) ca -= 2 * PI;
        rl = rl * cos(ca);

        if (rl < 1) rl = 1;
        int lh = DISPLAY_HEIGHT * CELL_SIZE / rl;
        if (lh > DISPLAY_HEIGHT) lh = DISPLAY_HEIGHT;

        int sx = i;
        int sy = (DISPLAY_HEIGHT - lh) / 2;

        glColor3f(0.f, 1.f, 1.f);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(sx, 0);
        glVertex2i(sx, sy);
        glColor3f(0.f, 1.f, 0.f);
        glVertex2i(sx, sy);
        glVertex2i(sx, sy + lh);
        glEnd();

        // // DEBUG BEGIN
        // int px = DISPLAY_WIDTH + MINIMAP_WIDTH_RATIO * (p->Pos.x - DISPLAY_WIDTH);
        // int py = DISPLAY_HEIGHT + MINIMAP_HEIGHT_RATIO * (p->Pos.y - DISPLAY_HEIGHT);
        // int rrx = DISPLAY_WIDTH + MINIMAP_WIDTH_RATIO * (rx - DISPLAY_WIDTH);
        // int rry = DISPLAY_HEIGHT + MINIMAP_HEIGHT_RATIO * (ry - DISPLAY_HEIGHT);
        // glColor3f(1.f, 0.f, 0.f);
        // glLineWidth(1);
        // glBegin(GL_LINES);
        // glVertex2i(px, py);
        // glVertex2i(rrx, rry);
        // glEnd();
        // // DEBUG END

        ra -= da;
    }
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

    else if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
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