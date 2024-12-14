#define WIDTH 640
#define HEIGHT 480

float zbuffer[WIDTH * HEIGHT];

void init_zbuffer() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        zbuffer[i] = INFINITY;
    }
}

void putpixel(int x, int y, float z, Color color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return; 
    }

    int index = y * WIDTH + x;
    if (z < zbuffer[index]) {
        zbuffer[index] = z;
        framebuffer[index] = color;
    }
}

void draw_triangle(Vec3 v0, Vec3 v1, Vec3 v2, Color color) {

    Vec2 p0 = project(v0);
    Vec2 p1 = project(v1);
    Vec2 p2 = project(v2);
    int minX = fmin(fmin(p0.x, p1.x), p2.x);
    int maxX = fmax(fmax(p0.x, p1.x), p2.x);
    int minY = fmin(fmin(p0.y, p1.y), p2.y);
    int maxY = fmax(fmax(p0.y, p1.y), p2.y);


    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            Vec3 barycentric = barycentric_coordinates(x, y, p0, p1, p2);
            if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0) {
                float z = barycentric.x * v0.z + barycentric.y * v1.z + barycentric.z * v2.z;
                putpixel(x, y, z, color);
            }
        }
    }
}

Vec2 project(Vec3 v) {

    float fov = 90.0f;
    float aspect = (float)WIDTH / HEIGHT;
    float znear = 0.1f;
    float zfar = 100.0f;

    float f = 1.0f / tan(fov * 0.5f * M_PI / 180.0f);
    float x = v.x * f / aspect;
    float y = v.y * f;

    x = (x + 1.0f) * WIDTH * 0.5f;
    y = (1.0f - y) * HEIGHT * 0.5f;

    return (Vec2){x, y};
}


int main() {
    init_zbuffer();

    //Figure out 3d scene implementation, idk

}
