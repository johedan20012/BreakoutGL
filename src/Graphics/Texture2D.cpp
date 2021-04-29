#include "Texture2D.h"

Texture2D::Texture2D(){}

void Texture2D::generate(){
    glGenTextures(1,&textureId);
}

void Texture2D::loadFile(const char* filename,bool flip){
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);

    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    GLenum colorMode = GL_RGB;
	switch (nrChannels) {
		case 1:
			colorMode = GL_RED;
			break;
        case 3:
            colorMode = GL_RGB;
            break;
		case 4:
			colorMode = GL_RGBA;
            break;
	}

    glBindTexture(GL_TEXTURE_2D,textureId);

    //Especifica la forma en que se trata una coordenada de textura fuera del rango [0,1] por eje, en este caso es para una textura 2D
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT); 

    //Especifica el filtro de textura, para "min" cuando se "reduce" la textura y "mag" al contrario
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //?Los 4 comandos de arriba solo afectan a la textura "actual"

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);//Genera el mipmap para la textura actual, que es "texture"
    }
    else{
        std::cout << "No se pudo cargar la textura\n"<<filename<<"\n";
    }
    stbi_image_free(data); //Libera los datos de la imagen, ya que ahora estan en la GPU
}

void Texture2D::loadData(int width,int height,void* data){
    glBindTexture(GL_TEXTURE_2D,textureId);

    //Especifica la forma en que se trata una coordenada de textura fuera del rango [0,1] por eje, en este caso es para una textura 2D
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE); 

    //Especifica el filtro de textura, para "min" cuando se "reduce" la textura y "mag" al contrario
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
}

void Texture2D::bind(){
    glBindTexture(GL_TEXTURE_2D,textureId);
}

void Texture2D::cleanup(){
    glDeleteTextures(1,&textureId);
}