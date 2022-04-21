#include <BoxShape.h>
#include <World.h>

#include <GL/glut.h>

#include <chrono>
#include <thread>

using namespace utad;

static World world;

void DisplayCallback()
{
    world.Simulate(0.01f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.Draw();

    glutSwapBuffers();
}

void SetupView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 1.333f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 7.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void SetupWorld()
{
    for (int i = -5; i <= 5; ++i) {
        for (int j = -5; j <= 5; ++j) {
            Vector3f halfSize = Vector3f(0.2, 0.4, 0.05);
            Shape *shape = makeBox(halfSize);
            RigidBody *rb = new RigidBody(shape);
            rb->m_Position = Vector3f(i, 0, j);
            rb->m_Color = Vector3f(0.5 + 0.1 * i, 0, 1);
            Vector3f posToApplyForce = rb->m_Position + halfSize*2;
            //posToApplyForce.x() += halfSize.x();
            //posToApplyForce.y() += halfSize.y();
            //posToApplyForce.z() += halfSize.z();
            rb->ApplyForce(Vector3f(1, 0, -1), posToApplyForce);
            world.rbs.push_back(rb);
        }
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("UTAD-SIM02-RigidBody");
    glutDisplayFunc(DisplayCallback);
    glutIdleFunc(DisplayCallback);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    SetupView();
    SetupWorld();

    glutMainLoop();

    return 0;
}