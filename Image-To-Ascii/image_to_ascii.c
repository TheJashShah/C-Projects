/*
IMAGE TO ASCII IN C, USING STBI
*/

# include <stdio.h>
# define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"

int main(){

    int width, height, comp;
    unsigned char *data = stbi_load("trial.jpg", &width, &height, &comp, 0); // 0 means to load the image as it is.

/*
in data, which is an array of characters, each character is either an R, G, or B value of a pixel.
So, the first three elements of data are the RGB values of the first pixel.
*/

    long long int size_of_data = width * height * comp;
    int pixels = (width * height);

    unsigned char **img = (unsigned char**)malloc(pixels * sizeof(unsigned char*));

    for(int i = 0; i < pixels; i++){
        img[i] = (unsigned char*)malloc(comp * sizeof(unsigned char));
    }

    for(int i = 0; i < pixels; i++){
        for(int j = 0; j < comp; j++){
            img[i][j] = data[(i * comp) + j];
        }
    }

    char characters[] = {'@', '#', '$', '%', '&'};

    char **ascii_img = (char **)malloc(height * sizeof(char *));
    for(int i = 0; i < height; i++){
        ascii_img[i] = (char *)malloc(width * sizeof(char));
    }

    if(data){

        for(int i = 0; i < pixels; i++){

            int sum = 0;
            for(int j = 0; j < comp; j++){
                sum += (int)img[i][j];
            }

            if(sum <= 30){
                    ascii_img[i / height][(i % width)] = ' ';
            }
            else if(sum <= 100){
                ascii_img[i / width][(i % width)] = characters[0];
            }
            else if(sum <= 150){
                ascii_img[i / width][(i % width)] = characters[1];
            }
            else if(sum <= 200){
                ascii_img[i / width][(i % width)] = characters[2];
            }
            else if(sum <= 250){
                ascii_img[i / width][(i % width)] = characters[3];
            }
            else{
                ascii_img[i / width][(i % width)] = characters[4];
            }
        }

        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                printf("%c", ascii_img[i][j]);
            }
            printf("\n");
        }

    }
    else {
        printf("Image could not be loaded. \n");
    }

    for(int i = 0; i < pixels; i++){
        free(img[i]);
    }

    free(img);

    stbi_image_free(data);
    return 0;
}
