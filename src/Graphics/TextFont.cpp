#include "TextFont.h"

void TextFont::init(){
    VAO.generate();
    VAO.bind();
        VAO["VBO"] = BufferObject(GL_ARRAY_BUFFER);
        VAO["VBO"].generate();
        VAO["VBO"].bind();
        VAO["VBO"].setData<float>(24,NULL,GL_DYNAMIC_DRAW);
        VAO["VBO"].setVertexAttribPointer<float>(0,4,GL_FLOAT,4,0);
        VAO["VBO"].unbind();
    VAO.unbind();
}

void TextFont::loadFont(std::string font,unsigned int fontSize){
    cleanCharacters();

    FT_Library ft;
    if(FT_Init_FreeType(&ft)){
        std::cout<<"ERROR: No se pudo iniciar la libreria FreeType\n";
        return;
    }

    FT_Face face;
    if(FT_New_Face(ft,font.c_str(),0,&face)){
        std::cout<<"ERROR: No se pudo cargar la fuente\n";
        return;
    }

    FT_Set_Pixel_Sizes(face,0,fontSize); 

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    for (GLubyte c = 0; c < 128; c++){

        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR: No se pudo cargar el caracter:"<<c<<"\n";
            continue;
        }
        
        Texture2D texture;
        texture.generate();
        texture.loadData(face->glyph->bitmap.width,face->glyph->bitmap.rows,face->glyph->bitmap.buffer);
        
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextFont::renderText(std::string text,glm::vec2 pos,float scale,Shader shader,glm::vec4 color){
    shader.activate();

    shader.setFloat4("textColor",color);

    glActiveTexture(GL_TEXTURE0);

    VAO.bind();

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++){
        Character ch = characters[*c];

        float xpos = pos.x + ch.bearing.x * scale;
        float ypos = pos.y + (characters['H'].bearing.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[] = {
            xpos,     ypos + h,   0.0f, 1.0f ,
            xpos + w, ypos,       1.0f, 0.0f ,
            xpos,     ypos,       0.0f, 0.0f ,

            xpos,     ypos + h,   0.0f, 1.0f ,
            xpos + w, ypos + h,   1.0f, 1.0f ,
            xpos + w, ypos,       1.0f, 0.0f 
        };
        
        ch.texture.bind();

        //Actualiza los datos en el VBO
        VAO["VBO"].bind();
        VAO["VBO"].setSubData<float>(24,0,vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph
        pos.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextFont::cleanup(){
    cleanCharacters();
    VAO.cleanup();
}

void TextFont::cleanCharacters(){
    for(auto& pair: characters){
        pair.second.texture.cleanup();
    }
    characters.clear();
}