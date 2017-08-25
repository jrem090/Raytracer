#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"
#include <QImage>

class image_texture : public texture
{
public:
    image_texture() {}
    image_texture(QString filename)
    {
        image = QImage(filename);
        nx = image.width();
        ny = image.height();
    }
    virtual vec3 value(float u, float v, const vec3 &p) const;
    QImage image;

    int nx, ny;
};

vec3 image_texture::value(float u, float v, const vec3 &p) const
{
    Q_UNUSED(p);

    //get_sphere_uv(p,u,v);

    int i = (u)*(float)nx;
    int j = (1-v)*(float)ny-.001;

    std::cout << "wh: " << nx << ", " << ny << "  ";

    if(i < 0) i = 0;
    if(j < 0) j = 0;
    if(i > nx-1) i = nx-1;
    if(j > ny-1) j = ny-1;

//    float r = int(data[3*i + 3*nx*j]  ) / 255.0;
//    float g = int(data[3*i + 3*nx*j+1]) / 255.0;
//    float b = int(data[3*i + 3*nx*j+2]) / 255.0;
    float r,g,b;

    r = image.pixelColor(i,j).red()   / 255.0;
    g = image.pixelColor(i,j).green() / 255.0;
    b = image.pixelColor(i,j).blue()  / 255.0;

    std::cout << "rgb: " << r << " " << g << " " << b << std::endl;

    return vec3(r,g,b);
}



#endif // IMAGE_TEXTURE_H
