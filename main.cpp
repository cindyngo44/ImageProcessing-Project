#include <iostream>
#include "Header.h"
    //Multiplies the standardized (based on the domain 0...1) tonal values of the fore- and background's pixels. The effect can be compared to two
    // slides put on top of each other and projected together. The light, forced to pass through each of the slides, is weakened twice.
void multiply(Header &top, Header &bottom, Header &task1Final){
    task1Final = top;
    //pixel range 0-255
    int imgDimensions = top.width * top.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    float redf;
    float greenf;
    float bluef;

    //convert to 0-1, calculate, revert back
    //C = A*B
    task1Final.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++){
        redf = ((float)top.pixelVector[i].red) * ((float)bottom.pixelVector[i].red);
        greenf = ((float)top.pixelVector[i].green) * ((float)bottom.pixelVector[i].green);
        bluef = ((float)top.pixelVector[i].blue) * ((float)bottom.pixelVector[i].blue);

        red = (unsigned char) ((redf / 255.0f) + 0.5f);
        green = (unsigned char) ((greenf / 255.0f) + 0.5f);
        blue = (unsigned char) ((bluef / 255.0f) + 0.5f);

        Header::Pixels pixel(red, green, blue);
        task1Final.pixelVector.push_back(pixel);
    }
}
    //b2 = source 1
    //c = b1 - b2
    //also account for mins
    //subtract source 1 from source 2
    //subtracts top layer from bottom layer
    //b1 = bot b2 = top
