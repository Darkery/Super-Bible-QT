#ifndef GLWIDGET_H
#define GLWIDGET_H


//#include <GL/glew.h>
#include <GLTools/include/GLTools.h>   // OpenGL toolkit
#include <GLTools/include/GLFrame.h>
#include <GLTools/include/GLShaderManager.h>
#include <GLTools/include/GLFrustum.h>
#include <GLTools/include/GLMatrixStack.h>
#include <GLTools/include/GLGeometryTransform.h>
#include <GLTools/include/StopWatch.h>

#include <ImfRgbaFile.h>            // OpenEXR headers
#include <ImfArray.h>
#include <QGLWidget>
#include <QTime>

class GLWidget : public QGLWidget {

    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
protected:
    void paintGL ();
    void resizeGL(int w, int h);
    void initializeGL ();
    void keyPressEvent(QKeyEvent *e);
private:

    GLsizei  screenWidth;        // Desired window or desktop width
    GLsizei  screenHeight;       // Desired window or desktop height

    GLboolean bFullScreen;       // Request to run full screen
    GLboolean bAnimated;         // Request for continual updates

    GLMatrixStack       modelViewMatrix;      // Modelview Matrix
    GLMatrixStack       projectionMatrix;     // Projection Matrix
    GLFrustum           viewFrustum;          // View Frustum
    GLGeometryTransform transformPipeline;    // Geometry Transform Pipeline
    GLFrame             cameraFrame;          // Camera frame
    GLBatch             screenQuad;
    M3DMatrix44f        orthoMatrix;

    GLBatch             floorBatch;
    GLBatch             windowBatch;
    GLBatch             windowBorderBatch;
    GLBatch             windowGridBatch;

    GLuint              flatColorProg;
    GLuint              texReplaceProg;
    GLuint              hdrBloomProg;
    GLuint              blurProg;

    GLuint              hdrFBO[1];
    GLuint              brightPassFBO[4];
    GLuint              textures[1];
    GLuint              hdrTextures[1];
    GLuint              brightBlurTextures[5];
    GLuint              windowTexture;
    GLfloat             exposure;
    GLfloat             bloomLevel;
    GLfloat             texCoordOffsets[5*5*2];

    void UpdateMode(void);
    void GenerateOrtho2DMat(GLuint imageWidth, GLuint imageHeight);
    bool LoadBMPTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
    bool LoadOpenEXRImage(char *fileName, GLint textureName, GLuint &texWidth, GLuint &texHeight);
    void GenTexCoordOffsets(GLuint width, GLuint height);
    void SetupTexReplaceProg(GLfloat *vLightPos, GLfloat *vColor);
    void SetupFlatColorProg(GLfloat *vLightPos, GLfloat *vColor);
    void SetupHDRProg();
    void SetupBlurProg();


};
#endif
