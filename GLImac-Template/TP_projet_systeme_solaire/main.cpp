#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
     Sphere sphere(1, 32, 16);

     GLuint vbo;
     // création du vertex buffer object (1 VBO créé, dont l'ID est stocké dans vbo)
     glGenBuffers(1, &vbo); 

     // binding du vbo sur la cible GL_ARRAY_BUFFER (permet de modifier le contenu du VBO)
     glBindBuffer(GL_ARRAY_BUFFER, vbo);

     // création des sommets
     int sphere_vertex_count = sphere.getVertexCount();
     const ShapeVertex* vertices = sphere.getDataPointer();

     //envoi des coordonnées au buffer
     glBufferData(GL_ARRAY_BUFFER,  sphere_vertex_count * sizeof(ShapeVertex), vertices, GL_STATIC_DRAW);

     // Unbinding du vbo sur la cible GL_ARRAY_BUFFER
     glBindBuffer(GL_ARRAY_BUFFER, 0);


     GLuint vao;
    // création du vertex array object (1 VAO créé, dont l'ID est stocké dans vao)
     glGenVertexArrays(1, &vao);
     // binding du vao (il n'y a pas de cible à spécifier car une seule cible existe)
     glBindVertexArray(vao);

     // utilisation de l'attribut 0 du vao (la position par défaut)
     const GLuint VERTEX_ATTR_POSITION = 0;
     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

     // Binding du vbo créé (pour l'utiliser dans le prochain appel à glVertexAttribPointer)
     glBindBuffer(GL_ARRAY_BUFFER, vbo);

     //ajout d'informations liées à la lecture des différents sommets
     glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (GLvoid*) offsetof(ShapeVertex, position));

     //Unbinding du vbo
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     //Unbinding du vao
     glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

	 //effaçage du rendu précédent
         glClear(GL_COLOR_BUFFER_BIT);

         //Binding du vao
         glBindVertexArray(vao);

         //Affichage du triangle
         glDrawArrays(GL_TRIANGLES, 0, sphere_vertex_count); // type de primitive, indice du premier sommet (vbo), nombre de sommets à dessiner

         //Unbinding du vao
         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