void subtract(Header top, Header bottom, Header &task2Final){
        task2Final = top;
        int imgDimensions = top.width * top.height;

        unsigned char red;
        unsigned char green;
        unsigned char blue;

        task2Final.pixelVector.clear();
        for (int i = 0; i < imgDimensions; i++) {
            float redf = ((float) bottom.pixelVector[i].red) - ((float) top.pixelVector[i].red);
            if(redf < 0.0f){
                redf = 0;
            }

            float greenf = ((float) bottom.pixelVector[i].green) - ((float) top.pixelVector[i].green);
            if(greenf < 0.0f){
                greenf = 0;
            }

            float bluef = ((float) bottom.pixelVector[i].blue) - ((float) top.pixelVector[i].blue);
            if(bluef < 0.0f){
                bluef = 0;
            }

            red = (unsigned char) (redf + 0.5f);
            green = (unsigned char) (greenf + 0.5f);
            blue = (unsigned char) (bluef + 0.5f);

            Header::Pixels pixel(red, green, blue);
            task2Final.pixelVector.push_back(pixel);
        }
}
void screen(Header top, Header bottom, Header &task3Final){
    //The opposite of the previous mode. Fore- and background are »negatively multiplied« and lighten each other
    // (as if two slides are projected with different projectors onto the same screen). The correlation with the Multiply mode becomes clear
    // if the formula is written as in the second row in the formula box to the right. I.e. if you blend the negatives of the two images with
    // Multiply, you will get the negative of the result you would get with Screen.
    //C = 1 - (1 - A) * (1 - B)
    task3Final = top;
    //pixel range 0-255
    int imgDimensions = top.width * top.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    float redf;
    float greenf;
    float bluef;

    //convert to 0-1, calculate, revert back
    //normalize
    //C = A*B
    task3Final.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++){
        redf = 1 - (1 - ((float)top.pixelVector[i].red / 255)) * (1 - ((float)bottom.pixelVector[i].red / 255));
        greenf = 1 - (1 - ((float)top.pixelVector[i].green / 255)) * (1 - ((float)bottom.pixelVector[i].green / 255));
        bluef = 1 - (1 - ((float)top.pixelVector[i].blue / 255)) * (1 - ((float)bottom.pixelVector[i].blue / 255));

        red = (unsigned char) ((redf * 255) + 0.5f);
        green = (unsigned char) ((greenf * 255) + 0.5f);
        blue = (unsigned char) ((bluef * 255) + 0.5f);

        Header::Pixels pixel(red, green, blue);
        task3Final.pixelVector.push_back(pixel);
    }

}
void overlay(Header top, Header bottom, Header &task5Final){
    //If the background is darker than 50% gray, the tonal values get multiplied
    // B <= 0.5 C = 2*A*B
    //B > 0.5 C= 1-2*(1-A) * (1-B)
    //B = Background = bot
    task5Final = top;
    //pixel range 0-255
    int imgDimensions = top.width * top.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    float redf;
    float greenf;
    float bluef;

    task5Final.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        float redA = (float)top.pixelVector[i].red / 255;
        float greenA = (float)top.pixelVector[i].green / 255;
        float blueA = (float)top.pixelVector[i].blue / 255;

        float redB = (float)bottom.pixelVector[i].red / 255;
        float greenB = (float)bottom.pixelVector[i].green / 255;
        float blueB = (float)bottom.pixelVector[i].blue / 255;
        //red
        if (redB <= 0.5f){
            redf = 2 * redA * redB;
        }
        else if (redB > 0.5f){
            redf = 1 - (2 * (1 - redA) * (1 - redB));
        }
        //green
        if (greenB <= 0.5f){
            greenf = 2 * greenA * greenB;
        }
        else if (greenB > 0.5f){
            greenf = 1 - (2 * (1 - greenA) * (1 - greenB));
        }
        //blue
        if (blueB <= 0.5f){
            bluef = 2 * blueA * blueB;
        }
        else if (blueB > 0.5f){
            bluef = 1 - (2 * (1 - blueA) * (1 - blueB));
        }

        if(redf > 1.0f){
            redf = 1.0;
        }
        else if (redf < 0.0f){
            redf = 0.0f;
        }

        if(greenf > 1.0f){
            greenf = 1.0;
        }
        else if (greenf < 0.0f){
            greenf = 0.0f;
        }

        if(bluef > 1.0f){
            bluef = 1.0;
        }
        else if (bluef < 0.0f){
            bluef = 0.0f;
        }

        red = (unsigned char) ((redf * 255) + 0.5f);
        green = (unsigned char) ((greenf * 255) + 0.5f);
        blue = (unsigned char) ((bluef * 255) + 0.5f);

        Header::Pixels pixel(red, green, blue);
        task5Final.pixelVector.push_back(pixel);
    }

}
void addGreen200(Header image, Header &task6Final){
    task6Final = image;
    //pixel range 0-255
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task6Final.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        float greenf = ((float) image.pixelVector[i].green) + 200;
        if (greenf > 255){
            greenf = 255;
        }
        red = image.pixelVector[i].red;
        green = (unsigned char) (greenf);
        blue = image.pixelVector[i].blue;

        Header::Pixels pixel(red, green, blue);
        task6Final.pixelVector.push_back(pixel);
    }
}
void ScaleRedBlue(Header image, Header &task7Final){
    //Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0.
    task7Final = image;
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char blue;

    for (int i = 0; i < imgDimensions; i++) {
        float redf = ((float) image.pixelVector[i].red) * 4;
        if (redf > 255){
            redf = 255;
        }

        float bluef = ((float) image.pixelVector[i].blue) * 0;

        red = (unsigned char) redf;
        blue = (unsigned char) bluef;

        task7Final.pixelVector[i].red = red;
        task7Final.pixelVector[i].blue = blue;
    }

}
void Red(Header image, Header &task8FinalR){
    task8FinalR = image;
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task8FinalR.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        red = image.pixelVector[i].red;
        green = image.pixelVector[i].red;
        blue = image.pixelVector[i].red;

        Header::Pixels pixel(red, green, blue);
        task8FinalR.pixelVector.push_back(pixel);
    }
}
void Green(Header image, Header &task8FinalG){
    task8FinalG = image;
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task8FinalG.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        red = image.pixelVector[i].green;
        green = image.pixelVector[i].green;
        blue = image.pixelVector[i].green;

        Header::Pixels pixel(red, green, blue);
        task8FinalG.pixelVector.push_back(pixel);
    }
}
void Blue(Header image, Header &task8FinalB){
    task8FinalB = image;
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task8FinalB.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        red = image.pixelVector[i].blue;
        green = image.pixelVector[i].blue;
        blue = image.pixelVector[i].blue;

        Header::Pixels pixel(red, green, blue);
        task8FinalB.pixelVector.push_back(pixel);
    }

}
void combine(Header layer_red,Header layer_green, Header layer_blue, Header &task9Final){
    task9Final = layer_red;
    int imgDimensions = layer_red.width * layer_red.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task9Final.pixelVector.clear();
    for (int i = 0; i < imgDimensions; i++) {
        red = layer_red.pixelVector[i].red;
        green = layer_green.pixelVector[i].green;
        blue = layer_blue.pixelVector[i].blue;

        Header::Pixels pixel(red, green, blue);
        task9Final.pixelVector.push_back(pixel);
    }
}
void rotate(Header image, Header &task10Final){
    task10Final = image;
    int imgDimensions = image.width * image.height;

    unsigned char red;
    unsigned char green;
    unsigned char blue;

    task10Final.pixelVector.clear();
    for (int i = imgDimensions - 1; i >= 0 ; i--) {
        red = image.pixelVector[i].red;
        green = image.pixelVector[i].green;
        blue = image.pixelVector[i].blue;

        Header::Pixels pixel(red, green, blue);
        task10Final.pixelVector.push_back(pixel);
    }
}
//verification tests
void verify(Header image, Header example){
    int imgDimensions = image.width * image.height;

    bool match = true;
    for (int i = 0; i < imgDimensions; i++) {
        if (image.idLength != example.idLength){
            match = false;
        }
        if (image.colorMapType != example.colorMapType){
            match = false;
        }
        if (image.dataTypeCode != example.dataTypeCode){
            match = false;
        }
        if (image.colorMapOrigin != example.colorMapOrigin){
            match = false;
        }
        if (image.colorMapLength != example.colorMapLength){
            match = false;
        }
        if (image.colorMapDepth != example.colorMapDepth){
            match = false;
        }
        if( image.xOrigin != example.xOrigin){
            match = false;
        }
        if (image.yOrigin != example.yOrigin){
            match = false;
        }
        if (image.width != example.width){
            match = false;
        }
        if (image.height != example.height){
            match = false;
        }
        if (image.bitsPerPixel != example.bitsPerPixel){
            match = false;
        }
        if (image.imageDescriptor != example.imageDescriptor){
            match = false;
        }
        if (image.pixelVector[i].red != example.pixelVector[i].red){
            //cout << (float) image.pixelVector[i].red << "    " << (float) example.pixelVector[i].red << endl;
            match = false;
        }
        if (image.pixelVector[i].green != example.pixelVector[i].green) {
            //cout << (float) image.pixelVector[i].green << "    " << (float) example.pixelVector[i].green << endl;
            match = false;
        }
        if (image.pixelVector[i].blue != example.pixelVector[i].blue){
            cout << (float) image.pixelVector[i].green << "    " << (float) example.pixelVector[i].green << endl;
            match = false;
        }
    }

    if(match){
        cout << "Test passed!" << endl;
    }
    else{
        cout << "Test failed!" << endl;
    }
}
int main() {
    //task 1
    // Use the Multiply blending mode to combine “layer1.tga” (top layer) with “pattern1.tga” (bottom layer)
    Header layer1;
    Header pattern1;
    Header task1Final;

    layer1.readTGA("input/layer1.tga", layer1);
    pattern1.readTGA("input/pattern1.tga", pattern1);


    multiply(layer1 , pattern1, task1Final);
    task1Final.writeTGA("output/part1.tga", task1Final);

    Header verify1;
    verify1.readTGA("examples/EXAMPLE_part1.tga", verify1);
    verify(task1Final, verify1);

    //task 2
    // Use the Subtract blending mode to combine “layer2.tga” (top layer) with “car.tga” (bottom layer).
    // This mode subtracts the top layer from the bottom layer.
    Header layer2;
    Header car;
    Header task2Final;

    layer2.readTGA("input/layer2.tga", layer2);
    car.readTGA("input/car.tga", car);

    subtract(layer2, car, task2Final);
    task2Final.writeTGA("output/part2.tga", task2Final);

    Header verify2;
    verify2.readTGA("examples/EXAMPLE_part2.tga", verify2);
    verify(task2Final, verify2);
    //task 3
    //Use the Multiply blending mode to combine “layer1.tga” with “pattern2.tga”, and store the results temporarily.
    // Load the image “text.tga” and, using that as the top layer, combine it with the previous results of layer1/pattern2
    // using the Screen blending mode.
    Header pattern2;
    Header text;
    Header temp3;
    Header task3Final;

    pattern2.readTGA("input/pattern2.tga", pattern2);
    text.readTGA("input/text.tga", text);
    multiply(layer1, pattern2, temp3);
    screen(text, temp3, task3Final);

    task3Final.writeTGA("output/part3.tga", task3Final);

    Header verify3;
    verify3.readTGA("examples/EXAMPLE_part3.tga", verify3);
    verify(task3Final, verify3);
    //task 4
    //Multiply “layer2.tga” with “circles.tga”, and store it. Load “pattern2.tga” and, using that as the top layer,
    // combine it with the previous result using the Subtract blending mode.
    Header circles;
    Header temp4;
    Header task4Final;

    circles.readTGA("input/circles.tga", circles);

    multiply(layer2, circles, temp4);
    subtract(pattern2, temp4, task4Final);

    task4Final.writeTGA("output/part4.tga", task4Final);

    Header verify4;
    verify4.readTGA("examples/EXAMPLE_part4.tga", verify4);
    verify(task4Final, verify4);
    //task 5
    //Combine “layer1.tga” (as the top layer) with “pattern1.tga” using the Overlay blending mode.
    Header task5Final;

    overlay(layer1, pattern1, task5Final);
    //task5Final.writeTGA("output/part5.tga", task5Final);

    Header verify5;
    verify5.readTGA("examples/EXAMPLE_part5.tga", verify5);
    verify(task5Final, verify5);
    //task 6
    //Load “car.tga” and add 200 to the green channel.
    Header task6Final;

    addGreen200(car, task6Final);
    task6Final.writeTGA("output/part6.tga", task6Final);

    Header verify6;
    verify6.readTGA("examples/EXAMPLE_part6.tga", verify6);
    verify(task6Final, verify6);
    //task 7
    //Load “car.tga” and scale (multiply) the red channel by 4, and the blue channel by 0. This will
    //increase the intensity of any red in the image, while negating any blue it may have.
    Header task7Final;

    ScaleRedBlue(car, task7Final);
    task7Final.writeTGA("output/part7.tga", task7Final);

    Header verify7;
    verify7.readTGA("examples/EXAMPLE_part7.tga", verify7);
    verify(task7Final, verify7);
    //task 8
    //Load “car.tga” and write each channel to a separate file: the red channel should be
    //“part8_r.tga”, the green channel should be “part8_g.tga”, and the blue channel should be
    //“part8_b.tga”
    Header task8FinalR;
    Header task8FinalG;
    Header task8FinalB;


    Red(car, task8FinalR);
    Green(car, task8FinalG);
    Blue(car, task8FinalB);
    task8FinalR.writeTGA("output/part8_r.tga", task8FinalR);
    task8FinalG.writeTGA("output/part8_g.tga", task8FinalG);
    task8FinalB.writeTGA("output/part8_b.tga", task8FinalB);

    Header verify8R;
    verify8R.readTGA("examples/EXAMPLE_part8_r.tga", verify8R);
    verify(task8FinalR, verify8R);

    Header verify8G;
    verify8G.readTGA("examples/EXAMPLE_part8_g.tga", verify8G);
    verify(task8FinalG, verify8G);

    Header verify8B;
    verify8B.readTGA("examples/EXAMPLE_part8_b.tga", verify8B);
    verify(task8FinalB, verify8B);
    //task 9
    //Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”, and combine the three files into
    //one file. The data from “layer_red.tga” is the red channel of the new image, layer_green is
    //green, and layer_blue is blue.
    Header layer_red;
    Header layer_green;
    Header layer_blue;
    Header task9Final;

    layer_red.readTGA("input/layer_red.tga", layer_red);
    layer_green.readTGA("input/layer_green.tga", layer_green);
    layer_blue.readTGA("input/layer_blue.tga", layer_blue);
    combine(layer_red, layer_green, layer_blue, task9Final);
    task9Final.writeTGA("output/part9.tga", task9Final);

    Header verify9;
    verify9.readTGA("examples/EXAMPLE_part9.tga", verify9);
    verify(task9Final, verify9);
    //task 10
    //Load “text2.tga”, and rotate it 180 degrees, flipping it upside down. This is easier than you think!
    //Try diagramming the data of an image (such as earlier in this document).
    // What would the data look like if you flipped it? Now, how to write some code to accomplish that...?
    Header text2;
    Header task10Final;

    text2.readTGA("input/text2.tga", text2);

    rotate(text2, task10Final);
    task10Final.writeTGA("output/part10.tga", task10Final);

    Header verify10;
    verify10.readTGA("examples/EXAMPLE_part10.tga", verify10);
    verify(task10Final, verify10);
    return 0;
}
