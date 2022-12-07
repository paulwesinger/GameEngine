
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "meshobject.h"
#include "../logs/logs.h"
#include "../utils/utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


CMeshObject::CMeshObject()
    :BaseObject(){
    init();
}
CMeshObject::CMeshObject(std::string filename)
    :BaseObject() {
    init();
}

CMeshObject::~CMeshObject() {
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}

void CMeshObject::init() {
    _Filename = "";
    meshLoaded = false;

    _CountTextures = 0;
    _Color = vec4(1.0f,1.0f,1.0f,1.0f);
}

void CMeshObject::initOBJMesh(){

}


void CMeshObject::storeInVertexArray(std::vector<GLfloat> &arrayvar, VECTOR v, VECTOR n, TEXTURECOORDS t) {

    arrayvar.push_back(v.x);
    arrayvar.push_back(v.y);
    arrayvar.push_back(v.z);

    // NormVektor
    arrayvar.push_back(n.x);
    arrayvar.push_back(n.y);
    arrayvar.push_back(n.z);

    // Textures
    arrayvar.push_back(t.u);  // oder v ?
    arrayvar.push_back(t.v);

}

void CMeshObject::Draw(Camera *cam, GLuint shaderprog){

    glUseProgram( shaderprog);
   // glEnable(GL_CULL_FACE);
   // glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);


    // Locate uniforms in shader
    mv_location = glGetUniformLocation(currentShader, "mv_matrix");
    int projectionloc = glGetUniformLocation(currentShader,"projection");
    int viewloc = glGetUniformLocation(currentShader,"view");

    color_location = glGetUniformLocation(currentShader,"triangleColor");
    ortho_location = glGetUniformLocation(currentShader,"orthomatrix");

    // Model  Lightning
    int modellocation = glGetUniformLocation(currentShader,"model");
    int lightlocation = glGetUniformLocation(currentShader,"lightpos");
    int lightcolorlocation = glGetUniformLocation(currentShader,"lightcolor");


    glUniform4f(color_location,_Color.r,_Color.g, _Color.b, _Color.a);
    //Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model= glm::mat4(1.0f);

    if (  GetFirstTranslate() ) {

        Model = glm::translate(Model,GetTranslate());
        //printf ( "Cube::Draw glm::translate :  %f, %f ,%f \n",GetTranslate().x,GetTranslate().y,GetTranslate().z);
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));
    }
    else {
        Model = glm::rotate(Model, radians(GetRotate().x),vec3(1.0,0.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().y),vec3(0.0,1.0,0.0));
        Model = glm::rotate(Model, radians(GetRotate().z),vec3(0.0,0.0,1.0));

        Model = glm::translate(Model,GetTranslate());
    }
    if (_IsOrtho) {
        glm::mat4 view = glm::lookAt(vec3(0.0f,0.0f,0.1f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp =  GetProjection() * view * Model;
        glUniformMatrix4fv(ortho_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }
    else {
       glm::mat4 mvp =  GetProjection() * cam ->GetView() *  Model;
       glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mvp));
    }

    // -----------------------------------------
    // Lightning
    // -----------------------------------------
    glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(Model));

    if ( _Light != nullptr) {
        glm::vec3 c =   _Light->getColor();
        glm::vec3 p =   _Light->getPos();
        glUniform3f(lightlocation,p.x,p.y,p.z);
        glUniform3f(lightcolorlocation,c.x,c.y,c.z);
    }
    else {
        glm::vec3 lightpos = vec3(-10.0,2.0,-5.0);
        glm::vec3 lightcolor = glm::vec3( 0.0,1.0,0.0);
        glUniform3f(lightlocation,lightpos.x,lightpos.y,lightpos.z);
        glUniform3f(lightcolorlocation,lightcolor.x,lightcolor.y,lightcolor.z);
    }


    glUniformMatrix4fv(projectionloc,1,GL_FALSE,glm::value_ptr(GetProjection()));
    glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam->GetView()));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_Textures[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _Textures[0]);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glDrawElements( GL_TRIANGLES, sizeof(meshIndexes), GL_UNSIGNED_SHORT, 0);//GL_TRIANGLES

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);

}



















