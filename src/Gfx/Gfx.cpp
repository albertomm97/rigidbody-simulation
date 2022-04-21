#include "Gfx.h"

#include <GL/glut.h>

namespace utad
{
namespace Gfx
{
void clear(Vector3f c)
{
    glClearColor(c[0], c[1], c[2], 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void setColor(Vector3f c)
{
    glColor3f(c[0], c[1], c[2]);
}

void setPointSize(float s)
{
    glPointSize(s);
}

void drawPoint(Vector3f x)
{
    glBegin(GL_POINTS);
    glVertex3f(x[0], x[1], x[2]);
    glEnd();
}

void setLineWidth(float w)
{
    glLineWidth(w);
}

void drawLine(Vector3f x0, Vector3f x1)
{
    glBegin(GL_LINES);
    glVertex3f(x0[0], x0[1], x0[2]);
    glVertex3f(x1[0], x1[1], x1[2]);
    glEnd();
}

void drawTri(Vector3f x0, Vector3f x1, Vector3f x2)
{
    Vector3f n = (x1 - x0).cross(x2 - x0).normalized();
    glBegin(GL_TRIANGLES);
    glNormal3f(n[0], n[1], n[2]);
    glVertex3f(x0[0], x0[1], x0[2]);
    glVertex3f(x1[0], x1[1], x1[2]);
    glVertex3f(x2[0], x2[1], x2[2]);
    glEnd();
}

void drawTri(Vector3f x0, Vector3f x1, Vector3f x2, Vector3f n0, Vector3f n1, Vector3f n2)
{
    glBegin(GL_TRIANGLES);
    glNormal3f(n0[0], n0[1], n0[2]);
    glVertex3f(x0[0], x0[1], x0[2]);
    glNormal3f(n1[0], n1[1], n1[2]);
    glVertex3f(x1[0], x1[1], x1[2]);
    glNormal3f(n2[0], n2[1], n2[2]);
    glVertex3f(x2[0], x2[1], x2[2]);
    glEnd();
}

void drawQuad(Vector3f x0, Vector3f x1, Vector3f x2, Vector3f x3)
{
    Vector3f n = ((x1 - x0).cross(x2 - x0) + (x2 - x0).cross(x3 - x0)).normalized();
    glBegin(GL_QUADS);
    glNormal3f(n[0], n[1], n[2]);
    glVertex3f(x0[0], x0[1], x0[2]);
    glVertex3f(x1[0], x1[1], x1[2]);
    glVertex3f(x2[0], x2[1], x2[2]);
    glVertex3f(x3[0], x3[1], x3[2]);
    glEnd();
}

void drawQuad(Vector3f x0, Vector3f x1, Vector3f x2, Vector3f x3, Vector3f n0, Vector3f n1, Vector3f n2, Vector3f n3)
{
    glBegin(GL_QUADS);
    glNormal3f(n0[0], n0[1], n0[2]);
    glVertex3f(x0[0], x0[1], x0[2]);
    glNormal3f(n1[0], n1[1], n1[2]);
    glVertex3f(x1[0], x1[1], x1[2]);
    glNormal3f(n2[0], n2[1], n2[2]);
    glVertex3f(x2[0], x2[1], x2[2]);
    glNormal3f(n3[0], n3[1], n3[2]);
    glVertex3f(x3[0], x3[1], x3[2]);
    glEnd();
}

void drawArrow(Vector3f base, Vector3f vector, float thick)
{
    float vnorm = vector.norm();
    if (vnorm == 0)
        return;
    glPushMatrix();
    glTranslatef(base[0], base[1], base[2]);
    Vector3f vhat = vector / vnorm;
    Vector3f w = Vector3f(0, 0, 1).cross(vhat);
    float angle = acos(vhat[2]);
    if (w.norm() > 0) {
        glRotatef(angle * 180 / M_PI, w[0], w[1], w[2]);
    } else {
        glRotatef(angle * 180 / M_PI, 1, 0, 0);
    }
    GLUquadric *quadric = gluNewQuadric();
    gluCylinder(quadric, 0, thick / 3, 0, 30, 1);
    gluCylinder(quadric, thick / 3, thick / 3, vnorm - 3 * thick, 30, 1);
    glTranslatef(0, 0, vnorm - 3 * thick);
    gluCylinder(quadric, thick / 3, thick, 0, 30, 1);
    gluCylinder(quadric, thick, 0, 3 * thick, 30, 1);
    gluDeleteQuadric(quadric);
    glPopMatrix();
}

void drawAxes()
{
    setColor(Vector3f(0.8, 0.2, 0.2));
    drawArrow(Vector3f(0, 0, 0), Vector3f(1, 0, 0), 0.05);
    setColor(Vector3f(0.2, 0.6, 0.2));
    drawArrow(Vector3f(0, 0, 0), Vector3f(0, 1, 0), 0.05);
    setColor(Vector3f(0.2, 0.2, 0.8));
    drawArrow(Vector3f(0, 0, 0), Vector3f(0, 0, 1), 0.05);
}

void drawBox(Vector3f xmin, Vector3f xmax, bool drawSurf, bool drawWire)
{
    float x0 = xmin[0], x1 = xmax[0];
    float y0 = xmin[1], y1 = xmax[1];
    float z0 = xmin[2], z1 = xmax[2];
    if (drawSurf) {
        if (drawWire) {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1, 1);
        }
        drawQuad(Vector3f(x0, y0, z0), Vector3f(x0, y1, z0), Vector3f(x0, y1, z1), Vector3f(x0, y0, z1));
        drawQuad(Vector3f(x1, y0, z0), Vector3f(x1, y1, z0), Vector3f(x1, y1, z1), Vector3f(x1, y0, z1));
        drawQuad(Vector3f(x0, y0, z0), Vector3f(x0, y0, z1), Vector3f(x1, y0, z1), Vector3f(x1, y0, z0));
        drawQuad(Vector3f(x0, y1, z0), Vector3f(x0, y1, z1), Vector3f(x1, y1, z1), Vector3f(x1, y1, z0));
        drawQuad(Vector3f(x0, y0, z0), Vector3f(x1, y0, z0), Vector3f(x1, y1, z0), Vector3f(x0, y1, z0));
        drawQuad(Vector3f(x0, y0, z1), Vector3f(x1, y0, z1), Vector3f(x1, y1, z1), Vector3f(x0, y1, z1));
        if (drawWire)
            glDisable(GL_POLYGON_OFFSET_FILL);
    }
    if (drawWire) {
        if (drawSurf) {
            glPushAttrib(GL_CURRENT_BIT);
            setColor(Vector3f(0, 0, 0));
        }
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        drawLine(Vector3f(x0, y0, z0), Vector3f(x1, y0, z0));
        drawLine(Vector3f(x0, y1, z0), Vector3f(x1, y1, z0));
        drawLine(Vector3f(x0, y0, z1), Vector3f(x1, y0, z1));
        drawLine(Vector3f(x0, y1, z1), Vector3f(x1, y1, z1));
        drawLine(Vector3f(x0, y0, z0), Vector3f(x0, y1, z0));
        drawLine(Vector3f(x1, y0, z0), Vector3f(x1, y1, z0));
        drawLine(Vector3f(x0, y0, z1), Vector3f(x0, y1, z1));
        drawLine(Vector3f(x1, y0, z1), Vector3f(x1, y1, z1));
        drawLine(Vector3f(x0, y0, z0), Vector3f(x0, y0, z1));
        drawLine(Vector3f(x1, y0, z0), Vector3f(x1, y0, z1));
        drawLine(Vector3f(x0, y1, z0), Vector3f(x0, y1, z1));
        drawLine(Vector3f(x1, y1, z0), Vector3f(x1, y1, z1));
        glPopAttrib();
        if (drawSurf)
            glPopAttrib();
    }
}

void drawCircle(Vector3f center, Vector3f axis0, Vector3f axis1)
{
    int n = 60;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        Vector3f x = center + axis0 * cos(2 * M_PI * i / n) + axis1 * sin(2 * M_PI * i / n);
        glVertex3f(x[0], x[1], x[2]);
    }
    glEnd();
}

void drawSphere(Vector3f center, float radius, bool drawSurf, bool drawWire)
{
    glPushMatrix();
    glTranslatef(center[0], center[1], center[2]);
    if (drawSurf) {
        if (drawWire) {
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1, 1);
        }
        GLUquadric *quadric = gluNewQuadric();
        gluSphere(quadric, radius, 30, 30);
        gluDeleteQuadric(quadric);
        if (drawWire)
            glDisable(GL_POLYGON_OFFSET_FILL);
    }
    if (drawWire) {
        if (drawSurf) {
            glPushAttrib(GL_CURRENT_BIT);
            setColor(Vector3f(0, 0, 0));
        }
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        drawCircle(Vector3f(0, 0, 0), radius * Vector3f(1, 0, 0), radius * Vector3f(0, 1, 0));
        drawCircle(Vector3f(0, 0, 0), radius * Vector3f(0, 1, 0), radius * Vector3f(0, 0, 1));
        drawCircle(Vector3f(0, 0, 0), radius * Vector3f(0, 0, 1), radius * Vector3f(1, 0, 0));
        glPopAttrib();
        if (drawSurf)
            glPopAttrib();
    }
    glPopMatrix();
}

void translate(Vector3f x)
{
    glTranslatef(x[0], x[1], x[2]);
}

void rotate(Quaternionf q)
{
    Eigen::AngleAxis<float> aa(q);
    Vector3f a = aa.axis();
    glRotatef(aa.angle() * 180 / M_PI, a[0], a[1], a[2]);
}

void pushTransform()
{
    glPushMatrix();
}

void popTransform()
{
    glPopMatrix();
}
}  // namespace Gfx
}  // namespace utad
