// oled.c

#include <msp430.h>
#include <Defines.h>
#include <Timer.h>
#include <Oled.h>
#include <Oled_Letras.h>

////////////////////////////////////////////////////////////
///////
/////// Letras
///////
////////////////////////////////////////////////////////////

void oled_frase(char letras[], char xc, char yc, char oque){
    int i=0, delta=0;

    while (letras[i] != 0){
        if (i == 0) delta=0;
        else{
            if       (letras[i-1] == ' ')  delta+=2;
            else if ((letras[i-1] == 'I') ||
                     (letras[i-1] == '!') ||
                     (letras[i-1] == '.') ||
                     (letras[i-1] == ',') ||
                     (letras[i-1] == ':')) delta+=3;
            else if ((letras[i-1] == 'T') ||
                     (letras[i-1] == 'Y')) delta+=4;
            else if ((letras[i-1] == 'M') ||
                     (letras[i-1] == 'W') ||
                     (letras[i-1] == '*')) delta+=6;
            else                           delta+=5;
        }

        if (letras[i] != ' '){
            oled_letra(letras[i], xc+delta, yc, oque);
        }

        i++;
    }
}

void oled_frase_delay10ms(char letras[], char xc, char yc, char oque, char delay10ms){
    int i=0, delta=0;

    while (letras[i] != 0){
        if (i == 0) delta=0;
        else{
            if       (letras[i-1] == ' ')  delta+=2;
            else if ((letras[i-1] == 'I') ||
                     (letras[i-1] == '!') ||
                     (letras[i-1] == '.') ||
                     (letras[i-1] == ',') ||
                     (letras[i-1] == ':')) delta+=3;
            else if ((letras[i-1] == 'T') ||
                     (letras[i-1] == 'Y')) delta+=4;
            else if ((letras[i-1] == 'M') ||
                     (letras[i-1] == 'W') ||
                     (letras[i-1] == '*')) delta+=6;
            else                           delta+=5;
        }

        if (letras[i] != ' '){
            oled_letra(letras[i], xc+delta, yc, oque);
        }

        espera_10ms(delay10ms);

        i++;
    }
}

void oled_letra(char letra, char xc, char yc, char oque){
    if (letra == 'A'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'B'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'C'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'D'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'E'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'F'){
        oled_pix(xc  ,yc,oque);

        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'G'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'H'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'I'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);

        oled_pix(xc+1,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
    }
    else if (letra == 'J'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'K'){
        oled_pix(xc,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'L'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
    }
    else if (letra == 'M'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+4,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+4,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+4,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+1,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);
        oled_pix(xc+4,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+4,yc-4,oque);
    }
    else if (letra == 'N'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+1,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'O'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'P'){
        oled_pix(xc  ,yc,oque);

        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'Q'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'R'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'S'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'T'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);

        oled_pix(xc+1,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'U'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == 'V'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'W'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);
        oled_pix(xc+4,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+4,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+4,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+4,yc-4,oque);
    }
    else if (letra == 'X'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'Y'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == 'Z'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == '.'){
        oled_pix(xc+1,yc,oque);
    }
    else if (letra == ','){
        oled_pix(xc+1,yc+1,oque);
        oled_pix(xc+1,yc  ,oque);
    }
    else if (letra == '!'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+1,yc-2,oque);

        oled_pix(xc+1,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
    }
    else if (letra == '?'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '*'){
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);
        oled_pix(xc+4,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);
        oled_pix(xc+4,yc-3,oque);

        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '='){
        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+1,yc-1,oque);
        oled_pix(xc+2,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+1,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);
    }
    else if (letra == ':'){
        oled_pix(xc  ,yc-1,oque);

        oled_pix(xc  ,yc-3,oque);
    }
    else if (letra == '1'){
        oled_pix(xc+3,yc,oque);

        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc+2,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == '2'){
        oled_pix(xc  ,yc,oque);
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);
        oled_pix(xc+3,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '3'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '4'){
        oled_pix(xc+3,yc,oque);

        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc+1,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == '5'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+1,yc-3,oque);
        oled_pix(xc+2,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == '6'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc+1,yc-3,oque);

        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '7'){
        oled_pix(xc  ,yc,oque);

        oled_pix(xc+1,yc-1,oque);

        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc  ,yc-4,oque);
        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
        oled_pix(xc+3,yc-4,oque);
    }
    else if (letra == '8'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '9'){
        oled_pix(xc+1,yc,oque);

        oled_pix(xc+2,yc-1,oque);

        oled_pix(xc+1,yc-2,oque);
        oled_pix(xc+2,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
    else if (letra == '0'){
        oled_pix(xc+1,yc,oque);
        oled_pix(xc+2,yc,oque);

        oled_pix(xc  ,yc-1,oque);
        oled_pix(xc+3,yc-1,oque);

        oled_pix(xc  ,yc-2,oque);
        oled_pix(xc+3,yc-2,oque);

        oled_pix(xc  ,yc-3,oque);
        oled_pix(xc+3,yc-3,oque);

        oled_pix(xc+1,yc-4,oque);
        oled_pix(xc+2,yc-4,oque);
    }
}
